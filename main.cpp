#include "main.h"
#include "FPS.h"
#include "DXInput.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//�E�B���h�E����
	WinApp* win = nullptr;
	win = WinApp::GetInstance();
	win->CreateWindow_(L"DirectX");

	Masage* masage;	//���b�Z�[�W
	masage = Masage::GetInstance();

	//DirectX����������
	DirectXCommon* dx = nullptr;
	dx = DirectXCommon::GetInstance();
	dx->Initialize(win);

	//�L�[�{�[�h
	Input* input = nullptr;
	input = Input::GetInstance();
	input->Initialize(win);

	//�Q�[���V�[��
	GameScene* gameScene = nullptr;
	gameScene = new GameScene();
	gameScene->Initialize(dx, input);

	//FPS���Œ�
	FPS* fps = nullptr;
	fps = new FPS;
	fps->SetFrameRate(60.0f);
	fps->FpsControlBegin();;

#pragma endregion

		//�Q�[�����[�v
	while (true)
	{
		//X�{�^���ŏI�����b�Z����������Q�[�����[�v�𔲂��� 
		if (masage->Update() == 1)break;

#pragma region DirectX���t���[������

		//�L�[�{�[�h�X�V
		input->Update();

		gameScene->Update();

		dx->PreDraw();
		// 4. �`��R�}���h
		gameScene->Draw();


		dx->PostDraw();

#pragma endregion
	}
	
	//FPS�Œ������
	fps->FpsControlEnd();
	dx->EndImgui();

	delete fps;
	delete gameScene;

	masage->ExitGameloop();

	//�E�B���h�E�N���X��o�^����
	win->deleteWindow();

	return 0;
}