# 波普特酒店管理系统极限编程实践

## 项目简介
很急，一会再编

## 项目结构
- `CMakeLists.txt`：CMake配置文件
- `README.md`：项目说明文件
- `src`：源代码目录
  - `main.cpp`：主程序入口
  - `server`：服务端代码目录
    - `air_conditioner_schedule.cpp`：空调调度对象代码
    - `air_conditioner_schedule.h`：空调调度对象
    - `air_condition_service.cpp`：空调服务对象代码
    - `air_condition_service.h`：空调服务对象 
    - `server.cpp`：服务端主程序
    - `server.h`：服务端头文件
    - 'server_test.cpp'：服务端测试代码
  - `client`：客户端代码目录
    - 使用web实现
  - `common`：公共代码目录
    - `socket.cpp`：套接字操作代码
    - `socket.h`: 套接字操作头文件
    - `database.c`: 数据库
    - `database.h`: 数据库头文件
- `test`：测试代码目录
  - `cooling.cpp`：测试降温功能
  - `heating.cpp`：测试升温功能 
  - `test_air_conditioner_schedule.cpp`：空调调度对象测试代码
  - `test_air_condition_service.cpp`：空调服务对象测试代码
  - `test_socket.cpp`：套接字操作测试代码