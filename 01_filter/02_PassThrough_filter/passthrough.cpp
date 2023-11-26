#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/passthrough.h>
#include <pcl/visualization/cloud_viewer.h>

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
    pass.setInputCloud(cloud);              // 1.设置输入源
    pass.setFilterFieldName("z");           // 2.设置过滤域名
    pass.setFilterLimits(0.0, 1.0);         // 3.设置过滤范围
    // pass.setFilterLimitsNegative(true);     // 设置获取Limits之外的内容,结果取反
    pass.filter(*cloud_filtered);           // 4.执行filter,并将结果保存至cloud_filtered

    std::cerr << "Clouds after filtering: " << std::endl;
    for (const auto& point : *cloud_filtered) {
        std::cerr << "      " << point.x << " "
                              << point.y << " "
                              << point.z << " " << std::endl;
    }

    pcl::visualization::CloudViewer viewer("Cloud Viewer");

    // 这里会一直阻塞直到点云被渲染
    viewer.showCloud(cloud);
    while (!viewer.wasStopped()){
    }
    

    return 0;
}