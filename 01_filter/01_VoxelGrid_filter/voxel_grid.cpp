#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>

int main() {
    pcl::PCLPointCloud2::Ptr cloud (new pcl::PCLPointCloud2());
    pcl::PCLPointCloud2::Ptr cloud_filtered (new pcl::PCLPointCloud2());

    //读取点云数据
    pcl::PCDReader reader;
    reader.read("table_scene_lms400.pcd", *cloud);

    std::cerr << "PointCloud before filtering: " << cloud->width * cloud->height << " data points (" << pcl::getFieldsList(*cloud) << ")." << std::endl;
    
    //创建一个边长为1cm的体素过滤器
    float leafSize = 0.01f;

    //创建VoxelGrid过滤器,使用定义好的体素边长
    pcl::VoxelGrid<pcl::PCLPointCloud2> sor;
    sor.setInputCloud(cloud);
    sor.setLeafSize(leafSize, leafSize, leafSize);
    sor.filter(*cloud_filtered);

    std::cerr << "PointCloud after filtering: " << cloud_filtered->width * cloud_filtered->height << " data points (" << pcl::getFieldsList (*cloud_filtered) << ")." << std::endl;

    //将过滤后的数据写入磁盘
    pcl::PCDWriter writer;
    writer.write("table_scene_lms400_downsample.pcd", *cloud_filtered, Eigen::Vector4f::Zero(), Eigen::Quaternionf::Identity(), false);

    return (0);
}