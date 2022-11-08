
#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	/*for (int i = 0; i < object3ds_.size(); i++)
	{
		delete &object3ds_[i];
	}
	delete& cube_;*/
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input)
{
	this->dxCommon_ = dxCommon;
	this->input_ = input;

	//���f��������
	Model* newModel = new Model();
	newModel->Initialize(dxCommon_, "fighter", "Resources/fighter.png");
	model_.reset(newModel);
	//�I�u�W�F�N�g������
	Object3D* newObject = new Object3D();
	newObject->Initialize(dxCommon_, model_.get());
	object3Ds_.reset(newObject);

	//�J����������
	matView = XMMatrixLookAtLH(XMLoadFloat3(&eye), XMLoadFloat3(&target), XMLoadFloat3(&up));
}

void GameScene::Update()
{
	object3Ds_->Update(matView, matProjection);
}

void GameScene::Draw()
{
	object3Ds_->Draw(model_->vbView,model_->ibView);
}
