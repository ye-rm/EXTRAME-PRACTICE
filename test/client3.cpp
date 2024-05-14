//
// Created by 98770 on 2024/5/13.
//
#include "../src/client/client.h"
#include "../src/common/common.h"

int main(){
    Client client(3);
    client.start_client_working();

    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);

    // 3
    client.power_on();
    sleep(SECOND_PER_MINUTE);

    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);

    // 15
    client.change_wind_speed(LOW_SPEED);
    sleep(SECOND_PER_MINUTE);

    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);

    // 18
    client.change_wind_speed(HIGH_SPEED);
    sleep(SECOND_PER_MINUTE);

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