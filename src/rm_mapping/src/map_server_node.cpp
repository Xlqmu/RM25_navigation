#include <rclcpp/rclcpp.hpp>
#include <nav_msgs/msg/occupancy_grid.hpp>
#include <sensor_msgs/msg/laser_scan.hpp>
#include <mp2p_icp/metricmap.h>
#include "../include/map_server_node.h" // 假设 map_server_node.h 提供了加载地图的功能

class MapServerNode : public rclcpp::Node {
public:
    MapServerNode() : Node("map_server_node") {
        // 发布 map 话题
        map_pub = this->create_publisher<nav_msgs::msg::OccupancyGrid>("map", 10);

        // 订阅 /scan 话题
        scan_sub = this->create_subscription<sensor_msgs::msg::LaserScan>(
            "/scan", 10, std::bind(&MapServerNode::scanCallback, this, std::placeholders::_1));

        // 加载静态地图
        loadMap();
    }

private:
    void loadMap() {
        // 假设 map_server.h 提供了一个函数 loadMapFromFile 来加载地图
        nav_msgs::msg::OccupancyGrid map;
        if (loadMapFromFile("path_to_map_file.yaml", map)) {
            map_pub->publish(map);
        } else {
            RCLCPP_ERROR(this->get_logger(), "Failed to load map");
        }
    }

    void scanCallback(const sensor_msgs::msg::LaserScan::SharedPtr scan) {
        // 处理 /scan 话题的回调函数
        RCLCPP_INFO(this->get_logger(), "Received a scan");
        // 在这里添加处理激光扫描数据的代码
    }

    rclcpp::Publisher<nav_msgs::msg::OccupancyGrid>::SharedPtr map_pub;
    rclcpp::Subscription<sensor_msgs::msg::LaserScan>::SharedPtr scan_sub;
};

int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<MapServerNode>());
    rclcpp::shutdown();
    return 0;
}