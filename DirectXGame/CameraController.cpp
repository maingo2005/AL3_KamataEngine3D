#define NOMINMAX
#include "CameraController.h"
#include "Player.h"
#include "myMath.h"
#include <algorithm>

void CameraController::Initialize() {
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
}

void CameraController::Update() {
	// 追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	Vector3 targetVelocity = target_->GetVelocity();

	// 追従対象とオフセットと追従対象の速度からカメラの座標を計算
	objective = targetWorldTransform.translation_ + targetVelocity * kVelocityBias + targetOffset_;

	// 座標補間によるゆったり追従
	viewProjection_.translation_ = Lerp(viewProjection_.translation_, objective, kInterpolationRate);

	//追従対象が画面外に出ないように補正
	viewProjection_.translation_.x = std::clamp(viewProjection_.translation_.x, targetWorldTransform.translation_.x + margin.left, targetWorldTransform.translation_.x + margin.right);
	viewProjection_.translation_.y = std::clamp(viewProjection_.translation_.y, targetWorldTransform.translation_.y + margin.bottom, targetWorldTransform.translation_.y + margin.top);

	// 移動範囲制限
	viewProjection_.translation_.x = std::clamp(viewProjection_.translation_.x, movadeArea_.left, movadeArea_.right);
	viewProjection_.translation_.y = std::clamp(viewProjection_.translation_.y, movadeArea_.bottom, movadeArea_.top);

	// 行列を更新
	viewProjection_.UpdateMatrix();
}

void CameraController::Reset() {
	// 追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	// 追従対象とオフセットからカメラの座標を計算
	viewProjection_.translation_ = targetWorldTransform.translation_ + targetOffset_;
}