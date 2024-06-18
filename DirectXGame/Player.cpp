#define NOMINMAX
#include "Player.h"
#include "MathUtilityForText.h"
#include <Input.h>
#include <algorithm>
#include <cassert>
#include <numbers>

void Player::Initialize(Model* model, ViewProjection* viewProjection, const Vector3& position) {
	// NULLポインタチェック
	assert(model);
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = position;
	worldTransform_.translation_.y = std::numbers::pi_v<float> / 2.0f;

	// 引数の内容をメンバ変数に記録
	model_ = model;
	// textureHandle_ = textureHandle;
	viewProjection_ = viewProjection;
}

void Player::Update() {
	bool landing = false;
	// 移動入力
	if (onGround_) {
		if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {
			// 左右加速
			Vector3 acceleration = {};
			if (Input::GetInstance()->PushKey(DIK_RIGHT)) {
				// 左移動中の右入力
				if (velocity_.x < 0.0f) {
					// 速度と逆方向に入力中は急ブレーキ
					velocity_.x *= (1.0f - kAttenuation);
				}

				acceleration.x += kAcceleratio;

				if (lrDirection_ != LRDirection::kRight) {
					lrDirection_ = LRDirection::kRight;
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					turnTimer_ = kTimeTurn;
				}
			} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {
				// 左移動中の右入力
				if (velocity_.x > 0.0f) {
					// 速度と逆方向に入力中は急ブレーキ
					velocity_.x *= (1.0f - kAttenuation);
				}
				if (lrDirection_ != LRDirection::kLeft) {
					lrDirection_ = LRDirection::kLeft;
					turnFirstRotationY_ = worldTransform_.rotation_.y;
					turnTimer_ = kTimeTurn;
				}
				// 旋回制御
				if (turnTimer_ > 0.0f) {
					turnTimer_ = (1.0f / 60.0f);

					// 左右の自キャラ角度テーブル
					float destinationRotationYTable[] = {
					    std::numbers::pi_v<float> / 2.0f,
					    std::numbers::pi_v<float> * 3.0f / 2.0f,
					};
					// 状態に応じた角度を取得する
					float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
					// 自キャラの角度を設定する
					worldTransform_.rotation_.y = EaseInOut(destinationRotationY, turnFirstRotationY_, turnTimer_ / kTimeTurn);
				}
				acceleration.x -= kAcceleratio;
			} else {
				// 非入力時は移動減衰をかける
				velocity_.x *= (1.0f - kAttenuation);
			}
			if (Input::GetInstance()->PushKey(DIK_UP)) {
				velocity_ += Vector3(0, kJumpAcceleration, 0);
			}

			// 加速／減速
			operator+=(velocity_, acceleration);

			// 最大速度制限
			velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);
		}
	} else {
		velocity_ += Vector3(0, -kGravityAcceleration, 0);
		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);

		if (velocity_.y < 0) {
			if (worldTransform_.translation_.y <= 1.0f) {
				landing = true;
			}
		}
	}
	//接地判定
	if (onGround_) {
		// 接地判定
		if (velocity_.y > 0.0f) { 
			// 接地判定
			onGround_ = false; 
		}
	} else {
		// 接地判定
		if (landing) {
			// めり込み排斥
			worldTransform_.translation_.y = 1.0f;
			// 摩擦で横方向速度が減衰する
			velocity_.x *= (1.0f - kAcceleratio);
			// 下方向速度のリセット
			velocity_.y = 0.0f;
			// 接地状態の移行
			onGround_ = true;
		}
	}

	// 移動
	operator+=(worldTransform_.translation_, velocity_);

	// 行列を定数バッファに転送
	worldTransform_.UpdateMatrix();
}

void Player::Draw() {
	// 3Dモデルの描画
	model_->Draw(worldTransform_, *viewProjection_, textureHandle_);
}