#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>

int main(int argc, char **argv)
{
    std::cout << "argc: " << argc << std::endl;
    std::cout << "argv: " << argv[1] << std::endl;
    
    if (argc != 2)
    {
        std::cerr << " Please specify command line arg '-f' or '-p'" << std::endl;
        exit(0);
    }
    
    /*******************************************************************
    定义了连接点云会用到的5个点云对象：3个输入（cloud_a cloud_b 和n_cloud_b）
    两个输出（cloud_c  n_cloud_c）然后就是为两个输入点云cloud_a和 cloud_b 或者 cloud_a 和n_cloud_b填充数据
    ********************************************************************/

    pcl::PointCloud<pcl::PointXYZ> cloud_a, cloud_b, cloud_c;
    
    // PointNormal和Normal分别是什么含义?
    // Normal - float normal[3], curvature 法线方向，对应的曲率的测量值
    // PointNormal - float x, y, z, normal[3], curvature 采样点，法线和曲率

    pcl::PointCloud<pcl::Normal> n_cloud_b;

    pcl::PointCloud<pcl::PointNormal> p_n_cloud_c;

    // 创建点云
    cloud_a.width = 5;
    cloud_a.height = cloud_b.height = cloud_c.height = 1;   // 无序点云
    cloud_a.points.resize(cloud_a.width * cloud_a.height);

    if (strcmp(argv[1], "-p") == 0)     // 判断argv[1]是否"-p", == 0 表示argv[1]为"-p"
    {
        cloud_b.width = 3;
        cloud_b.points.resize(cloud_b.width * cloud_b.height);
    }
    else
    {
        n_cloud_b.width = 5;            // 5个法线
        n_cloud_b.points.resize(n_cloud_b.width * n_cloud_b.height);
    }

    for (size_t i = 0; i < cloud_a.points.size(); ++i)
    {
        cloud_a.points[i].x = 1024 * rand() / (RAND_MAX + 1.0f);
        cloud_a.points[i].y = 1024 * rand() / (RAND_MAX + 1.0f);
        cloud_a.points[i].z = 1024 * rand() / (RAND_MAX + 1.0f);
    }
    if (strcmp(argv[1], "-p") ==0 )
    {
        for (size_t i = 0; i < cloud_b.size(); ++i)
        {
            cloud_b.points[i].x = 1024 * rand() / (RAND_MAX + 1.0f);
            cloud_b.points[i].y = 1024 * rand() / (RAND_MAX + 1.0f);
            cloud_b.points[i].z = 1024 * rand() / (RAND_MAX + 1.0f);
        }
    }
    else
    {
        for (size_t i = 0; i < n_cloud_b.size(); ++i)
        {
            n_cloud_b.points[i].normal[0] = 1024 * rand() / (RAND_MAX + 1.0f);
            n_cloud_b.points[i].normal[1] = 1024 * rand() / (RAND_MAX + 1.0f);
            n_cloud_b.points[i].normal[2] = 1024 * rand() / (RAND_MAX + 1.0f);
        }
    }

    // 输出Cloud A
    std::cerr << "Cloud A: " << std::endl;
    for (size_t i = 0; i < cloud_a.points.size(); ++i)
        std::cerr << "  " << cloud_a.points[i].x << " " << cloud_a.points[i].y << " " << cloud_a.points[i].z << std::endl;
    
    // 输出Cloud B
    std::cerr << "Cloud B: " << std::endl;
    if (strcmp(argv[1], "-p") == 0)     // 如果argv[1]为 "-p"
        for (size_t i = 0; i < cloud_b.points.size(); ++i)
            std::cerr << "  " << cloud_b.points[i].x << " " << cloud_b.points[i].y << " " << cloud_b.points[i].z << std::endl;
    else    // 输出 n_cloud_b
        for (size_t i = 0; i < n_cloud_b.points.size(); ++i)
            std::cerr << "  " << n_cloud_b.points[i].normal[0] << " " << n_cloud_b.points[i].normal[1] << " " << n_cloud_b.points[i].normal[2] << std::endl;

    if (strcmp(argv[1], "-p") == 0)
    {
        cloud_c = cloud_a;
        cloud_c += cloud_b;     // 把cloud_a和cloud_b连接一起创建cloud_c 并输出

        std::cerr << "Cloud C: " << std::endl;
        for (size_t i = 0; i < cloud_c.points.size(); ++i)
            std::cerr << "  " << cloud_c.points[i].x << " " << cloud_c.points[i].y << " " << cloud_c.points[i].z << std::endl;
    }

    return (0);
}