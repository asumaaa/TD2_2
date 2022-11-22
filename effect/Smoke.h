#pragma once
#include "Model.h"
#include "Object3D.h"
#include "DirectXCommon.h"

class Smoke
{
public:
	//�V���O���g���C���X�^���X
	Smoke* GetInstance();
	Smoke();
	~Smoke();
	void Initialize(ID3D12Device* device, Model* model,XMFLOAT3 position);
	void Update(XMMATRIX& matView, XMMATRIX& matProjection, XMFLOAT3 position, XMFLOAT3 rotation);
	void Draw(ID3D12GraphicsCommandList* cmdList);
	bool IsDead()const { return isDead_; }
	void SetIsDeadTrue() { isDead_ = true; };
private:
	/*DirectXCommon* dx_;*/
	ID3D12Device* device_;
	Model* model_;

	//���I�u�W�F�̐�
	int smokeNum_ = 20;

	//�^�C�}�[
	int timer = 0;
	int timerNum = smokeNum_;

	//�I�u�W�F
	std::list<std::unique_ptr<Object3D>> object3Ds_;
	
	std::vector<XMFLOAT3> position_;
	std::vector<XMFLOAT3> scale_;
	std::vector<XMFLOAT3> rotation_;

	//�X�P�[�����Z�b�g����ۂ̐��l
	float scaleSetNum_ = 0.8f;

	//���𔭐������郂�f���Ɖ��̒��S����̋���
	float length_ = 7;

	//����
	static const int32_t lifeTime = 60 * 5;
	//�f�X�^�C�}�[
	int32_t deathTimer_ = lifeTime;
	//�f�X�t���O
	bool isDead_ = false;
};

