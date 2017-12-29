#ifndef DATA_WINE_HPP_
#define DATA_WINE_HPP_

#include <iostream>
#include <string>
#include <vector>

namespace data
{

struct Wine
{
    Wine() = default;
    ~Wine() = default;

    unsigned int classId_;
    float alcohol_;
    float malicAcid_;
    float ash_;
    float ashAlcalinity_;
    float magnesium_;
    float totalPhenols_;
    float flavanoids_;
    float nonFlavanoidPhenols_;
    float proAnthocyaninis_;
    float colorIntensity_;
    float hue_;
    float od280od315ofDilutedWines_;

    std::vector<float> getFeaturesAsVector() const
    {
        return {alcohol_, malicAcid_, ash_, ashAlcalinity_, magnesium_, totalPhenols_, flavanoids_,
            nonFlavanoidPhenols_, proAnthocyaninis_, colorIntensity_, hue_,
            od280od315ofDilutedWines_};
    }

    std::string getClassName() const
    {
        return std::to_string(classId_);
    }

    static const std::vector<std::string> possibleClasses_;
};

inline std::ostream& operator<< (std::ostream& stream, const Wine& wine)
{
    stream << "classId: " << wine.classId_ << std::endl;
    stream << "alcohol: " << wine.alcohol_ << std::endl;
    stream << "malicAcid: " << wine.malicAcid_ << std::endl;
    stream << "ash: " << wine.ash_ << std::endl;
    stream << "ashAlcalinity: " << wine.ashAlcalinity_ << std::endl;
    stream << "magnesium: " << wine.magnesium_ << std::endl;
    stream << "totalPhenols: " << wine.totalPhenols_ << std::endl;
    stream << "flavanoids: " << wine.flavanoids_ << std::endl;
    stream << "nonFlavanoidPhenols: " << wine.nonFlavanoidPhenols_ << std::endl;
    stream << "proAnthocyaninis: " << wine.proAnthocyaninis_ << std::endl;
    stream << "colorIntensity: " << wine.colorIntensity_ << std::endl;
    stream << "hue: " << wine.hue_ << std::endl;
    stream << "od280od315ofDilutedWines: " << wine.od280od315ofDilutedWines_ << std::endl;
    return stream;
}

inline std::istream& operator>> (std::istream& stream, Wine& wine)
{
    stream >> wine.classId_
        >> wine.alcohol_
        >> wine.malicAcid_
        >> wine.ash_
        >> wine.ashAlcalinity_
        >> wine.magnesium_
        >> wine.totalPhenols_
        >> wine.flavanoids_
        >> wine.nonFlavanoidPhenols_
        >> wine.proAnthocyaninis_
        >> wine.colorIntensity_
        >> wine.hue_
        >> wine.od280od315ofDilutedWines_;
    return stream;
}

}  // namespace data

#endif  // DATA_WINE_HPP_
