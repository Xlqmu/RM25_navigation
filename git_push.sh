#!/bin/bash

# 提交更改
git add .

# 检查是否有变更需要提交
if git diff --cached --quiet; then
    echo "没有需要提交的更改。"
else
    git commit -m "main"
    if [ $? -ne 0 ]; then
        echo "提交失败，请检查错误信息。"
        exit 1
    fi
    echo "更改已提交。"
fi

# 推送到远程主分支
echo "正在推送到远程主分支..."
git push origin main
if [ $? -ne 0 ]; then
    echo "推送失败，请检查网络连接和远程仓库配置。"
    exit 1
fi
echo "推送成功。"

# 获取远程标签列表并排除带有 ^{} 的标签
echo "正在获取远程标签..."
git fetch --tags
if [ $? -ne 0 ]; then
    echo "获取远程标签失败。"
    exit 1
fi

# 获取远程仓库的最新标签，排除 ^{}
latest_tag=$(git ls-remote --tags origin | awk '{print $2}' | grep -E 'refs/tags/v[0-9]+\.[0-9]+\.[0-9]+$' | sort -V | tail -n1 | sed 's|refs/tags/||')

if [ -z "$latest_tag" ]; then
    # 如果没有标签，初始化为 v1.0.0
    new_tag="v1.0.0"
else
    echo "最新的远程标签是 $latest_tag"
    # 移除 'v' 前缀
    version=${latest_tag#v}
    major=$(echo "$version" | cut -d. -f1)
    minor=$(echo "$version" | cut -d. -f2)
    patch=$(echo "$version" | cut -d. -f3)

    # 询问用户选择增加主版本号、次版本号、还是取消操作
    echo "请选择要执行的操作："
    echo "1) 增加主版本号 (从 v$major.$minor.$patch 到 v$((major + 1)).0.0)"
    echo "2) 增加次版本号 (从 v$major.$minor.$patch 到 v$major.$((minor + 1)).0)"
    echo "3) 取消推送和创建标签"
    read -p "请输入选项编号 (1、2 或 3)： " choice

    case "$choice" in
        1)
            major=$((major + 1))
            minor=0
            patch=0
            ;;
        2)
            minor=$((minor + 1))
            patch=0
            ;;
        3)
            echo "已取消推送和创建标签。"
            exit 0
            ;;
        *)
            echo "无效的选项。请重新运行脚本并选择 1、2 或 3。"
            exit 1
            ;;
    esac

    new_tag="v${major}.${minor}.${patch}"
fi

echo "将创建新标签: $new_tag"

# 检查新标签是否已存在（防止重复）
if git rev-parse "$new_tag" >/dev/null 2>&1; then
    echo "标签 $new_tag 已存在。"
    exit 1
fi

# 创建新标签
git tag -a "$new_tag" -m "$new_tag"
if [ $? -ne 0 ]; then
    echo "标签创建失败。"
    exit 1
fi
echo "已创建标签 $new_tag。"

# 推送新标签到远程仓库
echo "正在推送标签 $new_tag 到远程仓库..."
git push origin "$new_tag"
if [ $? -ne 0 ]; then
    echo "标签推送失败。"
    exit 1
fi
echo "标签 $new_tag 已成功推送到远程仓库。"