# 波普特酒店管理系统

本项目适合只会C/C++的同学（根据身边统计学，大三还在这样写课设的组不多了，因为没有好本领😭），项目使用C++&Qt，没什么框架可言

适合摆烂，到了大三还只会c/c++，不愿意学新技术，只求通过这门课程的同学，不要指望这个能得高分，不建议拿这个联合验收，真不好拼起来

## 项目简介
北京邮电大学2021级计科软件工程大作业，酒店管理系统

实现了后台空调监控，房间内控制面板，房间入住退房（账单和详单生成），后台数据导出。

使用`C++&Qt`，支持`msvc`和`gcc`

## Quick Start
如使用`MSVC`,在`Visual Studio`中直接克隆项目，参考网络上的教程，配置好Qt环境（本项目使用`Qt6.7.1-msvc2019_64`）

在`CMakeList.txt`中，把

```cmake
if (WIN32)
set(CMAKE_PREFIX_PATH "C:/Qt/6.7.1/msvc2019_64")
endif ()
```

中的路径，修改为你电脑上的相应路径

在`src/common/common.h`中，修改

```c++
#define TEST_CONFIG_FILE 
#define SCHEDULER_CONFIG_FILE 
#define SOCKET_CONFIG_FILE 
#define SQLITE_FILE 
```

这几个宏定义的文件路径为你电脑上相应的路径

最好改一下，搞一个配置文件，让程序初始化的时候把这些参数读进来，我写死是因为我懒

之后右键`CMakeList.txt`，生成即可

如在Linux下构建项目，只需修改`common.h`中的文件路径，并通过包管理器安装`Qt6`开发环境及工具即可。

微软的MSVC是确认能行的，Linux我印象中可以跑，但或许会有问题。

允许`run.bat`可以同时以命令行形式启动服务端和5个客户端（可能需要修改其中可执行文件路径，自己去改）

如果允许提示缺少`Qt6`的某个`dll`，可在你Qt msvc环境的安装路径的`bin`目录下，在终端中运行

```powershell
PS C:\Qt\6.7.1\msvc2019_64\bin> .\windeployqt.exe ........\EXTRAME-PRACTICE\out\build\x64-debug\RoomService.exe
```

把后面的路径替换为你电脑上编译得到`exe`的相应路径即可

## 项目文件

```
C:.
├─gui
│  ├─data_manager
│  ├─monitor
│  ├─reception
│  └─room_client
│      ├─icon
│      └─qss
├─lib
│  ├─loguru
│  │  ├─cmake
│  │  ├─docs
│  │  ├─glog_bench
│  │  ├─glog_example
│  │  ├─loguru_bench
│  │  ├─loguru_cmake_example
│  │  ├─loguru_example
│  │  └─test
│  ├─rapidcsv
│  └─sqlite3pp
├─sqlite
├─src
│  ├─client
│  ├─common
│  └─server
└─test
```

`./gui`下为项目的`gui`实现，分别为数据导出，空调状态监控，前台，室内空调客户端界面

`./lib`下，`loguru`，`rapidcsv`和`sqlite3pp`分别提供日志，`csv`文件读取，数据库操作封装功能，`sqlite3pp`暂时没有使用

## 项目架构

本项目使用了`C++&Qt`实现，项目架构如下

![image-20240629104323725](https://typora-markdown-2003.obs.cn-north-4.myhuaweicloud.com/image-20240629104323725.png)

## 问题⚠️

- 计费会比预期少计一点（良心商家👍）
- 通信协议完全不可靠（高情商：把可靠性问题交给网络）
- 数据库操作没有进行封装（缺少课程中的数据持久层，换库就得改代码）
- 空调到达目标温度直接自动关机（优点：为用户省钱💰。缺点：用户半夜红温😡）
- 数据导出功能简陋（凑数做的）
- 界面简陋（除了那个室内空调使用界面，其余全是GPT的作品）
