#pragma once
#include <string>


class ModuleBase {
private:
	bool isEnabled = true;
public:

	virtual void OnUpdate() = 0;

	virtual void OnGui() = 0;

	virtual std::string ModuleType() = 0; // champion name/utility

	virtual std::string GetName() = 0;

	bool IsEnabled() { return this->isEnabled; }

	void Toggle() { this->isEnabled = !this->isEnabled; }
};