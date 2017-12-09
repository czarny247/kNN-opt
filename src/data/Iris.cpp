#include "Iris.hpp"

#include <string>
#include <vector>

namespace data
{
    const std::vector<std::string> Iris::possibleClasses_ {
        "Iris-setosa", "Iris-versicolor", "Iris-virginica"};

    /*int Iris::defCtorCalls_ = 0;
    int Iris::argCtorCalls_ = 0;
    int Iris::cpCtorCalls_ = 0;
    int Iris::cpAssOpCalls_ = 0;
    int Iris::mvCtorCalls_ = 0;
    int Iris::mvAssOpCalls_ = 0;
    int Iris::dtorCalls_ = 0;

    void Iris::showCallsSummary()
    {
        std::cout << "\ndefCtorCalls_: " << defCtorCalls_;
        std::cout << "\nargCtorCalls_: " << argCtorCalls_;
        std::cout << "\ncpCtorCalls_: " << cpCtorCalls_;
        std::cout << "\ncpAssOpCalls_: " << cpAssOpCalls_;
        std::cout << "\nmvCtorCalls_: " << mvCtorCalls_;
        std::cout << "\nmvAssOpCalls_: " << mvAssOpCalls_;
        std::cout << "\ndtorCalls_: " << dtorCalls_;
    }*/

}  // namespace data
