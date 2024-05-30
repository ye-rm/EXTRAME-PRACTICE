//
// Created by 98770 on 2024/5/13.
//
#include "../src/client/client.h"

//int main(){
//    Client client(1);
//    client.start_client_working();
//    // 0
//    client.power_on();
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    // 1
//    client.change_target_temp(18);
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    // 5
//    client.change_wind_speed(HIGH_SPEED);
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    // 9
//    client.change_target_temp(22);
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    // 14
//    client.power_off();
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    // 18
//    client.power_on();
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    std::this_thread::sleep_for(std::chrono::seconds(1));
//    // 24
//    client.power_off();
//    while (true){
//
//    }
//}


int main(){
    Client client(1);
    client.start_client_working();
    // 1
    client.power_on();
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    // 2
    client.change_target_temp(24);
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    // 6
    client.change_wind_speed(HIGH_SPEED);
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    // 10
    client.change_target_temp(28);
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    // 15
    client.power_off();
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    // 19
    client.power_on();
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