//
// Created by 98770 on 2024/5/13.
//
#include "../src/client/client.h"
#include "../src/common/common.h"

int main(){
    Client client(3);
    client.start_client_working();

    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));

    // 3
    client.power_on();
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));

    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));

    // 5
    client.change_target_temp(27);
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));

    // 15
    client.change_wind_speed(LOW_SPEED);
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));

    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));

    // 18
    client.change_wind_speed(HIGH_SPEED);
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));

    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));

    // 25
    client.power_off();
    while (true){

    }
}