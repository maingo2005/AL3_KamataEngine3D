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

	//旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;
	//旋回タイマー
	float turnTimer_ = 0.7f;

	//接地状態のフラグ
	bool onGround_ = true;

	bool landing = false;

	static inline const float kAcceleratio = 10.0f;
	static inline const float kAttenuation = 10.0f;
	static inline const float kLimitRunSpeed = 10.0f;
	static inline const float kTimeTurn = 0.3f;
	static inline const float kGravityAcceleration = 0.98f;
	static inline const float kLimitFallSpeed = 0.5f;
	static inline const float kJumpAcceleration = 20.0f;
};
