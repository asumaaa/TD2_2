#include "DirectXCommon.h"
#include "input.h"
#include "DirectXTex.h"
#include "Cube.h"
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

class GameScene
{
	//�����o�֐�
public:
	GameScene();
	~GameScene();
	void Initialize(DirectXCommon* dxCommon, Input* input);
	void Update();
	void Draw();
	void Delete();

	//�����o�ϐ�
private: 
	//�f�o�C�X��input
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;

	////�v���C���[�̃��f��
	//std::unique_ptr<Model> playerModel_;

	////�v���C���[
	//std::unique_ptr<Player> player_;

	////�I�u�W�F�N�g
	//std::unique_ptr<Object3D> object3Ds_;

	////�����̃��f��
	//std::unique_ptr<Model> starDustModel_;

	////����
	//std::unique_ptr<StarDust> starDust_;

	////�J����
	//std::unique_ptr<Camera> camera_;
};
