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

# set up qt environment
set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)

include(FetchContent)
FetchContent_Declare(LoguruGitRepo
        GIT_REPOSITORY "https://github.com/emilk/loguru" # can be a filesystem path
        GIT_TAG        "master"
)
# set any loguru compile-time flags before calling MakeAvailable()
set(LOGURU_WITH_STREAMS TRUE)
FetchContent_MakeAvailable(LoguruGitRepo) # defines target 'loguru::loguru'

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(qt_demo gui/client.cpp)
target_link_libraries(qt_demo
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
)

if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()


# set up sqlite3
add_compile_options(-l sqlite3)

add_library(db ./sqlite/sqlite3.c)

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
target_link_libraries(service db)

add_library(server
        src/server/scheduler.cpp
        src/server/scheduler.h
        lib/rapidcsv/rapidcsv.h
        src/common/common.h
)

target_link_libraries(server service)

add_library(client
        ./src/client/client.cpp
        ./src/client/client.h
        ./lib/rapidcsv/rapidcsv.h
        ./src/common/common.h
)

#add_executable(client_ui ./gui/client.cpp ./gui/client.h ./gui/client.ui)
#target_link_libraries(client_ui client Qt5::Core Qt5::Widgets)

target_link_libraries(client socket)

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
# 包含子项目。

enable_testing()
add_test(NAME socket_test COMMAND socket_test)
add_test(NAME server_test COMMAND server_test)
add_test(NAME service_test COMMAND service_test)
add_test(NAME all_client_test COMMAND client1 client2 client3 client4 client5)