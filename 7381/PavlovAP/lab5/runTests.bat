@echo off
cl /EHsc .\Source\main.cpp
echo Test 1:
type .\Tests\Test1.txt
echo.
main < .\Tests\Test1.txt
echo.
echo Test 2:
type .\Tests\Test2.txt
echo.
main < .\Tests\Test2.txt
echo.
echo Test 3:
type .\Tests\Test3.txt
echo.
main < .\Tests\Test3.txt
echo.
echo Test 4:
type .\Tests\Test4.txt
echo.
main < .\Tests\Test4.txt
echo.
