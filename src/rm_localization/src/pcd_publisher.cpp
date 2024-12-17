#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/point_cloud2.hpp>
#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>
#include <pcl_conversions/pcl_conversions.h>

class PCDPublisher : public rclcpp::Node {
public:
    PCDPublisher() : Node("pcd_publisher") {
        publisher_ = this->create_publisher<sensor_msgs::msg::PointCloud2>("pcd_points", 10);

        // 加载 PCD 文件
        pcl::PointCloud<pcl::PointXYZI>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZI>());
        if (pcl::io::loadPCDFile<pcl::PointXYZI>("your_file.pcd", *cloud) == -1) {
            RCLCPP_ERROR(this->get_logger(), "Couldn't read the PCD file");
            return;
        }

        RCLCPP_INFO(this->get_logger(), "Loaded PCD file with %d points", cloud->size());

        // 转换为 ROS 点云格式
        sensor_msgs::msg::PointCloud2 output;
        pcl::toROSMsg(*cloud, output);
        output.header.frame_id = "map";

        // 定时发布
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(100),
            [this, output]() mutable {
                publisher_->publish(output);
            });
    }

private:
    rclcpp::Publisher<sensor_msgs::msg::PointCloud2>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<PCDPublisher>());
    rclcpp::shutdown();
    return 0;
}

