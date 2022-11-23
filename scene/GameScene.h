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
#include "Smoke2.h"

class GameScene
{
	//メンバ関数
public:
	GameScene();
	~GameScene();
	void Initialize(DirectXCommon* dxCommon, Input* input);
	void Initialize();
	void Update();
	void Draw();

	void Title();
	void Phase1();
	void Phase1Recollection();
	void GameOver();
	void GameClear();
	void TitleDraw();
	void Phase1Draw();
	void Phase1RecollectionDraw();
	void GameClearDraw();
	void GameOverDraw();

	//プレイヤーの弾と敵の当たり判定
	void EnmeyCollition();
	//敵の弾とプレイヤーの当たり判定
	void PlayerCollition();

	void SetTitle();
	//メンバ変数
private: 
	//デバイスとinput
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;

	//コントローラ
	DXInput* dxInput = new DXInput();

	//プレイヤーのモデル
	std::unique_ptr<Model> playerModel_;

	//プレイヤー
	std::unique_ptr<Player> player_;

	//プレイヤーの煙
	std::unique_ptr<Smoke> smoke_;

	//オブジェクト
	std::unique_ptr<Object3D> object3Ds_;

	//星屑のモデル
	std::unique_ptr<Model> starDustModel_;

	//星屑
	std::unique_ptr<StarDust> starDust_;

	//カメラ
	std::unique_ptr<Camera> camera_;

	//弾のモデル
	std::unique_ptr<Model> bulletModel_;

	//弾
	std::list<std::unique_ptr<PlayerBullet>> playerBullet_;

	//爆発エフェクト
	std::list<std::unique_ptr<BreakEffect>> breakEffect_;

	//敵のモデル
	std::unique_ptr<Model> enemyModel_;

	//敵
	std::unique_ptr<Enemy> enemy_;

	//敵の弾のモデル
	std::unique_ptr<Model> enemyBulletModel_;

	//敵の弾
	std::list<std::unique_ptr<EnemyBullet>> enemyBullet_;

	//敵の弾の煙
	std::list<std::unique_ptr<Smoke>> enemyBulletSmoke_;
	//敵の弾の煙
	std::unique_ptr<Smoke2> enemySmoke2_[4];

	//スプライトの共通データ生成
	/*std::unique_ptr<SpriteCommon> spriteCommon_;
	std::unique_ptr<Sprite> sprite_;*/

	//スプライト
	Sprite* sprite_ = new Sprite;
	Sprite titleSprite_;	//title.png
	Sprite operationSprite_;	//oparation.png
	Sprite operation1Sprite_;	//oparation1.png
	Sprite operation2Sprite_;	//oparation2.png
	Sprite operation3Sprite_;	//oparation3.png
	Sprite playerHpSprite_[5];	//playerHp.png
	Sprite enemyHpSprite_;	//playerHp.png
	Sprite enemyHp1Sprite_;	//enemyHp.png
	Sprite curtainSprite_[2];	//curtainHp.png
	Sprite gameClearSprite_;	//curtainHp.png
	Sprite gameOverSprite_;	//curtainHp.png
	Sprite pushSprite_;	//curtainHp.png
	//スプライト共通データ生成
	SpriteCommon spriteCommon_;

	//音
	IXAudio2MasteringVoice* masterVoice;
	ComPtr<IXAudio2> xAudio2;

	////音ごとに生成
	//Sound* BGMSound = new Sound;
	////音声読み込み
	//SoundData BGMSoundData = BGMSound->SoundLoadWave("Resources/sound/shoot.wav");

	//シーン
	enum class Scene
	{
		Title,	//タイトル
		Phase1Recollection,	//回想
		Phase1,	//操作
		GameClear,	//クリア
		GameOver,	//クリア
	};
	//シーン	最初がタイトル
	size_t scene_ = static_cast<size_t>(Scene::Title);
	//メンバ関数のポインタテーブル
	static void (GameScene::* Scene_[])();

	//シーンの描画
	enum class SceneDraw
	{
		TitleDraw,	//タイトル
		Phase1RecollectionDraw,	//回想
		Phase1Draw,	//操作
		GameClearDraw,	//クリア
		GameOverDraw,	//クリア
	};
	//シーン	最初がタイトル
	size_t sceneDraw_ = static_cast<size_t>(SceneDraw::TitleDraw);
	//メンバ関数のポインタテーブル
	static void (GameScene::* SceneDraw_[])();

	//シーン切り替え用のフラグ
	bool moveToGameFlag_ = false;	//タイトルからゲーム
	bool moveFromTitleFlag_ = true;

	//タイトルから移るタイマー
	float moveToGameTimer_ = 0;
	
	float addTitleSprite_ = 0;

	//フェーズ1ゲーム前のシーン用タイマー
	float Phase1RecollectionTimer_ = 0;
	void Phase1RecollectionTimerReset() { Phase1RecollectionTimer_ = 0; };

	//フェーズ１が始まる時のタイマー
	int phase1Timer_ = 0;
	void phase1TimerRiset() { phase1Timer_ = 0; };

	//enemyのHPの演出用の処理
	float addEnemyHpSprite_ = 0;
	float addEnemyHp1Sprite_ = 0;
	//enemyのhpを100等分した値
	float addEnemyHp1SpriteNum_ = 7.38f;

	//操作方法のスプライトの演出用の変数
	float addOperationSprite_ = 0;

	//プレイヤーのHPの演出
	float addPlayerHpSprite_ = 0;

	float titleTimer_ = 0;

private:
	float GameClearTimer_ = 0;
	float addGameClear_ = 0;
public:
	void GameClearReset_() { GameClearTimer_ = 0; addGameClear_ = 0; };
};
