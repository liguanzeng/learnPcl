#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>

int main(int argc, char **argv)
{
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);

    if (pcl::io::loadPCDFile<pcl::PointXYZ>("../../_pcd_data/bunny.pcd", *cloud) == -1)
    {
        PCL_ERROR("Couldn't read pcd file \n");
        return -1;
    }

    std::cout << "Loaded "
              << cloud->width * cloud->height
              << " data points from bunny.pcd with the following fields: "  
              << std::endl;
    for (size_t i = 0; i < cloud->points.size(); ++i)
    {
        std::cout << "  " << cloud->points[i].x
                  << " " << cloud->points[i].y
                  << " " << cloud->points[i].z  << std::endl;
    }
}