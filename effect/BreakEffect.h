#pragma once
#include "DirectXCommon.h"
#include "DirectXMath.h"
#include "Model.h"
#include "Object3D.h"

class BreakEffect
{
public:
	//�V���O���g���C���X�^���X
	BreakEffect* GetInstance();
	BreakEffect();
	~BreakEffect();
	void Initialize(ID3D12Device* device, Model* model,XMFLOAT3 position);
	void Update(XMMATRIX& matView, XMMATRIX& matProjection);
	void Draw(ID3D12GraphicsCommandList* cmdList);
	bool IsDead()const { return isDead_; }
	void SetIsDeadTrue() { isDead_ = true; };
private:
	/*DirectXCommon* dx_;*/
	ID3D12Device* device_;
	Model* model_;

	//�����G�t�F�N�g�̐�
	int breakEffectNum = 60;

	std::list<std::unique_ptr<Object3D>> object3Ds_;

	std::vector<XMFLOAT3> position_;
	std::vector<XMFLOAT3> scale_;
	std::vector<XMFLOAT3> rotation_;

	//����
	static const int32_t lifeTime = 30;
	//�f�X�^�C�}�[
	int32_t deathTimer_ = lifeTime;
	//�f�X�t���O
	bool isDead_ = false;

	std::vector<XMFLOAT3> velocity_;
	float speed = 1.0f;
};

