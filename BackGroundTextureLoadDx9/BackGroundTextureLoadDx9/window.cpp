/**
* @file		window.cpp
* @brief	Window�N���X
* @author	S.OIKAWA
* @date		2016/4/16
*/

//-----------------------------------------------------------
// include
//-----------------------------------------------------------
#include"window.h"
#include"Constant.h"
//-----------------------------------------------------------
//define 
//-----------------------------------------------------------

		//-----------------------------------------------------------
		// ctor 
		//-----------------------------------------------------------
Window::Window() :
	m_ExStyle(0),
	m_Style(0),
	m_Atom(0),
	m_Wnd(0),
	m_Instance(0),
	m_Menu(0),
	m_ClassName(Constant::ClassName),
	m_WindowName(0),
	m_Param(0),
	m_fullScreen(false),
	m_ClientRect({ CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT })
{
	m_Instance = (HINSTANCE)::GetModuleHandle(NULL);
}

//-----------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------
Window::~Window()
{
	if (m_Wnd)
	{
		//�E�B���h�E�n���h���̔j��
		::RemoveProp(m_Wnd, Constant::ClientProc);
		::DestroyWindow(m_Wnd);
	}
	if (m_Atom)
	{
		//�N���X�o�^����
		::UnregisterClass(m_ClassName, m_Instance);
		m_Atom = NULL;
	}
}

//-----------------------------------------------------------
// ���[�g�v���V�[�W��
//-----------------------------------------------------------
LRESULT CALLBACK Window::WndRootProc(HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam)
{
	Window* pWnd = (Window*)::GetProp(hWnd, Constant::ClientProc);
	if (pWnd)	// �C���X�^���X���̃v���V�[�W������
		return pWnd->WndProc(uMsg, wParam, lParam);

	// �_�C�A���O�̏ꍇ�AFALSE��Ԃ�
	if (::GetWindowLong(hWnd, DWL_DLGPROC))
		return FALSE;
	// �f�t�H���g�E�B���h�E�v���V�[�W�����Ăяo��
	return ::DefWindowProc(hWnd, uMsg, wParam, lParam);
}

//-----------------------------------------------------------
// GetClientRect 
//-----------------------------------------------------------
bool Window::GetClientRect(LPRECT pRect)
{
	return ::GetClientRect(m_Wnd, pRect) != FALSE;
}

//-----------------------------------------------------------
// �E�B���h�E�v���V�[�W��
//-----------------------------------------------------------
LRESULT Window::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		return OnCreate((LPCREATESTRUCT)lParam);

	case WM_DROPFILES:
		OnDropFiles((HDROP)wParam);
		return 0;

	case WM_CLOSE:
	case WM_DESTROY:
		OnDestroy();
		break;

	default:
		break;
	}
	return DefWindowProc(uMsg, wParam, lParam);
}

//-----------------------------------------------------------
// �f�t�H���g�E�B���h�E�v���V�[�W��
//-----------------------------------------------------------
LRESULT Window::DefWindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return ::DefWindowProc(m_Wnd, uMsg, wParam, lParam);
}

//-----------------------------------------------------------
// �����C�x���g
//-----------------------------------------------------------
int Window::OnCreate(LPCREATESTRUCT pcs)
{
	return 0;
}

//-----------------------------------------------------------
// �t�@�C���h���b�v�C�x���g
//-----------------------------------------------------------
void Window::OnDropFiles(HDROP hDropInfo)
{
	DefWindowProc(WM_DROPFILES, (WPARAM)hDropInfo, 0);
}

//-----------------------------------------------------------
// �I���C�x���g
//-----------------------------------------------------------
void Window::OnDestroy()
{
	// �A�v���P�[�V�����I��
	::PostQuitMessage(0);
}

//-----------------------------------------------------------
// �N���X�o�^
//-----------------------------------------------------------
void Window::RegisterClass()
{
	if (!m_Atom)
	{
		WNDCLASSEX wcex;
		ZeroMemory(&wcex, sizeof(WNDCLASSEX));
		wcex.cbSize = sizeof(wcex);
		wcex.lpszClassName = m_ClassName;							// �N���X��
		wcex.lpfnWndProc = WndRootProc;								// �E�B���h�E�v���V�[�W��
		wcex.style = CS_VREDRAW | CS_HREDRAW;						// ��L�w��
		wcex.hInstance = m_Instance;								// �C���X�^���X
		wcex.hCursor = ::LoadCursor(NULL, IDC_ARROW);				// �f�t�H���g �J�[�\��
		wcex.hIcon = ::LoadIcon(NULL, IDI_APPLICATION);				// �f�t�H���g �A�C�R��
		wcex.hbrBackground = (HBRUSH)::GetStockObject(WHITE_BRUSH); // �w�i�F
		wcex.hIconSm = ::LoadIcon(NULL, IDI_APPLICATION);			// �f�t�H���g �A�C�R��
		m_Atom = ::RegisterClassEx(&wcex);

		if (!m_Atom)
		{
			//Err;
		}
	}
}

//-----------------------------------------------------------
// �E�B���h�E����
//-----------------------------------------------------------
void Window::Create
(
	LPCTSTR		_windowName,
	int			_width, int			_height,
	DWORD		_style, DWORD		_exStyle,
	int			_x, int			_y,
	HWND		_hwndParent,
	HMENU		_hMenu,
	LPVOID		_pParam
)
{
	m_Style = _style;
	m_ExStyle = _exStyle;
	m_Menu = _hMenu;
	m_Param = _pParam;

	RECT rc = { 0, 0, _width, _height };
	if (!::AdjustWindowRectEx(&rc, _style,
		_hMenu && !IS_INTRESOURCE(_hMenu), _exStyle))
	{
		//Err;
	}
	RegisterClass();

	//����
	HWND hWnd = ::CreateWindowEx(
		_exStyle, m_ClassName, _windowName, _style,
		_x, _y, _width, _height,
		_hwndParent, _hMenu, m_Instance, _pParam
	);

	if (!hWnd)
	{
		//Err;
	}
	m_Wnd = hWnd;

	//�����o�^
	::SetProp(m_Wnd, Constant::ClientProc, (LPVOID)this);
}

//-----------------------------------------------------------
//�t���X�N���[���E�B���h�E����
//-----------------------------------------------------------
void Window::CreateFullScreen
(
	LPCTSTR	_windowName
)
{
	Create(_windowName, CW_USEDEFAULT, CW_USEDEFAULT);
	m_fullScreen = true;
}

//-----------------------------------------------------------
// �C���X�^���X������
//-----------------------------------------------------------
bool Window::InitInstance()
{
	return true;
}

// ---------------------------------------------------------------------
// �A�v���P�[�V�����I�����̏���
// ---------------------------------------------------------------------
int Window::ExitInstance()
{
	return m_Msg.wParam;
}

//-----------------------------------------------------------
// GetHwnd
//-----------------------------------------------------------
HWND Window::GetHwnd() const
{
	return (this) ? m_Wnd : NULL;
}

//-----------------------------------------------------------
// operator
//-----------------------------------------------------------
Window::operator HWND() const
{
	return GetHwnd();
}

//-----------------------------------------------------------
// Show 
//-----------------------------------------------------------
bool Window::Show(int nCmdShow)
{
	return ::ShowWindow(m_Wnd, nCmdShow) != FALSE;
}

//-----------------------------------------------------------
// Update 
//-----------------------------------------------------------
void Window::Update()
{
	::UpdateWindow(m_Wnd);
}

//-----------------------------------------------------------
// ���b�Z�[�W����
//-----------------------------------------------------------
bool Window::MessageProc()
{
	//���b�Z�[�W���͂��Ă���΃v���V�[�W���Ƀf�B�X�p�b�`����
	if (PeekMessage(&m_Msg, NULL, 0, 0, PM_REMOVE)) {
		if (m_Msg.message == WM_QUIT)
		{
			return false;
		}
		TranslateMessage(&m_Msg);
		DispatchMessage(&m_Msg);
	}

	return true;
}


//-----------------------------------------------------------
// EOF
//-----------------------------------------------------------