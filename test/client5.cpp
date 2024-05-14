//
// Created by 98770 on 2024/5/13.
//
#include "../src/client/client.h"
#include "../src/common/common.h"

int main(){
    Client client(5);
    client.start_client_working();

    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);

    //4
    client.power_on();
    sleep(SECOND_PER_MINUTE);

    //5
    client.change_wind_speed(HIGH_SPEED);
    sleep(SECOND_PER_MINUTE);

    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);

    //8
    client.change_target_temp(24);
    sleep(SECOND_PER_MINUTE);

    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    //12
    client.change_wind_speed(MEDIUM_SPEED);
    sleep(SECOND_PER_MINUTE);

    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);

    //17
    client.power_off();
    sleep(SECOND_PER_MINUTE);

    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);

    //21
    client.power_on();
    sleep(SECOND_PER_MINUTE);

    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);
    sleep(SECOND_PER_MINUTE);

    //25
    client.power_off();
    while (true){

    }
}
