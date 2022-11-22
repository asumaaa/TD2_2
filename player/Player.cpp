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

void Player::Initialize(ID3D12Device* device,Model* model, DXInput* dxInput)
{
	//��������󂯎�����l����
	this->device_ = device;
	this->model_ = model;
	this->dxInput_ = dxInput;

	//�I�u�W�F�N�g������
	Object3D* newObject = new Object3D();
	newObject->Initialize(device_, model_);
	object3d_.reset(newObject);
}

void Player::Update(XMMATRIX& matView, XMMATRIX& matProjection)
{
	//�v���C���[�����X�ɏオ���Ă��鏈��
	if (phase1Timer_ < 200)
	{
		position1_.z += speed;
		position2_.z += speed;

		rotation2_.x -= PI * 25 / 36000;
		position2_.y += 0.125;
		phase1Timer_++;
	}

	if (phase1Timer_ >= 200)
	{
		Move();
	}

	object3d_->setScale(scale_);
	object3d_->setRotation(rotation2_);
	object3d_->setPosition(position2_);
	//�I�u�W�F�N�g�X�V
	object3d_->Update(matView, matProjection);
}

void Player::TitleUpdate(XMMATRIX& matView, XMMATRIX& matProjection)
{
	velocity = { 0, 0, speed };

	rotation1_.y -= PI / 900;
	rotation2_.y -= PI / 900;

	rollRotation(&velocity, rotation1_);

	position1_.x += velocity.x * speed;
	position1_.y += velocity.y * speed;
	position1_.z += velocity.z * speed;

	position2_.x += velocity.x * speed;
	position2_.y += velocity.y * speed;
	position2_.z += velocity.z * speed;

	object3d_->setScale(scale_);
	object3d_->setRotation(rotation2_);
	object3d_->setPosition(position2_);
	//�I�u�W�F�N�g�X�V
	object3d_->Update(matView, matProjection);
}

void Player::MoveToGameUpdate(XMMATRIX& matView, XMMATRIX& matProjection)
{
	//�^�C�}�[�n��
	moveToGameTimer_++;

	//���ۂ̋@��
	rotation1_.y -= PI / 900;
	rotation2_.y -= PI / 900;

	velocity = { 0, 0, speed };
	rollRotation(&velocity, rotation1_);

	position1_.x += velocity.x * speed;
	position1_.y += velocity.y * speed;
	position1_.z += velocity.z * speed;

	//�J�����ɔ��f������@�̂̈ʒu
	if (moveToGameTimer_ < 50)
	{
		speed2 -= 0.004;
	}
	if (moveToGameTimer_ >= 50 && moveToGameTimer_ < 280)
	{
		speed2 += 0.005;
	}
	velocity = { 0, 0, speed2 };
	rollRotation(&velocity, rotation1_);
	position2_.x += velocity.x * speed2;
	position2_.y += velocity.y * speed2;
	position2_.z += velocity.z * speed2;

	object3d_->setScale(scale_);
	object3d_->setRotation(rotation2_);
	object3d_->setPosition(position2_);
	//�I�u�W�F�N�g�X�V
	object3d_->Update(matView, matProjection);

	//400�t���[���������Q�[���Ɉڂ�t���O�𑗂�
	if (moveToGameTimer_ == 400)
	{
		GameStartFlag_ = true;
		moveToGameTimer_  = 0;
	}
}

bool Player::Attack()
{
	//R�{�^�������������邱�ƂŒe��A��
	if (dxInput_->GamePad.state.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)
	{
		bulletTimer_++;
		if (bulletTimer_ % 10 == 0)
		{
			return 1;
		}
	}
	return 0;
}

void Player::Move()
{
	velocity = { 0, 0, speed };

	//���X�e�b�N�̕ϐ�
	float x = dxInput_->GamePad.state.Gamepad.sThumbLY / (32767.0f) * (PI / 90.0f);
	float y = dxInput_->GamePad.state.Gamepad.sThumbLX / (32767.0f) * (PI / 90.0f) * 0.7f;
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
			rotation1_.x = -PI / 4 - x;
			rotation2_.x = -PI / 4 - x;
		}
	}
	//���E
	if (dxInput_->GamePad.state.Gamepad.sThumbLX != 0)
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

	position1_.x += velocity.x * speed;
	position1_.y += velocity.y * speed;
	position1_.z += velocity.z * speed;

	position2_.x += velocity.x * speed;
	position2_.y += velocity.y * speed;
	position2_.z += velocity.z * speed;
}

void Player::Draw(ID3D12GraphicsCommandList* cmdList)
{
	object3d_->Draw(cmdList,model_->vbView, model_->ibView);
}

void Player::setPosition(XMFLOAT3 pos)
{ 
	position1_ = pos;
}

void Player::setRotation(XMFLOAT3 rot)
{
	rotation1_ = rot;
}

void Player::setScale(XMFLOAT3 sca)
{
	scale_ = sca;
}

void Player::SetTitle()
{
	scale_ = { 1,1,1 };
	rotation1_ = { 0,0,0 };	//�v���C���[�{���̊p�x
	rotation2_ = { 0,0,0 };	//�I�u�W�F�N�g�ɓn���p�x
	position1_ = { 0,0,-300 };
	position2_ = { 0,0,-300 };	//�I�u�W�F�N�g�ɓn�����W
}

void Player::SetPhase1()
{
	scale_ = { 1,1,1 };
	rotation1_ = { 0,0,0 };	//�v���C���[�{���̊p�x
	rotation2_ = { PI * 25/180,0,0};	//�I�u�W�F�N�g�ɓn���p�x
	position1_ = { 0,0,-900 };
	position2_ = { 0,-25,-900 };	//�I�u�W�F�N�g�ɓn�����W
}
