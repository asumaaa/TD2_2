#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	delete dxInput;
	/*delete starDust_.get();
	delete starDustModel_.get();
	delete playerModel_.get();
	delete player_.get();
	delete camera_.get();*/
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input)
{
	this->dxCommon_ = dxCommon;
	this->input_ = input;

	//�v���C���[�̃��f��������
	Model* newModel = new Model();
	newModel->Initialize(dxCommon_->GetDevice(), "fighter", "Resources/fighter.png");
	playerModel_.reset(newModel);

	//�e�̃��f���̏�����
	Model* newBulletModel = new Model();
	newBulletModel->Initialize(dxCommon_->GetDevice(), "bullet", "Resources/bullet.png");
	bulletModel_.reset(newBulletModel);

	//�����̃��f���̏�����
	Model* newStarModel = new Model();
	newStarModel->Initialize(dxCommon_->GetDevice(), "star", "Resources/star.png");
	starDustModel_.reset(newStarModel);

	//�v���C���[������
	Player* newPlayer = new Player();
	newPlayer->Initialize(dxCommon_->GetDevice(), playerModel_.get(),dxInput);
	player_.reset(newPlayer);

	//�v���C���[�̉�������
	Smoke* newSmoke = new Smoke();
	newSmoke->Initialize(dxCommon_->GetDevice(), starDustModel_.get(), player_->GetPosition());
	smoke_.reset(newSmoke);

	//����������
	StarDust* newStarDust = new StarDust();
	newStarDust->Initialize(dxCommon_->GetDevice(), starDustModel_.get());
	starDust_.reset(newStarDust);

	//�J����������
	Camera* newCamera = new Camera();
	newCamera->Initialize(input_,dxInput, player_.get());
	camera_.reset(newCamera);
}

void GameScene::Update()
{
	//�R���g���[���[�X�V
	dxInput->InputProcess();

	//�J�����X�V
	camera_->Update();
	XMMATRIX matView = camera_->GetMatView();
	XMMATRIX matProjection = camera_->GetMatProjection();

	//�f�o�b�O�p���_
	/*XMFLOAT3 eye_(0,5,-30);
	XMFLOAT3 target_(0,0,0);
	XMFLOAT3 up_(0,1,0);
	XMMATRIX matView = XMMatrixLookAtLH(XMLoadFloat3(&eye_), XMLoadFloat3(&target_), XMLoadFloat3(&up_));*/

	//�����X�V
	starDust_->Update(matView, matProjection);

	//�v���C���[�X�V
	player_->Update(matView, matProjection);

	//�v���C���[�̉��X�V
	smoke_->Update(matView, matProjection,player_->GetPosition(), player_->GetRotation());
	
	//�v���C���[����󂯎�����t���O�Œe����
	if (player_->Attack() == 1)
	{
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(dxCommon_->GetDevice(), bulletModel_.get(), player_->GetPosition(), player_->GetVelocity());
		playerBullet_.push_back(std::move(newBullet));
	}
	//�v���C���[�̒e�X�V
	for (std::unique_ptr<PlayerBullet>& bullet : playerBullet_)
	{
		bullet->Update(matView, matProjection);
	}
	//�f�X�t���O�̗������e���폜
	playerBullet_.remove_if([](std::unique_ptr<PlayerBullet>& bullet)
		{return bullet->IsDead(); }
	);
}

void GameScene::Draw()
{
	starDust_->Draw(dxCommon_->GetCommandList());
	player_->Draw(dxCommon_->GetCommandList());
	smoke_->Draw(dxCommon_->GetCommandList());
	//�v���C���[�̒e�X�V
	for (std::unique_ptr<PlayerBullet>& bullet : playerBullet_)
	{
		bullet->Draw(dxCommon_->GetCommandList());
	}
}

void GameScene::Delete()
{
	/*starDust_->Delete();*/
	/*delete starDust_.get();
	delete starDustModel_.get();
	delete playerModel_.get();
	delete player_.get();
	delete camera_.get();*/
}
