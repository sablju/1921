#!/bin/bash

# 编译 maze.c 以生成可执行文件 maze
g++ maze.cpp -o maze

# 提示用户输入测试地图的名称
read -p "Enter the name of the test map file: " map_file

echo -e "~~ Testing Map File: $map_file ~~"

# 测试地图文件是否能够读取
echo -n "Testing map display: "
timeout 0.2s ./maze $map_file > tmp
if grep -q "Current Map:" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

# 删除临时文件
rm tmp
