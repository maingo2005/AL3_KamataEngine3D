#include <cstdint>
#include <stdint.h>
#include <vector>
#include "Vector3.h"

enum class MapChipType {
	kBlank,
	kBlock,
};

struct MapChipData {
	std::vector<std::vector<MapChipType>> data;
};

class MapChipField {
public:
	void ResetMapChipData();

	void LoadMapChipCsv(const std::string& filePath);

private:
	static inline const float kBlockWidth = 1.0f;
	static inline const float kBlockHeight = 1.0f;

	static inline const uint32_t kNumkBlockVirtical = 20;
	static inline const uint32_t kNumkBlockHorizontal = 100;

	MapChipData mapChipData_;
};