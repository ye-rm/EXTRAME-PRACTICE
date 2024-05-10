#include<iostream>
#include "./common/socket.h"
#include "../lib/loguru/loguru.hpp"

int main(int argc, char* argv[])
{

    loguru::init(argc, argv);
    loguru::add_file("test.log", loguru::Append, loguru::Verbosity_MAX);
    LOG_F(INFO, "Hello World");
    LOG_F(WARNING, "Hello World");
    LOG_F(ERROR, "Hello World");
	return 0;
}