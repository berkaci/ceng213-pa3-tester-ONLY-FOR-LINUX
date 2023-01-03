#!/bin/bash
g++ -O0 main-man.cpp
./a.out
g++ -O0 main-facem.cpp
./a.out
g++ -O0 main-tux.cpp
./a.out

mkdir your_outputs your_outputs/man-low your_outputs/facem-low2 your_outputs/Tux

cd your_outputs
passed=0
for i in */*
do
	if cmp -s "$i" "../outputs/$i"
	then
		passed=$((passed+1))
	else
		echo different
		echo $i
	fi
done
echo "total:"
echo 1106
echo "passed:"
echo $passed

