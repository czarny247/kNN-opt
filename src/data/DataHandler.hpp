#ifndef DATA_HANDLER_HPP_
#define DATA_HANDLER_HPP_

#include <algorithm>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include <boost/tokenizer.hpp>

using Tokenizer = boost::tokenizer< boost::escaped_list_separator<char> >;

namespace data
{

template <typename DataType>
class DataHandler
{
public:
    void loadData(const std::string& pathToFile)
    {
        std::ifstream in(pathToFile.c_str());
        if (!in.is_open())
        {
            std::cout << "File with path: " << pathToFile << " not found!" << std::endl;
            return;
        }

        std::vector <std::string> parsedLine;
        std::string line;

        while (std::getline(in, line))
        {
            Tokenizer tok(line);
            parsedLine.assign(tok.begin(), tok.end());
            dataSet_.push_back(deserialize(parsedLine));
        }
    }

    void printData() const
    {
        auto idx = 1;
        for (const auto& dataObject : dataSet_)
        {
            std::cout << "Iris #" << idx << std::endl;
            std::cout << dataObject << std::endl;
            std::cout << "-------------------------\n";
            ++idx;
        }
    }

    void printTrainSet() const
    {
        auto idx = 1;
        std::cout << "###### TRAIN SET ######\n";
        std::cout << "SIZE: " << trainSet_.size() << std::endl;
        for (const auto& element : trainSet_)
        {
            std::cout << "Train #" << idx << std::endl;
            std::cout << element << std::endl;
            std::cout << "-------------------------\n";
            ++idx;
        }
    }

    void printTestSet() const
    {
        auto idx = 1;
        std::cout << "###### TEST SET ######\n";
        std::cout << "SIZE: " << testSet_.size() << std::endl;
        for (const auto& element : testSet_)
        {
            std::cout << "Test #" << idx << std::endl;
            std::cout << element << std::endl;
            std::cout << "-------------------------\n";
            ++idx;
        }
    }

    const std::vector <DataType>& getDataSet() const
    {
        return dataSet_;
    }

    const std::vector <DataType>& getTrainSet() const
    {
        return trainSet_;
    }

    const std::vector <DataType>& getTestSet() const
    {
        return testSet_;
    }

    void splitData(const float trainPartInPercent, unsigned int seed)
    {
        auto dataToSplit = dataSet_;

        std::shuffle(dataToSplit.begin(), dataToSplit.end(), std::default_random_engine(seed));

        // TO DO: make split more "smart" - e.g. how to deal with non-integers?
        // check if it doesn't go out of range;
        auto trainBegin = dataToSplit.begin();
        auto trainEnd = trainBegin + (trainPartInPercent * dataToSplit.size());
        trainSet_ = {trainBegin, trainEnd};

        auto testBegin = trainEnd;
        auto testEnd = dataToSplit.end();
        testSet_ = {testBegin, testEnd};
    }

private:
    std::vector <DataType> dataSet_;
    std::vector <DataType> trainSet_;
    std::vector <DataType> testSet_;

    DataType deserialize(const std::vector<std::string>& serializedData)
    {
        std::stringstream streamedData;
        std::copy(serializedData.begin(), serializedData.end(),
            std::ostream_iterator<std::string>(streamedData, "\n"));
        DataType dataObject;
        streamedData >> dataObject;
        return dataObject;
    }
};

}  // namespace data
#endif  // DATA_HANDLER_HPP_
