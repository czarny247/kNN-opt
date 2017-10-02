#ifndef KNN_HPP_
#define KNN_HPP_

#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "../data/Iris.hpp" // remove relative path - fix cmake

template <typename DataType>
using NeighborWithDistance = typename std::pair<DataType, float>;

template <typename DataType>
using NeighborsWithDistances = typename std::vector<std::pair<DataType, float> >;

namespace
{

template <typename DataType>
float countEuclideanDistance(const DataType& lhs, const DataType& rhs)
{
    auto lhsFeatures = lhs.getFeaturesAsVector();
    auto rhsFeatures = rhs.getFeaturesAsVector();

    float distance = 0.0f;

    for (unsigned int idx = 0; idx < lhsFeatures.size(); ++idx)
    {
        distance += pow((lhsFeatures.at(idx) - rhsFeatures.at(idx)), 2);
    }

    return sqrt(distance);
}

template <typename DataType>
NeighborsWithDistances<DataType> getAllNeighbors(const DataType& test,
    const std::vector<DataType>& trainSet)
{
    //std::cout << "in getAllNeighbors(...)" << std::endl;
    NeighborsWithDistances<DataType> neighborsWithDistances;

    for (auto& train : trainSet)
    {
        //std::cout << "train: " << train << std::endl;
        neighborsWithDistances.push_back(std::make_pair(
            train, countEuclideanDistance(test, train)));
    }

    return neighborsWithDistances;
}

template <typename DataType>
NeighborsWithDistances<DataType> getNearestNeighbors(NeighborsWithDistances<DataType> allNeighbors,
    const unsigned int k)
{
    //std::cout << "in getNearestNeighbors(...)" << std::endl;

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
    // get possible classes from data interface, not from object

    //std::cout << "in resetClassNameToAmountMap(...)" << std::endl;

    if (classNameToAmountMap.empty())
    {
        for (const auto& possibleClass : test.possibleClasses)
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
    //std::cout << "in chooseClassBasedOnNeighbors(...)" << std::endl;

    for (const auto& kNearestNeighbor : kNearestNeighbors)
    {
        auto neighborsClassName = kNearestNeighbor.first.getClassName();
        auto classNameToAmountIt = classNameToAmountMap.find(neighborsClassName);
        if (classNameToAmountIt == classNameToAmountMap.end())
        {
            // print some info that this neighbor has incorrect class
            continue;
        }
        classNameToAmountIt->second += 1;
        // consider how to handle no greatest element
    }

    auto dominantClassNameToAmount = std::max_element(classNameToAmountMap.begin(),
        classNameToAmountMap.end(),
        [](const std::pair<std::string, int>& lhs, const std::pair<std::string, int>& rhs)
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
    void predict(const std::vector<DataType>& testSet, const std::vector<DataType>& trainSet,
        const unsigned int k)
    {
        //std::cout << "in predict(...)" << std::endl;

        std::map<std::string, int> classNameToAmountMap;
        // All of these are made float to make accuracy easier to compute
        float correctChoices = 0.0f;
        float incorrectChoices = 0.0f;
        float allChoices = static_cast<float>(testSet.size());  // it will be removed in refactor

        for (const auto& test : testSet)
        {
            resetClassNameToAmountMap(test, classNameToAmountMap);
            auto kNearestNeighbors = getNearestNeighbors(getAllNeighbors(test, trainSet), k);

            std::string dominantClassInNeighborhood = chooseClassBasedOnNeighbors(kNearestNeighbors,
                classNameToAmountMap);

            if (dominantClassInNeighborhood == test.getClassName())
            {
                ++correctChoices;
            }

            else
            {
                ++incorrectChoices;
            }
        }
        std::cout << "correctChoices: " << correctChoices << std::endl;
        std::cout << "incorrectChoices: " << incorrectChoices << std::endl;
        std::cout << "allChoices: " << allChoices << std::endl;
        accuracy_ = (correctChoices - incorrectChoices) / allChoices;
    };

    float getAccuracy() const {return accuracy_;}

private:
    float accuracy_ {0.0f};
};

}  // namespace classifier
#endif  // KNN_HPP_
