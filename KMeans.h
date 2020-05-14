#ifndef NAIVE_K_MEANS_KMEANS_H
#define NAIVE_K_MEANS_KMEANS_H

#include <vector>
#include <iostream>
#include <random>

class KMeans {
private:
    struct PointCoordinate {
        double x{0}, y{0};
    };
    size_t points;
    size_t means;
    size_t max_number;
    std::mt19937 mersenne_engine;
    std::uniform_real_distribution<double> distribution;

    static double euclideanDistance(const PointCoordinate& point, const PointCoordinate& cluster);

    void
    updateCentroids(const PointCoordinate& point, const int& centroid_id, std::vector<PointCoordinate>& new_centroids);

    void updateMean(const std::vector<PointCoordinate>& updated_centroids, const std::vector<size_t>& cluster_size, std::vector<PointCoordinate>& centroids);

public:
    KMeans() : max_number(0), points(0), means(0) {}

    /* Initialize pseudorandom number generator with a single random number produced by seed */
    explicit KMeans(double max) : max_number(max), mersenne_engine{std::random_device{}()}, distribution{0.0, max} {}

    int generateNumber();

    std::vector<PointCoordinate> randomPointGenerator(size_t points_);

    std::vector<PointCoordinate> randomClusterGenerator(const std::vector<PointCoordinate>& data, size_t means_);

    void assign(const std::vector<PointCoordinate>& data, const std::vector<PointCoordinate>& centroids, const int& iterations_);

    //friend std::ostream& operator<<(std::ostream& os, const PointCoordinate& pc);
};


#endif //NAIVE_K_MEANS_KMEANS_H
