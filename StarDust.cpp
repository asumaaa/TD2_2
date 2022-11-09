#include "StarDust.h"
#include "stdlib.h"

StarDust* StarDust::GetInstance()
{
	static StarDust instance;
	return &instance;
}

StarDust::StarDust()
{
}

StarDust::~StarDust()
{
}

void StarDust::Initialize(DirectXCommon* dx, Model* model)
{
	this->dx_ = dx;
	this->model_ = model;


	position_.resize(starDustNum);
	scale_.resize(starDustNum);
	rotation_.resize(starDustNum);

	//初期値設定
	for (int i = 0; i < starDustNum; i++)
	{
		position_[i].x = static_cast<float>(rand() % 100 - 50);
		position_[i].y = static_cast<float>(rand() % 100 - 50);
		position_[i].z = static_cast<float>(rand() % 100 - 50);
		scale_[i] = { 0.05f,0.05f,0.05f };
		rotation_[i] = { 0.0f,0.0f,0.0f };
	}
	//オブジェクト初期化
	for (int i = 0; i < starDustNum; i++)
	{
		std::unique_ptr<Object3D> newObject = std::make_unique<Object3D>();
		newObject->Initialize(dx_, model_);
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

void StarDust::Update(XMMATRIX& matView, XMMATRIX& matProjection)
{
	for (std::unique_ptr<Object3D>& object : object3Ds_)
	{
		object->Update(matView, matProjection);
	}
}

void StarDust::Draw()
{
	for (std::unique_ptr<Object3D>& object : object3Ds_)
	{
		object->Draw(model_->vbView, model_->ibView);
	}
}

void StarDust::Delete()
{
	/*for (std::unique_ptr<Object3D>& object : object3Ds_)
	{
		delete& object3Ds_;
	}*/
}
