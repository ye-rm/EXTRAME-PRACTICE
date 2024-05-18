#!/bin/bash

# 查找并杀死所有包含 "client" 关键字的进程
pids=$(pgrep -f "client")

# 杀死每个找到的进程
for pid in $pids; do
    kill $pid
done

