#include "KMeans.h"

int main() {
    size_t number_of_points = 100.00;
    size_t number_of_centroids = 10.00;
    int number_of_iterations = 3;
    double max_number = 10.0;
    KMeans kMeans_data(max_number);
    const auto data = kMeans_data.randomPointGenerator(number_of_points);
    KMeans kMeans_cluster(10.0);
    const auto clusters = kMeans_cluster.randomClusterGenerator(data, number_of_centroids);
    KMeans kMeans;
    kMeans.assign(data, clusters, number_of_iterations);
    return 0;
}
