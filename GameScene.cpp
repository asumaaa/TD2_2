
#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input)
{
	this->dxCommon_ = dxCommon;
	this->input_ = input;

	//�v���C���[�̃��f��������
	Model* newModel = new Model();
	newModel->Initialize(dxCommon_, "fighter", "Resources/fighter.png");
	playerModel_.reset(newModel);

	//�v���C���[������
	//Player player;
	//player.Initialize(dxCommon, playerModel_.get());
	Player* newPlayer = new Player();
	newPlayer->Initialize(dxCommon, playerModel_.get());
	player_.reset(newPlayer);

	////�I�u�W�F�N�g������
	//Object3D* newObject = new Object3D();
	//newObject->Initialize(dxCommon_, playerModel_.get());
	//object3Ds_.reset(newObject);

	//�J����������
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
}

void GameScene::Update()
{
	/*object3Ds_->Update(matView, matProjection);*/
	player_->Update(matView, matProjection);
}

void GameScene::Draw()
{
	/*object3Ds_->Draw(playerModel_->vbView,playerModel_->ibView);*/
	player_->Draw();
}
