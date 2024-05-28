#include "Tama.h"
#include <cassert>

void Tama::Initialize(Model* model,ViewProjection* viewProjection) {
	// NULLポインタチェック
	assert(model);
	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	// 引数の内容をメンバ変数に記録
	model_ = model;
	viewProjection_ = viewProjection;
}

void Tama::Update() {
	// 行列を定数バッファに転送
	worldTransform_.TransferMatrix();
}

void Tama::Draw() {
	// 3Dモデルの描画
	model_->Draw(worldTransform_, *viewProjection_);
}