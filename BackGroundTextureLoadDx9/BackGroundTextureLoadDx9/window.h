/**
* @file		window.h
* @brief	Window�N���X
* @author	S.OIKAWA
* @date		2016/4/18
*/
#pragma once

//-----------------------------------------------------------
// include 
//-----------------------------------------------------------
#include<Windows.h>
#include<tchar.h>
#include<stdlib.h>

//-----------------------------------------------------------
// define
//-----------------------------------------------------------
		/// <summary>
		/// Window�N���X
		/// �v���V�[�W�����I�[�o�[���C�h���邱�ƂœƎ���Window�N���X�𐶐��\
		/// </summary>
class Window
{
public:
	//-----------------------------------------------------------
	// defaults 
	//-----------------------------------------------------------
	Window();
	virtual ~Window();

	//-----------------------------------------------------------
	// function 
	//-----------------------------------------------------------
		/// <summary>
		/// ��t���X�N���[���̃E�B���h�쐬
		/// </summary>
	void Create
	(
		LPCTSTR		_windowName,
		int			_width = CW_USEDEFAULT,
		int			_height = CW_USEDEFAULT,
		DWORD		_style = WS_OVERLAPPEDWINDOW,
		DWORD		_exStyle = 0,
		int			_x = CW_USEDEFAULT,
		int			_y = CW_USEDEFAULT,
		HWND		_hwndParent = NULL,
		HMENU		_hMenu = NULL,
		LPVOID		_pParam = NULL
	);

	/// <summary>
	/// �t���X�N���[���E�B���h�쐬
	/// </summary>
	void CreateFullScreen(LPCTSTR	_windowName);

	/// <summary>
	/// ���b�Z�[�W���͂��Ă���΃f�B�X�p�b�`����
	/// </summary>
	bool MessageProc();

	/// <summary>
	/// ������
	/// </summary>
	virtual bool InitInstance();

	/// <summary>
	/// �I������
	/// </summary>
	virtual int ExitInstance();

	/// <summary>
	/// �E�B���h�E�n���h���擾
	/// </summary>
	HWND GetHwnd() const;

	/// <summary>
	/// �n���h���擾�I�y���[�^
	/// </summary>
	operator HWND() const;

	/// <summary>
	/// �E�B���h�E�̕\��
	/// </summary>
	bool Show(int nCmdShow);

	/// <summary>
	/// �E�B���h�E�X�V
	/// </summary>
	void Update();

	/// <summary>
	/// ���b�Z�[�W�{�b�N�X�\��
	/// </summary>
	int MessageBox(LPCTSTR pszText,
		LPCTSTR pszCaption = NULL,
		UINT nType = MB_OK);

	/// <summary>
	/// �E�B���h�E �T�C�Y�擾
	/// </summary>
	bool GetClientRect(LPRECT pRect);

protected:
	/// <summary>
	/// �C�x���g����������
	/// </summary>
	virtual LRESULT WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

	/// <summary>
	/// �f�t�H���g�v���[�W��
	/// </summary>
	virtual LRESULT DefWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

	/// <summary>
	/// �E�B���h�E�����C�x���g
	/// </summary>
	virtual int OnCreate(LPCREATESTRUCT pcs);

	/// <summary>
	/// �t�@�C���h���b�v�C�x���g
	/// </summary>
	virtual void OnDropFiles(HDROP hDropInfo);

	/// <summary>
	/// �j���C�x���g
	/// </summary>
	virtual void OnDestroy();

	/// <summary>
	/// �E�B���h�E�N���X�o�^
	/// </summary>
	void RegisterClass();

private:
	/// <summary>
	/// �h���v���[�W���Ƀ��b�Z�[�W��z�z
	/// </summary>
	static LRESULT CALLBACK WndRootProc(HWND hWnd,
		UINT uMsg,
		WPARAM wParam,
		LPARAM lParam);

private:
	MSG			m_Msg;				//!< ���b�Z�[�W
	RECT		m_ClientRect;		//!< �N���C�A���g�T�C�Y
	DWORD		m_ExStyle;			//!< �g���X�^�C��
	DWORD		m_Style;			//!< �E�B���h�E�X�^�C��
	ATOM		m_Atom;				//!< �����ԋp�l
	HWND		m_Wnd;				//!< �E�B���h�E�n���h��
	HINSTANCE	m_Instance;			//!< �E�B���h�E�C���X�^���X
	HMENU		m_Menu;				//!< ���j���[�n���h���܂��͎q�E�B���h�E ID
	LPCTSTR		m_ClassName;		//!< �o�^�N���X��
	LPCTSTR		m_WindowName;		//!< �E�B���h�E��
	LPVOID		m_Param;			//!< �E�B���h�E�n���h��	
	bool		m_fullScreen;		//!< �t���X�N���[�����[�h�H

};


//-----------------------------------------------------------
// EOF
//-----------------------------------------------------------