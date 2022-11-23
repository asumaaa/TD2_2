#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	delete dxInput;
	//XAudio2���
	xAudio2.Reset();
	/*delete &titleSprite_;
	delete &spriteCommon_;
	delete sprite_;*/
	/*delete starDust_.get();
	delete starDustModel_.get();
	delete playerModel_.get();
	delete player_.get();
	delete camera_.get();*/
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input)
{
	HRESULT result;
	this->dxCommon_ = dxCommon;
	this->input_ = input;

	//�v���C���[�̃��f��������
	Model* newModel = new Model();
	newModel->Initialize(dxCommon_->GetDevice(), "fighter", "Resources/fighter.png");
	playerModel_.reset(newModel);

	//�G�̃��f��������
	Model* newEnemyModel = new Model();
	newEnemyModel->Initialize(dxCommon_->GetDevice(), "boss", "Resources/boss.png");
	enemyModel_.reset(newEnemyModel);

	//�e�̃��f���̏�����
	Model* newBulletModel = new Model();
	newBulletModel->Initialize(dxCommon_->GetDevice(), "bullet", "Resources/bullet.png");
	bulletModel_.reset(newBulletModel);

	//�G�̒e�̃��f���̏�����
	Model* newEnemyBulletModel = new Model();
	newEnemyBulletModel->Initialize(dxCommon_->GetDevice(), "enemyBullet", "Resources/enemyBullet.png");
	enemyBulletModel_.reset(newEnemyBulletModel);

	//�����̃��f���̏�����
	Model* newStarModel = new Model();
	newStarModel->Initialize(dxCommon_->GetDevice(), "star", "Resources/star.png");
	starDustModel_.reset(newStarModel);

	//�v���C���[������
	Player* newPlayer = new Player();
	newPlayer->Initialize(dxCommon_->GetDevice(), playerModel_.get(),dxInput);
	player_.reset(newPlayer);
	//���W���Z�b�g
	player_->SetTitle();

	//�v���C���[�̉�������
	Smoke* newSmoke = new Smoke();
	newSmoke->Initialize(dxCommon_->GetDevice(), starDustModel_.get(), player_->GetPosition1());
	smoke_.reset(newSmoke);

	//�G������
	Enemy* newEnemy = new Enemy();
	newEnemy->Initialize(dxCommon_->GetDevice(), enemyModel_.get());
	enemy_.reset(newEnemy);

	//����������
	StarDust* newStarDust = new StarDust();
	newStarDust->Initialize(dxCommon_->GetDevice(), starDustModel_.get());
	starDust_.reset(newStarDust);

	//�v���C���[�̉�������
	for (int i = 0; i < 4; i++)
	{
		Smoke2* newSmoke2 = new Smoke2();
		if (i == 0)newSmoke2->Initialize(dxCommon_->GetDevice(), starDustModel_.get(), XMFLOAT3(25, 25, 0));
		if (i == 1)newSmoke2->Initialize(dxCommon_->GetDevice(), starDustModel_.get(), XMFLOAT3(-15, 15, 0));
		if (i == 2)newSmoke2->Initialize(dxCommon_->GetDevice(), starDustModel_.get(), XMFLOAT3(0, 25, 0));
		if(i == 3)newSmoke2->Initialize(dxCommon_->GetDevice(), starDustModel_.get(), XMFLOAT3(-25, -25, 0));
		enemySmoke2_[i].reset(newSmoke2);
	}


	//XAudio�G���W���̃C���X�^���X�𐶐�
	result = XAudio2Create(&xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	//�}�X�^�[�{�C�X�𐶐�
	result = xAudio2->CreateMasteringVoice(&masterVoice);

	//��
	/*SoundData BGMSoundData = BGMSound->SoundLoadWave("Resources/sound/shot1.wav");*/

	//�X�v���C�g������
	spriteCommon_ = sprite_->SpriteCommonCreate(dxCommon_->GetDevice(), 1280, 720);
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 0, L"Resources/title.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 1, L"Resources/operation.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 2, L"Resources/operation1.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 3, L"Resources/Sprite-0005.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 4, L"Resources/operation91.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 5, L"Resources/playerHp.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 6, L"Resources/enemyHp.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 7, L"Resources/enemyHp1.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 8, L"Resources/curtain.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 9, L"Resources/gameclear.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 10, L"Resources/gameover.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 11, L"Resources/gametitle_4.png", dxCommon_->GetDevice());
	titleSprite_.SpriteCreate(dxCommon_->GetDevice(), 1280, 720);
	pushSprite_.SpriteCreate(dxCommon_->GetDevice(), 1280, 720);
	pushSprite_.SetTexNumber(11);
	pushSprite_.SetScale(XMFLOAT2(564, 71));
	pushSprite_.SetPosition(XMFLOAT3(0, 620, 0));
	pushSprite_.SpriteTransferVertexBuffer(pushSprite_);
	pushSprite_.SpriteUpdate(pushSprite_, spriteCommon_);
	operationSprite_.SpriteCreate(dxCommon_->GetDevice(), 1280, 720);	//oparation.png
	operation1Sprite_.SpriteCreate(dxCommon_->GetDevice(), 1280, 720);	//oparation1.png
	operation2Sprite_.SpriteCreate(dxCommon_->GetDevice(), 1280, 720);	//oparation2.png
	operation3Sprite_.SpriteCreate(dxCommon_->GetDevice(), 1280, 720);	//oparation3.png
	//playerHp.png
	for (int i = 0; i < 5; i++)
	{
		playerHpSprite_[i].SpriteCreate(dxCommon_->GetDevice(), 1280, 720);
		playerHpSprite_[i].SetTexNumber(5);
	}
	enemyHpSprite_.SpriteCreate(dxCommon_->GetDevice(), 1280, 720);	//playerHp.png
	enemyHp1Sprite_.SpriteCreate(dxCommon_->GetDevice(), 1280, 720);	//enemyHp.png
	//�e�N�X�`���ԍ��Z�b�g
	titleSprite_.SetTexNumber(0);
	operationSprite_.SetTexNumber(1);	//oparation.png
	operation1Sprite_.SetTexNumber(2);	//oparation1.png
	operation2Sprite_.SetTexNumber(3);	//oparation2.png
	operation3Sprite_.SetTexNumber(4);	//oparation3.png
	enemyHpSprite_.SetTexNumber(6);	//playerHp.png
	enemyHp1Sprite_.SetTexNumber(7);	//enemyHp.png
	for (int i = 0; i < 2; i++)
	{
		curtainSprite_[i].SpriteCreate(dxCommon_->GetDevice(), 1280, 720);
		curtainSprite_[i].SetTexNumber(8);
		curtainSprite_[i].SetScale(XMFLOAT2(1280, 360));
		curtainSprite_[0].SetPosition(XMFLOAT3(0, 0, 0));
		curtainSprite_[1].SetPosition(XMFLOAT3(0, 620, 0));
		curtainSprite_[i].SpriteTransferVertexBuffer(curtainSprite_[i]);
		curtainSprite_[i].SpriteUpdate(curtainSprite_[i], spriteCommon_);
	}
	gameClearSprite_.SpriteCreate(dxCommon_->GetDevice(), 1280, 720);
	gameClearSprite_.SetTexNumber(9);
	gameClearSprite_.SetPosition(XMFLOAT3(200, -150, 0));
	gameClearSprite_.SetScale(XMFLOAT2(387 * 2.2, 62 * 2.2));
	gameClearSprite_.SpriteTransferVertexBuffer(gameClearSprite_);
	gameClearSprite_.SpriteUpdate(gameClearSprite_, spriteCommon_);
	gameOverSprite_.SpriteCreate(dxCommon_->GetDevice(), 1280, 720);
	gameOverSprite_.SetTexNumber(10);
	gameOverSprite_.SetPosition(XMFLOAT3(200, -150, 0));
	gameOverSprite_.SetScale(XMFLOAT2(387 * 2.2, 62 * 2.2));
	gameOverSprite_.SpriteTransferVertexBuffer(gameOverSprite_);
	gameOverSprite_.SpriteUpdate(gameOverSprite_, spriteCommon_);
	//�e�N�X�`���T�C�Y�ݒ�
	//�^�C�g��
	titleSprite_.SetPosition(XMFLOAT3(200, 100, 0));
	titleSprite_.SetScale(XMFLOAT2(414 * 2.2, 54 * 2.2));
	//����
	operationSprite_.SetScale(XMFLOAT2(600, 80));
	operationSprite_.SetPosition(XMFLOAT3(350,600,0));
	//����1
	operation1Sprite_.SetScale(XMFLOAT2(680 / 2, 80 / 2));
	operation1Sprite_.SetPosition(XMFLOAT3(900, 550 + 200,0));
	//����2
	operation2Sprite_.SetScale(XMFLOAT2(680 / 2, 80 / 2));
	operation2Sprite_.SetPosition(XMFLOAT3(900, 600 + 200,0));
	//����3
	operation3Sprite_.SetScale(XMFLOAT2(680 / 2, 80 / 2));
	operation3Sprite_.SetPosition(XMFLOAT3(900, 650 + 200,0));
	//�v���C���[��HP
	for (int i = 0; i < 5; i++)
	{
		playerHpSprite_[i].SetScale(XMFLOAT2(80, 80));
		playerHpSprite_[i].SetPosition(XMFLOAT3(0, -720,0));
		playerHpSprite_[i].SpriteTransferVertexBuffer(playerHpSprite_[i]);
		playerHpSprite_[i].SpriteUpdate(playerHpSprite_[i], spriteCommon_);
	}
	//�G��HP1
	enemyHpSprite_.SetScale(XMFLOAT2(820, 100));
	enemyHpSprite_.SetPosition(XMFLOAT3(200, -90,0));
	//�G��HP2
	enemyHp1Sprite_.SetScale(XMFLOAT2(0, 100));
	enemyHp1Sprite_.SetPosition(XMFLOAT3(242, 10,0));

	//���f
	//�^�C�g��
	titleSprite_.SpriteTransferVertexBuffer(titleSprite_);
	titleSprite_.SpriteUpdate(titleSprite_, spriteCommon_);
	//����
	operationSprite_.SpriteTransferVertexBuffer(operationSprite_);
	operationSprite_.SpriteUpdate(operationSprite_, spriteCommon_);
	//����1
	operation1Sprite_.SpriteTransferVertexBuffer(operation1Sprite_);
	operation1Sprite_.SpriteUpdate(operation1Sprite_, spriteCommon_);
	//����2
	operation2Sprite_.SpriteTransferVertexBuffer(operation2Sprite_);
	operation2Sprite_.SpriteUpdate(operation2Sprite_, spriteCommon_);
	//����3
	operation3Sprite_.SpriteTransferVertexBuffer(operation3Sprite_);
	operation3Sprite_.SpriteUpdate(operation3Sprite_, spriteCommon_);
	//�G��HP1
	enemyHpSprite_.SpriteTransferVertexBuffer(enemyHpSprite_);
	enemyHpSprite_.SpriteUpdate(enemyHpSprite_, spriteCommon_);
	//�G��HP2
	enemyHp1Sprite_.SpriteTransferVertexBuffer(enemyHp1Sprite_);
	enemyHp1Sprite_.SpriteUpdate(enemyHp1Sprite_, spriteCommon_);
	// �X�v���C�g�p�p�C�v���C�������Ăяo��
	PipelineSet spritePipelineSet = sprite_->SpriteCreateGraphicsPipeline(dxCommon_->GetDevice());

	//�J����������
	Camera* newCamera = new Camera();
	newCamera->Initialize(input_,dxInput, player_.get());
	camera_.reset(newCamera);
}

void GameScene::Initialize()
{
	//�v���C���[�̉�������
	for (int i = 0; i < 4; i++)
	{
		Smoke2* newSmoke2 = new Smoke2();
		if (i == 0)newSmoke2->Initialize(dxCommon_->GetDevice(), starDustModel_.get(), XMFLOAT3(25, 25, 0));
		if (i == 1)newSmoke2->Initialize(dxCommon_->GetDevice(), starDustModel_.get(), XMFLOAT3(-15, 15, 0));
		if (i == 2)newSmoke2->Initialize(dxCommon_->GetDevice(), starDustModel_.get(), XMFLOAT3(0, 25, 0));
		if (i == 3)newSmoke2->Initialize(dxCommon_->GetDevice(), starDustModel_.get(), XMFLOAT3(-25, -25, 0));
		enemySmoke2_[i].reset(newSmoke2);
	}

	//�X�v���C�g������
	spriteCommon_ = sprite_->SpriteCommonCreate(dxCommon_->GetDevice(), 1280, 720);
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 0, L"Resources/title.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 1, L"Resources/operation.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 2, L"Resources/operation1.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 3, L"Resources/Sprite-0005.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 4, L"Resources/operation91.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 5, L"Resources/playerHp.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 6, L"Resources/enemyHp.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 7, L"Resources/enemyHp1.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 8, L"Resources/curtain.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 9, L"Resources/gameclear.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 10, L"Resources/gameover.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 11, L"Resources/gametitle_4.png", dxCommon_->GetDevice());
	titleSprite_.SpriteCreate(dxCommon_->GetDevice(), 1280, 720);
	pushSprite_.SpriteCreate(dxCommon_->GetDevice(), 1280, 720);
	pushSprite_.SetTexNumber(11);
	pushSprite_.SetScale(XMFLOAT2(564, 71));
	pushSprite_.SetPosition(XMFLOAT3(0, 620, 0));
	pushSprite_.SpriteTransferVertexBuffer(pushSprite_);
	pushSprite_.SpriteUpdate(pushSprite_, spriteCommon_);
	operationSprite_.SpriteCreate(dxCommon_->GetDevice(), 1280, 720);	//oparation.png
	operation1Sprite_.SpriteCreate(dxCommon_->GetDevice(), 1280, 720);	//oparation1.png
	operation2Sprite_.SpriteCreate(dxCommon_->GetDevice(), 1280, 720);	//oparation2.png
	operation3Sprite_.SpriteCreate(dxCommon_->GetDevice(), 1280, 720);	//oparation3.png
	//playerHp.png
	for (int i = 0; i < 5; i++)
	{
		playerHpSprite_[i].SpriteCreate(dxCommon_->GetDevice(), 1280, 720);
		playerHpSprite_[i].SetTexNumber(5);
	}
	enemyHpSprite_.SpriteCreate(dxCommon_->GetDevice(), 1280, 720);	//playerHp.png
	enemyHp1Sprite_.SpriteCreate(dxCommon_->GetDevice(), 1280, 720);	//enemyHp.png
	//�e�N�X�`���ԍ��Z�b�g
	titleSprite_.SetTexNumber(0);
	operationSprite_.SetTexNumber(1);	//oparation.png
	operation1Sprite_.SetTexNumber(2);	//oparation1.png
	operation2Sprite_.SetTexNumber(3);	//oparation2.png
	operation3Sprite_.SetTexNumber(4);	//oparation3.png
	enemyHpSprite_.SetTexNumber(6);	//playerHp.png
	enemyHp1Sprite_.SetTexNumber(7);	//enemyHp.png
	for (int i = 0; i < 2; i++)
	{
		curtainSprite_[i].SpriteCreate(dxCommon_->GetDevice(), 1280, 720);
		curtainSprite_[i].SetTexNumber(8);
		curtainSprite_[i].SetScale(XMFLOAT2(1280, 360));
		curtainSprite_[0].SetPosition(XMFLOAT3(0, 0, 0));
		curtainSprite_[1].SetPosition(XMFLOAT3(0, 620, 0));
		curtainSprite_[i].SpriteTransferVertexBuffer(curtainSprite_[i]);
		curtainSprite_[i].SpriteUpdate(curtainSprite_[i], spriteCommon_);
	}
	gameClearSprite_.SpriteCreate(dxCommon_->GetDevice(), 1280, 720);
	gameClearSprite_.SetTexNumber(9);
	gameClearSprite_.SetPosition(XMFLOAT3(200, -150, 0));
	gameClearSprite_.SetScale(XMFLOAT2(387 * 2.2, 62 * 2.2));
	gameClearSprite_.SpriteTransferVertexBuffer(gameClearSprite_);
	gameClearSprite_.SpriteUpdate(gameClearSprite_, spriteCommon_);
	gameOverSprite_.SpriteCreate(dxCommon_->GetDevice(), 1280, 720);
	gameOverSprite_.SetTexNumber(10);
	gameOverSprite_.SetPosition(XMFLOAT3(200, -150, 0));
	gameOverSprite_.SetScale(XMFLOAT2(387 * 2.2, 62 * 2.2));
	gameOverSprite_.SpriteTransferVertexBuffer(gameOverSprite_);
	gameOverSprite_.SpriteUpdate(gameOverSprite_, spriteCommon_);
	//�e�N�X�`���T�C�Y�ݒ�
	//�^�C�g��
	titleSprite_.SetPosition(XMFLOAT3(200, 100, 0));
	titleSprite_.SetScale(XMFLOAT2(414 * 2.2, 54 * 2.2));
	//����
	operationSprite_.SetScale(XMFLOAT2(600, 80));
	operationSprite_.SetPosition(XMFLOAT3(350, 600, 0));
	//����1
	operation1Sprite_.SetScale(XMFLOAT2(680 / 2, 80 / 2));
	operation1Sprite_.SetPosition(XMFLOAT3(900, 550 + 200, 0));
	//����2
	operation2Sprite_.SetScale(XMFLOAT2(680 / 2, 80 / 2));
	operation2Sprite_.SetPosition(XMFLOAT3(900, 600 + 200, 0));
	//����3
	operation3Sprite_.SetScale(XMFLOAT2(680 / 2, 80 / 2));
	operation3Sprite_.SetPosition(XMFLOAT3(900, 650 + 200, 0));
	//�v���C���[��HP
	for (int i = 0; i < 5; i++)
	{
		playerHpSprite_[i].SetScale(XMFLOAT2(80, 80));
		playerHpSprite_[i].SetPosition(XMFLOAT3(0, -720, 0));
		playerHpSprite_[i].SpriteTransferVertexBuffer(playerHpSprite_[i]);
		playerHpSprite_[i].SpriteUpdate(playerHpSprite_[i], spriteCommon_);
	}
	//�G��HP1
	enemyHpSprite_.SetScale(XMFLOAT2(820, 100));
	enemyHpSprite_.SetPosition(XMFLOAT3(200, -90, 0));
	//�G��HP2
	enemyHp1Sprite_.SetScale(XMFLOAT2(0, 100));
	enemyHp1Sprite_.SetPosition(XMFLOAT3(242, 10, 0));

	//���f
	//�^�C�g��
	titleSprite_.SpriteTransferVertexBuffer(titleSprite_);
	titleSprite_.SpriteUpdate(titleSprite_, spriteCommon_);
	//����
	operationSprite_.SpriteTransferVertexBuffer(operationSprite_);
	operationSprite_.SpriteUpdate(operationSprite_, spriteCommon_);
	//����1
	operation1Sprite_.SpriteTransferVertexBuffer(operation1Sprite_);
	operation1Sprite_.SpriteUpdate(operation1Sprite_, spriteCommon_);
	//����2
	operation2Sprite_.SpriteTransferVertexBuffer(operation2Sprite_);
	operation2Sprite_.SpriteUpdate(operation2Sprite_, spriteCommon_);
	//����3
	operation3Sprite_.SpriteTransferVertexBuffer(operation3Sprite_);
	operation3Sprite_.SpriteUpdate(operation3Sprite_, spriteCommon_);
	//�G��HP1
	enemyHpSprite_.SpriteTransferVertexBuffer(enemyHpSprite_);
	enemyHpSprite_.SpriteUpdate(enemyHpSprite_, spriteCommon_);
	//�G��HP2
	enemyHp1Sprite_.SpriteTransferVertexBuffer(enemyHp1Sprite_);
	enemyHp1Sprite_.SpriteUpdate(enemyHp1Sprite_, spriteCommon_);
	// �X�v���C�g�p�p�C�v���C�������Ăяo��
	PipelineSet spritePipelineSet = sprite_->SpriteCreateGraphicsPipeline(dxCommon_->GetDevice());

	//�J����������
	Camera* newCamera = new Camera();
	newCamera->Initialize(input_, dxInput, player_.get());
	camera_.reset(newCamera);
}

void GameScene::Update()
{
	//�R���g���[���[�X�V
	dxInput->InputProcess();
	//�V�[�����Ƃ̏���
	(this->*Scene_[scene_])();
}

void GameScene::Draw()
{
	(this->*SceneDraw_[sceneDraw_])();
}

void GameScene::Title()
{
	titleTimer_++;
	//A�{�^���ŃQ�[���Ɉڂ�t���O�𗧂Ă�
	if (dxInput->GamePad.state.Gamepad.wButtons & XINPUT_GAMEPAD_A && titleTimer_ >= 60)
	{
		/*BGMSound->SoundStopWave(xAudio2.Get(), BGMSoundData);*/
		moveToGameFlag_ = true;
	}

	//�v���C���[����t���O���󂯎������Q�[���Ɉڂ�
	if (player_->GetGameStartFlag_() == true)
	{
		scene_ = static_cast<size_t>(Scene::Phase1Recollection);
		sceneDraw_ = static_cast<size_t>(SceneDraw::Phase1RecollectionDraw);
		//�v���C���[�̍��W���Q�[���p�ɃZ�b�g
		player_->SetPhase1();
		moveToGameFlag_ = false;	//�t���O���Z�b�g
	}

	//�J�����X�V
	//�^�C�g�����
	if (moveToGameFlag_ == false)
	{
		camera_->TitleUpdate();
	}
	//�Q�[���Ɉڂ鎞�̍X�V
	if (moveToGameFlag_ == true)
	{
		camera_->MoveToGameUpdate();
	}

	XMMATRIX matView = camera_->GetMatView();
	XMMATRIX matProjection = camera_->GetMatProjection();
	
	/*if (dxInput->GamePad.state.Gamepad.wButtons & XINPUT_GAMEPAD_B)
	{
		BGMSound->SoundPlayWave(xAudio2.Get(), BGMSoundData);
	}*/

	//�v���C���[�X�V
	//�^�C�g�����
	if (moveToGameFlag_ == false)
	{
		player_->TitleUpdate(matView, matProjection);
	}
	//�Q�[���Ɉڂ鎞�̍X�V
	if (moveToGameFlag_ == true)
	{
		moveToGameTimer_++;

		if (moveToGameTimer_ > 280)
		{
			addTitleSprite_ += 10;

			//�^�C�g��
			titleSprite_.SetPosition(XMFLOAT3(1280, 200 + addTitleSprite_,0));
			//����
			operationSprite_.SetPosition(XMFLOAT3(350, 600 + addTitleSprite_, 0));

			//�^�C�g��
			titleSprite_.SpriteTransferVertexBuffer(titleSprite_);
			titleSprite_.SpriteUpdate(titleSprite_, spriteCommon_);
			//����
			operationSprite_.SpriteTransferVertexBuffer(operationSprite_);
			operationSprite_.SpriteUpdate(operationSprite_, spriteCommon_);
		}

		player_->MoveToGameUpdate(matView, matProjection);
	}

	//�v���C���[�̉��X�V
	smoke_->Update(matView, matProjection, player_->GetPosition2(), player_->GetRotation());

	//�����X�V
	starDust_->Update(matView, matProjection);
}

void GameScene::Phase1()
{
	//�J�����X�V
	if (phase1Timer_ < 200)
	{
		camera_->Update2();
	}
	if (phase1Timer_ >= 200)
	{
		camera_->Update();
	}
	XMMATRIX matView = camera_->GetMatView();
	XMMATRIX matProjection = camera_->GetMatProjection();

	//�G��HP0��
	if (enemy_->GetHp() <= 0)
	{
		camera_->SetGameClear();
		scene_ = static_cast<size_t>(Scene::GameClear);
		sceneDraw_ = static_cast<size_t>(SceneDraw::GameClearDraw);
		//�v���C���[�̒e�X�V
		for (std::unique_ptr<PlayerBullet>& bullet : playerBullet_)
		{
			bullet->SetIsDeadTrue();
		}
		//�v���C���[�̒e�X�V
		for (std::unique_ptr<EnemyBullet>& bullet : enemyBullet_)
		{
			bullet->SetIsDeadTrue();
		}
		for (std::unique_ptr<Smoke>& smoke : enemyBulletSmoke_)
		{
			smoke->SetIsDeadTrue();
		}
		//�G�t�F�N�g�X�V
		for (std::unique_ptr<BreakEffect>& effect : breakEffect_)
		{
			effect->SetIsDeadTrue();
		}
	}

	//�v���C���[��HP0��
	if (player_->GetHp() <= 0)
	{
		scene_ = static_cast<size_t>(Scene::GameOver);
		sceneDraw_ = static_cast<size_t>(SceneDraw::GameOverDraw);
		//�v���C���[�̒e�X�V
		for (std::unique_ptr<PlayerBullet>& bullet : playerBullet_)
		{
			bullet->SetIsDeadTrue();
		}
		//�v���C���[�̒e�X�V
		for (std::unique_ptr<EnemyBullet>& bullet : enemyBullet_)
		{
			bullet->SetIsDeadTrue();
		}
		for (std::unique_ptr<Smoke>& smoke : enemyBulletSmoke_)
		{
			smoke->SetIsDeadTrue();
		}
		//�G�t�F�N�g�X�V
		for (std::unique_ptr<BreakEffect>& effect : breakEffect_)
		{
			effect->SetIsDeadTrue();
		}
	}

	addCurtain_ -= phase1Timer_ * 4;

	for (int i = 0; i < 2; i++)
	{
		curtainSprite_[0].SetPosition(XMFLOAT3(0, -240 + addCurtain_, 0));
		curtainSprite_[1].SetPosition(XMFLOAT3(0, 620 - addCurtain_, 0));
		curtainSprite_[i].SpriteTransferVertexBuffer(curtainSprite_[i]);
		curtainSprite_[i].SpriteUpdate(curtainSprite_[i], spriteCommon_);
	}

	//�����蔻��X�V
	EnmeyCollition();
	PlayerCollition();

	//�^�C�}�[�X�V
	phase1Timer_++;

	//�v���C���[�X�V
	player_->Update(matView, matProjection);

	//�G�X�V
	enemy_->Update(matView, matProjection,player_->GetPosition1());

	//�����X�V
	starDust_->Update(matView, matProjection);

	//1�t���[���ڂ���X�V�J�n
	if (phase1Timer_ >= 10)
	{
		//�v���C���[�̉��X�V
		smoke_->Update(matView, matProjection, player_->GetPosition2(), player_->GetRotation());
	}

	//�G��HP�̘g����ʊO���炨�낷����
	if (phase1Timer_ >= 0 && phase1Timer_ <= 100)
	{
		addEnemyHpSprite_ = phase1Timer_ - 90;
		enemyHpSprite_.SetPosition(XMFLOAT3(200, addEnemyHpSprite_,0));

		enemyHpSprite_.SpriteTransferVertexBuffer(enemyHpSprite_);
		enemyHpSprite_.SpriteUpdate(enemyHpSprite_, spriteCommon_);
	}

	//������@����ʊO����o������
	if (phase1Timer_ >= 0 && phase1Timer_ <= 100)
	{
		addOperationSprite_ = phase1Timer_ * 2;
		operation1Sprite_.SetPosition(XMFLOAT3(900, 750 - addOperationSprite_, 0));
		operation2Sprite_.SetPosition(XMFLOAT3(900, 800 - addOperationSprite_, 0));
		operation3Sprite_.SetPosition(XMFLOAT3(900, 850 - addOperationSprite_, 0));

		operation1Sprite_.SpriteTransferVertexBuffer(operation1Sprite_);
		operation1Sprite_.SpriteUpdate(operation1Sprite_, spriteCommon_);
		operation2Sprite_.SpriteTransferVertexBuffer(operation2Sprite_);
		operation2Sprite_.SpriteUpdate(operation2Sprite_, spriteCommon_);
		operation3Sprite_.SpriteTransferVertexBuffer(operation3Sprite_);
		operation3Sprite_.SpriteUpdate(operation3Sprite_, spriteCommon_);
	}

	//�v���C���[��HP����ʊO����o������
	if (phase1Timer_ >= 50 && phase1Timer_ <= 150)
	{
		addPlayerHpSprite_ = phase1Timer_ - 50;
		for (int i = 0; i < 5; i++)
		{
			playerHpSprite_[i].SetPosition(XMFLOAT3(i * 80, 740 - addPlayerHpSprite_, 0));
			playerHpSprite_[i].SpriteTransferVertexBuffer(playerHpSprite_[i]);
			playerHpSprite_[i].SpriteUpdate(playerHpSprite_[i], spriteCommon_);
		}
	}

	//�G��HP�̃o�[���ǂ�ǂ񑝂₷����
	if (phase1Timer_ >= 100 && phase1Timer_ <= 200)
	{
		addEnemyHp1Sprite_ = (phase1Timer_ - 100.0f) * addEnemyHp1SpriteNum_;
		enemyHp1Sprite_.SetScale(XMFLOAT2(addEnemyHp1Sprite_, 100));

		enemyHp1Sprite_.SpriteTransferVertexBuffer(enemyHp1Sprite_);
		enemyHp1Sprite_.SpriteUpdate(enemyHp1Sprite_, spriteCommon_);
	}

	//�G��HP�̃o�[���ǂ�ǂ񑝂₷����
	if (phase1Timer_ > 200)
	{
		addEnemyHp1Sprite_ = addEnemyHp1SpriteNum_ * (enemy_->GetHp() * 2/3);
		enemyHp1Sprite_.SetScale(XMFLOAT2(addEnemyHp1Sprite_, 100));

		enemyHp1Sprite_.SpriteTransferVertexBuffer(enemyHp1Sprite_);
		enemyHp1Sprite_.SpriteUpdate(enemyHp1Sprite_, spriteCommon_);
	}
	
	//200�t���[���o���Ă���X�V
	if (phase1Timer_ >= 200)
	{
		//�v���C���[����󂯎�����t���O�Œe����
		if (player_->Attack() == 1)
		{
			std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
			newBullet->Initialize(dxCommon_->GetDevice(), bulletModel_.get(), player_->GetPosition1(),player_->GetRotation(), player_->GetVelocity());
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

		//�G����󂯎�����t���O�Œe����
		if (enemy_->Attack(player_->GetPosition1()) == 1)
		{
			//�e
			std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
			newBullet->Initialize(dxCommon_->GetDevice(), enemyBulletModel_.get(), enemy_->GetPosition(),enemy_->GetRotation(), player_->GetPosition1());
			enemyBullet_.push_back(std::move(newBullet));
			//��
			std::unique_ptr<Smoke> newSmoke = std::make_unique<Smoke>();
			newSmoke->Initialize(dxCommon_->GetDevice(), starDustModel_.get(), enemy_->GetPosition());
			enemyBulletSmoke_.push_back(std::move(newSmoke));
		}
		//�G�̒e�X�V
		for (std::unique_ptr<EnemyBullet>& bullet : enemyBullet_)
		{
			bullet->Update(matView, matProjection);
			for (std::unique_ptr<Smoke>& smoke : enemyBulletSmoke_)
			{
				smoke->Update(matView, matProjection, bullet->GetPosition(), bullet->GetRotation());
			}
		}
		//�f�X�t���O�̗������e���폜
		enemyBullet_.remove_if([](std::unique_ptr<EnemyBullet>& bullet)
			{return bullet->IsDead(); }
		);
		//�f�X�t���O�̗����������폜
		enemyBulletSmoke_.remove_if([](std::unique_ptr<Smoke>& smoke)
			{return smoke->IsDead(); }
		);
	}

	//�G�t�F�N�g�X�V
	for (std::unique_ptr<BreakEffect>& effect : breakEffect_)
	{
		effect->Update(matView, matProjection);
	}
	//�f�X�t���O�̗������G�t�F�N�g���폜
	breakEffect_.remove_if([](std::unique_ptr<BreakEffect>& effect)
		{return effect->IsDead(); }
	);
}

void GameScene::Phase1Recollection()
{
	Phase1RecollectionTimer_++;

	//�J�����X�V
	camera_->Phase1RecollectionUpdate();;
	XMMATRIX matView = camera_->GetMatView();
	XMMATRIX matProjection = camera_->GetMatProjection();

	//�����X�V
	starDust_->Update(matView, matProjection);

	//�G�X�V
	enemy_->Update(matView, matProjection,player_->GetPosition1());

	player_->SetPhase1();

	//540�t���[���Ńt�F�[�Y1�Ɉڍs
	if (Phase1RecollectionTimer_ > 480)
	{
		scene_ = static_cast<size_t>(Scene::Phase1);
		sceneDraw_ = static_cast<size_t>(SceneDraw::Phase1Draw);
		//�^�C�}�[���Z�b�g
		camera_->phase1RecollectionTimerReset();
		Phase1RecollectionTimerReset();
	}

	if (Phase1RecollectionTimer_ > 360)
	{
		addCurtain_ += 2;
	}

	for (int i = 0; i < 2; i++)
	{
		curtainSprite_[0].SetPosition(XMFLOAT3(0, -240 + addCurtain_, 0));
		curtainSprite_[1].SetPosition(XMFLOAT3(0, 620 - addCurtain_, 0));
		curtainSprite_[i].SpriteTransferVertexBuffer(curtainSprite_[i]);
		curtainSprite_[i].SpriteUpdate(curtainSprite_[i], spriteCommon_);
	}
}

void GameScene::TitleDraw()
{
	//�X�v���C�g���ʃR�}���h
	sprite_->SpriteCommonBeginDraw(dxCommon_->GetCommandList(), spriteCommon_);

	titleSprite_.SpriteDraw(dxCommon_->GetCommandList(),spriteCommon_, dxCommon_->GetDevice(), titleSprite_.vbView);
	operationSprite_.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice(), operationSprite_.vbView);

	starDust_->Draw(dxCommon_->GetCommandList());
	player_->Draw(dxCommon_->GetCommandList());
	smoke_->Draw(dxCommon_->GetCommandList());
}

void GameScene::Phase1Draw()
{
	starDust_->Draw(dxCommon_->GetCommandList());
	player_->Draw(dxCommon_->GetCommandList());
	smoke_->Draw(dxCommon_->GetCommandList());
	enemy_->Draw(dxCommon_->GetCommandList());
	//�v���C���[�̒e�X�V
	for (std::unique_ptr<PlayerBullet>& bullet : playerBullet_)
	{
		bullet->Draw(dxCommon_->GetCommandList());
	}
	//�G�̒e
	for (std::unique_ptr<EnemyBullet>& bullet : enemyBullet_)
	{
		bullet->Draw(dxCommon_->GetCommandList());
	}
	//�G�̒e
	for (std::unique_ptr<Smoke>& smoke : enemyBulletSmoke_)
	{
		smoke->Draw(dxCommon_->GetCommandList());
	}
	//�����G�t�F�N�g�`��
	for (std::unique_ptr<BreakEffect>& effect : breakEffect_)
	{
		effect->Draw(dxCommon_->GetCommandList());
	}

	//�X�v���C�g���ʃR�}���h
	sprite_->SpriteCommonBeginDraw(dxCommon_->GetCommandList(), spriteCommon_);

	//�X�v���C�g�`��
	enemyHpSprite_.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice(),enemyHpSprite_.vbView);
	enemyHp1Sprite_.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice(), enemyHp1Sprite_.vbView);
	operation1Sprite_.SpriteDraw(dxCommon_->GetCommandList(),spriteCommon_, dxCommon_->GetDevice(), operation1Sprite_.vbView);
	operation2Sprite_.SpriteDraw(dxCommon_->GetCommandList(),spriteCommon_, dxCommon_->GetDevice(), operation2Sprite_.vbView);
	operation3Sprite_.SpriteDraw(dxCommon_->GetCommandList(),spriteCommon_, dxCommon_->GetDevice(), operation3Sprite_.vbView);
	for (int i = 0; i < 5; i++)
	{
		if (i < player_->GetHp())
		{
			playerHpSprite_[i].SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice(), playerHpSprite_[i].vbView);
		}
	}
	for (int i = 0; i < 2; i++)
	{
		curtainSprite_[i].SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice(), curtainSprite_[i].vbView);
	}
}

void GameScene::Phase1RecollectionDraw()
{

	starDust_->Draw(dxCommon_->GetCommandList());
	enemy_->Draw(dxCommon_->GetCommandList());
	//�X�v���C�g���ʃR�}���h
	sprite_->SpriteCommonBeginDraw(dxCommon_->GetCommandList(), spriteCommon_);
	for (int i = 0; i < 2; i++)
	{
		curtainSprite_[i].SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice(), curtainSprite_[i].vbView);
	}
}

void GameScene::EnmeyCollition()
{
	//�G�ɒe������������e���� �����G�t�F�N�g�쐬
	for (std::unique_ptr<PlayerBullet>& bullet : playerBullet_)
	{
		float x = bullet->GetPosition().x - enemy_->GetPosition().x;
		float y = bullet->GetPosition().y - enemy_->GetPosition().y;
		float z = bullet->GetPosition().z - enemy_->GetPosition().z;
		if ((x * x) + (y * y) + (z * z) <= 2000)
		{
			enemy_->SetHp(enemy_->GetHp() - 1);
			/*enemy_->SetHp(0);*/
			std::unique_ptr<BreakEffect> newEffect = std::make_unique<BreakEffect>();
			newEffect->Initialize(dxCommon_->GetDevice(), starDustModel_.get(), bullet->GetPosition());
			breakEffect_.push_back(std::move(newEffect));

			bullet->SetIsDeadTrue();
		}
	}
}

void GameScene::PlayerCollition()
{
	//���@�ɒe������������e���� �����G�t�F�N�g�쐬
	for (std::unique_ptr<EnemyBullet>& bullet : enemyBullet_)
	{
		float x = bullet->GetPosition().x - player_->GetPosition1().x;
		float y = bullet->GetPosition().y - player_->GetPosition1().y;
		float z = bullet->GetPosition().z - player_->GetPosition1().z;
		if ((x * x) + (y * y) + (z * z) <= 25)
		{
			player_->SetHp(player_->GetHp() - 1);
			std::unique_ptr<BreakEffect> newEffect = std::make_unique<BreakEffect>();
			newEffect->Initialize(dxCommon_->GetDevice(), starDustModel_.get(), bullet->GetPosition());
			breakEffect_.push_back(std::move(newEffect));

			bullet->SetIsDeadTrue();
			for (std::unique_ptr<Smoke>& smoke : enemyBulletSmoke_)
			{
				smoke->SetIsDeadTrue();
			}
		}
	}
}

//�����o�֐��̃|�C���^�e�[�u��
void (GameScene::* GameScene::Scene_[])() =
{
	&GameScene::Title,
	&GameScene::Phase1Recollection,
	&GameScene::Phase1,
	& GameScene::GameClear,
	&GameScene::GameOver,
};

void (GameScene::* GameScene::SceneDraw_[])() =
{
	&GameScene::TitleDraw,
	& GameScene::Phase1RecollectionDraw,
	& GameScene::Phase1Draw,
	& GameScene::GameClearDraw,
	&GameScene::GameOverDraw,
};


void GameScene::GameClear()
{
	GameClearTimer_++;
	camera_->GameClearUpdate();
	XMMATRIX matView = camera_->GetMatView();
	XMMATRIX matProjection = camera_->GetMatProjection();

	for (int i = 0; i < 4; i++)
	{
		enemySmoke2_[i]->Update(matView, matProjection);
	}

	if (GameClearTimer_ >= 250 && addGameClear_ < 250)
	{
		addGameClear_+= 10;
	}

	if (addGameClear_ >= 250)
	{
		//A�{�^���ŃQ�[���Ɉڂ�t���O�𗧂Ă�
		if (dxInput->GamePad.state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			scene_ = static_cast<size_t>(Scene::Title);
			sceneDraw_ = static_cast<size_t>(SceneDraw::TitleDraw);
			player_->HpReset();
			player_->SetTitle();
			enemy_->SetTitle();
			enemy_->HpReset();
			SetTitle();
			GameClearReset_();
			Initialize();
		}
	}

	for (int i = 0; i < 2; i++)
	{
		curtainSprite_[i].SetScale(XMFLOAT2(1280, 120));
		curtainSprite_[0].SetPosition(XMFLOAT3(0, -240, 0));
		curtainSprite_[1].SetPosition(XMFLOAT3(0, 620, 0));
		curtainSprite_[i].SpriteTransferVertexBuffer(curtainSprite_[i]);
		curtainSprite_[i].SpriteUpdate(curtainSprite_[i], spriteCommon_);
	}

	gameClearSprite_.SetPosition(XMFLOAT3(200, -150 + addGameClear_, 0));
	gameClearSprite_.SpriteTransferVertexBuffer(gameClearSprite_);
	gameClearSprite_.SpriteUpdate(gameClearSprite_, spriteCommon_);

	pushSprite_.SetScale(XMFLOAT2(564, 71));
	pushSprite_.SetPosition(XMFLOAT3(360, 720 - addGameClear_, 0));
	pushSprite_.SpriteTransferVertexBuffer(pushSprite_);
	pushSprite_.SpriteUpdate(pushSprite_, spriteCommon_);


	enemy_->Update(matView, matProjection, player_->GetPosition1());
}

void GameScene::GameClearDraw()
{
	enemy_->Draw(dxCommon_->GetCommandList());
	for (int i = 0; i < 4; i++)
	{
		enemySmoke2_[i]->Draw(dxCommon_->GetCommandList());
	}
	//�X�v���C�g���ʃR�}���h
	sprite_->SpriteCommonBeginDraw(dxCommon_->GetCommandList(), spriteCommon_);
	for (int i = 0; i < 2; i++)
	{
		curtainSprite_[i].SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice(), curtainSprite_[i].vbView);
	}
	gameClearSprite_.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice(), gameClearSprite_.vbView);
	pushSprite_.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice(), pushSprite_.vbView);
}

void GameScene::GameOver()
{
	GameClearTimer_++;
	//�J�����X�V
	camera_->Update();
	XMMATRIX matView = camera_->GetMatView();
	XMMATRIX matProjection = camera_->GetMatProjection();

	if (GameClearTimer_ >= 250 && addGameClear_ < 250)
	{
		addGameClear_ += 10;
	}

	if (addGameClear_ >= 250)
	{
		//A�{�^���ŃQ�[���Ɉڂ�t���O�𗧂Ă�
		if (dxInput->GamePad.state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
		{
			scene_ = static_cast<size_t>(Scene::Title);
			sceneDraw_ = static_cast<size_t>(SceneDraw::TitleDraw);
			player_->HpReset();
			player_->SetTitle();
			enemy_->SetTitle();
			enemy_->HpReset();
			SetTitle();
			GameClearReset_();
			Initialize();
		}
	}

	gameOverSprite_.SetPosition(XMFLOAT3(200, -150 + addGameClear_, 0));
	gameOverSprite_.SpriteTransferVertexBuffer(gameOverSprite_);
	gameOverSprite_.SpriteUpdate(gameOverSprite_, spriteCommon_);

	pushSprite_.SetScale(XMFLOAT2(564, 71));
	pushSprite_.SetPosition(XMFLOAT3(360, 720 - addGameClear_, 0));
	pushSprite_.SpriteTransferVertexBuffer(pushSprite_);
	pushSprite_.SpriteUpdate(pushSprite_, spriteCommon_);

	//�v���C���[�X�V
	player_->GameOverUpdate(matView, matProjection);

	//�G�X�V
	enemy_->Update(matView, matProjection, player_->GetPosition1());

	//�����X�V
	starDust_->Update(matView, matProjection);

	smoke_->Update(matView, matProjection, player_->GetPosition2(), player_->GetRotation());
}

void GameScene::GameOverDraw()
{
	starDust_->Draw(dxCommon_->GetCommandList());
	player_->Draw(dxCommon_->GetCommandList());
	smoke_->Draw(dxCommon_->GetCommandList());
	enemy_->Draw(dxCommon_->GetCommandList());

	//�X�v���C�g���ʃR�}���h
	sprite_->SpriteCommonBeginDraw(dxCommon_->GetCommandList(), spriteCommon_);

	gameOverSprite_.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice(), gameOverSprite_.vbView);
	pushSprite_.SpriteDraw(dxCommon_->GetCommandList(), spriteCommon_, dxCommon_->GetDevice(), pushSprite_.vbView);
}

void GameScene::SetTitle()
{
	moveToGameFlag_ = false;	//�^�C�g������Q�[��
	moveFromTitleFlag_ = true;
	moveToGameTimer_ = 0;
	addTitleSprite_ = 0;
	Phase1RecollectionTimer_ = 0;
	phase1Timer_ = 0;
	addEnemyHpSprite_ = 0;
	addEnemyHp1Sprite_ = 0;
	addOperationSprite_ = 0;
	addPlayerHpSprite_ = 0;
	titleTimer_ = 0;
	addCurtain_ = 0;
}