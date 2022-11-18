#include "GameData.h"
#include "../../Utils/StringUtils.h"
#include "../../../json/json.hpp"
#include <filesystem>
#include "../../Security/XorStr.hpp"

using json = nlohmann::json;
namespace fs = std::experimental::filesystem;


void GameData::Load(std::string& path) {
	std::string unitData = path + XorStr("\\UnitData.json").c_str(); //  TODO CHANGE

	logger->Info(XorStr("Loading unit data..").c_str());

	LoadUnitData(unitData);

	logger->Info(XorStr("Loaded %i units!").c_str(), this->Units.size());
}

UnitInfo* GameData::GetUnitInfoByName(std::string& name) {
	auto find = Units.find(name);
	return (find == Units.end() ? nullptr : find->second);
}


void GameData::LoadUnitData(std::string& path) {

	std::ifstream file(path);

	if (!file.is_open()) {
		logger->Error(XorStr("Couldn't open file!").c_str());
		return;
	}

	json j;
	file >> j;

	for (auto unitObj : j) {

		UnitInfo* unit = new UnitInfo();
		std::string strName = unitObj[XorStr("name").c_str()].get<std::string>();
		std::string basicAtk = unitObj[XorStr("basicAtk").c_str()].get<std::string>();



		unit->acquisitionRange = unitObj[XorStr("acquisitionRange").c_str()].get<float>();
		unit->attackSpeedRatio = unitObj[XorStr("attackSpeedRatio").c_str()].get<float>();
		unit->baseAttackRange = unitObj[XorStr("attackRange").c_str()].get<float>();
		unit->baseAttackSpeed = unitObj[XorStr("attackSpeed").c_str()].get<float>();
		unit->baseMovementSpeed = unitObj[XorStr("baseMoveSpeed").c_str()].get<float>();
		unit->basicAttackWindup = unitObj[XorStr("basicAtkWindup").c_str()].get<float>();
		unit->gameplayRadius = unitObj[XorStr("gameplayRadius").c_str()].get<float>();
		unit->healthBarHeight = unitObj[XorStr("healthBarHeight").c_str()].get<float>();
		unit->name = StringUtils::ToLower(std::string(unitObj[XorStr("name").c_str()]));
		unit->pathRadius = unitObj[XorStr("pathingRadius").c_str()].get<float>();
		unit->selectionRadius = unitObj[XorStr("selectionRadius").c_str()].get<float>();

		auto tags = unitObj[XorStr("tags").c_str()];
		/*
		for (auto tag : tags) {
			std::string tagStr = tag.get<std::string>();
			unit->SetTag(tagStr);
		}*/

		Units[unit->name] = unit;
	}

}
