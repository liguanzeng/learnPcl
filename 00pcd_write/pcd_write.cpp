#include <iostream>   //标准c++输入输出相关头文件
#include <pcl/io/pcd_io.h>    //pcd读写相关头文件
#include <pcl/point_types.h>  //pcl中支持的点类型头文件

// 定义点云格式
typedef pcl::PointXYZ PointT;

int
  main (int argc, char** argv)
{
  pcl::PointCloud<PointT> cloud;

  // Fill in the cloud data
  cloud.width    = 5;
  cloud.height   = 1;
  cloud.is_dense = false;
  cloud.resize (cloud.width * cloud.height);

  for (auto& point: cloud)
  {
    point.x = 1024 * rand () / (RAND_MAX + 1.0f);
    point.y = 1024 * rand () / (RAND_MAX + 1.0f);
    point.z = 1024 * rand () / (RAND_MAX + 1.0f);
  }

  pcl::io::savePCDFileASCII ("test_pcd.pcd", cloud);
  std::cerr << "Saved " << cloud.size () << " data points to test_pcd.pcd." << std::endl;

  for (const auto& point: cloud)
    std::cerr << "    " << point.x << " " << point.y << " " << point.z << std::endl;

  return (0);
}
