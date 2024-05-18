#!/bin/bash

# 启动 client1
./out/build/linux-debug/client1 &

# 启动 client2
./out/build/linux-debug/client2 &

# 启动 client3
./out/build/linux-debug/client3 &

# 启动 client4
./out/build/linux-debug/client4 &

# 启动 client5
./out/build/linux-debug/client5 &

# 等待所有程序执行完成
wait