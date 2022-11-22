#include "PlayerBullet.h"
#include <cassert>

PlayerBullet* PlayerBullet::GetInstance()
{
	static PlayerBullet instance;
	return &instance;
}

PlayerBullet::PlayerBullet()
{
}

PlayerBullet::~PlayerBullet()
{
}

void PlayerBullet::Initialize(ID3D12Device* device, Model* model, const XMFLOAT3& position, const XMFLOAT3& rotation, const XMFLOAT3& velocity)
{
	assert(model);

	//��������󂯎�����l��ϐ��ɑ��
	this->device_ = device;
	this->model_ = model;
	this->position_ = position;
	this->rotation_ = rotation;
	this->velocity_ = velocity;

	Object3D* newObject = new Object3D();
	newObject->Initialize(device_, model_);
	object3d_.reset(newObject);

	object3d_->setPosition(position_);
	object3d_->setRotation(rotation_);
	object3d_->setScale(scale_);
}

void PlayerBullet::Update(XMMATRIX& matView, XMMATRIX& matProjection)
{
	//�e�̈ړ�
	Move();

	object3d_->setPosition(position_);
	object3d_->setRotation(rotation_);
	object3d_->setScale(scale_);

	object3d_->Update(matView, matProjection);

	//��莞�Ԍo�߂Œe�폜
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void PlayerBullet::Move()
{
	//�e�̈ړ�
	position_.x += velocity_.x * speed;
	position_.y += velocity_.y * speed;
	position_.z += velocity_.z * speed;
}

void PlayerBullet::OnCollision()
{
	isDead_ = true;
}

void PlayerBullet::Draw(ID3D12GraphicsCommandList* cmdList)
{
	object3d_->Draw(cmdList, model_->vbView, model_->ibView);
}
