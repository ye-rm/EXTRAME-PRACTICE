//
// Created by 98770 on 2024/5/11.
//
#include "service.h"
#include "../../loguru.hpp"
#include <thread>
int main(){
    service s(1);
    s.change_target_temp(17);
    s.start_service();
    s.change_wind_speed(3);
    s.update_cur_temp(20);
	std::this_thread::sleep_for(std::chrono::seconds(SECOND_PER_MINUTE));
    s.generate_detailed_record();
}