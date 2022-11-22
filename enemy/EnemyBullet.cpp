#include "EnemyBullet.h"
#include "Math2.h"

EnemyBullet* EnemyBullet::GetInstance()
{
	static EnemyBullet instance;
	return &instance;
}

EnemyBullet::EnemyBullet()
{
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Initialize(ID3D12Device* device, Model* model, const XMFLOAT3& enemyPosition, const XMFLOAT3& enemyRotation, const XMFLOAT3& playerPosition)
{
	//ˆø”‚©‚çó‚¯æ‚Á‚½’l‚ğ•Ï”‚É‘ã“ü
	this->device_ = device;
	this->model_ = model;
	this->position_ = enemyPosition;
	this->rotation_ = enemyRotation;
	this->playerPosition_ = playerPosition;

	Object3D* newObject = new Object3D();
	newObject->Initialize(device_, model_);
	object3d_.reset(newObject);

	object3d_->setPosition(position_);
	object3d_->setRotation(rotation_);
	object3d_->setScale(scale_);

	velocity_.x = position_.x + playerPosition_.x;
	velocity_.y = position_.y + playerPosition_.y;
	velocity_.z = position_.z + playerPosition_.z;
}

void EnemyBullet::Update(XMMATRIX& matView, XMMATRIX& matProjection)
{
	//’e‚ÌˆÚ“®
	Move();

	object3d_->setPosition(position_);
	object3d_->setRotation(rotation_);
	object3d_->setScale(scale_);

	object3d_->Update(matView, matProjection);

	//ˆê’èŠÔŒo‰ß‚Å’eíœ
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void EnemyBullet::Move()
{
	position_.x += vector3Normalize(velocity_).x * speed;
	position_.y += vector3Normalize(velocity_).y * speed;
	position_.z += vector3Normalize(velocity_).z * speed;
}

void EnemyBullet::OnCollision()
{
	isDead_ = true;
}

void EnemyBullet::Draw(ID3D12GraphicsCommandList* cmdList)
{
	object3d_->Draw(cmdList, model_->vbView, model_->ibView);
}
