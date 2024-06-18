#include <ViewProjection.h>

class Player;

class CameraController {
public:
	/// 初期化
	void Initialize();

	/// 更新
	void Update();

	void SetTarget(Player* target) { target_ = target; };

	void Reset();

private:
	// ビュープロジェクション
	ViewProjection viewProjection_;
	Player* target_ = nullptr;

	Vector3 targetOffset_ = {0, 0, -15.0f};
};