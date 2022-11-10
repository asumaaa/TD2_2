
#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
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

	////プレイヤーのモデル初期化
	//Model* newModel = new Model();
	//newModel->Initialize(dxCommon_, "fighter", "Resources/fighter.png");
	//playerModel_.reset(newModel);

	////プレイヤー初期化
	//Player* newPlayer = new Player();
	//newPlayer->Initialize(dxCommon, playerModel_.get());
	//player_.reset(newPlayer);

	////星屑のモデルの初期化
	//Model* newStarModel = new Model();
	//newStarModel->Initialize(dxCommon_, "star", "Resources/star.png");
	//starDustModel_.reset(newStarModel);

	////星屑初期化
	//StarDust* newStarDust = new StarDust();
	//newStarDust->Initialize(dxCommon_, starDustModel_.get());
	//starDust_.reset(newStarDust);

	////カメラ初期化
	//Camera* newCamera = new Camera();
	//newCamera->Initialize(input_, player_.get());
	//camera_.reset(newCamera);
}

void GameScene::Update()
{
	/*camera_->Update();
	XMMATRIX matView = camera_->GetMatView();
	XMMATRIX matProjection = camera_->GetMatProjection();*/

	/*starDust_->Update(matView, matProjection);
	player_->Update(matView, matProjection);*/
}

void GameScene::Draw()
{
	/*starDust_->Draw();
	player_->Draw();*/
}

void GameScene::Delete()
{
	/*starDust_->Delete();
	delete starDust_.get();
	delete starDustModel_.get();
	delete playerModel_.get();
	delete player_.get();
	delete camera_.get();*/
}
