#include "main.h"
#include "FPS.h"
#include "DXInput.h"
#include "Pera.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	//�E�B���h�E����
	WinApp* win = nullptr;
	win = WinApp::GetInstance();
	win->CreateWindow_(L"�X�y�[�X���b�V��");

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

	/*Pera* pera_ = new Pera();
	pera_->Initialize(dx->GetDevice(), dx);*/

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

		/*pera_->Update();*/

		/*dx->PeraPreDraw();*/


		/*if (pera_->GetMode() != 0) {
			pera_->Draw();
		}*/

		/*dx->PeraPostDraw();*/


		dx->PreDraw();

		gameScene->Draw();
		/*pera_->Draw();*/

		dx->PostDraw();

#pragma endregion
	}
	
	//FPS�Œ������
	fps->FpsControlEnd();
	/*dx->EndImgui();*/

	delete fps;
	delete gameScene;
	/*delete dx;*/

	masage->ExitGameloop();

	//�E�B���h�E�N���X��o�^����
	win->deleteWindow();

	return 0;
}