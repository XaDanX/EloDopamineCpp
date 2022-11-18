#pragma once
#include <string>
#include "UnitInfo.h"
#include <map>
#include <iostream>
#include <fstream>
#include <filesystem>
#include "../../Utils/Logger.h"
class GameData {
public:
	void Load(std::string& path);

	UnitInfo* GetUnitInfoByName(std::string& name);
public:
	std::map<std::string, UnitInfo*>  Units{};

private:
	void LoadUnitData(std::string& path);

};
inline extern std::unique_ptr<GameData> gameData = std::make_unique<GameData>();
