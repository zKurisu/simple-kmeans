#include "kmeans.h"
#include <iostream>

int main(void) {
    kmeans::Kmeans test(10);
    std::vector<kmeans::Point> vec = kmeans::readFilePoints("points.csv");
    test.initPoints(vec);
    // test.initPoints(100);
    std::cout << test << std::endl;
    // test.savePoints();
    return 0;
}
