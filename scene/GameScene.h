#include "DirectXCommon.h"
#include "input.h"
#include "DirectXTex.h"
#include "object3D.h"
#include "list"
#include "memory"
#include "Texture.h"
#include "Model.h"
#include "Object3D.h"
#include "Player.h"
#include "Sound.h"
#include "Camera.h"
#include "StarDust.h"
#include "Smoke.h"
#include "DXInput.h"
#include "PlayerBullet.h"
#include "BreakEffect.h"
#include "Sprite.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Sprite.h"

class GameScene
{
	//�����o�֐�
public:
	GameScene();
	~GameScene();
	void Initialize(DirectXCommon* dxCommon, Input* input);
	void Update();
	void Draw();

	void Title();
	void Phase1();
	void Phase1Recollection();
	void TitleDraw();
	void Phase1Draw();
	void Phase1RecollectionDraw();

	//�v���C���[�̒e�ƓG�̓����蔻��
	void EnmeyCollition();
	//�G�̒e�ƃv���C���[�̓����蔻��
	void PlayerCollition();
	//�����o�ϐ�
private: 
	//�f�o�C�X��input
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;

	//�R���g���[��
	DXInput* dxInput = new DXInput();

	//�v���C���[�̃��f��
	std::unique_ptr<Model> playerModel_;

	//�v���C���[
	std::unique_ptr<Player> player_;

	//�v���C���[�̉�
	std::unique_ptr<Smoke> smoke_;

	//�I�u�W�F�N�g
	std::unique_ptr<Object3D> object3Ds_;

	//�����̃��f��
	std::unique_ptr<Model> starDustModel_;

	//����
	std::unique_ptr<StarDust> starDust_;

	//�J����
	std::unique_ptr<Camera> camera_;

	//�e�̃��f��
	std::unique_ptr<Model> bulletModel_;

	//�e
	std::list<std::unique_ptr<PlayerBullet>> playerBullet_;

	//�����G�t�F�N�g
	std::list<std::unique_ptr<BreakEffect>> breakEffect_;

	//�G�̃��f��
	std::unique_ptr<Model> enemyModel_;

	//�G
	std::unique_ptr<Enemy> enemy_;

	//�G�̒e�̃��f��
	std::unique_ptr<Model> enemyBulletModel_;

	//�G�̒e
	std::list<std::unique_ptr<EnemyBullet>> enemyBullet_;

	//�G�̒e�̉�
	std::list<std::unique_ptr<Smoke>> enemyBulletSmoke_;

	//�X�v���C�g�̋��ʃf�[�^����
	/*std::unique_ptr<SpriteCommon> spriteCommon_;
	std::unique_ptr<Sprite> sprite_;*/

	//�X�v���C�g
	Sprite* sprite_ = new Sprite;
	Sprite titleSprite_;	//title.png
	Sprite operationSprite_;	//oparation.png
	Sprite operation1Sprite_;	//oparation1.png
	Sprite operation2Sprite_;	//oparation2.png
	Sprite playerHpSprite_;	//playerHp.png
	Sprite enemyHpSprite_;	//playerHp.png
	Sprite enemyHp1Sprite_;	//enemyHp.png
	//�X�v���C�g���ʃf�[�^����
	SpriteCommon spriteCommon_;

	//�V�[��
	enum class Scene
	{
		Title,	//�^�C�g��
		Phase1Recollection,	//��z
		Phase1,	//����
	};
	//�V�[��	�ŏ����^�C�g��
	size_t scene_ = static_cast<size_t>(Scene::Phase1);
	//�����o�֐��̃|�C���^�e�[�u��
	static void (GameScene::* Scene_[])();

	//�V�[���̕`��
	enum class SceneDraw
	{
		TitleDraw,	//�^�C�g��
		Phase1RecollectionDraw,	//��z
		Phase1Draw,	//����
	};
	//�V�[��	�ŏ����^�C�g��
	size_t sceneDraw_ = static_cast<size_t>(SceneDraw::Phase1Draw);
	//�����o�֐��̃|�C���^�e�[�u��
	static void (GameScene::* SceneDraw_[])();

	//�V�[���؂�ւ��p�̃t���O
	bool moveToGameFlag_ = false;	//�^�C�g������Q�[��
	bool moveFromTitleFlag_ = true;

	//�t�F�[�Y1�Q�[���O�̃V�[���p�^�C�}�[
	float Phase1RecollectionTimer_ = 0;
	void Phase1RecollectionTimerReset() { Phase1RecollectionTimer_ = 0; };

	//�t�F�[�Y�P���n�܂鎞�̃^�C�}�[
	int phase1Timer_ = 0;
	void phase1TimerRiset() { phase1Timer_ = 0; };

	//enemy��HP�̉��o�p�̏���
	float addEnemyHpSprite_ = 0;
	float addEnemyHp1Sprite_ = 0;
	//enemy��hp��100���������l
	float addEnemyHp1SpriteNum_ = 7.38f;
};
