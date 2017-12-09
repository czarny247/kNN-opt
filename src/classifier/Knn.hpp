#ifndef CLASSIFIER_KNN_HPP_
#define CLASSIFIER_KNN_HPP_

#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <map>
#include <memory>
#include <mutex>
#include <numeric>
#include <string>
#include <thread>
#include <utility>
#include <vector>

#include <boost/chrono/process_cpu_clocks.hpp>
#include <boost/optional.hpp>

#include "src/data/Iris.hpp"

template <typename DataType>
using NeighborWithDistance = typename std::pair<std::shared_ptr<DataType> , float>;

template <typename DataType>
using NeighborsWithDistances =
    typename std::vector<std::pair<std::shared_ptr<DataType>, float> >;

using LockGuard = std::lock_guard<std::mutex>;

namespace
{

template <typename DataType>
float countEuclideanDistance(const std::shared_ptr<DataType>& lhs,
    const std::shared_ptr<DataType>& rhs)
{
    auto lhsFeatures = lhs->getFeaturesAsVector();
    auto rhsFeatures = rhs->getFeaturesAsVector();

    float distance = 0.0f;

    for (unsigned int idx = 0; idx < lhsFeatures.size(); ++idx)
    {
        distance += pow((lhsFeatures.at(idx) - rhsFeatures.at(idx)), 2);
    }

    return sqrt(distance);
}

template <typename DataType>
NeighborsWithDistances<DataType> getAllNeighbors(const std::shared_ptr<DataType>& test,
    const std::vector<std::shared_ptr<DataType>>& trainSet)
{
    NeighborsWithDistances<DataType> neighborsWithDistances;

    for (auto train : trainSet)
    {
        neighborsWithDistances.push_back(std::make_pair(
            train, countEuclideanDistance(test, train)));
    }

    return neighborsWithDistances;
}

template <typename DataType>
NeighborsWithDistances<DataType> getNearestNeighbors(NeighborsWithDistances<DataType> allNeighbors,
    const unsigned int k)
{
    std::sort(allNeighbors.begin(), allNeighbors.end(),
        [](const auto& lhs, const auto& rhs)
        {
            return lhs.second < rhs.second;
        });

    return {allNeighbors.begin(), allNeighbors.begin() + (k-1)};
}

template <typename DataType>
void resetClassNameToAmountMap(const DataType& test,
    std::map<std::string, int>& classNameToAmountMap)
{
    if (classNameToAmountMap.empty())
    {
        for (const auto& possibleClass : test->possibleClasses_)
        {
            classNameToAmountMap[possibleClass] = 0;
        }
        return;
    }

    for (auto& classNameToAmount : classNameToAmountMap)
    {
        classNameToAmount.second = 0;
    }
}

template <typename DataType>
std::string chooseClassBasedOnNeighbors(const NeighborsWithDistances<DataType>& kNearestNeighbors,
    std::map<std::string, int>& classNameToAmountMap)
{
    for (const auto& kNearestNeighbor : kNearestNeighbors)
    {
        auto neighborsClassName = kNearestNeighbor.first->getClassName();
        auto classNameToAmountIt = classNameToAmountMap.find(neighborsClassName);
        if (classNameToAmountIt == classNameToAmountMap.end())
        {
            continue;
        }
        classNameToAmountIt->second += 1;
    }

    auto dominantClassNameToAmount = std::max_element(classNameToAmountMap.begin(),
        classNameToAmountMap.end(),
        [](const auto& lhs, const auto& rhs)
        {
            return lhs.second < rhs.second;
        });

    return (*dominantClassNameToAmount).first;
}

}  // namespace

namespace classifier
{

class Knn
{
public:
    template <typename DataType>
    void predict(const std::vector <std::shared_ptr<DataType>>& testSet,
        const std::vector <std::shared_ptr<DataType>>& trainSet,
        const unsigned int k, const boost::optional<unsigned int> numOfThreads)
    {
        std::map<std::string, int> classNameToAmountMap;
        int correctChoices {0};
        float allChoices = static_cast<float>(testSet.size());

        auto begin = testSet.cbegin();
        auto end = testSet.cend();

        if (!numOfThreads)
        {
            std::clock_t start = std::clock();
            makePredictions(begin, end, trainSet, k, classNameToAmountMap, correctChoices);
            accuracy_ = correctChoices / allChoices;
            measuredTime_ = (std::clock() - start) / (double)CLOCKS_PER_SEC;
            return;
        }

        std::vector<int> correctChoicesPerThread;

        for (unsigned int numOfThread = 0; numOfThread < *numOfThreads; ++numOfThread)
        {
            correctChoicesPerThread.push_back(0);
        }

        std::clock_t start = std::clock();
        for (unsigned int numOfThread = 0; numOfThread < *numOfThreads; ++numOfThread)
        {
            begin = testSet.cbegin() + numOfThread * (testSet.size() / *numOfThreads);
            end = begin + (testSet.size() / *numOfThreads);

            workingThreads_.emplace_back(
                [&, numOfThread]
                {
                    this->makePredictions(begin, end, trainSet, k, classNameToAmountMap,
                        correctChoicesPerThread[numOfThread]);
                });
        }

        for (auto& thread : workingThreads_)
        {
            thread.join();
        }

        workingThreads_.clear();

        correctChoices = std::accumulate(correctChoicesPerThread.begin(),
            correctChoicesPerThread.end(), 0);

        accuracy_ = round(correctChoices) / allChoices;
        measuredTime_ = (std::clock() - start) / (double)CLOCKS_PER_SEC;
    }

    float getAccuracy() const {return accuracy_;}
    double getMeasuredTime() const {return measuredTime_;}

private:
    template <typename DataType>
    void makePredictions(
        typename std::vector <std::shared_ptr<DataType>>::const_iterator& testBegin,
        typename std::vector <std::shared_ptr<DataType>>::const_iterator& testEnd,
        const std::vector <std::shared_ptr<DataType>>& trainSet, const unsigned int k,
        std::map<std::string, int>& classNameToAmountMap, int& correctChoices)
    {
        for (auto it = testBegin; it != testEnd; it++)
        {
            predictionMutex_.lock();
            resetClassNameToAmountMap(*it, classNameToAmountMap);
            auto kNearestNeighbors = getNearestNeighbors(getAllNeighbors(*it, trainSet), k);
            std::string dominantClassInNeighborhood = chooseClassBasedOnNeighbors(
                kNearestNeighbors, classNameToAmountMap);
            predictionMutex_.unlock();
            if (dominantClassInNeighborhood == (*it)->getClassName())
            {
                correctChoices++;
            }
        }
    }

    float accuracy_ {0.0f};
    std::mutex predictionMutex_ {};
    double measuredTime_{0};
    std::vector<std::thread> workingThreads_;
};

}  // namespace classifier
#endif  // CLASSIFIER_KNN_HPP_
