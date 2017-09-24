#ifndef DATA_IRIS_HPP_
#define DATA_IRIS_HPP_

#include <fstream>
#include <string>

namespace data
{

struct Iris
{
    Iris()
    : sepalLength_(0.0f), sepalWidth_(0.0f), petalLength_(0.0f), petalWidth_(0.0f), species_("")
    {}

    Iris(float sepalLength, float sepalWidth, float petalLength, float petalWidth,
        std::string species)
    : sepalLength_(sepalLength), sepalWidth_(sepalWidth), petalLength_(petalLength),
    petalWidth_(petalWidth), species_(species)
    {}

    float sepalLength_;
    float sepalWidth_;
    float petalLength_;
    float petalWidth_;
    std::string species_;
};

std::ostream& operator<< (std::ostream& stream, const Iris& iris)
{
    stream << "sepalLength: " << iris.sepalLength_ << std::endl;
    stream << "sepalWidth: " << iris.sepalWidth_ << std::endl;
    stream << "petalLength: " << iris.petalLength_ << std::endl;
    stream << "petalWidth: " << iris.petalWidth_ << std::endl;
    stream << "species: " << iris.species_ << std::endl;
    return stream;
}

std::istream& operator>> (std::istream& stream, Iris& iris)
{
    stream >> iris.sepalLength_
        >> iris.sepalWidth_
        >> iris.petalLength_
        >> iris.petalWidth_
        >> iris.species_;
    return stream;
}

// TO DO: set input operator to make generic input in templated data handler

}  // namespace data

#endif  // DATA_IRIS_HPP_
