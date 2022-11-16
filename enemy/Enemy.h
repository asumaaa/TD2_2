#pragma once
#include "Model.h"
#include "Object3D.h"
#include "DirectXCommon.h"

class Enemy
{
public:
	//�V���O���g���C���X�^���X
	Enemy* GetInstance();
	Enemy();
	~Enemy();
	void Initialize(ID3D12Device* device, Model* model);
	void Update(XMMATRIX& matView, XMMATRIX& matProjection);
	bool Attack();
	void Move();
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//�Q�b�^�[�@�Z�b�^�[�@
	XMFLOAT3 GetPosition() { return position_; };
	XMFLOAT3 GetRotation() { return rotation_; };
	XMFLOAT3 GetScale() { return scale_; };
	void setPosition(XMFLOAT3 pos);
	void setRotation(XMFLOAT3 rot);
	void setScale(XMFLOAT3 sca);
private:
	/*DirectXCommon* dx_ = nullptr;*/
	ID3D12Device* device_;
	Model* model_ = nullptr;
	std::unique_ptr<Object3D> object3d_;
	//�A�t�B���ϊ����
	XMFLOAT3 scale_ = { 10,10,10 };
	XMFLOAT3 rotation_ = { 0,0,0 };
	XMFLOAT3 position_ = { 0,0,0 };

	//�e�̃^�C�}�[
	int bulletTimer_ = 0;

	//�̗�
	float hp_ = 100;
};

