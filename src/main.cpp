#include <iostream>
#include <random>
#include <thread>

#include <boost/optional.hpp>
#include <boost/range/irange.hpp>

#include "classifier/Knn.hpp"
#include "data/DataHandler.hpp"
#include "data/Iris.hpp"

int main()
{
    const unsigned int k = 5;
    const float split = 0.8;
    float accSumRegular {0.0f};
    float accSumParallel {0.0f};
    double timeSumRegular {0.0};
    double timeSumParallel {0.0};
    int runs = 10000;

    data::DataHandler<data::Iris> irisDataHandler;
    irisDataHandler.loadData("../iris.data");

    classifier::Knn kNN;
    std::random_device rd;

    std::vector<unsigned int> seeds;

    for (auto run : boost::irange(0, runs))
    {
        seeds.push_back(rd());
    }

    std::cout << "Running non-threaded kNN" << std::endl;
    for (auto run : boost::irange(0, runs))
    {
        irisDataHandler.splitData(split, seeds.at(run));
        kNN.predict(irisDataHandler.getTestSet(), irisDataHandler.getTrainSet(), k, boost::none);
        accSumRegular += kNN.getAccuracy();
        timeSumRegular += kNN.getMeasuredTime();
    }

    std::cout << "Avg accuracy for " << runs << " runs of kNN (k=" << k << ", split=" << split
        << "): " << round(accSumRegular)/runs << std::endl;
    std::cout << "Avg time for " << runs << " runs of kNN (k=" << k << ", split=" << split
        << "): " << timeSumRegular/runs << " seconds." << std::endl;

    std::cout << "Running threaded kNN" << std::endl;
    for (auto run : boost::irange(0, runs))
    {
        irisDataHandler.splitData(split, seeds.at(run));
        kNN.predict(irisDataHandler.getTestSet(), irisDataHandler.getTrainSet(), k,
            std::thread::hardware_concurrency());
        accSumParallel += kNN.getAccuracy();
        timeSumParallel += kNN.getMeasuredTime();
    }

    std::cout << "Avg accuracy for " << runs << " runs of threaded kNN (k=" << k << ", split="
        << split << "): " << round(accSumParallel)/runs << std::endl;
    std::cout << "Avg time for " << runs << " runs of threaded kNN (k=" << k << ", split="
        << split << "): " << timeSumParallel/runs << " seconds." << std::endl;

    return 0;
}
