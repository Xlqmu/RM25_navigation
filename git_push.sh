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

# 获取最新的标签
latest_tag=$(git describe --tags $(git rev-list --tags --max-count=1))

if [ -z "$latest_tag" ]; then
    # 如果没有标签，初始化为 v1.0
    new_tag="v1.0"
else
    # 移除 'v' 前缀
    version=${latest_tag#v}
    major=$(echo $version | cut -d. -f1)
    minor=$(echo $version | cut -d. -f2)

    # 增加次版本号
    minor=$((minor + 1))

    # 如果次版本号达到10，重置为0并增加主版本号
    if [ $minor -ge 10 ]; then
        minor=0
        major=$((major + 1))
    fi

    new_tag="v${major}.${minor}"
fi

# 创建新标签
git tag -a "$new_tag" -m "$new_tag"
if [ $? -ne 0 ]; then
    echo "标签创建失败。"
    exit 1
fi
echo "已创建标签 $new_tag。"

# 推送新标签到远程仓库
git push origin "$new_tag"
if [ $? -ne 0 ]; then
    echo "标签推送失败。"
    exit 1
fi
echo "标签 $new_tag 已成功推送到远程仓库。"