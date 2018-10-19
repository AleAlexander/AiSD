#!/bin/bash
g++ ./Source/main.cpp ./Source/functions.cpp -o Lab
echo 'Test 1:'
cat ./Tests/Test1.txt
echo '\n'
./Lab < ./Tests/Test1.txt
echo '\n'
echo 'Test 2:'
cat ./Tests/Test2.txt
echo '\n'
./Lab < ./Tests/Test2.txt
echo '\n'
echo 'Test 3:'
cat ./Tests/Test3.txt
echo '\n'
./Lab < ./Tests/Test3.txt
echo '\n'
echo 'Test 4:'
cat ./Tests/Test4.txt
echo '\n'
./Lab < ./Tests/Test4.txt
echo '\n'
echo 'Test 5:'
cat ./Tests/Test5.txt
echo '\n'
./Lab < ./Tests/Test5.txt
echo '\n'