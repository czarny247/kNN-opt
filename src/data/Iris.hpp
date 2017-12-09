#ifndef DATA_IRIS_HPP_
#define DATA_IRIS_HPP_

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace data
{

// consider making common interface for data classes

struct Iris
{
    Iris()
    : sepalLength_(0.0f), sepalWidth_(0.0f), petalLength_(0.0f),
    petalWidth_(0.0f), species_("")
    {
        //++defCtorCalls_;
        //std::cout << "Iris()" << std::endl;
    }

    ~Iris()
    {
        //++dtorCalls_;
        //std::cout << "~Iris()" << std::endl;
    }

    Iris(float sepalLength, float sepalWidth, float petalLength, float petalWidth,
        std::string species)
    : sepalLength_(sepalLength), sepalWidth_(sepalWidth), petalLength_(petalLength),
    petalWidth_(petalWidth), species_(species)
    {
        //++argCtorCalls_;
        //std::cout << "Iris(...)" << std::endl;
    }

    Iris(const Iris& iris)
    : sepalLength_(iris.sepalLength_), sepalWidth_(iris.sepalWidth_),
    petalLength_(iris.petalLength_), petalWidth_(iris.petalWidth_), species_(iris.species_)
    {
        //++cpCtorCalls_;
        //std::cout << "Iris(const Iris& iris)" << std::endl;
    }

    Iris& operator=(const Iris& iris)
    {
        //++cpAssOpCalls_;
        //std::cout << "Iris& operator=(const Iris& iris)" << std::endl;
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
    {
        //++mvCtorCalls_;
        //std::cout << "Iris(const Iris&& iris)" << std::endl;
    }

    Iris& operator=(Iris&& iris)
    {
        //++mvAssOpCalls_;
        //std::cout << "Iris& operator=(const Iris&& iris)" << std::endl;

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

    // it will be in common interface for data classes
    std::vector<float> getFeaturesAsVector() const
    {
        return {sepalLength_, sepalWidth_, petalLength_, petalWidth_};
    }

    // also will be in common interface
    static const std::vector<std::string> possibleClasses_;
    /*static int defCtorCalls_;
    static int argCtorCalls_;
    static int cpCtorCalls_;
    static int cpAssOpCalls_;
    static int mvCtorCalls_;
    static int mvAssOpCalls_;
    static int dtorCalls_;*/

    // also will be in common interface
    std::string getClassName() const
    {
        return species_;
    }

    //static void showCallsSummary();
};

inline std::ostream& operator<< (std::ostream& stream, const Iris& iris)
{
    stream << "sepalLength: " << iris.sepalLength_ << std::endl;
    stream << "sepalWidth: " << iris.sepalWidth_ << std::endl;
    stream << "petalLength: " << iris.petalLength_ << std::endl;
    stream << "petalWidth: " << iris.petalWidth_ << std::endl;
    stream << "species: " << iris.species_ << std::endl;
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
