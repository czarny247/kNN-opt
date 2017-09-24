
#include "data/DataHandler.hpp"
#include "data/Iris.hpp"

int main()
{
    data::DataHandler<data::Iris> irisDataHandler;
    irisDataHandler.loadData("../iris.data");
    irisDataHandler.splitData(0.7);
    irisDataHandler.printTrainSet();
    irisDataHandler.printTestSet();
    // irisDataHandler.printData();
    return 0;
}
