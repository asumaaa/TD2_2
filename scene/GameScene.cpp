#include "GameScene.h"

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	delete dxInput;
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
	player_->SetPhase1();

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

	//�X�v���C�g������
	spriteCommon_ = sprite_->SpriteCommonCreate(dxCommon_->GetDevice(), 1280, 720);
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 0, L"Resources/title.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 1, L"Resources/operation.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 2, L"Resources/operation1.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 3, L"Resources/operation2.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 4, L"Resources/playerHp.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 5, L"Resources/enemyHp.png", dxCommon_->GetDevice());
	sprite_->SpriteCommonLoadTexture(spriteCommon_, 6, L"Resources/enemyHp1.png", dxCommon_->GetDevice());
	titleSprite_ = titleSprite_.SpriteCreate(dxCommon_->GetDevice(), 1280, 720);
	operationSprite_ = operationSprite_.SpriteCreate(dxCommon_->GetDevice(), 1280, 720);	//oparation.png
	operation1Sprite_ = operation1Sprite_.SpriteCreate(dxCommon_->GetDevice(), 1280, 720);	//oparation1.png
	operation2Sprite_ = operation2Sprite_.SpriteCreate(dxCommon_->GetDevice(), 1280, 720);	//oparation2.png
	playerHpSprite_ = playerHpSprite_.SpriteCreate(dxCommon_->GetDevice(), 1280, 720);	//playerHp.png
	enemyHpSprite_ = enemyHpSprite_.SpriteCreate(dxCommon_->GetDevice(), 1280, 720);	//playerHp.png
	enemyHp1Sprite_ = enemyHp1Sprite_.SpriteCreate(dxCommon_->GetDevice(), 1280, 720);	//enemyHp.png
	//�e�N�X�`���ԍ��Z�b�g
	titleSprite_.SetTexNumber(0);
	operationSprite_.SetTexNumber(1);	//oparation.png
	operation1Sprite_.SetTexNumber(2);	//oparation1.png
	operation2Sprite_.SetTexNumber(3);	//oparation2.png
	playerHpSprite_.SetTexNumber(4);	//playerHp.png
	enemyHpSprite_.SetTexNumber(5);	//playerHp.png
	enemyHp1Sprite_.SetTexNumber(6);	//enemyHp.png
	//�e�N�X�`���T�C�Y�ݒ�
	//�^�C�g��
	titleSprite_.SetScale(XMFLOAT2(1280, 200));
	//����
	operationSprite_.SetScale(XMFLOAT2(600, 80));
	operationSprite_.SetPosition(XMFLOAT3(350,600,0));
	//����1
	operation1Sprite_.SetScale(XMFLOAT2(1280, 200));
	//����2
	operation2Sprite_.SetScale(XMFLOAT2(1280, 200));
	//�v���C���[��HP
	playerHpSprite_.SetScale(XMFLOAT2(1280, 200));
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
	//�v���C���[��HP
	playerHpSprite_.SpriteTransferVertexBuffer(playerHpSprite_);
	playerHpSprite_.SpriteUpdate(playerHpSprite_, spriteCommon_);
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
	//A�{�^���ŃQ�[���Ɉڂ�t���O�𗧂Ă�
	if (dxInput->GamePad.state.Gamepad.wButtons & XINPUT_GAMEPAD_A)
	{
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
	

	//�v���C���[�X�V
	//�^�C�g�����
	if (moveToGameFlag_ == false)
	{
		player_->TitleUpdate(matView, matProjection);
	}
	//�Q�[���Ɉڂ鎞�̍X�V
	if (moveToGameFlag_ == true)
	{
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
	camera_->Update();
	XMMATRIX matView = camera_->GetMatView();
	XMMATRIX matProjection = camera_->GetMatProjection();

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

	//�G��HP�̃o�[���ǂ�ǂ񑝂₷����
	if (phase1Timer_ >= 100 && phase1Timer_ <= 200)
	{
		addEnemyHp1Sprite_ = (phase1Timer_ - 100.0f) * addEnemyHp1SpriteNum_;
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

	//540�t���[���Ńt�F�[�Y1�Ɉڍs
	if (Phase1RecollectionTimer_ > 480)
	{
		scene_ = static_cast<size_t>(Scene::Phase1);
		sceneDraw_ = static_cast<size_t>(SceneDraw::Phase1Draw);
		//�^�C�}�[���Z�b�g
		camera_->phase1RecollectionTimerReset();
		Phase1RecollectionTimerReset();
	}
}

void GameScene::TitleDraw()
{
	//�X�v���C�g���ʃR�}���h
	sprite_->SpriteCommonBeginDraw(dxCommon_->GetCommandList(), spriteCommon_);

	titleSprite_.SpriteDraw(dxCommon_->GetCommandList(), titleSprite_, spriteCommon_, dxCommon_->GetDevice());
	operationSprite_.SpriteDraw(dxCommon_->GetCommandList(), operationSprite_, spriteCommon_, dxCommon_->GetDevice());

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
	enemyHpSprite_.SpriteDraw(dxCommon_->GetCommandList(), enemyHpSprite_, spriteCommon_, dxCommon_->GetDevice());
	enemyHp1Sprite_.SpriteDraw(dxCommon_->GetCommandList(), enemyHp1Sprite_, spriteCommon_, dxCommon_->GetDevice());
}

void GameScene::Phase1RecollectionDraw()
{
	//�X�v���C�g���ʃR�}���h
	sprite_->SpriteCommonBeginDraw(dxCommon_->GetCommandList(), spriteCommon_);

	starDust_->Draw(dxCommon_->GetCommandList());
	enemy_->Draw(dxCommon_->GetCommandList());
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
	&GameScene::Phase1
};

void (GameScene::* GameScene::SceneDraw_[])() =
{
	&GameScene::TitleDraw,
	& GameScene::Phase1RecollectionDraw,
	&GameScene::Phase1Draw
};