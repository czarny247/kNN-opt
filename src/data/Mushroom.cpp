#include "Mushroom.hpp"

namespace data
{
    const std::array<std::string, 23> Mushroom::names_
    {
        "class",
        "cap-shape",
        "cap-surface",
        "cap-color",
        "bruises",
        "odor",
        "gill-attachment",
        "gill-spacing",
        "gill-size",
        "gill-color",
        "stalk-shape",
        "stalk-root",
        "stalk-surface-above-ring",
        "stalk-surface-below-ring",
        "stalk-color-above-ring",
        "stalk-color-below-ring",
        "veil-type",
        "veil-color",
        "ring-number",
        "ring-type",
        "spore-print-color",
        "population",
        "habitat"
    };

    const std::vector<std::string> Mushroom::possibleClasses_ { "e", "p" };
    const std::map<std::string, std::string> Mushroom::attributeNameToCorrectVaules_
    {
        {"class", "ep"},
        {"cap-shape", "bcfksx"},
        {"cap-surface", "fgsy"},
        {"cap-color", "bcegnpruwy"},
        {"bruises", "ft"},
        {"odor", "acflmnpsy"},
        {"gill-attachment", "adfn"},
        {"gill-spacing", "cdw"},
        {"gill-size", "bn"},
        {"gill-color", "beghknopruwy"},
        {"stalk-shape", "et"},
        {"stalk-root", "bceruz"},
        {"stalk-surface-above-ring", "fksy"},
        {"stalk-surface-below-ring", "fksy"},
        {"stalk-color-above-ring", "bcegnopwy"},
        {"stalk-color-below-ring", "bcegnopwy"},
        {"veil-type", "pu"},
        {"veil-color", "nowy"},
        {"ring-number", "not"},
        {"ring-type", "ceflnpsz"},
        {"spore-print-color", "bhknoruwy"},
        {"population", "acnsvy"},
        {"habitat", "dglmpuw"}
    };

    // to do: redundant repeatability of data - get rid of this! remember that map have other
    // of keys than in code
}  // namespace data
