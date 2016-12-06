/**
* @file			Graphics.cpp
* @brief		DirectX�̃f�o�C�X�������N���X
* @author		S.OIKAWA
* @date			2016/4/18
*/

//-----------------------------------------------------------
// include
//-----------------------------------------------------------
#include <windows.h>
#include <tchar.h>
#include "Graphics.h"

//-----------------------------------------------------------
// define 
//-----------------------------------------------------------

		//-----------------------------------------------------------
		// dtor 
		//-----------------------------------------------------------
Graphics::~Graphics()
{
	Release();
}

//-----------------------------------------------------------
// �C�j�V�����C�Y
//-----------------------------------------------------------
bool Graphics::Initialize(HWND _hWnd, int _Width, int _Height, bool _Window)
{
	if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		//Err
	}

	m_Height = _Height;
	m_Width = _Width;

	ZeroMemory(&m_D3DPP, sizeof(D3DPRESENT_PARAMETERS));
	m_D3DPP.Windowed = _Window;
	m_D3DPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_D3DPP.EnableAutoDepthStencil = true;
	m_D3DPP.AutoDepthStencilFormat = D3DFMT_D24S8;

	if (_Window)
	{
		m_D3DPP.BackBufferWidth = (UINT)m_Width;						// �Q�[����ʃT�C�Y
		m_D3DPP.BackBufferHeight = (UINT)m_Height;
		m_D3DPP.BackBufferFormat = D3DFMT_UNKNOWN;						// �o�b�N�o�b�t�@
		m_D3DPP.FullScreen_RefreshRateInHz = 0;							// ���t���b�V�����[�g
		m_D3DPP.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// �C���^�[�o��
	}
	else
	{
		D3DDISPLAYMODE    d3dspMode;
		m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3dspMode);

		m_D3DPP.BackBufferWidth = d3dspMode.Width;						// �Q�[����ʃT�C�Y
		m_D3DPP.BackBufferHeight = d3dspMode.Height;

		m_D3DPP.BackBufferFormat = d3dspMode.Format;					// �o�b�N�o�b�t�@
		m_D3DPP.BackBufferCount = 1;
		m_D3DPP.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ���t���b�V�����[�g
		m_D3DPP.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��
	}

	//�f�o�C�X����
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_D3DPP, &m_pDevice))) //�n�[�h:�n�[�h
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, _hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_D3DPP, &m_pDevice))) //�n�[�h:�\�t�g
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, _hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_D3DPP, &m_pDevice))) //�\�t�g:�n�[�h
				if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_REF, _hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_D3DPP, &m_pDevice))) //�\�t�g:�\�t�g
				{
					//Err
				}

	return true;
}

//-----------------------------------------------------------
// �I������ 
//-----------------------------------------------------------
void Graphics::Finalize()
{
}

//-----------------------------------------------------------
// �f�o�C�X�쐻
//-----------------------------------------------------------
void Graphics::Create(HWND _hWnd, int _Width, int _Height, bool _Window)
{
	Initialize(_hWnd, _Width, _Height, _Window);
}

//-----------------------------------------------------------
// �J��
//-----------------------------------------------------------
void Graphics::Release()
{
	SAFE_RELEASE(m_pDevice);
	SAFE_RELEASE(m_pD3D);
}


//-----------------------------------------------------------
// EOF 
//-----------------------------------------------------------




