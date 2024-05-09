add_library(socket SHARED socket.cpp socket.h)

add_executable(socket_test socket_test.cpp)
target_link_libraries(socket_test socket)

add_test(NAME socket COMMAND socket_test)