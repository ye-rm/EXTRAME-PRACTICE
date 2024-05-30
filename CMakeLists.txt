# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required(VERSION 3.5)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
    cmake_policy(SET CMP0141 NEW)
    set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif ()

project("EXTRAME-PRACTICE")

set(LOGURU_WITH_STREAMS TRUE)
add_subdirectory(lib/loguru) # defines target 'loguru::loguru'

# set up qt environment
set(CMAKE_CXX_STANDARD 17)
if (WIN32)
set(CMAKE_PREFIX_PATH "C:/Qt/6.7.1/msvc2019_64")
endif ()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


find_package(Qt6 COMPONENTS Core Widgets Sql REQUIRED)

# set up sqlite3
add_library(db ./sqlite/sqlite3.c)

# socket library for scheduler and client
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
        ./src/common/common.h
)
target_link_libraries(service db loguru::loguru)



add_library(server
        src/server/scheduler.cpp
        src/server/scheduler.h
        lib/rapidcsv/rapidcsv.h
        src/common/common.h
)
target_link_libraries(server service socket)

add_library(client
        ./src/client/client.cpp
        ./src/client/client.h
        ./lib/rapidcsv/rapidcsv.h
        ./src/common/common.h
)

target_link_libraries(client socket)

add_executable(RoomService gui/reception/RoomService.cpp gui/reception/RoomService.h gui/reception/RoomService.ui gui/reception/BillWindow.cpp gui/reception/BillWindow.h gui/reception/AirConditionDetailsWindow.h gui/reception/AirConditionDetailsWindow.cpp)
target_link_libraries(RoomService Qt6::Core Qt6::Widgets Qt6::Sql db)

add_executable(airc gui/room_client/main.cpp gui/room_client/mainwindow.cpp gui/room_client/mainwindow.h gui/room_client/mainwindow.ui gui/room_client/airconditioneroptthread.cpp gui/room_client/airconditioneroptthread.h gui/room_client/gettemperaturethread.cpp gui/room_client/gettemperaturethread.h gui/room_client/qrc.qrc)
target_link_libraries(airc Qt6::Core Qt6::Widgets client)

add_executable(monitor gui/monitor/main.cpp gui/monitor/MainWindow.cpp gui/monitor/MainWindow.h)
target_link_libraries(monitor Qt6::Core Qt6::Widgets service server)

add_executable(data_manager gui/data_manager/main.cpp gui/data_manager/mainwindow.cpp gui/data_manager/mainwindow.h lib/rapidcsv/rapidcsv.h)
target_link_libraries(data_manager Qt6::Core Qt6::Widgets db)

add_executable(service_test ./src/server/service_test.cpp)
target_link_libraries(service_test service loguru::loguru)

add_executable(server_test ./src/server/server_test.cpp)
target_link_libraries(server_test server socket)

add_executable(client_test ./src/client/client_test.cpp)
target_link_libraries(client_test client socket)

add_executable(socket_test ./src/common/socket_test.cpp)
target_link_libraries(socket_test socket)

add_executable(client1 ./test/client1.cpp)
target_link_libraries(client1 client)

add_executable(client2 ./test/client2.cpp)
target_link_libraries(client2 client)

add_executable(client3 ./test/client3.cpp)
target_link_libraries(client3 client)

add_executable(client4 ./test/client4.cpp)
target_link_libraries(client4 client)

add_executable(client5 ./test/client5.cpp)
target_link_libraries(client5 client)

add_executable(manager_test ./src/manager/managertest.cpp)
# 包含子项目。

enable_testing()
add_test(NAME client_ui COMMAND client_ui)
add_test(NAME socket_test COMMAND socket_test)
add_test(NAME server_test COMMAND server_test)
add_test(NAME service_test COMMAND service_test)
add_test(NAME all_client_test COMMAND client1 client2 client3 client4 client5)