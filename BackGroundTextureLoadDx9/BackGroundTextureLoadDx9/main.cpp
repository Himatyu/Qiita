#include <windows.h>
#include "window.h"
#include "Graphics.h"


#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

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

	while (window.MessageProc())
	{
		auto pDevice = graphics.Device;

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