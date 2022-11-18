#pragma once

#include "OrderBase.h"
#include <Windows.h>
#include "../../../Utils/KeyCodes.h"


class KeyClickOrder : public OrderBase {
private:
	int clickType;
	HKey key;
public:
	KeyClickOrder(HKey key, int type) {
		this->clickType = type;
		this->key = key;
	}
	bool Execute() {


		INPUT input;
		input.type = INPUT_KEYBOARD;
		input.ki.wScan = this->key;
		input.ki.time = 0;
		input.ki.dwExtraInfo = 0;
		input.ki.wVk = 0;
		input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &input, sizeof(INPUT));
		if (this->clickType == 0)
			input.ki.dwFlags = KEYEVENTF_SCANCODE;
		else
			input.ki.dwFlags = KEYEVENTF_SCANCODE | KEYEVENTF_KEYUP;
		SendInput(1, &input, sizeof(INPUT));
		return true;

	}
};