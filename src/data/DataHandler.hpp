#ifndef DATA_HANDLER_HPP_
#define DATA_HANDLER_HPP_

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
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
            dataObjects_.push_back(deserialize(parsedLine));
        }
    }

    void printData()
    {
        auto idx = 1;
        for (const auto& dataObject : dataObjects_)
        {
            std::cout << "Iris #" << idx << std::endl;
            std::cout << dataObject << std::endl;
            std::cout << "-------------------------\n";
            ++idx;
        }
    }

private:
    std::vector <DataType> dataObjects_;

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
