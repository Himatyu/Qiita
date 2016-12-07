#include <windows.h>
#include "window.h"
#include "Graphics.h"
#include "Macro.h"
#include<vector>
#include<thread>
#include<mutex>
#include<chrono>
#include<fstream>
#include<string>
#include<cmath>

#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

ID3DXSprite* pSprite;
LPDIRECT3DDEVICE9 pDevice;
D3DXMATRIX rotateMat;

bool isLoaded = false;
std::mutex isLoadedMutex;



struct Texture
{
	IDirect3DTexture9* pTexture;
	D3DXIMAGE_INFO imageInfo;
};

Texture CreateTexture(std::string _path, Graphics& _graphics)
{
	Texture texture;
	D3DXGetImageInfoFromFile(_path.c_str(), &texture.imageInfo);
	auto pDevice = _graphics.Device;

	D3DXCreateTextureFromFileEx
	(
		pDevice,
		_path.c_str(),
		texture.imageInfo.Width,
		texture.imageInfo.Height,
		1,
		0,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0,
		&texture.imageInfo,
		NULL,
		&texture.pTexture
	);

	return texture;
}

void DrawTextureRotate(Texture _texture,float rot)
{ 
	D3DXMatrixRotationZ(&rotateMat, D3DXToRadian(rot));
	rotateMat._41 = _texture.imageInfo.Width *0.5f;
	rotateMat._42 = _texture.imageInfo.Height *0.5f;

	D3DXVECTOR3 Center(
		_texture.imageInfo.Width *0.5f,
		_texture.imageInfo.Height *0.5f,
		0.0f);

	rot += 0.001f;

	pSprite->SetTransform(&rotateMat);

	pDevice->BeginScene();
	pSprite->Begin(0);
	pSprite->Draw(_texture.pTexture,
		NULL,
		&Center,
		NULL,
		0xffffffff);
	pSprite->End();
	pDevice->EndScene();

}



void SetLockFlag(bool _)
{
	std::lock_guard<std::mutex>  lock(isLoadedMutex);
	isLoaded = true;
}

bool GetLockFlag()
{
	std::lock_guard<std::mutex>  lock(isLoadedMutex);
	return isLoaded;
}

void AsyncLoad()
{
	auto sleepTime = std::chrono::seconds(10);
	std::this_thread::sleep_for(sleepTime);

	SetLockFlag(true);
}

int APIENTRY _tWinMain(
	HINSTANCE _hInstance,
	HINSTANCE _hPrevInstance,
	LPTSTR _CmdLine,
	int _CmdShow)
{
	Window window;
	window.Create("BackGroundTextureLoadDx9", 500, 500);
	window.Show(_CmdShow);
	window.Update();

	Graphics graphics;
	graphics.Create(window.GetHwnd(), 500, 500, true);
	pDevice = graphics.Device;

	auto texture = CreateTexture("loadImg.png", graphics);
	auto doneTexture = CreateTexture("doneTex.png", graphics);

	D3DXCreateSprite(pDevice, &pSprite);
	float angle = 0;

	auto count = std::thread::hardware_concurrency();
	if (count < 3)
	{
		//Err
	}
	std::thread th = std::thread(AsyncLoad);


	while (window.MessageProc())
	{
		pDevice->Clear
		(0, NULL,
			D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER,
			D3DCOLOR_XRGB(0, 0, 0),
			1.0f, 0
		);

		if (!GetLockFlag())
		{
			angle += 0.001f;
			DrawTextureRotate(texture, angle);
		}
		else
		{
			DrawTextureRotate(doneTexture, 0);
		}

		if (FAILED(pDevice->Present(NULL, NULL, NULL, NULL)))
		{
			//Err
		}

	}
	th.join();
	SAFE_RELEASE(texture.pTexture);
	SAFE_RELEASE(pSprite);

	return 0;
}