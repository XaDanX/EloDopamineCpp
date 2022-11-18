#include "Engine.h"


void Engine::Update() {
	this->gameTime = memoryManager->Read<float>(memoryManager->BaseAddress() + Offsets::GameTime);

	if (this->hudInstance == 0) {
		this->hudInstance = memoryManager->Read<int>(memoryManager->BaseAddress() + Offsets::HudInstance);
	}

	char buff[128];

	memoryManager->ReadBuffer(memoryManager->BaseAddress() + Offsets::ViewProjMatrices, buff, 128);
	memcpy(viewMatrix, buff, 16 * sizeof(float));
	memcpy(projectionMatrix, &buff[16 * sizeof(float)], 16 * sizeof(float));
	MultiplySquareMatrices(this->viewProjectionMatrix, this->viewMatrix, this->projectionMatrix);

	char renderBuff[0x14];
	if (this->renderer == 0) this->renderer = memoryManager->Read<int>(memoryManager->BaseAddress() + Offsets::Renderer);
	memoryManager->ReadBuffer(this->renderer, renderBuff, 0x14);
	memcpy(&windowHeight, &renderBuff[Offsets::RendererHeight], sizeof(int));
	memcpy(&windowWidth, &renderBuff[Offsets::RendererWidth], sizeof(int));

	char hudBuff[0x200];
	memoryManager->ReadBuffer(this->hudInstance, hudBuff, 0x200);
	memcpy(&this->worldMousePos, &hudBuff[Offsets::HudInstanceWorldMousePos], sizeof(Vector3));


}

float Engine::GameTime() const {
	return this->gameTime;
}

int Engine::WindowWidth() const {
	return this->windowWidth;
}

int Engine::WindowHeight() const {
	return this->windowHeight;
}

Vector3 Engine::MouseWorldPos() {
	return this->worldMousePos;
}

[[noreturn]] void Engine::UpdateLoopThread() {
	while (true) {
		this->Update();
		std::this_thread::sleep_for(1ms);
	}
}


Vector2 Engine::WorldToScreen(const Vector3& pos) {
	Vector2 out = { 0.f, 0.f };
	Vector2 screen = { (float)this->windowWidth, (float)windowHeight };
	static Vector4 clipCoords;
	clipCoords.x = pos.x * this->viewProjectionMatrix[0] + pos.y * this->viewProjectionMatrix[4] + pos.z * this->viewProjectionMatrix[8] + this->viewProjectionMatrix[12];
	clipCoords.y = pos.x * this->viewProjectionMatrix[1] + pos.y * this->viewProjectionMatrix[5] + pos.z * this->viewProjectionMatrix[9] + this->viewProjectionMatrix[13];
	clipCoords.z = pos.x * this->viewProjectionMatrix[2] + pos.y * this->viewProjectionMatrix[6] + pos.z * this->viewProjectionMatrix[10] + this->viewProjectionMatrix[14];
	clipCoords.w = pos.x * this->viewProjectionMatrix[3] + pos.y * this->viewProjectionMatrix[7] + pos.z * this->viewProjectionMatrix[11] + this->viewProjectionMatrix[15];

	if (clipCoords.w < 1.0f)
		clipCoords.w = 1.f;

	Vector3 M;
	M.x = clipCoords.x / clipCoords.w;
	M.y = clipCoords.y / clipCoords.w;
	M.z = clipCoords.z / clipCoords.w;

	out.x = (screen.x / 2.f * M.x) + (M.x + screen.x / 2.f);
	out.y = -(screen.y / 2.f * M.y) + (M.y + screen.y / 2.f);


	return out;
}


DWORD __cdecl Engine::CollisionFlag(float a1, float a2, float a3)
{


	auto collisionFlag = memoryManager->Read<DWORD>(memoryManager->BaseAddress() + Offsets::CollisionFlag);

	auto world = memoryManager->Read<DWORD>(collisionFlag + 0x4);
	auto fOffsetX = memoryManager->Read<float>(world + 0x64);
	auto fOffsetZ = memoryManager->Read<float>(world + 0x6C);
	auto fCellScale = memoryManager->Read<float>(world + 0x5AC);

	int x = (int)(((a1 - fOffsetX) * fCellScale));
	int y = (int)(((a3 - fOffsetZ) * fCellScale));

	auto target = memoryManager->Read<unsigned int>(world + 0x80);
	unsigned int target2 = target + 0x8 * (memoryManager->Read<unsigned int>(world + 0x5A0) * y + x);
	auto target3 = memoryManager->Read<unsigned int>(target2);
	unsigned short flag;

	if (target3 != 0) {
		flag = memoryManager->Read<unsigned short>(target3 + 0x6);
	}
	else {
		flag = memoryManager->Read<unsigned short>(target2 + 0x4);
	}
	//target4 = target4 & 0xC00;
	return flag;
}

bool Engine::IsNotWall(Vector3 pos) {
	return !(CollisionFlag(pos.x, pos.y, pos.z) & 2);
}