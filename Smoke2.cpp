#include "Smoke2.h"
#include "stdlib.h"
#define PI 3.141592653589793238462643

Smoke2* Smoke2::GetInstance()
{
	return nullptr;
}

Smoke2::Smoke2()
{
}

Smoke2::~Smoke2()
{
}

void Smoke2::Initialize(ID3D12Device* device, Model* model, XMFLOAT3 position)
{
	//引数から受け取った変数を代入
	this->device_ = device;
	this->model_ = model;
	this->pos_ = position;
	//要素数確定
	position_.resize(smokeNum_);
	scale_.resize(smokeNum_);
	rotation_.resize(smokeNum_);

	//初期値設定
	for (int i = 0; i < smokeNum_; i++)
	{
		position_[i].x = position.x;
		position_[i].y = position.y;
		position_[i].z = position.z;
		scale_[i] = { 1,1,1 };
		rotation_[i] = { 0.0f,0.0f,0.0f };
	}
	//オブジェクト初期化
	for (int i = 0; i < smokeNum_; i++)
	{
		std::unique_ptr<Object3D> newObject = std::make_unique<Object3D>();
		newObject->Initialize(device_, model_);
		object3Ds_.push_back(std::move(newObject));
	}

	int i = 0;
	for (std::unique_ptr<Object3D>& object : object3Ds_)
	{
		object->setPosition(position_[i]);
		object->setRotation(rotation_[i]);
		object->setScale(scale_[i]);
		i++;
	}
}

void Smoke2::Update(XMMATRIX& matView, XMMATRIX& matProjection)
{
	//タイマー処理
	timer++;
	if (timer >= timerNum)
	{
		timer = 0;
	}

	//時間によってオブジェクトの位置を変更
	for (int i = 0; i < smokeNum_; i++)
	{
		if (i == timer)
		{
			//ランダムで位置を決定
			position_[i] = {
				pos_.x + static_cast<float>(rand() % 10 - 5),
				pos_.y + static_cast<float>(rand() % 10 - 5),
				pos_.z + static_cast<float>(rand() % 10 - 5) };
			scale_[i] = { 0.1,0.1 ,0.1};
		}
		position_[i].y += 4;
	}

	//スケールを段々と小さくする処理
	for (int i = 0; i < smokeNum_; i++)
	{
		scale_[i].x += 0.3;
		scale_[i].y += 0.3;
		scale_[i].z += 0.3;
	}

	//オブジェクト更新
	int i = 0;
	for (std::unique_ptr<Object3D>& object : object3Ds_)
	{
		object->setPosition(position_[i]);
		object->setRotation(rotation_[i]);
		object->setScale(scale_[i]);
		object->Update(matView, matProjection);
		i++;
	}
}

void Smoke2::Draw(ID3D12GraphicsCommandList* cmdList)
{
	for (std::unique_ptr<Object3D>& object : object3Ds_)
	{
		object->Draw(cmdList, model_->vbView, model_->ibView);
	}
}