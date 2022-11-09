#include "Camera.h"
#include "Math.h"
#define PI 3.14159265359

Camera* Camera::GetInstance()
{
	static Camera instance;
	return &instance;
}

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Initialize(Input* input, Player* player)
{
	//��������󂯎�����f�[�^����
	this->input_ = input;
	this->player_ = player;

	//�ˉe�ϊ�
	 matProjection_ = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(45.0f),			//�㉺��p45�x
		(float)window_width / window_height,//�A�X�y�N�g��(��ʉ���/��ʗ���)
		0.1f, 1000.0f						//�O�[�A���[
	);

	 //�s��v�Z
	 matView_ = XMMatrixLookAtLH(XMLoadFloat3(&eye_), XMLoadFloat3(&target_), XMLoadFloat3(&up_));
}


void Camera::Update()
{
	homind();
	//�s��v�Z
	matView_ = XMMatrixLookAtLH(XMLoadFloat3(&eye_), XMLoadFloat3(&target_), XMLoadFloat3(&up_));
}

void Camera::homind()
{
	float x, y, z;

	//�J�������v���C���[�̐^���Ɉړ�
	x = player_->GetPosition().x + (sin(-player_->GetRotation().x + (PI / 2)) * cos(-player_->GetRotation().y - (PI / 2)) * length_);
	y = player_->GetPosition().y + (cos(-player_->GetRotation().x + (PI * 9/20))* length_);
	z = player_->GetPosition().z + (sin(-player_->GetRotation().x + (PI / 2)) * sin(-player_->GetRotation().y - (PI / 2)) * length_);

	//�V��𒲐�
	if (sin(-player_->GetRotation().x + (PI / 2)) <= 0)
	{
		up_ = { 0,-1,0 };
	}
	else
	{
		up_ = { 0,1,0 };
	}

	//�J�����̍��W�ɑ��
	eye_ = { x,y,z };
	//�����_���v���C���[�̍��W�ɂ���
	target_ = { player_->GetPosition().x ,player_->GetPosition().y,player_->GetPosition().z };
}

void Camera::SetTarget(XMFLOAT3 pos)
{
	target_ = pos;
}

void Camera::SetEye(XMFLOAT3 pos)
{
	eye_ = pos;
}