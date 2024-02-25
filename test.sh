#!/bin/bash

# 编译 maze.c 以生成可执行文件 maze
gcc maze.c -o maze

# 测试地图初始化功能
echo "Testing map initialization:"
if ./maze map.txt; then
    echo "Map initialization: PASS"
else
    echo "Map initialization: FAIL"
fi

# 测试地图显示功能
echo -e "\nTesting map display:"
if ./maze map.txt; then
    echo "Map display: PASS"
else
    echo "Map display: FAIL"
fi

# 测试玩家移动功能
echo -e "\nTesting player movement functionality:"
# 向上移动
echo "w" | ./maze map4.csv
# 向下移动
echo "s" | ./maze map4.csv
# 向左移动
echo "a" | ./maze map4.csv
# 向右移动
echo "d" | ./maze map4.csv

# 测试无效输入
echo -e "\nTesting invalid input:"
if ! echo "x" | ./maze map4.csv> /dev/null; then
    echo "Invalid input test: PASS"
else
    echo "Invalid input test: FAIL"
fi

# 测试到达终点功能
echo -e "\nTesting reaching the end functionality:"
# 移动到终点
if echo "wwwwd" | ./maze map4.csv; then
    echo "Reaching the end functionality: PASS"
else
    echo "Reaching the end functionality: FAIL"
fi

# 测试无法移动到指定位置
echo -e "\nTesting inability to move to specified position:"
# 将玩家移动到墙壁位置
if ! echo "www" | ./maze map4.csv > /dev/null; then
    echo "Inability to move to specified position: PASS"
else
    echo "Inability to move to specified position: FAIL"
fi

# 删除生成的可执行文件
rm maze

# 检查删除的退出状态码
if [ $? -eq 0 ]; then
    echo "Executable file 'maze' deleted successfully."
else
    echo "Failed to delete executable file 'maze'."
fi
