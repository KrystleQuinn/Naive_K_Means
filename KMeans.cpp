#include "KMeans.h"
#include <cmath>
#include <limits>
#include <queue>
#include <iomanip>

/* Private Methods */
double KMeans::euclideanDistance(const PointCoordinate& point, const PointCoordinate& cluster) {
    const double squared_distance = std::pow((point.x - cluster.x), 2.0) + std::pow((point.y - cluster.y), 2.0);
    const double distance = std::sqrt(std::abs(squared_distance));
    return distance;
}

/* Don't need coordinates of cluster because it's already the coordinates of a point,
 * recompute each centroid as the mean of all the POINTS assigned to it */
void KMeans::updateCentroids(const PointCoordinate& point, const int& centroid_id,
                             std::vector<PointCoordinate>& updated_centroids) {
    updated_centroids[centroid_id].x += point.x;
    updated_centroids[centroid_id].y += point.y;
}

void KMeans::updateMean(const std::vector<PointCoordinate>& updated_centroids, const std::vector<size_t>& cluster_size,
                        std::vector<PointCoordinate>& centroids) {
    for (size_t centroid = 0; centroid < updated_centroids.size(); ++centroid) {
        if (cluster_size[centroid] > 0) {
            centroids[centroid].x = updated_centroids[centroid].x / cluster_size[centroid];
            centroids[centroid].y = updated_centroids[centroid].y / cluster_size[centroid];
        }
    }
    std::cout << "New means: \n";
    for (auto const& centroid : centroids)
        std::cout << "(" << centroid.x << "," << centroid.y << ")\n";
    /* What do I want to do here? */
    // return centroids;
}

/* Public Methods */

int KMeans::generateNumber() {
    return distribution(mersenne_engine);
}

/* Generate fake data for testing purposes only */
std::vector<KMeans::PointCoordinate> KMeans::randomPointGenerator(size_t points_) {
    points = points_;
    std::vector<PointCoordinate> data(points);
    //   std::cout << "Points: " << std::endl;
    for (auto it = std::begin(data); it != std::end(data); ++it) {
        it->x = generateNumber();
        it->y = generateNumber();
        //      std::cout << "(" << it->x << "," << it->y << ")" << std::endl;
    }
    return data;
}

/* Pick centroids as random points from dataset */
std::vector<KMeans::PointCoordinate>
KMeans::randomClusterGenerator(const std::vector<PointCoordinate>& data, size_t means_) {
    means = means_;
    std::vector<PointCoordinate> clusters(means);
    std::cout << "Clusters: \n";
    for (auto& cluster : clusters) {
        cluster = data[generateNumber()];
        std::cout << "(" << cluster.x << "," << cluster.y << ")" << std::endl;
    }
    return clusters;
}

/* Assign data point to closest cluster */
/* Do I want to put the number of iterations in here or outside the function?? */
void KMeans::assign(const std::vector<PointCoordinate>& data, const std::vector<PointCoordinate>& centroids) {
    std::vector<PointCoordinate> centroids_(centroids);
    std::vector<PointCoordinate> update_centroids(centroids.size());
    std::vector<size_t> cluster_size(centroids.size(), 0);
    std::queue<int> cluster_ids;
    size_t cluster_id;
    std::vector<PointCoordinate> assignments(data.size());
    for (auto const& point : data) {
        /* set min distance to max to start with */
        double minimum_distance = std::numeric_limits<double>::max();
        for (auto const& cluster : centroids) {
            size_t distance = euclideanDistance(point, cluster);
            if (distance < minimum_distance) {
                minimum_distance = distance;
                cluster_ids.push(&cluster - &centroids[0]);
            }
        }
        while (cluster_ids.size() > 1) {
            cluster_ids.pop();
        }
        cluster_id = cluster_ids.back();
        ++cluster_size[cluster_id];
        updateCentroids(point, cluster_id, update_centroids);
    }
    std::cout << "Updated centroids: \n";
    for (auto const& cluster : update_centroids) {
        std::cout << "(" << cluster.x << "," << cluster.y << ")\n";
    }
    std::cout << "Cluster size: \n";
    for (auto const& cluster : cluster_size) {
        std::cout << cluster << " \n";
    }
    updateMean(update_centroids, cluster_size, centroids_);
}

/*std::ostream& operator<<(std::ostream& os, const KMeans::PointCoordinate& pc)
{
    os << pc.x << " " << pc.y;
    return os;
} */

