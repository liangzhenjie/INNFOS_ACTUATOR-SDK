#!/bin/sh

exe="libmotorsControll.so.1"
des=$PWD

deplist=$(ldd $exe | awk '{if(match($3,"/")){printf("%s "),$3 } }')
echo $deplist
cp $deplist $des
