#include <iostream>
#include <string>
#include <rclcpp/rclcpp.hpp>
#include <geometry_msgs/msg/twist.hpp>
#include <nav_msgs/msg/odometry.hpp>
#include <tf2_ros/transform_listener.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.hpp>
#include <termios.h>
#include <unistd.h>
#include <chrono>

#define UNIT_ANGLE 180 / 3.14159  // 将弧度转换为角度

// 默认速度
double rotation_vel = 20.0;  // 旋转速度
double linear_vel = 0.5;    // 线速度
double lateral_vel = 0.5;   // 横向速度（左右移动）
double publish_rate = 10.0; // 发布频率 (Hz)
geometry_msgs::msg::Vector3 rpy;
tf2::Quaternion q_msg;
double roll, pitch, yaw, i_yaw, m_yaw = 0;

enum ControlMode {
    LINEAR,
    GYRO
};

class ControlPublisherNode : public rclcpp::Node {
public:
    ControlPublisherNode() : Node("control_publisher") {
        // 创建发布者
        control_pub_chassis_ = this->create_publisher<geometry_msgs::msg::Twist>("/cmd_vel_chassis", 10);
        control_pub_mecanum_ = this->create_publisher<geometry_msgs::msg::Twist>("/mecanum_controller", 10);
        
        // 创建订阅者获取里程计数据
        pose_sub_ = this->create_subscription<nav_msgs::msg::Odometry>(
            "/odom", 10, std::bind(&ControlPublisherNode::poseCallback, this, std::placeholders::_1));

        // 打印帮助信息
        printHelp();
    }

    void poseCallback(const nav_msgs::msg::Odometry::SharedPtr odom) {
        tf2::Quaternion q_msg;
        tf2::fromMsg(odom->pose.pose.orientation, q_msg);
        tf2::Matrix3x3(q_msg).getRPY(roll, pitch, yaw);
    }

// 控制循环函数，发布消息
void controlLoop() {
    geometry_msgs::msg::Twist control_msg;
    rclcpp::WallRate loop_rate(publish_rate);  // 控制发布频率
    ControlMode mode = LINEAR;  // 默认进入线性控制模式

    // 持续发布控制消息
    while (rclcpp::ok()) {
        char key = getKey();  // 获取键盘输入
        updateVelocity(key);  // 更新控制速度

        // 急停，停止所有运动
        if (key == 't') {
            control_msg.linear.x = 0.0;
            control_msg.linear.y = 0.0;
            control_msg.angular.z = 0.0;
            mode = LINEAR;  // 急停后恢复为线性控制模式
            RCLCPP_INFO(this->get_logger(), "Emergency Stop Activated.");
        }

        // 线性控制模式
        if (mode == LINEAR) {
            if (key == 'i') {
                control_msg.linear.x = linear_vel;  // 前进
            } else if (key == 'k') {
                control_msg.linear.x = -linear_vel; // 后退
            } else if (key == 'j') {
                control_msg.linear.y = lateral_vel; // 向左横向移动
            } else if (key == 'l') {
                control_msg.linear.y = -lateral_vel; // 向右横向移动
            } else if (key == 'u') {
                mode = GYRO;  // 切换到小陀螺模式
                control_msg.angular.z = rotation_vel;  // 向左旋转
            } else if (key == 'o') {
                mode = GYRO;  // 切换到小陀螺模式
                control_msg.angular.z = -rotation_vel;  // 向右旋转
            }
        }

        // 小陀螺模式
        else if (mode == GYRO) {
            if (key == 'i' || key == 'k' || key == 'j' || key == 'l') {
                mode = LINEAR;  // 切换到线性控制模式
                control_msg.linear.x = 0.0;
                control_msg.linear.y = 0.0;
            } else if (key == 'u') {
                control_msg.angular.z = rotation_vel;  // 向左旋转
            } else if (key == 'o') {
                control_msg.angular.z = -rotation_vel;  // 向右旋转
            }
        }

        // 发布控制消息到两个话题
        control_pub_chassis_->publish(control_msg);
        control_pub_mecanum_->publish(control_msg);

        // 打印日志
        RCLCPP_INFO(this->get_logger(), "Mode: %s, Linear Velocity: %.2f, Angular Velocity: %.2f, Timestamp: %ld",
                    mode == LINEAR ? "LINEAR" : "GYRO", linear_vel, rotation_vel, this->now().nanoseconds());

        // 控制发布频率，避免发布过快
        loop_rate.sleep();
    }
}

    // 更新速度参数
    void updateVelocity(char key) {
        if (key == 'w') {
            linear_vel += 0.1;    // 增加线速度
        } else if (key == 's') {
            linear_vel = std::max(0.1, linear_vel - 0.1);   // 减少线速度
        }

        if (key == 'a') {
            lateral_vel += 0.1;   // 增加横向速度
        } else if (key == 'd') {
            lateral_vel = std::max(0.1, lateral_vel - 0.1);  // 减少横向速度
        }

        if (key == 'q') {
            rotation_vel += 0.1;   // 增加角速度
        } else if (key == 'e') {
            rotation_vel = std::max(0.1, rotation_vel - 0.1);  // 减少角速度
        }
    }

private:
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr control_pub_chassis_;
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr control_pub_mecanum_;
    rclcpp::Subscription<nav_msgs::msg::Odometry>::SharedPtr pose_sub_;

    // 打印帮助信息
    void printHelp() {
        std::cout << "Control Instructions:\n";
        std::cout << "----------------------------------\n";
        std::cout << "w - Increase linear velocity (forward)\n";
        std::cout << "s - Decrease linear velocity (backward)\n";
        std::cout << "a - Increase lateral velocity (left/right)\n";
        std::cout << "d - Decrease lateral velocity (left/right)\n";
        std::cout << "q - Increase angular velocity (rotate)\n";
        std::cout << "e - Decrease angular velocity (rotate)\n";
        std::cout << "i - Move forward\n";
        std::cout << "k - Move backward\n";
        std::cout << "j - Move left\n";
        std::cout << "l - Move right\n";
        std::cout << "u - Rotate counterclockwise\n";
        std::cout << "o - Rotate clockwise\n";
        std::cout << "t - Emergency stop\n";
        std::cout << "p - Exit\n";
        std::cout << "----------------------------------\n";
    }

    // 获取键盘输入
    char getKey() {
        struct termios oldt, newt;
        char ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);    // 禁用规范模式和回显
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // 恢复原设置
        return ch;
    }
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ControlPublisherNode>();
    node->controlLoop();  // 启动控制循环
    rclcpp::shutdown();
    return 0;
}
