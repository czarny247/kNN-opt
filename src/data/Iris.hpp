#ifndef DATA_IRIS_HPP_
#define DATA_IRIS_HPP_

#include <fstream>
#include <string>
#include <vector>

namespace data
{

//TODO: consider making common interface for data classes

struct Iris
{
    Iris()
    : sepalLength_(0.0f), sepalWidth_(0.0f), petalLength_(0.0f),
    petalWidth_(0.0f), species_("")
    {}

    ~Iris()
    {}

    Iris(float sepalLength, float sepalWidth, float petalLength, float petalWidth,
        std::string species)
    : sepalLength_(sepalLength), sepalWidth_(sepalWidth), petalLength_(petalLength),
    petalWidth_(petalWidth), species_(species)
    {}

    Iris(const Iris& iris)
    : sepalLength_(iris.sepalLength_), sepalWidth_(iris.sepalWidth_),
    petalLength_(iris.petalLength_), petalWidth_(iris.petalWidth_), species_(iris.species_)
    {}

    Iris& operator=(const Iris& iris)
    {
        sepalLength_ = iris.sepalLength_;
        sepalWidth_ = iris.sepalWidth_;
        petalLength_ = iris.petalLength_;
        petalWidth_ = iris.petalWidth_;
        species_ = iris.species_;
        return *this;
    }

    Iris(Iris&& iris)
    : sepalLength_(iris.sepalLength_), sepalWidth_(iris.sepalWidth_),
    petalLength_(iris.petalLength_), petalWidth_(iris.petalWidth_), species_(iris.species_)
    {}

    Iris& operator=(Iris&& iris)
    {
        if (this != &iris)
        {
            sepalLength_ = iris.sepalLength_;
            sepalWidth_ = iris.sepalWidth_;
            petalLength_ = iris.petalLength_;
            petalWidth_ = iris.petalWidth_;
            species_ = iris.species_;
        }
        return *this;
    }

    float sepalLength_;
    float sepalWidth_;
    float petalLength_;
    float petalWidth_;
    std::string species_;

    //TODO: it will be in common interface for data classes
    std::vector<float> getFeaturesAsVector() const
    {
        return {sepalLength_, sepalWidth_, petalLength_, petalWidth_};
    }

    //TODO: also will be in common interface
    static const std::vector<std::string> possibleClasses_;

    //TODO: also will be in common interface
    std::string getClassName() const
    {
        return species_;
    }
};

inline std::ostream& operator<< (std::ostream& stream, const Iris& iris)
{
    stream << "sepalLength: " << iris.sepalLength_ << "\n";
    stream << "sepalWidth: " << iris.sepalWidth_ << "\n";
    stream << "petalLength: " << iris.petalLength_ << "\n";
    stream << "petalWidth: " << iris.petalWidth_ << "\n";
    stream << "species: " << iris.species_ << "\n";
    return stream;
}

inline std::istream& operator>> (std::istream& stream, Iris& iris)
{
    stream >> iris.sepalLength_
        >> iris.sepalWidth_
        >> iris.petalLength_
        >> iris.petalWidth_
        >> iris.species_;
    return stream;
}

}  // namespace data

#endif  // DATA_IRIS_HPP_
