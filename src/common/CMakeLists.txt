add_library(socket SHARED socket.cpp socket.h rapidcsv.h)


add_executable(socket_test socket_test.cpp)
target_link_libraries(socket_test socket)

enable_testing()

add_test(NAME socket_test COMMAND socket_test)