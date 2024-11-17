#!/bin/bash

# 获取当前工作空间的 src 目录
WORKSPACE_SRC="$(pwd)/src"

# 检查 src 目录是否存在
if [ ! -d "$WORKSPACE_SRC" ]; then
    echo "错误: 未找到 src 目录。请确保在 ROS 工作空间的根目录下运行此脚本。"
    return 1 2>/dev/null || exit 1
fi

# 检索所有功能包
packages=($(colcon list --names-only))

# 检查是否有功能包
if [ ${#packages[@]} -eq 0 ]; then
    echo "未在 src 目录中找到任何功能包。"
    return 1 2>/dev/null || exit 1
fi

echo "请选择要构建的选项："
echo "0) 构建整个工作空间"

# 列出所有功能包
for i in "${!packages[@]}"; do
    echo "$((i+1))) ${packages[$i]}"
done

# 添加放弃构建的选项
abandon_option=$(( ${#packages[@]} + 1 ))
echo "$abandon_option) 放弃构建"

# 读取用户输入
read -p "请输入编号（例如 0 或 1-${abandon_option}）: " choice

# 验证输入是否为数字
if ! [[ "$choice" =~ ^[0-9]+$ ]]; then
    echo "无效输入: 请输入一个数字。"
    return 1 2>/dev/null || exit 1
fi

# 构建整个工作空间
if [ "$choice" -eq 0 ]; then
    echo "正在构建整个工作空间..."
    colcon build
    if [ $? -eq 0 ]; then
        echo "构建成功，正在 source 工作空间..."
        source install/setup.bash
    else
        echo "构建失败，请检查错误信息。"
        return 1 2>/dev/null || exit 1
    fi
    return 0 2>/dev/null || exit 0
fi

# 构建特定的功能包
if [ "$choice" -ge 1 ] && [ "$choice" -le "${#packages[@]}" ]; then
    selected_package=${packages[$((choice-1))]}
    echo "正在构建功能包: $selected_package"
    colcon build --packages-select "$selected_package"
    if [ $? -eq 0 ]; then
        echo "构建成功，正在 source 工作空间..."
        source install/setup.bash
    else
        echo "构建失败，请检查错误信息。"
        return 1 2>/dev/null || exit 1
    fi
    return 0 2>/dev/null || exit 0
fi

# 放弃构建选项
if [ "$choice" -eq "$abandon_option" ]; then
    echo "已选择放弃构建。"
    return 0 2>/dev/null || exit 0
fi

# 输入编号超出范围
echo "无效选择: 请输入 0 或 1-${abandon_option}。"
return 1 2>/dev/null || exit 1