
#include "data/DataHandler.hpp"
#include "data/Iris.hpp"

int main()
{
    data::DataHandler<data::Iris> irisDataHandler;
    irisDataHandler.loadData("../iris.data");
    irisDataHandler.printData();
    return 0;
}
