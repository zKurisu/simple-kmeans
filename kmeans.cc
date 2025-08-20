#include "kmeans.h"

#include <random>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace kmeans {

    // Random init points
    // MapSize: 100, 100
    void Kmeans::initPoints(int pointNum) {
        std::mt19937 rng;
        rng.seed(std::random_device{}());
        std::uniform_real_distribution<float> udist(0, 100);
        for (int i=0; i<pointNum; i++) {
            points.push_back(Point(
                udist(rng), udist(rng)
            ));
        }
    }
    // Random init points
    void Kmeans::initPoints(std::vector<Point> pointVec) {
        for (auto it=pointVec.begin(); it<pointVec.end(); it++)
            points.push_back(*it);
    }

    // Return points size
    int Kmeans::pointNum() {
        return points.size();
    }

    // Save to CSV file
    void Kmeans::savePoints() {
        std::ofstream saveFile("points.csv", std::ios::out);
        if (saveFile.is_open()) {
            saveFile << "x,y,gid" << std::endl;
            for (int i=0; i<points.size(); i++)
                saveFile << points[i]._x << ","
                    << points[i]._y << ","
                    << points[i]._group << std::endl;
        }
        saveFile.close();
    }

    std::ostream& operator<<(std::ostream& os, const Kmeans& kms) {
        const auto& pts = kms.points;
        if (pts.size() == 0) return os << "No points in Kmeans";
        for (int i=0; i<kms.points.size(); i++) {
            if (i % 3 == 0) os << '\n';
            os << '(' << pts[i]._x << ','
            << pts[i]._y << ',' 
            << pts[i]._group << ')';
        }
        return os;
    }

    std::vector<Point> readFilePoints(std::string fileName) {
        std::ifstream readCSV(fileName, std::ios::in);
        std::vector<Point> filePoints;
        if (readCSV.is_open()) {
            std::string line;
            std::getline(readCSV, line); // escape first header line
            while (std::getline(readCSV, line)) {
                float x, y;
                int group;
                char comma;
                std::istringstream iss(line);
                iss >> x >> comma >> y >> comma >> group;
                filePoints.push_back(Point(
                    x, y, group
                ));
            }
        } else {
            std::cerr << fileName << " can not open..." << std::endl;
        }
        return filePoints;
    }

}
