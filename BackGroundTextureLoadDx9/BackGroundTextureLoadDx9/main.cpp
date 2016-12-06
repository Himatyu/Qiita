#include <windows.h>
#include "window.h"
#include "Graphics.h"
#include "Macro.h"
#include<chrono>
#include<vector>
#include<iostream>
#include<fstream>

#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

std::chrono::milliseconds LoadTexture(Graphics& graphics)
{
	IDirect3DTexture9*	pTexture[10];
	auto pDevice = graphics.Device;
	std::string path("tex1.jpg");

	D3DXIMAGE_INFO imageInfo;
	D3DXGetImageInfoFromFile(path.c_str(), &imageInfo);

	std::chrono::milliseconds total = std::chrono::milliseconds::zero();

	for (int i = 0; i < 10; i++)
	{
		auto start = std::chrono::system_clock::now();
		D3DXCreateTextureFromFileEx
		(
			pDevice,
			path.c_str(),
			imageInfo.Width,
			imageInfo.Height,
			1,
			0,
			D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			0,
			&imageInfo,
			NULL,
			&pTexture[i]
		);
		total +=
			std::chrono::duration_cast<std::chrono::milliseconds>(
				std::chrono::system_clock::now() - start);
	}

	for (int i = 0; i < 10; i++)
	{
		SAFE_RELEASE(pTexture[i]);
	}

	return total / 10;
}
std::chrono::milliseconds LoadTextureInMemory(Graphics& graphics)
{
	auto pDevice = graphics.Device;
	std::string path("tex1.jpg");

	std::vector<char> data;
	std::fstream stream;
	stream.open(path, std::ios::binary | std::ios::in);

	stream.seekg(0, std::ios::end);
	auto tell = stream.tellg();
	stream.clear();
	stream.seekg(0, std::ios::beg);
	auto head = stream.tellg();

	auto size = tell - head;
	data.resize(size);
	stream.read(data.data(), size);
	stream.close();

	D3DXIMAGE_INFO imageInfo2;
	D3DXGetImageInfoFromFileInMemory(data.data(), data.size(), &imageInfo2);

	IDirect3DTexture9*	pTexture[10];
	std::chrono::milliseconds total = std::chrono::milliseconds::zero();

	for (int i = 0; i < 10; i++)
	{
		auto start2 = std::chrono::system_clock::now();
		D3DXCreateTextureFromFileInMemoryEx
		(
			pDevice,
			data.data(),
			data.size(),
			imageInfo2.Width,
			imageInfo2.Height,
			1,
			0,
			D3DFMT_A8R8G8B8,
			D3DPOOL_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			0,
			&imageInfo2,
			NULL,
			&pTexture[i]
		);
		total +=
			std::chrono::duration_cast<std::chrono::milliseconds>(
				std::chrono::system_clock::now() - start2);
	}
	for (int i = 0; i < 10; i++)
	{
		SAFE_RELEASE(pTexture[i]);
	}

	return total / 10;
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
	auto pDevice = graphics.Device;

	auto t1 = LoadTexture(graphics);
	auto t2 = LoadTextureInMemory(graphics);

	while (window.MessageProc())
	{

		pDevice->Clear
		(0, NULL,
			D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER,
			D3DCOLOR_XRGB(0, 0, 0),
			1.0f, 0
		);



		if (FAILED(pDevice->Present(NULL, NULL, NULL, NULL)))
		{
			auto presntParams = graphics.PresentParameters;
			pDevice->Reset(&presntParams);
		}

	}

	return 0;
}