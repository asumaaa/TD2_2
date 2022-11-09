
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

	//プレイヤーのモデル初期化
	Model* newModel = new Model();
	newModel->Initialize(dxCommon_, "fighter", "Resources/fighter.png");
	playerModel_.reset(newModel);

	//プレイヤー初期化
	Player* newPlayer = new Player();
	newPlayer->Initialize(dxCommon, playerModel_.get());
	player_.reset(newPlayer);

	//カメラ初期化
	/*matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));*/
	Camera* newCamera = new Camera();
	newCamera->Initialize(input_, player_.get());
	camera_.reset(newCamera);
}

void GameScene::Update()
{
	camera_->Update();
	XMMATRIX matView = camera_->GetMatView();
	XMMATRIX matProjection = camera_->GetMatProjection();

	player_->Update(matView, matProjection);
}

void GameScene::Draw()
{
	player_->Draw();
}
