#include <assert.h>
#include <fstream>
#include <map>
#include <sstream>
#include <string>

#include "MapChipField.h"

namespace {

std::map<std::string, MapChipType> mapChipType = {
    {"0", MapChipType::kBlank},
    {"1", MapChipType::kBlock},
};

}

void MapChipField::ResetMapChipData() {
	// マップチップデータをリセット
	mapChipData_.data.clear();
	mapChipData_.data.resize(kNumkBlockVirtical);
	for (std::vector<MapChipType>& mapChipDataLine : mapChipData_.data) {
		mapChipDataLine.resize(kNumkBlockHorizontal);
	}
}

void MapChipField::LoadMapChipCsv(const std::string& filePath) {
	// ファイルを開く
	std::ifstream file;
	file.open(filePath);
	assert(file.is_open());

	// マップチップCSV
	std::stringstream mapChipCsv;

	// ファイルの内容を文字列ストリームにコピー
	mapChipCsv << file.rdbuf();

	// ファイルを閉じる
	file.close();

	// マップチップデータをリセット
	ResetMapChipData();

	std::string line;

	// CSVからマップチップデータを読み込む
	for (uint32_t i = 0; i < kNumkBlockVirtical; ++i) {
		getline(mapChipCsv, line);

		// 1行分の文字列をストリームに変換して解析しやすくする
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

Vector3 MapChipField::GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex) {
	return Vector3(kBlockWidth * (kNumkBlockHorizontal - 35 - xIndex), kBlockHeight * (kNumkBlockVirtical - 1 - yIndex), 0);
}

MapChipType MapChipField::GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex) {
	if (xIndex < 0 || kNumkBlockHorizontal - 1 < xIndex) {
		return MapChipType::kBlank;
	}
	if (yIndex < 0 || kNumkBlockVirtical - 1 < yIndex) {
		return MapChipType::kBlank;
	}
	return mapChipData_.data[yIndex][xIndex];
}

MapChipField::IndexSet MapChipField::GetMapChipIndexSetByPosition(const Vector3& position) {
	MapChipField::IndexSet indexSet = {};
	indexSet.xIndex = static_cast<uint32_t>((position.x + kBlockWidth / 2) / kBlockWidth);
	indexSet.yIndex = kNumkBlockVirtical - 1 - static_cast<uint32_t>(position.y + kBlockHeight / 2 / kBlockHeight);

	return indexSet;
}

MapChipField::Rect MapChipField::GetRectByIndex(uint32_t xIndex, uint32_t yIndex) {
	Vector3 center = GetMapChipPositionByIndex(xIndex, yIndex);

	Rect rect;
	rect.left = center.x - kBlockWidth / 2.0f;
	rect.right = center.x + kBlockWidth / 2.0f;
	rect.bottom = center.y - kBlockWidth / 2.0f;
	rect.top = center.y + kBlockWidth / 2.0f;

	return rect;
}