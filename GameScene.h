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
	//メンバ関数
public:
	GameScene();
	~GameScene();
	void Initialize(DirectXCommon* dxCommon, Input* input);
	void Update();
	void Draw();
	void Delete();

	//メンバ変数
private: 
	//デバイスとinput
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;

	////プレイヤーのモデル
	//std::unique_ptr<Model> playerModel_;

	////プレイヤー
	//std::unique_ptr<Player> player_;

	////オブジェクト
	//std::unique_ptr<Object3D> object3Ds_;

	////星屑のモデル
	//std::unique_ptr<Model> starDustModel_;

	////星屑
	//std::unique_ptr<StarDust> starDust_;

	////カメラ
	//std::unique_ptr<Camera> camera_;
};
