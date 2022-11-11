#include "AiManager.h"
#include "Offsets.h"

void AiManager::Update() {
	memoryManager->ReadBuffer(this->address, this->buff, AiManager::objectSize);
	memcpy(&startPath, &buff[Offsets::AIManagerStartPath], sizeof(Vector3));
	memcpy(&endPath, &buff[Offsets::AIManagerEndPath], sizeof(Vector3));
	memcpy(&isMoving, &buff[Offsets::AIManagerIsMoving], sizeof(bool));
	memcpy(&currentSegment, &buff[Offsets::AIManagerCurrentSegment], sizeof(int));
	memcpy(&movementSpeed, &buff[Offsets::AIManagerMoveSpeed], sizeof(float));
	memcpy(&serverPosition, &buff[Offsets::AIManagerServPosition], sizeof(Vector3));
	memcpy(&isDashing, &buff[Offsets::AIManagerIsDashing], sizeof(bool));
	memcpy(&dashSpeed, &buff[Offsets::AIManagerDashpeed], sizeof(float));
	memcpy(&velocity, &buff[Offsets::AIManagerVelocity], sizeof(Vector3));

	int navArray = 0;
	int navArrayLength = 0;
	memcpy(&navArray, &buff[Offsets::AIManagerNavigationArray], sizeof(int));
	memcpy(&navArrayLength, &buff[Offsets::AIManagerNavigationArrayLength], sizeof(int));

	memoryManager->ReadBuffer(navArray, this->navArrayBuff, navArrayLength * sizeof(Vector3));
	this->navigationArray.clear();
	if (navArrayLength > 1) {
		Vector3 current;
		for (int index = 0; index < navArrayLength; index++) {
			memcpy(&current, &this->navArrayBuff[12 * index], sizeof(Vector3));
			this->navigationArray.push_back(current);
		}
	}



}
