#pragma once
#include "WorldTransform.h"
#include "input.h"
#include "Model.h"
#include "DebugText.h"
#include <assert.h>
#include <memory.h>
#include <List>
#include "MathUtility.h"

#include "Affine.h"
#include "EnemyBullet.h"

using namespace MathUtility;

/// <summary>
///  自機クラスの前方宣言
/// </summary>
class Player;

/// <summary>
/// 敵
/// </summary>
class Enemy
{
public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="textureHandle">テクスチャハンドル</param>
	void Initailize(Model* model, const Vector3& position);

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="affine">アフィン変換</param>
	void Update(Affine* affine);

	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="viewProjection">ビュープロジェクション</param>
	void Draw(const ViewProjection& viewProjection);


	/// <summary>
	/// 敵の接近
	/// </summary>
	void ApproechMove();

	/// <summary>
	/// 敵の離脱
	/// </summary>
	void LeaveMove();

	/// <summary>
	/// 弾発射
	/// </summary>
	void Fire();

	/// <summary>
	/// 接近フェーズの初期化
	/// </summary>
	void ApproschInitislize();

	/// <summary>
	/// 差分ベクトル
	/// </summary>
	const void VecDifference();

	//衝突時コールバックを呼び出す
	void OnCollision();

	// 弾リストを取得
	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets() { return bullets_; }

public:
	// 発射間隔
	static int const kFireInterbal = 60;

	// セッター
	void SetPlayer(Player* player) { player_ = player; }

	// ワールド座標を取得
	Vector3 GetWorldPosition();

private:
	// ワールド変換データ
	WorldTransform worldTransform_;
	// モデル
	Model* model_ = nullptr;
	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;
	// デバックテキスト
	DebugText* debugText_ = nullptr;
	// 自キャラ
	Player* player_ = nullptr;

	// 弾
	std::list<std::unique_ptr<EnemyBullet>> bullets_;

	// 行動フェーズ
	enum class Phase {
		Approach,	// 接近する
		Leave,		// 離脱する
	};

	// フェーズ
	Phase phase_ = Phase::Approach;

	// 発射タイマー
	int32_t fireTimer = 0;
};

