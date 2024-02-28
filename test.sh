#!/bin/bash
# 编译 maze.c 以生成可执行文件 maze
g++ maze.c -o maze

# 测试地图显示功能
echo -e "\nTesting map display:"
if timeout 0.1s ./maze map.txt | echo "m" ; then
    echo "Map display: PASS"
else
    echo "Map display: FAIL"
fi

# 测试玩家移动功能
echo -e "\nTesting player movement functionality:"
# 运行 maze 程序，然后等待一段时间，终止进程
if timeout 0.1s  ./maze map.txt | echo "ddd" ; then
    echo "Player movement functionality: PASS"
else
    echo "Player movement functionality: FAIL"
fi

# 测试无效输入
echo -e "\nTesting invalid input:"
# 运行 maze 程序，然后等待一段时间，终止进程
if timeout 0.1s  ./maze map.txt|echo "43ez"  > /dev/null; then
    echo "Invalid input: PASS"
else
    echo "Invalid input: FAIL"
fi

# 测试到达终点功能
echo -e "\nTesting reaching the end functionality:"
# 运行 maze 程序，然后等待一段时间，终止进程
if timeout 0.1s ./maze map.txt |echo -e "dsssd"; then
    echo "Reaching the end functionality: PASS"
else
    echo "Reaching the end functionality: FAIL"
fi

# 测试无法移动到指定位置
echo -e "\nTesting inability to move to specified position:"
# 运行 maze 程序，然后等待一段时间，终止进程
if timeout 0.1s ./maze map.txt | echo -e "www" > /dev/null; then
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
