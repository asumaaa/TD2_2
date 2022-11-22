#include "Model.h"
#include "Object3D.h"
#include "DirectXCommon.h"
#include "DXInput.h"

#pragma once
class Player
{
public:
	//シングルトンインスタンス
	Player* GetInstance();
	Player();
	~Player();
	void Initialize(ID3D12Device* device,Model* model, DXInput* dxInput);
	void Update(XMMATRIX& matView, XMMATRIX& matProjection);
	void TitleUpdate(XMMATRIX& matView, XMMATRIX& matProjection);	//タイトル画面の処理
	void MoveToGameUpdate(XMMATRIX& matView, XMMATRIX& matProjection);	//タイトルからゲームに移る時の処理
	bool Attack();
	void Move();
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//ゲッター　セッター　
	XMFLOAT3 GetPosition1() { return position1_; };
	XMFLOAT3 GetPosition2() { return position2_; };
	XMFLOAT3 GetRotation() { return rotation1_; };
	XMFLOAT3 GetScale() { return scale_; };
	XMFLOAT3 GetVelocity() { return velocity; };
	bool GetGameStartFlag_() { return GameStartFlag_; };
	void setPosition(XMFLOAT3 pos);
	void setRotation(XMFLOAT3 rot);
	void setScale(XMFLOAT3 sca);
	//シーン切り替え時のセッター
	void SetTitle();
	void SetPhase1();
private:
	/*DirectXCommon* dx_ = nullptr;*/
	ID3D12Device* device_;
	Model* model_ = nullptr;
	std::unique_ptr<Object3D> object3d_;
	DXInput* dxInput_;
	//アフィン変換情報
	XMFLOAT3 scale_ = { 1,1,1 };
	XMFLOAT3 rotation1_ = { 0,0,0 };	//プレイヤー本来の角度
	XMFLOAT3 rotation2_ = { 0,0,0 };	//オブジェクトに渡す角度
	XMFLOAT3 position1_ = { 0,0,0 };
	XMFLOAT3 position2_ = { 0,0,0 };	//オブジェクトに渡す座標

	//スピード
	XMFLOAT3 velocity;
	float speed = 1.0f;
	float speed2 = 1.0f;

	//弾のタイマー
	int bulletTimer_ = 4;

	//体力
	float hp_ = 5;

	//タイトルから移る場面のフラグ
	int moveToGameTimer_ = 0;
	bool GameStartFlag_ = false;

	//フェーズ１が始まる時のタイマー
	int phase1Timer_ = 0;
public:
	void phase1TimerRiset() { phase1Timer_ = 0; };

};

