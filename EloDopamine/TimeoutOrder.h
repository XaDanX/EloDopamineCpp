#pragma once
#include "OrderBase.h"
#include <Windows.h>
#include "Logger.h"

class TimeoutOrder : public OrderBase {
private:

	float time = NULL;
	float startTime = NULL;
public:
	TimeoutOrder(float _time) {
		this->time = _time;
	}
	bool Execute() {
		if (this->startTime == NULL) {
			this->startTime = GetTickCount64();
		}

		if (this->startTime + this->time < GetTickCount64()) {
			return true;
		}
		return false;

	}
};