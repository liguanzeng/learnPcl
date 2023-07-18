// 如何从点云和给定传感器位置创建范围图像，该代码创建一个浮动在观察者前面的矩形的示例点云

#include <pcl/range_image/range_image.h>

int main () {
  pcl::PointCloud<pcl::PointXYZ> pointCloud;
  
  // Generate the data
  for (float y=-0.5f; y<=0.5f; y+=0.01f) {
    for (float z=-0.5f; z<=0.5f; z+=0.01f) {
      pcl::PointXYZ point;
      point.x = 2.0f - y;
      point.y = y;
      point.z = z;
      pointCloud.push_back(point);
    }
  }
  pointCloud.width = pointCloud.size();
  pointCloud.height = 1;
  
  // We now want to create a range image from the above point cloud, with a 1deg angular resolution
  float angularResolution = (float) (  1.0f * (M_PI/180.0f));  //   1.0 degree in radians
  float maxAngleWidth     = (float) (360.0f * (M_PI/180.0f));  // 360.0 degree in radians
  float maxAngleHeight    = (float) (180.0f * (M_PI/180.0f));  // 180.0 degree in radians

  //sensorPose将虚拟传感器的6自由度位置定义为原点，roll=pitch=yaw=0
  Eigen::Affine3f sensorPose = (Eigen::Affine3f)Eigen::Translation3f(0.0f, 0.0f, 0.0f);

  //coordinate_frame=CAMERA_FRAME 告诉系统x 朝右，y 朝下，z 轴向前。另一种选择是LASER_FRAME，x 朝前，y 朝左，z 朝上
  pcl::RangeImage::CoordinateFrame coordinate_frame = pcl::RangeImage::CAMERA_FRAME;

  float noiseLevel=0.00;    //对于噪声级别=0,范围图像是使用普通的z缓冲区创建的.但是,如果要对落在同一单元格中的点求平均值，则可以使用更高的值. 0.05 表示,所有与最近点的最大距离为 5cm 的点都用于计算范围
  float minRange = 0.0f;    //如果 minRange 大于 0,则将忽略所有较近的点
  int borderSize = 1;       //borderSize 大于 0 将在裁剪图像时在图像周围留下未观察到的点的边框
  
  pcl::RangeImage rangeImage;
  rangeImage.createFromPointCloud(pointCloud, angularResolution, maxAngleWidth, maxAngleHeight,
                                  sensorPose, coordinate_frame, noiseLevel, minRange, borderSize);
  
  std::cout << rangeImage << "\n";
}