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

class GameScene
{
	//�����o�֐�
public:
	GameScene();
	~GameScene();
	void Initialize(DirectXCommon* dxCommon, Input* input);
	void Update();
	void Draw();

	//�����o�ϐ�
private: 
	//�f�o�C�X��input
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;

	//�v���C���[�̃��f��
	std::unique_ptr<Model> playerModel_;

	//�v���C���[
	std::unique_ptr<Player> player_;

	//�I�u�W�F�N�g
	std::unique_ptr<Object3D> object3Ds_;

	////�ˉe�ϊ�
	//XMMATRIX matProjection = XMMatrixPerspectiveFovLH(
	//	XMConvertToRadians(45.0f),			//�㉺��p45�x
	//	(float)window_width / window_height,//�A�X�y�N�g��(��ʉ���/��ʗ���)
	//	0.1f, 1000.0f						//�O�[�A���[
	//);

	////�r���[�ϊ��s��
	//XMMATRIX matView;
	//XMFLOAT3 eye = { -10, 10, 30 };
	//XMFLOAT3 target = { 0, 0, 0 };
	//XMFLOAT3 up = { 0, 1, 0 };

	//�J����
	std::unique_ptr<Camera> camera_;
};