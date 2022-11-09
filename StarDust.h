#pragma once
#include "DirectXCommon.h"
#include "DirectXMath.h"
#include "Model.h"
#include "Object3D.h"

using namespace DirectX;

class StarDust
{
public:
	//シングルトンインスタンス
	StarDust* GetInstance();
	StarDust();
	~StarDust();
	void Initialize(DirectXCommon* dx, Model* model);
	void Update(XMMATRIX& matView, XMMATRIX& matProjection);
	void Draw();
	void Delete();
private:
	DirectXCommon* dx_;
	Model* model_;

	//星屑の数
	int starDustNum = 100;

	/*std::vector<ComPtr<Object3D>> object3ds_;*/
	std::list<std::unique_ptr<Object3D>> object3Ds_;

	std::vector<XMFLOAT3> position_;
	std::vector<XMFLOAT3> scale_;
	std::vector<XMFLOAT3> rotation_;
};

