#define NOMINMAX
#include "CameraController.h"
#include "myMath.h"
#include "Player.h"

void CameraController::Initialize() {
	// ビュープロジェクションの初期化
	viewProjection_.Initialize();
}

void CameraController::Update() {
	// 追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	// 追従対象とオフセットからカメラの座標を計算
	objective.x = targetWorldTransform.translation_.x + targetOffset_.x;
	objective.y = targetWorldTransform.translation_.y + targetOffset_.y;
	objective.z = targetWorldTransform.translation_.z + targetOffset_.z;

	// 座標補間によるゆったり追従
	viewProjection_.translation_ = Lerp(viewProjection_.translation_, objective, kInterpolationRate);

	// 移動範囲制限
	viewProjection_.translation_.x = std::max(viewProjection_.translation_.x, movadeArea_.left);
	viewProjection_.translation_.x = std::min(viewProjection_.translation_.x, movadeArea_.right);
	viewProjection_.translation_.y = std::max(viewProjection_.translation_.y, movadeArea_.bottom);
	viewProjection_.translation_.y = std::min(viewProjection_.translation_.y, movadeArea_.top);

	// 行列を更新
	viewProjection_.UpdateMatrix();
}

void CameraController::Reset() {
	// 追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();
	// 追従対象とオフセットからカメラの座標を計算
	viewProjection_.translation_.x = targetWorldTransform.translation_.x + targetOffset_.x;
	viewProjection_.translation_.y = targetWorldTransform.translation_.y + targetOffset_.y;
	viewProjection_.translation_.z = targetWorldTransform.translation_.z + targetOffset_.z;
}