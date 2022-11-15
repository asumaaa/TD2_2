#include "Smoke.h"
#include "stdlib.h"
#define PI 3.141592653589793238462643

Smoke* Smoke::GetInstance()
{
	return nullptr;
}

Smoke::Smoke()
{
}

Smoke::~Smoke()
{
}

void Smoke::Initialize(ID3D12Device* device, Model* model, XMFLOAT3 position)
{
	//��������󂯎�����ϐ�����
	this->device_ = device;
	this->model_ = model;
	//�v�f���m��
	position_.resize(smokeNum_);
	scale_.resize(smokeNum_);
	rotation_.resize(smokeNum_);

	//�����l�ݒ�
	for (int i = 0; i < smokeNum_; i++)
	{
		position_[i].x = position.x;
		position_[i].y = position.y;
		position_[i].z = position.z;
		scale_[i] = { 1,1,1 };
		rotation_[i] = { 0.0f,0.0f,0.0f };
	}
	//�I�u�W�F�N�g������
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

void Smoke::Update(XMMATRIX& matView, XMMATRIX& matProjection, XMFLOAT3 position, XMFLOAT3 rotation)
{
	//�^�C�}�[����
	timer++;
	if (timer >= timerNum)
	{
		timer = 0;
	}

	//���Ԃɂ���ăI�u�W�F�N�g�̈ʒu��ύX
	for (int i = 0; i < smokeNum_; i++)
	{
		if (i == timer)
		{
			//�����_���ňʒu������
			position_[i] = {
				position.x + static_cast<float>(cos(-rotation.y - (PI / 2)) * length_) + static_cast<float>(rand() % 2 - 1),
				position.y + static_cast<float>(cos(-rotation.x + (PI / 2)) * length_) + static_cast<float>(rand() % 2 - 1),
				position.z + static_cast<float>(sin(-rotation.y - (PI / 2)) * length_) + static_cast<float>(rand() % 2 - 1) };
			rotation_[i] = {rotation.x,rotation.y,rotation.z };
			scale_[i] = { scaleSetNum_,scaleSetNum_, scaleSetNum_ };
		}
	}

	//�X�P�[����i�X�Ə��������鏈��
	for (int i = 0; i < smokeNum_; i++)
	{
		scale_[i].x -= scaleSetNum_ / smokeNum_;
		scale_[i].y -= scaleSetNum_ / smokeNum_;
		scale_[i].z -= scaleSetNum_ / smokeNum_;
	}

	//�I�u�W�F�N�g�X�V
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

void Smoke::Draw(ID3D12GraphicsCommandList* cmdList)
{
	for (std::unique_ptr<Object3D>& object : object3Ds_)
	{
		object->Draw(cmdList,model_->vbView, model_->ibView);
	}
}
