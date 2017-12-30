#ifndef DATA_MUSHROOM_HPP_
#define DATA_MUSHROOM_HPP_

#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <memory>
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
