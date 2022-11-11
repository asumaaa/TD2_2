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
	//引数から受け取った値を代入
	this->dx_ = dx;
	this->model_ = model;
	this->dxInput_ = dxInput;

	//オブジェクト初期化
	Object3D* newObject = new Object3D();
	newObject->Initialize(dx_, model_);
	object3d_.reset(newObject);
}

void Player::Update(XMMATRIX& matView, XMMATRIX& matProjection)
{
	/*position_.z += 0.02;*/
	/*if (dxInput_->GamePad.state.Gamepad.wButtons == XINPUT_GAMEPAD_DPAD_LEFT)
	{
		position_.z += 0.02;
	}*/

	Move();

	object3d_->setPosition(position_);
	object3d_->setRotation(rotation2_);
	object3d_->setScale(scale_);
	//オブジェクト更新
	object3d_->Update(matView, matProjection);
}

void Player::Move()
{
	//コントローラーの入力によって傾ける
	float x = dxInput_->GamePad.state.Gamepad.sThumbLY / (32767.0f) * (PI / 90.0f);
	rotation1_.x -= x;
	rotation2_.x -= x;

	//左スティックで機体を傾ける処理
	float z = -dxInput_->GamePad.state.Gamepad.sThumbLX / (32767.0f) * (PI / 90.0f);
	if (dxInput_->GamePad.state.Gamepad.sThumbLX != 0)
	{
		if (rotation2_.z < PI / 6 && rotation2_.z > -PI / 6)
		{
			rotation2_.z += z;
		}
		if (rotation2_.z > PI / 6)
		{
			rotation2_.z = PI / 6 - z;
		}
		if (rotation2_.z < -PI / 6)
		{
			rotation2_.z = -PI / 6 + z;
		}
	}
	//ステックに触っていないときの処理
	else if (rotation2_.z != 0)
	{
		if (rotation2_.z < -(PI / 90.0f))
		{
			rotation2_.z += (PI / 90.0f);
		}
		else if(rotation2_.z > (PI / 90.0f))
		{
			rotation2_.z -= (PI / 90.0f);
		}
	}

	//左ステックで機体の角度を変えて進行方向を変更
	if (dxInput_->GamePad.state.Gamepad.sThumbLX != 0)
	{
		if (sin(rotation1_.x + (PI / 2) >= 0))
		{
			rotation1_.y += dxInput_->GamePad.state.Gamepad.sThumbLX / (32767.0f) * (PI / 90.0f);
			rotation2_.y += dxInput_->GamePad.state.Gamepad.sThumbLX / (32767.0f) * (PI / 90.0f);
		}
		else
		{
			rotation1_.y -= dxInput_->GamePad.state.Gamepad.sThumbLX / (32767.0f) * (PI / 90.0f);
			rotation2_.y -= dxInput_->GamePad.state.Gamepad.sThumbLX / (32767.0f) * (PI / 90.0f);
		}
	}

	//直進
	XMFLOAT3 velocity(0, 0, speed);
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
