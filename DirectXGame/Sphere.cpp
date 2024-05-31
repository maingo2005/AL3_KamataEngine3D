#include "Sphere.h"
#include <cassert>

/// 初期化
void Sphere::Initialize(Model* model, ViewProjection* viewProjection) {
	// NULLポインタチェック
	assert(model);
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	// 引数の内容をメンバ変数に記録
	model_ = model;
	viewProjection_ = viewProjection;
};

/// 毎フレーム処理
void Sphere::Update(){
	// 行列を定数バッファに転送
	worldTransform_.UpdateMatrix();
};

/// 描画
void Sphere::Draw() {
	// 3Dモデル描画
	model_->Draw(worldTransform_, *viewProjection_);
};