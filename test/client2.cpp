//
// Created by 98770 on 2024/5/13.
//
#include "../src/client/client.h"
#include "../src/common/common.h"

int main(){
    Client client(2);
    client.start_client_working();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 2
    client.power_on();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 4
    client.change_target_temp(25);
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::this_thread::sleep_for(std::chrono::seconds(1));

    // 13
    client.change_wind_speed(HIGH_SPEED);
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::this_thread::sleep_for(std::chrono::seconds(1));
// 21
    client.change_target_temp(27);
    client.change_wind_speed(MEDIUM_SPEED);
    std::this_thread::sleep_for(std::chrono::seconds(1));

    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::this_thread::sleep_for(std::chrono::seconds(1));
    // 26
    client.power_off();
    while (true){

    }
}