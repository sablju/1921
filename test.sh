#!/bin/bash

g++ maze.c -o maze

arg0="student_mazes/valid/reg_5x5.txt"
arg1="student_mazes/valid/reg_10x6.txt"
arg2="student_mazes/valid/reg_15x8.txt"
arg3="q"
arg4="w"
arg5="a"
arg6="d"
arg7="s"
arg8="m"

echo -e "~~ Argument Tests ~~"

echo -n "Testing no arguments - "
# 编译 maze.c 以生成可执行文件 maze
./maze > tmp
if grep -q "Usage: ./maze <map_file>" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Testing 2 arguments - "
./maze x x > tmp
if grep -q "Usage: ./maze <map_file>" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -e "\n~~ File Handling~~"

echo -n "Testing Error opening file - "
./maze nomap.txt > tmp
if grep -q "Error: Error opening file: nomap.txt" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Testing bad data (too low) - "
timeout 0.2s ./maze student_mazes/invalid/ireg_width_5x5.txt > tmp
if grep -q "ERROR:Wrong number of cols !!!" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -n "Testing bad data (too high) - "
timeout 0.2s ./maze student_mazes/invalid/ireg_height_5x5.txt > tmp
if grep -q "ERROR:Wrong number of rows !!!" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -e "\n~~ Success ~~"

echo -e "\nTesting map display:"
timeout 0.2s ./maze student_mazes/valid/reg_5x5.txt $arg8 > tmp
if grep -q "Current Map:" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi


echo -e "\nTesting player movement functionality:"
timeout 0.2s  ./maze $arg1 $arg5 > tmp 
if grep -q "Exiting the game. Goodbye !!!" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi


# 测试到达终点功能
echo -e "\nTesting reaching the end functionality:"
timeout 0.2s ./maze $arg1 $arg5 $arg4 $arg4 $arg4 $arg4 > tmp 
if grep -q "Congratulations! You win!" tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

echo -e "\nTesting reaching the end functionality:"
timeout 0.2s ./maze $arg3 $arg5 > tmp 
if grep -q "Invalid move. Use 'w', 'a', 's', or 'd'. " tmp;
then
    echo "PASS"
else
    echo "FAIL"
fi

# 删除生成的可执行文件
#rm maze

# 检查删除的退出状态码
if [ $? -eq 0 ]; then
    echo "Executable file 'maze' deleted successfully."
else
    echo "Failed to delete executable file 'maze'."
fi
