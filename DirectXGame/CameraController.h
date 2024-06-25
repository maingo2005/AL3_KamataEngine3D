#include "ViewProjection.h"

class Player;

class CameraController {
public:
	// 短形
	struct Rect {
		float left = 0.0f;   // 左端
		float right = 1.0f;  // 右端
		float bottom = 0.0f; // 下端
		float top = 1.0f;    // 上端
	};

	/// 初期化
	void Initialize();

	/// 更新
	void Update();

	void SetTarget(Player* target) { target_ = target; }

	void Reset();

	void SetMovableArea(const Rect& area) { movadeArea_ = area; }

private:
	// ビュープロジェクション
	ViewProjection viewProjection_;
	Player* target_ = nullptr;
	Vector3 targetOffset_ = {0, 0, -15.0f};
	Rect movadeArea_ = {0, 100, 0, 100};
	// カメラの目標座標
	Vector3 objective;
	// 座標補間割合
	static inline const float kInterpolationRate = 0.1f;
	//速度掛け率
	static inline const float kVelocityBias = 30.0f;
	//追従対象の各方向へのカメラ移動範囲
	static inline const Rect margin = {-90.0f, 90.0f, -50.0f, 50.0f};
};