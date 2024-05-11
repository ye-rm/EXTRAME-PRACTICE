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

set(LOGURU_WITH_STREAMS TRUE)
add_subdirectory(lib/loguru) # defines target 'loguru::loguru'

add_compile_options(-l sqlite3)

add_library(db ./sqlite/sqlite3.c)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

add_library(socket
        ./src/common/socket.cpp
        ./src/common/socket.h
        lib/rapidcsv/rapidcsv.h)

if (WIN32)
    target_link_libraries(socket ws2_32)
endif (WIN32)
target_link_libraries(socket loguru::loguru)

add_library(service
        ./src/server/service.h
        ./src/server/service.cpp
        ./sqlite/sqlite3.h
)
target_link_libraries(service db)

add_library(server
        src/server/scheduler.cpp
        src/server/scheduler.h
)
target_link_libraries(server service)

add_library(client
        ./src/client/client.cpp
        ./src/client/client.h
        ./lib/rapidcsv/rapidcsv.h
)

add_executable(SERVER_SIDE src/main.cpp)
target_link_libraries(SERVER_SIDE PRIVATE loguru::loguru)

add_executable(service_test ./src/server/service_test.cpp)
target_link_libraries(service_test service loguru::loguru)

add_executable(server_test ./src/server/server_test.cpp)
target_link_libraries(server_test server socket)

add_executable(client_test ./src/client/client_test.cpp)
target_link_libraries(client_test client socket)

add_executable(socket_test ./src/common/socket_test.cpp)
target_link_libraries(socket_test socket)
# 包含子项目。

enable_testing()
add_test(NAME socket_test COMMAND socket_test)
add_test(NAME server_test COMMAND server_test)
add_test(NAME service_test COMMAND service_test)