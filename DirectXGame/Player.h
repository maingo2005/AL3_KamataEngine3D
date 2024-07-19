#pragma once

#include "AABB.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class MapChipField;
class Enemy;

class Player {
public:
	enum class LRDirection {
		kRight,
		kLeft,
	};

	// 角
	enum Corner {
		kRightBottom, // 右下
		kLeftBottom,  // 左下
		kRightTop,    // 右上
		kLeftTop,     // 左上

		kNumCorner // 要素数
	};

	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);
	void Update();
	void Draw();

	// ワールド座標を取得
	Vector3 GetWorldPosition();
	AABB GetAABB();
	void OnCollision(const Enemy* enemy);

	const WorldTransform& GetWorldTransform() const { return worldTransform_; }

	const Vector3& GetVelocity() const { return velocity_; }

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }

	bool IsDeath() { return isDeath_; }

private:
	static inline const float kAcceleratio = 0.1f;
	static inline const float kAttenuation = 0.05f;
	static inline const float kJumpAcceleration = 20.0f;
	static inline const float kGravityAcceleration = 0.98f;
	static inline const float kAttenuationWall = 0.2f;
	static inline const float kAttenuationLanding = 0.5f;
	static inline const float kLimitFallSpeed = 0.5f;
	static inline const float kLimitRunSpeed = 0.5f;
	static inline const float kTimeTurn = 0.7f;
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;
	static inline const float kBlank = 0.04f;
	static inline const float kGroundSearchHeight = 0.06f;

	Model* model_ = nullptr;
	WorldTransform worldTransform_;
	ViewProjection* viewProjection_ = nullptr;
	Vector3 velocity_ = {};
	bool onGround_ = true;
	LRDirection lrDirection_ = LRDirection::kRight;
	float turnFirstRotationY_ = 0.0f;
	float turnTimer_ = 0.0f;
	MapChipField* mapChipField_ = nullptr;

	bool landing = false;
	bool isDeath_ = false;

	// マップチップとの当たり判定情報
	struct CollisionMapInfo {
		// 天井衝突フラグ
		bool ceiling = false;
		// 着地フラグ
		bool landing = false;
		// 壁接触フラグ
		bool hitWall = false;
		// 移動量
		Vector3 move;
	};

	// 移動処理
	void InMovement();
	// 旋回制御
	void TurningControl();
	// マップ衝突チェック
	void CollisionDetection(CollisionMapInfo& info);
	// 上
	void Top(CollisionMapInfo& info);
	// 下
	void Bottom(CollisionMapInfo& info);
	// 右
	void Right(CollisionMapInfo& info);
	// 左
	void Left(CollisionMapInfo& info);
	// 接地状態の切り替え処理
	void GroundingStateSwitching(const CollisionMapInfo& info);

	Vector3 CornerPosition(const Vector3& center, Corner corner);
};
