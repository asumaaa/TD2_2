#include "Model.h"
#include "Object3D.h"
#include "DirectXCommon.h"
#include "DXInput.h"

#pragma once
class Player
{
public:
	//�V���O���g���C���X�^���X
	Player* GetInstance();
	Player();
	~Player();
	void Initialize(ID3D12Device* device,Model* model, DXInput* dxInput);
	void Update(XMMATRIX& matView, XMMATRIX& matProjection);
	bool Attack();
	void Move();
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//�Q�b�^�[�@�Z�b�^�[�@
	XMFLOAT3 GetPosition() { return position_; };
	XMFLOAT3 GetRotation() { return rotation1_; };
	XMFLOAT3 GetScale() { return scale_; };
	XMFLOAT3 GetVelocity() { return velocity; };
	void setPosition(XMFLOAT3 pos);
	void setRotation(XMFLOAT3 rot);
	void setScale(XMFLOAT3 sca);
private:
	/*DirectXCommon* dx_ = nullptr;*/
	ID3D12Device* device_;
	Model* model_ = nullptr;
	std::unique_ptr<Object3D> object3d_;
	DXInput* dxInput_;
	//�A�t�B���ϊ����
	XMFLOAT3 scale_ = { 1,1,1 };
	XMFLOAT3 rotation1_ = { 0,0,0 };	//�v���C���[�{���̊p�x
	XMFLOAT3 rotation2_ = { 0,0,0 };	//�I�u�W�F�N�g�ɓn���p�x
	XMFLOAT3 position_ = { 0,0,-100 };

	//�X�s�[�h
	XMFLOAT3 velocity;
	float speed = 1.0f;

	//�e�̃^�C�}�[
	int bulletTimer_ = 4;

	//�̗�
	float hp_ = 5;
};

