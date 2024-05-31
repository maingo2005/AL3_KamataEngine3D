#include "Model.h"
#include "WorldTransform.h"

class Sphere {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, ViewProjection* viewProjection);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	// ワールドトランスフォームの初期化
	WorldTransform worldTransform_;
	// 3Dモデル
	Model* model_ = nullptr;

	ViewProjection* viewProjection_ = nullptr;
};