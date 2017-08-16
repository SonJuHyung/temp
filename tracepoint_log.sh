#!/bin/bash 

echo 1 > /sys/kernel/debug/tracing/events/fat_log_lecture/fat_log_check/enable 
echo > /sys/kernel/debug/tracing/trace 
cp file.c inode.c test
cat /sys/kernel/debug/tracing/trace 
echo 0 > /sys/kernel/debug/tracing/events/fat_log_lecture/fat_log_check/enable 
