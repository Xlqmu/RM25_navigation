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

# 获取远程标签列表并排除本地未获取的标签
echo "正在获取远程标签..."
git fetch --tags
if [ $? -ne 0 ]; then
    echo "获取远程标签失败。"
    exit 1
fi

# 获取远程仓库的最新标签
latest_tag=$(git ls-remote --tags origin | awk '{print $2}' | grep -E 'refs/tags/v[0-9]+\.[0-9]+' | sort -V | tail -n1 | sed 's|refs/tags/||')

if [ -z "$latest_tag" ]; then
    # 如果没有标签，初始化为 v1.0
    new_tag="v1.0"
else
    echo "最新的远程标签是 $latest_tag"
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