#pragma once
#include "OrderBase.h"
#include <Windows.h>
#include "Logger.h"

class BlockInputOrder : public OrderBase {
private:
	bool state;
public:
	BlockInputOrder(bool active) {
		this->state = active;
	}
	bool Execute() {
		BlockInput(this->state);
		return true;

	}
};