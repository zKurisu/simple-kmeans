#ifndef MY_KMEANS_H_
#define MY_KMEANS_H_

#include <vector>
#include <map>
#include <cmath>
#include <string>

namespace kmeans {

struct Point {
    float _x, _y;
    int _group;
    Point(float x, float y, int group = 0) { _x = x; _y = y; _group = group; };
    inline float distance(Point& another) {
        return (std::sqrtf(_x - another._x) * (_x - another._x) + (_y - another._y) * (_y - another._y));
    };
};


// Class Definition
class Kmeans {
public:
    Kmeans(int K) { k = K; };
    void initPoints(int pointNum);
    void initPoints(std::vector<Point> pointVec);
    void initCentersTraditional();
    void initCentersPlusPlus();
    void update(); // Loop to end
    void savePoints();

    int pointNum();
    friend std::ostream& operator<<(std::ostream& os, const Kmeans& kms);

private:
    int k;
    std::vector<Point> points;
    std::map<int,Point> centers; // gid -> Point
};
// End Class Definition

std::vector<Point> readFilePoints(std::string fileName);

}

#endif // MY_KMEANS_H_
