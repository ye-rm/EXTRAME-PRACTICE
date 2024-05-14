//
// Created by 98770 on 2024/5/13.
//
#include "../src/client/client.h"
#include "../src/common/common.h"

int main(){
    Client client(2);
    client.start_client_working();

    sleep(SECOND_PER_MINUTE);

    // 2
    client.power_on();
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);

    // 4
    client.change_target_temp(25);
    sleep(SECOND_PER_MINUTE);

    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);

    // 13
    client.change_wind_speed(HIGH_SPEED);
    sleep(SECOND_PER_MINUTE);

    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
// 21
    client.change_target_temp(27);
    client.change_wind_speed(MEDIUM_SPEED);
    sleep(SECOND_PER_MINUTE);

    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    // 26
    client.power_off();
    while (true){

    }
}