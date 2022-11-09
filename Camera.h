#pragma once
#include "DirectXMath.h"
#include "Input.h"
#include "WinApp.h"
#include "Player.h"

using namespace DirectX;

class Camera
{
public:
	//�V���O���g���C���X�^���X
	static Camera* GetInstance();
	//�C���X�g���N�^ �f�X�g���N�^
	Camera();
	~Camera();
	//������
	void Initialize(Input* input,Player* player);
	//�X�V
	void Update();
	//�v���C���[�̌������鋓��
	void homind();
	//�Q�b�^�[�Z�b�^�[
	void SetTarget(XMFLOAT3 pos);
	void SetEye(XMFLOAT3 pos);
	XMFLOAT3 GetEye() { return eye_; };
	XMFLOAT3 GetTraget() { return target_; };
	XMFLOAT3 GetUp() { return up_; };
	XMMATRIX GetMatProjection() { return matProjection_; };
	XMMATRIX GetMatView() { return matView_; };
private:
	//�v���C���[
	Player* player_;
	//����
	Input* input_;
	//�ˉe�ϊ�
	XMMATRIX matProjection_;
	//�r���[�ϊ��s��
	XMMATRIX matView_;
	XMFLOAT3 eye_ = { -10, 10, 30 };
	XMFLOAT3 target_ = { 0, 0, 0 };
	XMFLOAT3 up_ = { 0, 1, 0 };
	//�v���C���[�̌������鋓��
	//�v���C���[�ƃJ�����̋���
	float length_ = 30.0f;
};

