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
    int runs = 100;

    data::DataHandler<data::Iris> irisDataHandler;
    irisDataHandler.loadData("../iris.data");
    classifier::Knn kNN;
    std::random_device rd;
    std::vector<unsigned int> seeds;

    // make class for run predictions and print them and analyse etc.

    // std::cout << "Running non-threaded kNN" << std::endl;
    for (auto run : boost::irange(0, runs))
    {
        seeds.push_back(rd());
    }

    for (auto run : boost::irange(0, runs))
    {
        // std::cout << "run: " << run << std::endl;
        irisDataHandler.splitData(split, seeds.at(run));
        kNN.predict(irisDataHandler.getTestSet(), irisDataHandler.getTrainSet(), k, boost::none);
        accSumRegular += kNN.getAccuracy();
    }

    std::cout << "Mean accuracy for " << runs << " runs of kNN (k=" << k << ", split=" << split
        << "): " << accSumRegular/runs << std::endl;

    // std::cout << "Running threaded kNN" << std::endl;
    for (auto run : boost::irange(0, runs))
    {
        // std::cout << "run: " << run << std::endl;
        irisDataHandler.splitData(split, seeds.at(run));
        kNN.predict(irisDataHandler.getTestSet(), irisDataHandler.getTrainSet(), k,
            std::thread::hardware_concurrency());
        accSumParallel += kNN.getAccuracy();
    }

    std::cout << "Mean accuracy for " << runs << " runs of threaded kNN (k=" << k << ", split="
        << split << "): " << accSumParallel/runs << std::endl;

    return 0;
}
