#include "kmeans.h"
#include <iostream>

int main(void) {
    kmeans::Kmeans test(3);
    // std::vector<kmeans::Point> vec = kmeans::readFilePoints("points.csv");
    // test.initPoints(vec);
    test.initPoints(100);
    // test.update();
    test.initCentersPlusPlus();
    test.update(10000);
    // std::cout << test << std::endl;
    test.savePoints();
    return 0;
}
