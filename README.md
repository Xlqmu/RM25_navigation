### 25赛季导航方案
###
	
	sudo apt install ros-humble-gazebo-ros-pkgs


### 思路
使用fast_lio获得3D里程计
重定位：回环检测
对mid360进行点云分割，分割为地面(坡，台阶)和障碍物(动态)



-src
---rm_robot_description:机器人模型（采用一个四轮差速小车就行，全向轮后面再说）
### 导航构思

#### 需求：

1. 建图算法(cartographer) ->建图过程很慢 (因为它没有采用loop close ，所以导致建图速度不能太快，否则会出现飘的情况) -> 考虑换一个比较新的算法或者考虑加一个loop close
2. 定位算法:fast_lio
3. 导航算法nav2为框架

#### 硬件资源：

1. mid360
2. 大恒相机(自瞄模块)

#### 初步定位：

1. 能够上坡
2. 动态避障(全兵种)
3. 基于行为树的决策

#### 框架：

##### 感知：
1. mid360
2. 大恒相机
##### 定位:
amcl/fast_lio2
##### 建图:
fast_lio
##### 路径规划:
全局规划+局部动态避障

Hybrid A* + DWA/TEB
##### 导航:
nav2
##### 点云分割:
point_lio

-nav_bringup(启动相机程序、串口程序、自瞄程序和robot_state_publisher,参考rm_version)
-interfaces(自定义msg和srv)
-robot_description(机器人的urdf)
-autoaim(自瞄算法)
-nav2(nav2的launch和参数)
--src(nav2的参数)
--third_party(TEB算法)
-perception(处理传感器的算法)
--IMU
--点云分割
--pointcloud_to_lasercan(将Pointcloud转换为Laserscan)
-drive(传感器驱动)
--camera_driver(传感器的驱动，雷达和大恒)
--serial_driver(和下位机进行通信的串口驱动程序，参考rmoss开源)
--livox_ros_driver(mid360驱动)


#### 问题

1. 定位误差累积，导致与实际值产生偏差(闭环问题) -> 捆绑调整
2. 

#### 仿真平台

1. ros2 humble
2. rviz2
3. gazebo


解决了仿真包的导入，将各个launch文件分割成子launch文件
尝试接入fastlio接口进行定位算法开发