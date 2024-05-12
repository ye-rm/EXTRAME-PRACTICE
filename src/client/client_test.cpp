//
// Created by 98770 on 2024/5/11.
//
#include "client.h"

int main() {
    Client client1(1);
    client1.start_client_working();
    client1.power_on();
    client1.change_wind_speed(LOW_SPEED);
    client1.change_target_temp(25);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    client1.power_off();
    sleep(SECOND_PER_MINUTE);
    client1.power_on();
    client1.change_wind_speed(MEDIUM_SPEED);
    client1.change_target_temp(27);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    while (true){

    }
    return 0;
}