# main

- 解析命令行输入 ```parseCommandLine```
- 加载点云数据 ```Load clouds```
- 设置分辨率 ```Set up resolution invariance```
- 估计局部表面特征 ```Compute Normals```
- 点云降采样提取关键点 ```Downsample Clouds to Extract keypoints```
- 计算关键点描述子 ```Compute Descriptor for keypoints```
- 使用KdTree计算模型和场景之间的对应关系 ```Find Model-Scene Correspondences with KdTree```
    - For each scene keypoint descriptor, find nearest neighbor into the model keypoints descriptor cloud and add it to the correspondences vector.
- 聚类 ```Actual Clustering```
- 输出结果 ```Output results```
- 可视化 ```Visualization```