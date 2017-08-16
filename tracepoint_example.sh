#!/bin/bash 

echo > /sys/kernel/debug/tracing/trace 

echo 1 > /sys/kernel/debug/tracing/events/fat_log_lecture/fat_ent_new_write/enable 
echo fat_ent_write > /sys/kernel/debug/tracing/set_ftrace_filter 
echo function_graph > /sys/kernel/debug/tracing/current_tracer 

#fio --output=/home/fs-lecture/lecture/result/test.txt --directory=./test --name=test --rw=randwrite --size=20K
cp file.c ./test
cat /sys/kernel/debug/tracing/trace 

echo nop > /sys/kernel/debug/tracing/current_tracer  
echo > /sys/kernel/debug/tracing/set_ftrace_filter 
echo 0 > /sys/kernel/debug/tracing/events/fat_log_lecture/fat_ent_new_write/enable  




