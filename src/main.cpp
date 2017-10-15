#include <iostream>
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
    // unsigned int numOfThreads = std::thread::hardware_concurrency();

    data::DataHandler<data::Iris> irisDataHandler;
    irisDataHandler.loadData("../iris.data");
    irisDataHandler.splitData(split);
    classifier::Knn kNN;
    /*kNN.predict(irisDataHandler.getTestSet(), irisDataHandler.getTrainSet(), k, 2);
    std::cout << "accuracy: " << kNN.getAccuracy() << std::endl;*/

    // std::cout << "Running non-threaded kNN" << std::endl;

    // irisDataHandler.splitData(split);

    for (auto run : boost::irange(0, runs)) // run predicts for regular and parallel separately
    // save splits from regular runs and use them for parallel
    {
        irisDataHandler.splitData(split);
        // std::cout << "run: " << run << std::endl;
        kNN.predict(irisDataHandler.getTestSet(), irisDataHandler.getTrainSet(), k, boost::none);
        // const auto accuracy = kNN.getAccuracy();
        // std::cout << "accuracy: " << accuracy << std::endl;
        accSumRegular += kNN.getAccuracy();

        kNN.predict(irisDataHandler.getTestSet(), irisDataHandler.getTrainSet(), k,
            std::thread::hardware_concurrency());

        accSumParallel += kNN.getAccuracy();
    }

    std::cout << "Mean accuracy for " << runs << " runs of kNN (k=" << k << ", split=" << split
        << "): " << accSumRegular/runs << std::endl;
    // std::cout << "measured time: " << kNN.getMeasuredTime() << "[nanoseconds]" << std::endl;

    // accSum = 0.0f;

    /*std::cout << "Number of hardware thread contexts: " << std::thread::hardware_concurrency()
        << std::endl; */

    // std::cout << "Running threaded kNN" << std::endl;

    /*for (auto run : boost::irange(0, runs))
    {
        // irisDataHandler.splitData(split);
        // std::cout << "run: " << run << std::endl;
        kNN.predict(irisDataHandler.getTestSet(), irisDataHandler.getTrainSet(), k,
            std::thread::hardware_concurrency());
        // const auto accuracy = kNN.getAccuracy();
        // std::cout << "accuracy: " << accuracy << std::endl;
        accSum += kNN.getAccuracy();
    }*/

    std::cout << "Mean accuracy for " << runs << " runs of threaded kNN (k=" << k << ", split="
        << split << "): " << accSumParallel/runs << std::endl;

    return 0;
}
