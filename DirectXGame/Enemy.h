#pragma once

#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

class Enemy {
public:
	/// 初期化
	void Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position);

	/// 更新
	void Update();

	/// 描画
	void Draw();

private:
	Model* model_ = nullptr;
	WorldTransform worldTransform_;
	ViewProjection* viewProjection_ = nullptr;
	Vector3 velocity_ = {};
	float walkTimer = 0.0f;

	static inline const float kWalkSpeed = 0.02f;
	static inline const float kWalkMotionAngleStart = 0.0f;
	static inline const float kWalkMotionAngleEnd = 30.0f;
	static inline const float kWalkMotionTime = 1.0f;
};