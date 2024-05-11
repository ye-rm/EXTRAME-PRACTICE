//
// Created by 98770 on 2024/5/11.
//
#include "client.h"

int main() {
    Client client(1);
    client.get_environment_temp();
    client.power_on();
    client.change_working_mode(MODE_COOLING);
    client.change_target_temp(17);
    client.change_wind_speed(SPEED_HIGH);
//    while (true){
//        sleep(1);
//        client.listen_server();
//        client.handle_server_response();
//        client.get_status();
//    }
    return 0;
}