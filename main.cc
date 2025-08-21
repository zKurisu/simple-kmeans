#include "kmeans.h"
#include <iostream>

void createRandomPoints(int pointNum) {
    kmeans::Kmeans test(3);
    test.initPoints(pointNum);
    test.savePoints();
}

int main(void) {
    // createRandomPoints(10000);
    std::vector<kmeans::Point> input = kmeans::readFilePoints("./dataset/data.csv");
    kmeans::Kmeans test(3);
    test.initPoints(input);
    test.initCentersPlusPlus();
    test.update(10000, 10);
    test.savePoints();
    test.saveLoss();
    return 0;
}
