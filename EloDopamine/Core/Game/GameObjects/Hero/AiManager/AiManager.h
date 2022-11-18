#pragma once
#include "../../../../Math/Vector.h"
#include <iostream>
#include <vector>
#include "../../../Managers/MemoryManager/MemoryManager.h"
class AiManager {
protected:
	static const SIZE_T objectSize = 0x500;
	BYTE buff[objectSize];
	BYTE navArrayBuff[40 * sizeof(Vector3)];

public:
	AiManager() {}
public:
	int address{0};
	Vector3 startPath;
	Vector3 endPath;
	bool isMoving;
	std::vector<Vector3> navigationArray;
	int currentSegment;
	float movementSpeed;
	Vector3 serverPosition;
	bool isDashing;
	float dashSpeed;
	Vector3 velocity;


	void Update();

};

