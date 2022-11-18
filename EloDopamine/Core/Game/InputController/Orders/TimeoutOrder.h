#pragma once
#include "OrderBase.h"
#include <Windows.h>
#include "../../../Utils/Logger.h"
using namespace std::chrono_literals;

class TimeoutOrder : public OrderBase {
private:

	int time = NULL;
	float startTime = NULL;
public:
	TimeoutOrder(float _time) {
		this->time = _time;
	}
	bool Execute() {

		std::this_thread::sleep_for(std::chrono::microseconds(time));
		return true;

	}
};