#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/filters/statistical_outlier_removal.h>

typedef pcl::PointXYZ PointT;

int main(int argc, char** argv)
{
    pcl::PointCloud<PointT>::Ptr cloud(new pcl::PointCloud<PointT>);
    pcl::PointCloud<PointT>::Ptr filtered_cloud(new pcl::PointCloud<PointT>);

    pcl::PCDReader reader;
    reader.read<PointT>("../../../_pcd_data/table_scene_lms400.pcd", *cloud);

    std::cerr << "Cloud before filtering: " << std::endl;
    std::cerr << *cloud << std::endl;

    // 创建过滤器，每个点分析计算时考虑的最近邻居个数为50个；
    // 设置标准差阈值为1，这意味着所有距离查询点的平均距离的标准偏差均大于1个标准偏差的所有点都将被标记为离群值并删除。
    // 计算输出并将其存储在cloud_filtered中
    pcl::StatisticalOutlierRemoval<PointT> sor;
    sor.setInputCloud(cloud);
    sor.setMeanK(50);
    sor.setStddevMulThresh(1.0);
    sor.filter(*filtered_cloud);

    std::cerr << "Cloud after filtering: " << std::endl;
    std::cerr << *filtered_cloud << std::endl;

    pcl::PCDWriter writer;
    writer.write<PointT>("../table_scene_lms400_inliers.pcd", *filtered_cloud, false);

    sor.setNegative(true);
    sor.filter(*filtered_cloud);
    writer.write<PointT>("../table_scene_lms400_outliers.pcd", *filtered_cloud, false);

    return (0);
}