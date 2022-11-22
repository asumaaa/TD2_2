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
	void TitleUpdate(XMMATRIX& matView, XMMATRIX& matProjection);	//�^�C�g����ʂ̏���
	void MoveToGameUpdate(XMMATRIX& matView, XMMATRIX& matProjection);	//�^�C�g������Q�[���Ɉڂ鎞�̏���
	bool Attack();
	void Move();
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//�Q�b�^�[�@�Z�b�^�[�@
	XMFLOAT3 GetPosition1() { return position1_; };
	XMFLOAT3 GetPosition2() { return position2_; };
	XMFLOAT3 GetRotation() { return rotation1_; };
	XMFLOAT3 GetScale() { return scale_; };
	XMFLOAT3 GetVelocity() { return velocity; };
	bool GetGameStartFlag_() { return GameStartFlag_; };
	void setPosition(XMFLOAT3 pos);
	void setRotation(XMFLOAT3 rot);
	void setScale(XMFLOAT3 sca);
	//�V�[���؂�ւ����̃Z�b�^�[
	void SetTitle();
	void SetPhase1();
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
	XMFLOAT3 position1_ = { 0,0,0 };
	XMFLOAT3 position2_ = { 0,0,0 };	//�I�u�W�F�N�g�ɓn�����W

	//�X�s�[�h
	XMFLOAT3 velocity;
	float speed = 1.0f;
	float speed2 = 1.0f;

	//�e�̃^�C�}�[
	int bulletTimer_ = 4;

	//�̗�
	float hp_ = 5;

	//�^�C�g������ڂ��ʂ̃t���O
	int moveToGameTimer_ = 0;
	bool GameStartFlag_ = false;

	//�t�F�[�Y�P���n�܂鎞�̃^�C�}�[
	int phase1Timer_ = 0;
public:
	void phase1TimerRiset() { phase1Timer_ = 0; };

};

