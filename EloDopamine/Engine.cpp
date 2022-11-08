#include "Engine.h"


void Engine::Update() {
	this->gameTime = memoryManager->Read<float>(memoryManager->BaseAddress() + Offsets::GameTime);

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


}

float Engine::GameTime() {
	return this->gameTime;
}
int Engine::WindowWidth()
{
	return this->windowWidth;
}
int Engine::WindowHeight()
{
	return this->windowHeight;
}

void Engine::UpdateLoopThread() {
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
