
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
	newModel->Initialize(dxCommon_, "fighter", "Resources/fighter.png");
	playerModel_.reset(newModel);

	//�v���C���[������
	Player* newPlayer = new Player();
	newPlayer->Initialize(dxCommon, playerModel_.get(),dxInput);
	player_.reset(newPlayer);

	//�����̃��f���̏�����
	Model* newStarModel = new Model();
	newStarModel->Initialize(dxCommon_, "star", "Resources/star.png");
	starDustModel_.reset(newStarModel);

	//����������
	StarDust* newStarDust = new StarDust();
	newStarDust->Initialize(dxCommon_, starDustModel_.get());
	starDust_.reset(newStarDust);

	//�J����������
	Camera* newCamera = new Camera();
	newCamera->Initialize(input_, player_.get());
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

	//�f�o�b�O�p
	/*XMFLOAT3 eye_(0,5,-30);
	XMFLOAT3 target_(0,0,0);
	XMFLOAT3 up_(0,1,0);
	XMMATRIX matView = XMMatrixLookAtLH(XMLoadFloat3(&eye_), XMLoadFloat3(&target_), XMLoadFloat3(&up_));*/


	//�I�u�W�F�N�g�X�V
	starDust_->Update(matView, matProjection);
	player_->Update(matView, matProjection);
}

void GameScene::Draw()
{
	starDust_->Draw();
	player_->Draw();
}

void GameScene::Delete()
{
	starDust_->Delete();
	delete starDust_.get();
	delete starDustModel_.get();
	delete playerModel_.get();
	delete player_.get();
	delete camera_.get();
}
