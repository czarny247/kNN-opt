#ifndef DATA_MUSHROOM_HPP_
#define DATA_MUSHROOM_HPP_

#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace data
{

using AttributeNameWithValue = std::pair<std::string, std::shared_ptr<char>>;

struct Mushroom
{
    Mushroom() = default;
    ~Mushroom() = default;

    // to do : add explicitly deleted ctors / operators

    std::string attributes_;
    std::vector<AttributeNameWithValue> attributesNamesWithValues_;
    static const std::array<std::string, 23> names_;
    static const std::vector<std::string> possibleClasses_;
    static const std::map<std::string, std::string> attributeNameToCorrectVaules_;

    std::string getClassName() const
    {
        return std::string(1, attributes_[0]);
    }

    std::vector<float> getFeaturesAsVector()
    {
        std::vector<float> featuresVector;

        for (const AttributeNameWithValue& attributeNameWithValue : attributesNamesWithValues_)
        {
            auto featureAsNumeric = attributeNameToCorrectVaules_.at(attributeNameWithValue.first)
                .find(*attributeNameWithValue.second);
            featuresVector.push_back(++featureAsNumeric);
        }

        /*std::istringstream iss(attributes_);
        std::copy(std::istream_iterator<float>(iss), std::istream_iterator<float>(),
            std::back_inserter(featuresVector));*/

        for (const auto& fv : featuresVector)
        {
            std::cout << fv << ", ";
        }

        std::cout << std::endl;

        return featuresVector;
    }
};

namespace
{

void associateAttributeNamesWithValues(Mushroom& mushroom)
{
    for (unsigned int pos = 0; pos < mushroom.attributes_.length(); ++pos)
    {
        mushroom.attributesNamesWithValues_.push_back(std::make_pair(Mushroom::names_.at(pos),
            std::make_shared<char>(mushroom.attributes_.at(pos))));
    }
}

}  // namespace

inline std::ostream& operator<< (std::ostream& stream, const Mushroom& mushroom)
{
    for (const auto& attributeNameWithValue : mushroom.attributesNamesWithValues_)
    {
        stream << attributeNameWithValue.first << ": " << *attributeNameWithValue.second
            << std::endl;
    }

    return stream;
}

inline std::istream& operator>> (std::istream& stream, Mushroom& mushroom)
{
    std::string content {std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>()};
    content.erase(std::remove_if(content.begin(), content.end(),
        [](const char& c){return c == '\n';}), content.end());

    mushroom.attributes_ = content;
    associateAttributeNamesWithValues(mushroom);
    return stream;
}

}  // namespace data

#endif  // DATA_MUSHROOM_HPP_
