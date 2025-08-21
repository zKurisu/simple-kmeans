#include "kmeans.h"

#include <map>
#include <cmath>
#include <random>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace kmeans {

    // Random init points
    // MapSize: 100, 100
    void Kmeans::initPoints(int pointNum) {
        if (pointNum < k) pointNum = k;
        std::mt19937 rng;
        rng.seed(std::random_device{}());
        std::uniform_real_distribution<float> udist(0, 10000);
        for (int i=0; i<pointNum; i++) {
            points.push_back(Point(
                udist(rng), udist(rng)
            ));
        }
    }
    // Random init points
    void Kmeans::initPoints(std::vector<Point> pointVec) {
        if (pointVec.size() < k) 
            std::cerr << "Length of vector (" << pointVec.size() << ") "
                << "should greater than K " << "(" << k << ")...";
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

    void Kmeans::saveLoss() {
        std::ofstream saveFile("loss.csv", std::ios::out);
        if (saveFile.is_open()) {
            saveFile << "epoch,loss" << std::endl;
            for (int i=0; i<lossTrend.size(); i++)
                saveFile << i << ","
                    << lossTrend[i] << std::endl;
        }
        saveFile.close();
    }

    void Kmeans::initCentersTraditional() {
        for (int i=0; i<k; i++) {
            points[i]._group = i;
            centers.push_back(points[i]);
        }
    }

    void Kmeans::initCentersPlusPlus() {
        std::mt19937 rng;
        rng.seed(std::random_device{}());

        int psize = pointNum();
        // Select first center
        int firstCenterIndex = rng() % psize;
        points[firstCenterIndex]._group = 0;
        centers.push_back(points[firstCenterIndex]);

        // Select left centers
        std::vector<float> distances(psize, 0.0);
        while (centers.size() < k) {
            // Calculate distance
            for (int i=0; i<psize; i++)
                distances[i] = std::pow(centers[centers.size()-1].distance(points[i]), 2);

            std::discrete_distribution<int> dist(distances.begin(), distances.end());
            int indice = dist(rng);
            centers.push_back(points[indice]);
            points[indice]._group = centers.size()-1;
        }
    }

    void Kmeans::cluster() {
        std::vector<Point> clusters(k, Point(0,0,0));

        for (auto it=points.begin(); it<points.end(); it++) {
            float nearestDistance = MAXFLOAT;
            int nearestCenterID = 0;
            for (int i=0; i<centers.size(); i++) {
                float distance = (*it).distance(centers[i]);
                if (distance < nearestDistance) {
                    nearestCenterID = i;
                    nearestDistance = distance;
                }
                // std::cout << nearestDistance << "," << distance << std::endl;
            }
            (*it)._group = nearestCenterID;
            loss += nearestDistance * nearestDistance;

            clusters[nearestCenterID]._x += (*it)._x;
            clusters[nearestCenterID]._y += (*it)._y;
            clusters[nearestCenterID]._group++;
        }

        lossTrend.push_back(loss);

        // Calculate new centers
        for (int i=0; i<k; i++) {
            // std::cout << "In cluster point num: " << clusters[i]._group << std::endl;
            centers[i]._x = clusters[i]._x / clusters[i]._group;
            centers[i]._y = clusters[i]._y / clusters[i]._group;
        }
    }

    void Kmeans::update(int maxTry, int wait) {
        float prevLoss = -1;

        int tryCount = 0;
        int waitCount = 0;
        while (waitCount < wait) {
            prevLoss = loss;

            loss = 0; // Loss init to zero
            cluster();
            std::cout << "Loop count: " << tryCount << std::endl;
            std::cout << "Loss: " << loss << std::endl;

            tryCount++;
            if (loss == prevLoss) waitCount++;
            if (tryCount > maxTry) break;
        }
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
