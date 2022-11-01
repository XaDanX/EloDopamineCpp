#include "GameData.h"
#include "StringUtils.h"
#include "json/json.hpp"
#include <filesystem>

using json = nlohmann::json;
namespace fs = std::experimental::filesystem;


void GameData::Load(std::string& path) {
	std::string unitData = path + "\\UnitData.json";

	logger->Info("Loading unit data..");

	LoadUnitData(unitData);

	logger->Info("Loaded %i units!", this->Units.size());
}

UnitInfo* GameData::GetUnitInfoByName(std::string& name) {
	auto find = Units.find(name);
	return (find == Units.end() ? nullptr : find->second);
}


void GameData::LoadUnitData(std::string& path) {

	std::ifstream file(path);

	if (!file.is_open()) {
		logger->Error("Couldn't open file!");
		return;
	}

	json j;
	file >> j;

	for (auto unitObj : j) {

		UnitInfo* unit = new UnitInfo();
		std::string strName = unitObj["name"].get<std::string>();
		std::string basicAtk = unitObj["basicAtk"].get<std::string>();



		unit->acquisitionRange = unitObj["acquisitionRange"].get<float>();
		unit->attackSpeedRatio = unitObj["attackSpeedRatio"].get<float>();
		unit->baseAttackRange = unitObj["attackRange"].get<float>();
		unit->baseAttackSpeed = unitObj["attackSpeed"].get<float>();
		unit->baseMovementSpeed = unitObj["baseMoveSpeed"].get<float>();
		unit->basicAttackWindup = unitObj["basicAtkWindup"].get<float>();
		unit->gameplayRadius = unitObj["gameplayRadius"].get<float>();
		unit->healthBarHeight = unitObj["healthBarHeight"].get<float>();
		unit->name = StringUtils::ToLower(std::string(unitObj["name"]));
		unit->pathRadius = unitObj["pathingRadius"].get<float>();
		unit->selectionRadius = unitObj["selectionRadius"].get<float>();

		auto tags = unitObj["tags"];
		/*
		for (auto tag : tags) {
			std::string tagStr = tag.get<std::string>();
			unit->SetTag(tagStr);
		}*/

		Units[unit->name] = unit;
	}

}
