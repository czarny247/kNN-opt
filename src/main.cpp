#include "classifier/Knn.hpp"
#include "data/DataHandler.hpp"
#include "data/Iris.hpp"

int main()
{
    data::DataHandler<data::Iris> irisDataHandler;
    irisDataHandler.loadData("../iris.data");
    irisDataHandler.splitData(0.7);

    classifier::Knn kNN;
    kNN.predict<data::Iris>(irisDataHandler.getTestSet(), irisDataHandler.getTrainSet(), 5);
    std::cout << "accuracy: " << kNN.getAccuracy() << std::endl;

    return 0;
}
