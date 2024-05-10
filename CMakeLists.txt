# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required(VERSION 3.8)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif ()

project("EXTRAME-PRACTICE")

add_subdirectory("./src/common/OpenXLSX")

add_library(socket
        ./src/common/socket.cpp
        ./src/common/socket.h
        ./src/common/rapidcsv.h)
if (WIN32)
    target_link_libraries(socket ws2_32)
endif (WIN32)

add_library(service
        ./src/server/service.h
        ./src/server/service.cpp
)

add_library(server
        src/server/scheduler.cpp
        src/server/scheduler.h
)

add_library(client
        ./src/client/client.cpp
        ./src/client/client.h
)

add_executable(SERVER_SIDE src/main.cpp)
target_link_libraries(server)

add_executable(socket_test ./src/common/socket_test.cpp)
target_link_libraries(socket_test socket)
# 包含子项目。

enable_testing()
add_test(NAME socket_test COMMAND socket_test)