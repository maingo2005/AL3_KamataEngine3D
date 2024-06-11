#include "Model.h"
#include "WorldTransform.h"

enum class LRDirection {
	kRight,
	kLeft,
};

class Player {
public:
	/// 初期化
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	/// 更新
	void Update();

	/// 描画
	void Draw();

private:
	// ワールドトランスフォームの初期化
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	ViewProjection* viewProjection_ = nullptr;

	Vector3 velocity_ = {};

	LRDirection lrDirection_ = LRDirection::kRight;

	static inline const float kAcceleratio = 10;
	static inline const float kAttenuation = 10;
	static inline const float kLimitRunSpeed = 10;
};
