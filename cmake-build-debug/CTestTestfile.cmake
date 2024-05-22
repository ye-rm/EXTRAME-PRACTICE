# CMake generated Testfile for 
# Source directory: /home/ye/CLionProjects/EXTRAME-PRACTICE
# Build directory: /home/ye/CLionProjects/EXTRAME-PRACTICE/cmake-build-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(socket_test "/home/ye/CLionProjects/EXTRAME-PRACTICE/cmake-build-debug/socket_test")
set_tests_properties(socket_test PROPERTIES  _BACKTRACE_TRIPLES "/home/ye/CLionProjects/EXTRAME-PRACTICE/CMakeLists.txt;148;add_test;/home/ye/CLionProjects/EXTRAME-PRACTICE/CMakeLists.txt;0;")
add_test(server_test "/home/ye/CLionProjects/EXTRAME-PRACTICE/cmake-build-debug/server_test")
set_tests_properties(server_test PROPERTIES  _BACKTRACE_TRIPLES "/home/ye/CLionProjects/EXTRAME-PRACTICE/CMakeLists.txt;149;add_test;/home/ye/CLionProjects/EXTRAME-PRACTICE/CMakeLists.txt;0;")
add_test(service_test "/home/ye/CLionProjects/EXTRAME-PRACTICE/cmake-build-debug/service_test")
set_tests_properties(service_test PROPERTIES  _BACKTRACE_TRIPLES "/home/ye/CLionProjects/EXTRAME-PRACTICE/CMakeLists.txt;150;add_test;/home/ye/CLionProjects/EXTRAME-PRACTICE/CMakeLists.txt;0;")
add_test(all_client_test "/home/ye/CLionProjects/EXTRAME-PRACTICE/cmake-build-debug/client1" "client2" "client3" "client4" "client5")
set_tests_properties(all_client_test PROPERTIES  _BACKTRACE_TRIPLES "/home/ye/CLionProjects/EXTRAME-PRACTICE/CMakeLists.txt;151;add_test;/home/ye/CLionProjects/EXTRAME-PRACTICE/CMakeLists.txt;0;")
subdirs("_deps/logurugitrepo-build")
