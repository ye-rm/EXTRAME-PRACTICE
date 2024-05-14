//
// Created by 98770 on 2024/5/13.
//
#include "../src/client/client.h"
#include "../src/common/common.h"

int main(){
    Client client(4);
    client.start_client_working();

    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);

    // 4
    client.power_on();
    sleep(SECOND_PER_MINUTE);

    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);

    // 10
    client.change_wind_speed(HIGH_SPEED);
    client.change_target_temp(28);
    sleep(SECOND_PER_MINUTE);

    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    //19
    client.change_wind_speed(MEDIUM_SPEED);
    client.change_target_temp(25);
    sleep(SECOND_PER_MINUTE);

    sleep(SECOND_PER_MINUTE);
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