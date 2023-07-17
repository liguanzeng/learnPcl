# learnPcl

## 编译方式

```bash
mkdir build
cd build
cmake .. // 对上一级进行编译
make  // 生成可执行文件命令
./executedemo  // 运行可执行文件
```
## 包含内容

1. 去噪滤波
2. 分类
3. 目标检测与识别
4. 点云配准

## Filter

1. PassThrough 直通滤波器
2. VoxelGrid   体素滤波器

## Serach

1. KdTree
   1. K nearest neighbor
   2. Neighbors within radius

## Key points

1. NARF
2. SIFT
3. FAST

## Registration

> 将各种3D点云数据视图一致对齐到完整模型中的问题称为配准;其强依赖于 key points.

### 成对配准的步骤

1. 从一组点中,确定最能代表两个数据集中场景的 key points;
2. 在每个关键点,计算一个特征描述符;
3. 从特征描述符及其在两个数据集中的XYZ位置,根据特征和位置之间的相似性估计一组对应关系;
4. 鉴于数据是有噪声的,并非所有的通信都有效,故在配准过程中应拒绝哪些不良的数据(离群);
5. 从剩余的良好对应关系集中,估计运动变换.