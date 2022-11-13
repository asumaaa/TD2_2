#include "Player.h"
#include "Math2.h"
#define PI 3.141592653589793238462643

Player* Player::GetInstance()
{
	static Player instance;
	return &instance;
}

Player::Player()
{
}

Player::~Player()
{
}

void Player::Initialize(DirectXCommon* dx,Model* model, DXInput* dxInput)
{
	//��������󂯎�����l����
	this->dx_ = dx;
	this->model_ = model;
	this->dxInput_ = dxInput;

	//�I�u�W�F�N�g������
	Object3D* newObject = new Object3D();
	newObject->Initialize(dx_, model_);
	object3d_.reset(newObject);

	/*rotation1_.x = PI / 2;
	rotation2_.x = PI / 2;*/
}

void Player::Update(XMMATRIX& matView, XMMATRIX& matProjection)
{
	/*position_.z += 0.02;*/
	/*if (dxInput_->GamePad.state.Gamepad.wButtons == XINPUT_GAMEPAD_DPAD_LEFT)
	{
		position_.z += 0.02;
	}*/

	Move();

	object3d_->setScale(scale_);
	object3d_->setRotation(rotation2_);
	object3d_->setPosition(position_);
	//�I�u�W�F�N�g�X�V
	object3d_->Update(matView, matProjection);
}

void Player::Move()
{
	XMFLOAT3 velocity(0, 0, speed);
	//�R���g���[���[�̓��͂ɂ���ČX����
	/*float x = dxInput_->GamePad.state.Gamepad.sThumbLY / (32767.0f) * (PI / 90.0f);
	if (dxInput_->GamePad.state.Gamepad.sThumbLY > 15000 || dxInput_->GamePad.state.Gamepad.sThumbLY < -15000)
	{
		rotation1_.x -= x;
		rotation2_.x -= x;
	}*/

	//���X�e�B�b�N�ŋ@�̂��X���鏈��
	//float z = -dxInput_->GamePad.state.Gamepad.sThumbLX / (32767.0f) * (PI / 90.0f);
	//if (dxInput_->GamePad.state.Gamepad.sThumbLX > 15000 || dxInput_->GamePad.state.Gamepad.sThumbLX < -15000)
	//{
	//	if (rotation2_.z < PI / 6 && rotation2_.z > -PI / 6)
	//	{
	//		rotation2_.z += z;
	//	}
	//	if (rotation2_.z > PI / 6)
	//	{
	//		rotation2_.z = PI / 6 - z;
	//	}
	//	if (rotation2_.z < -PI / 6)
	//	{
	//		rotation2_.z = -PI / 6 + z;
	//	}
	//}
	////�X�e�b�N�ɐG���Ă��Ȃ��Ƃ��̏���
	//else if (rotation2_.z != 0)
	//{
	//	if (rotation2_.z < -(PI / 90.0f))
	//	{
	//		rotation2_.z += (PI / 90.0f);
	//	}
	//	else if(rotation2_.z > (PI / 90.0f))
	//	{
	//		rotation2_.z -= (PI / 90.0f);
	//	}
	//}

	//���X�e�b�N�̕ϐ�
	float x = dxInput_->GamePad.state.Gamepad.sThumbLY / (32767.0f) * (PI / 90.0f);
	float y = dxInput_->GamePad.state.Gamepad.sThumbLX / (32767.0f) * (PI / 90.0f);
	//�㉺
	if (dxInput_->GamePad.state.Gamepad.sThumbLY > 15000 || dxInput_->GamePad.state.Gamepad.sThumbLY < -15000)
	{
		if (rotation1_.x < PI / 4 && rotation1_.x > -PI / 4)
		{
			rotation1_.x -= x;
			rotation2_.x -= x;
		}
		if (rotation1_.x > PI / 4)
		{
			rotation1_.x = PI / 4 - x;
			rotation2_.x = PI / 4 - x;
		}
		if (rotation1_.x < -PI / 4)
		{
			rotation1_.x = -PI / 4 + x;
			rotation2_.x = -PI / 4 + x;
		}
	}
	//���E
	if (dxInput_->GamePad.state.Gamepad.sThumbLX > 15000 || dxInput_->GamePad.state.Gamepad.sThumbLX < -15000)
	{
		if (sin(rotation1_.x + (PI / 2) >= 0))
		{
			velocity = { speed * 3 / 10,  0, speed * 7 / 10 };
			rotation1_.y += y;
			rotation2_.y += y;
		}
		else
		{
			velocity = { -speed * 3 / 10,  0, speed * 7 / 10 };
			rotation1_.y -= y;
			rotation2_.y -= y;
		}
	}
	//���X�e�B�b�N�ŋ@�̂��X���鏈��
	if (dxInput_->GamePad.state.Gamepad.sThumbLX > 15000 || dxInput_->GamePad.state.Gamepad.sThumbLX < -15000)
	{
		if (rotation2_.z < PI / 6 && rotation2_.z > -PI / 6)
		{
			rotation2_.z -= y;
		}
		if (rotation2_.z > PI / 6)
		{
			rotation2_.z = PI / 6 - y;
		}
		if (rotation2_.z < -PI / 6)
		{
			rotation2_.z = -PI / 6 + y;
		}
	}
	//�X�e�b�N�ɐG���Ă��Ȃ��Ƃ��̏���
	else if (rotation2_.z != 0)
	{
		if (rotation2_.z < -(PI / 90.0f))
		{
			rotation2_.z += (PI / 90.0f);
		}
		else if (rotation2_.z > (PI / 90.0f))
		{
			rotation2_.z -= (PI / 90.0f);
		}
	}


	//���i
	/*XMFLOAT3 velocity(0, 0, speed);*/
	rollRotation(&velocity, rotation1_ );

	position_.x += velocity.x * speed;
	position_.y += velocity.y * speed;
	position_.z += velocity.z * speed;
}

void Player::Draw()
{
	object3d_->Draw(model_->vbView, model_->ibView);
}

void Player::setPosition(XMFLOAT3 pos)
{ 
	position_ = pos;
}

void Player::setRotation(XMFLOAT3 rot)
{
	rotation1_ = rot;
}

void Player::setScale(XMFLOAT3 sca)
{
	scale_ = sca;
}
