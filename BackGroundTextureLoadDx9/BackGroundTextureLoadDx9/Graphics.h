/**
* @file	    Graphics.h
* @brief    DirectX�̃f�o�C�X�������N���X
* @author   S.OIKAWA
* @date		2016/4/18
*/
#pragma once

//-----------------------------------------------------------
// include
//-----------------------------------------------------------
#include<d3d9.h>
#include<d3dx9.h>
#include<memory>
#include"Macro.h"
//-----------------------------------------------------------
// define
//-----------------------------------------------------------

		/// <summary>
		/// DirectX�̃f�o�C�X�������N���X
		/// </summary>
class Graphics final
{
public:
	//-----------------------------------------------------------
	// default
	//-----------------------------------------------------------
	Graphics() = default;
	~Graphics();

	Graphics(const Graphics&) = default;
	Graphics(Graphics&&) = default;

	Graphics&operator=(const Graphics&) = default;
	Graphics&operator=(Graphics&&) = default;

	//-----------------------------------------------------------
	// function
	//-----------------------------------------------------------

	/// <summary>
	/// �N���X����
	/// </summary>
	void Create(HWND _hWnd,
		int _Width = CW_USEDEFAULT,
		int _Height = CW_USEDEFAULT,
		bool _Window = true);

	/// <summary>
	/// �J��
	/// </summary>
	void Release();

private:

	/// <summary>
	/// ������
	/// </summary>
	bool Initialize(HWND _hWnd, int _Width, int _Height, bool _Window);

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

	//-----------------------------------------------------------
	// property
	//-----------------------------------------------------------	
public:
	PROPERTY_R_ONLY(m_Width, Width, int);
	PROPERTY_R_ONLY(m_Height, Height, int);
	PROPERTY_CR_R_ONLY(m_pDevice, Device, LPDIRECT3DDEVICE9);
	PROPERTY_CR_R_ONLY(m_D3DPP, PresentParameters, D3DPRESENT_PARAMETERS);

	//-----------------------------------------------------------
	// Val
	//-----------------------------------------------------------
private:
	D3DPRESENT_PARAMETERS		m_D3DPP;						// PRESENT PARAMETERS
	D3DDISPLAYMODE				m_DespMax;						// �ő��ʃT�C�Y

	HWND						m_hWnd;							// �E�B���h�E �n���h��
	int							m_Width;						// �\���̈敝
	int							m_Height;						// �\���̈捂��

	LPDIRECT3D9					m_pD3D;							// Direct3D9 �I�u�W�F�N�g
	LPDIRECT3DDEVICE9			m_pDevice;						// Direct3DDevice9 �I�u�W�F�N�g

};

//-----------------------------------------------------------
// EOF
//-----------------------------------------------------------