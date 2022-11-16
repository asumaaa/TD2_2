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

class GameScene
{
	//�����o�֐�
public:
	GameScene();
	~GameScene();
	void Initialize(DirectXCommon* dxCommon, Input* input);
	void Update();
	void Draw();

	void EnmeyCollition();
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
};
