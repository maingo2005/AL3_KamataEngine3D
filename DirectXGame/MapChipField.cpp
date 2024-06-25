#include "MapChipField.h"

#include <cassert>
#include <fstream>
#include <map>
#include <sstream>
#include <string>

namespace {

std::map<std::string, MapChipType> mapChipType = {
    {"0", MapChipType::kBlank},
    {"1", MapChipType::kBlock},
};

}

void MapChipField::Initialize(Model* model, ViewProjection* viewProjection) {
	// 引数の内容をメンバ変数に記録
	worldTransform_.Initialize();
	model_ = model;
	viewProjection_ = viewProjection;
}

void MapChipField::Update() {}

void MapChipField::Draw() {
	// 3Dモデル描画
	model_->Draw(worldTransform_, *viewProjection_);
}

void MapChipField::ResetMapChipData() {
	mapChipData_.data.clear();
	mapChipData_.data.resize(kNumkBlockVirtical);
	for (std::vector<MapChipType>& mapChipDataLine : mapChipData_.data) {
		mapChipDataLine.resize(kNumkBlockHorizontal);
	}
}

void MapChipField::LoadMapChipCsv(const std::string& filePath) {
	ResetMapChipData();

	std::ifstream file;
	file.open(filePath);
	assert(file.is_open());

	std::stringstream mapChipCsv;
	mapChipCsv << file.rdbuf();
	file.close();

	for (uint32_t i = 0; i < kNumkBlockVirtical; ++i) {
		std::string line;
		getline(mapChipCsv, line);

		std::istringstream line_stream(line);

		for (uint32_t j = 0; j < kNumkBlockHorizontal; ++j) {
			std::string word;
			getline(line_stream, word, ',');

			if (mapChipType.contains(word)) {
				mapChipData_.data[i][j] = mapChipType[word];
			}
		}
	}
}

MapChipType MapChipField::MapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex) {
	if (xIndex < 0 || kNumkBlockHorizontal - 1 < xIndex) {
		return MapChipType::kBlank;
	}
	if (yIndex < 0 || kNumkBlockVirtical - 1 < yIndex) {
		return MapChipType::kBlank;
	}
	return mapChipData_.data[yIndex][xIndex];
}

Vector3 MapChipField::MapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex) { return Vector3(kBlockWidth * xIndex, kBlockHeight * (kNumkBlockVirtical - 1 - yIndex), 0); }

uint32_t MapChipField::GetkNumkBlockVirtical() { return kNumkBlockVirtical; }

uint32_t MapChipField::GetkNumkBlockHorizontal() { return kNumkBlockHorizontal; }

MapChipField::IndexSet MapChipField::GetMapChipIndexSetByPosition(const Vector3& position) {
	MapChipField::IndexSet indexSet = {};
	indexSet.xIndex = ((uint32_t)position.x + (uint32_t)MapChipField::kBlockWidth / 2) / (uint32_t)MapChipField::kBlockWidth;
	indexSet.yIndex = MapChipField::kNumkBlockVirtical - 1 - ((uint32_t)position.y + (uint32_t)MapChipField::kBlockHeight / 2) / (uint32_t)MapChipField::kBlockHeight;

	return indexSet;
}

MapChipField::Rect MapChipField::GetRectByIndex(uint32_t xIndex, uint32_t yIndex) {
	Vector3 center = GetmapChipPositionByIndex(xIndex, yIndex);

	Rect rect;
	rect.left = center.x - kBlockWidth / 2.0f;
	rect.right = 0;
	rect.bottom = 0;
	rect.top = 0;

	return rect;
}

MapChipType MapChipField::GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex) { return MapChipType(xIndex - yIndex); }

Vector3 MapChipField::GetmapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex) { return Vector3(xIndex, yIndex); }
