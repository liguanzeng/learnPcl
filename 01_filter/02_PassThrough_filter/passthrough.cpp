#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>

// 定义点云格式
typedef pcl::PointXYZ PointT;

int main() {
    pcl::PointCloud<PointT>::Ptr cloud (new pcl::PointCloud<PointT>);
    pcl::PointCloud<PointT>::Ptr cloud_filtered (new pcl::PointCloud<PointT>);

    //Fill in the cloud data
    cloud->width = 5;
    cloud->height = 1;
    cloud->points.resize(cloud->width * cloud->height);

    for (auto & point : *cloud) {
        point.x = 1024 * rand() / (RAND_MAX + 1.0f);
        point.y = 1024 * rand() / (RAND_MAX + 1.0f);
        point.z = 1024 * rand() / (RAND_MAX + 1.0f);
    }

    std::cerr << "Clouds before filtering: " << std::endl;
    for (const auto& point : *cloud) {
        std::cerr << "      " << point.x << " "
                              << point.y << " "
                              << point.z << " " << std::endl;
    }

    //Create the filter obj
    pcl::PassThrough<PointT> pass;
    pass.setInputCloud(cloud);
    pass.setFilterFieldName("z");
    pass.setFilterLimits(0.0, 1.0);
    pass.filter(*cloud_filtered);

    std::cerr << "Clouds after filtering: " << std::endl;
    for (const auto& point : *cloud_filtered) {
        std::cerr << "      " << point.x << " "
                              << point.y << " "
                              << point.z << " " << std::endl;
    }

    return 0;
}