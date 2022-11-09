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
	//引数から受け取ったデータを代入
	this->input_ = input;
	this->player_ = player;

	//射影変換
	 matProjection_ = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(45.0f),			//上下画角45度
		(float)window_width / window_height,//アスペクト比(画面横幅/画面立幅)
		0.1f, 1000.0f						//前端、奥端
	);

	 //行列計算
	 matView_ = XMMatrixLookAtLH(XMLoadFloat3(&eye_), XMLoadFloat3(&target_), XMLoadFloat3(&up_));
}


void Camera::Update()
{
	homind();
	//行列計算
	matView_ = XMMatrixLookAtLH(XMLoadFloat3(&eye_), XMLoadFloat3(&target_), XMLoadFloat3(&up_));
}

void Camera::homind()
{
	float x, y, z;

	//カメラをプレイヤーの真後ろに移動
	x = player_->GetPosition().x + (sin(-player_->GetRotation().x + (PI / 2)) * cos(-player_->GetRotation().y - (PI / 2)) * length_);
	y = player_->GetPosition().y + (cos(-player_->GetRotation().x + (PI * 9/20))* length_);
	z = player_->GetPosition().z + (sin(-player_->GetRotation().x + (PI / 2)) * sin(-player_->GetRotation().y - (PI / 2)) * length_);

	//天井を調整
	if (sin(-player_->GetRotation().x + (PI / 2)) <= 0)
	{
		up_ = { 0,-1,0 };
	}
	else
	{
		up_ = { 0,1,0 };
	}

	//カメラの座標に代入
	eye_ = { x,y,z };
	//注視点をプレイヤーの座標にする
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