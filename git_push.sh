#!/bin/bash

# 提交更改
git add .
git commit -m "main"

# 使用 sshpass 自动输入密码
sshpass -p '123' git push origin main

# 获取最新的标签
latest_tag=$(git describe --tags `git rev-list --tags --max-count=1`)

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
git tag -a $new_tag -m "$new_tag"

# 推送新标签到远程仓库
sshpass -p '123' git push origin $new_tag