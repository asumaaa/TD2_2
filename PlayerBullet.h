#pragma once
#include "Model.h"
#include "Object3D.h"
#include "DirectXCommon.h"

class PlayerBullet
{
public:
	//�V���O���g���C���X�^���X
	PlayerBullet* GetInstance();
	PlayerBullet();
	~PlayerBullet();
	void Initialize(ID3D12Device* device, Model* model,const XMFLOAT3& position, const XMFLOAT3& velocity);
	void Update(XMMATRIX& matView, XMMATRIX& matProjection);
	void Move();
	void OnCollision();
	void Draw(ID3D12GraphicsCommandList* cmdList);
	bool IsDead()const { return isDead_; }
private:
	ID3D12Device* device_;
	Model* model_ = nullptr;
	std::unique_ptr<Object3D> object3d_;
	//�A�t�B���ϊ����
	XMFLOAT3 scale_ = { 1,1,1 };
	XMFLOAT3 rotation_ = { 0,0,0 };
	XMFLOAT3 position_ = { 0,0,0 };

	//�X�s�[�h
	XMFLOAT3 velocity_;
	float speed = 3.0f;

	//����
	static const int32_t lifeTime = 60;
	//�f�X�^�C�}�[
	int32_t deathTimer_ = lifeTime;
	//�f�X�t���O
	bool isDead_ = false;
};

