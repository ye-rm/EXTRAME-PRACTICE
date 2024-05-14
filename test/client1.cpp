//
// Created by 98770 on 2024/5/13.
//
#include "../src/client/client.h"
#include "../src/common/common.h"

//int main(){
//    Client client(1);
//    client.start_client_working();
//    // 0
//    client.power_on();
//    sleep(SECOND_PER_MINUTE);
//    // 1
//    client.change_target_temp(18);
//    sleep(SECOND_PER_MINUTE);
//    sleep(SECOND_PER_MINUTE);
//    sleep(SECOND_PER_MINUTE);
//    sleep(SECOND_PER_MINUTE);
//    // 5
//    client.change_wind_speed(HIGH_SPEED);
//    sleep(SECOND_PER_MINUTE);
//    sleep(SECOND_PER_MINUTE);
//    sleep(SECOND_PER_MINUTE);
//    sleep(SECOND_PER_MINUTE);
//    // 9
//    client.change_target_temp(22);
//    sleep(SECOND_PER_MINUTE);
//    sleep(SECOND_PER_MINUTE);
//    sleep(SECOND_PER_MINUTE);
//    sleep(SECOND_PER_MINUTE);
//    sleep(SECOND_PER_MINUTE);
//    // 14
//    client.power_off();
//    sleep(SECOND_PER_MINUTE);
//    sleep(SECOND_PER_MINUTE);
//    sleep(SECOND_PER_MINUTE);
//    sleep(SECOND_PER_MINUTE);
//    // 18
//    client.power_on();
//    sleep(SECOND_PER_MINUTE);
//    sleep(SECOND_PER_MINUTE);
//    sleep(SECOND_PER_MINUTE);
//    sleep(SECOND_PER_MINUTE);
//    sleep(SECOND_PER_MINUTE);
//    sleep(SECOND_PER_MINUTE);
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
    sleep(SECOND_PER_MINUTE);
    // 2
    client.change_target_temp(24);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    // 6
    client.change_wind_speed(HIGH_SPEED);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    // 10
    client.change_target_temp(28);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    // 15
    client.power_off();
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    // 19
    client.power_on();
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    // 25
    client.power_off();
    while (true){

    }
}