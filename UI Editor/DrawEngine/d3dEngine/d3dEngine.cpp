#include "d3dEngine.h"
#include "../../ErrorHandle/ErrorHandle.h"
#include "d3d9ResourceManager.h"
#include "d3dEngineImpl.h"
#include <tchar.h>

#ifdef UNICODE
const wchar_t* ENGINE_IMPL_TEX_FILE = L"dxutcontrols.dds";
#else
const char* ENGINE_IMPL_TEX_FILE = "dxutcontrols.dds";
#endif	// UNICODE

D3DEngine::D3DEngine(HWND mainWndId, D3DDEVTYPE devType, DWORD requestedVP)
	: m_d3dObject(nullptr),
	m_d3dDevice(nullptr)
{
	m_mainWnd = mainWndId;
	m_devType = devType;
	m_requestedVP = requestedVP;

	// 给予初始值，初始值为100帧每秒，每帧10毫秒
	m_fps = 100.0f;
	m_mspf = 10.0f;

	ZeroMemory(&m_d3dPP, sizeof(m_d3dPP));

	initDirect3D();
	initD3DFont();

	initEngineImpl();
}

D3DEngine::~D3DEngine()
{
	SAFE_DELETE(m_resourceManager);
	for (auto& val_pair : m_fonts)
	{
		ReleaseCOM(val_pair.second);
	}
	ReleaseCOM(m_d3dObject);
	ReleaseCOM(m_d3dDevice);
}

// 获取对应的字体
inline ID3DXFont* D3DEngine::getFont(FONT_TYPE fontType) const
{
	auto it = m_fonts.find(fontType);
	if (it != m_fonts.cend())
	{
		return it->second;
	}

	throw ExtraExcept::unexpected_situation("D3DEngine::getFont: font should be found here.");
}

// 处理对应窗口大小改变
void D3DEngine::handlgeSizeChange(UINT width, UINT height)
{
	if (m_d3dPP.BackBufferWidth == width && m_d3dPP.BackBufferHeight == height)
		return;

	m_d3dPP.BackBufferWidth = width;
	m_d3dPP.BackBufferHeight = height;

	onLostDevice();
	HR(m_d3dDevice->Reset(&m_d3dPP));
	onResetDevice();
}

// 处理可能的设备丢失
bool D3DEngine::checkDeviceLost()
{
	// Get the state of the graphics device.
	HRESULT hr = m_d3dDevice->TestCooperativeLevel();

	// If the device is lost and cannot be reset yet then sleep for a bit and we'll try
	// again on the next message loop cycle
	if (hr == D3DERR_DEVICELOST)
	{
		Sleep(20);
		return true;
	}
	// Driver error, exit.
	else if (hr == D3DERR_DRIVERINTERNALERROR)
	{
#if UNICODE
		MessageBox(0, L"Internal Driver Error...Exiting", 0, 0);
#else
		MessageBox(0, "Internal Driver Error...Exiting", 0, 0);
#endif
		PostQuitMessage(0);
		return true;
	}
	// The device is lost but we can reset and restore it.
	else if (hr == D3DERR_DEVICENOTRESET)
	{
		onLostDevice();
		HR(m_d3dDevice->Reset(&m_d3dPP));
		onResetDevice();
		return false;
	}
	else
		return false;
}


// 重设设备前的清理
void D3DEngine::onLostDevice()
{
	for (auto& val_pair : m_fonts)
	{
		val_pair.second->OnLostDevice();
	}
	m_resourceManager->OnD3DLostDevice();
}

// 重设设备后的处理
void D3DEngine::onResetDevice()
{
	for (auto& val_pair : m_fonts)
	{
		val_pair.second->OnResetDevice();
	}
	m_resourceManager->OnD3DResetDevice();
}

// 计算设备帧数信息
void D3DEngine::CalculateFrameStats()
{
	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.

	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	++frameCnt;

	// Compute averages over one second period.
	if ((m_timer.totalTime() - timeElapsed) >= 1.0f)
	{
		m_fps = static_cast<float>(frameCnt);		// fps = frameCnt / 1;
		m_mspf = 1000.0f / m_fps;

		// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}

// 初始化D3D相关
void D3DEngine::initDirect3D()
{
	// Step 1: Create the IDirect3D9 object.
	m_d3dObject = Direct3DCreate9(D3D_SDK_VERSION);
	if (!m_d3dObject)
	{
#if UNICODE
		MessageBox(0, L"Direct3DCreate9 FAILED", 0, 0);
#else
		MessageBox(0, "Direct3DCreate9 FAILED", 0, 0);
#endif	// UNICODE
		PostQuitMessage(0);
	}

	// Step 2: Verify hardware support for specified formats in windowed and full screen modes.
	D3DDISPLAYMODE mode;
	HR(m_d3dObject->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &mode));
	HR(m_d3dObject->CheckDeviceType(D3DADAPTER_DEFAULT, m_devType, mode.Format, mode.Format, true));
	HR(m_d3dObject->CheckDeviceType(D3DADAPTER_DEFAULT, m_devType, D3DFMT_X8R8G8B8, D3DFMT_X8R8G8B8, false));

	// Step 3: Check for requested vertex processing and pure device.
	D3DCAPS9 caps;
	HR(m_d3dObject->GetDeviceCaps(D3DADAPTER_DEFAULT, m_devType, &caps));

	DWORD devBehaviorFlags = 0;
	if (caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
		devBehaviorFlags |= m_requestedVP;
	else
		devBehaviorFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	// If pure device and HW T&L supported
	if (caps.DevCaps & D3DDEVCAPS_PUREDEVICE &&
		devBehaviorFlags & D3DCREATE_HARDWARE_VERTEXPROCESSING)
		devBehaviorFlags |= D3DCREATE_PUREDEVICE;

	// Step 4: Fill out the D3DPRESENT_PARAMETERS structure.
	m_d3dPP.BackBufferWidth = 0;
	m_d3dPP.BackBufferHeight = 0;
	m_d3dPP.BackBufferFormat = D3DFMT_UNKNOWN;
	m_d3dPP.BackBufferCount = 1;
	m_d3dPP.MultiSampleType = D3DMULTISAMPLE_NONE;
	m_d3dPP.MultiSampleQuality = 0;
	m_d3dPP.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_d3dPP.hDeviceWindow = m_mainWnd;
	m_d3dPP.Windowed = true;
	m_d3dPP.EnableAutoDepthStencil = true;
	m_d3dPP.AutoDepthStencilFormat = D3DFMT_D24S8;
	m_d3dPP.Flags = 0;
	m_d3dPP.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	m_d3dPP.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	// Step 5: Create the device.
	HR(m_d3dObject->CreateDevice(
		D3DADAPTER_DEFAULT,		// primary adapter
		m_devType,				// device type
		m_mainWnd,				// window assocaited with device
		devBehaviorFlags,		// vertex processing
		&m_d3dPP,				// present parameters
		&m_d3dDevice));			// return created device
}

// 初始化D3D字体
void D3DEngine::initD3DFont()
{
	D3DXFONT_DESC fontDesc;
	fontDesc.Width = 0;
	fontDesc.MipLevels = 1;
	fontDesc.Italic = false;
	fontDesc.CharSet = DEFAULT_CHARSET;
	fontDesc.OutputPrecision = OUT_DEFAULT_PRECIS;
	fontDesc.Quality = DEFAULT_QUALITY;
	fontDesc.PitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	_tcscpy(fontDesc.FaceName, _T("Arial"));

	createHeightWeightFont(FONT_12_NORMAL,	12, FW_NORMAL,	fontDesc);
	createHeightWeightFont(FONT_12_BOLD,	12, FW_BOLD,	fontDesc);
	createHeightWeightFont(FONT_14_NORMAL,	14,	FW_NORMAL,	fontDesc);
	createHeightWeightFont(FONT_14_BOLD,	14, FW_BOLD,	fontDesc);
	createHeightWeightFont(FONT_16_BOLD,	16, FW_BOLD,	fontDesc);
	createHeightWeightFont(FONT_18_BOLD,	18, FW_BOLD,	fontDesc);
	createHeightWeightFont(FONT_24_BOLD,	24, FW_BOLD,	fontDesc);
}

// 初始化EngineImpl
void D3DEngine::initEngineImpl()
{
	m_resourceManager = new D3D9ResourceManager();
	m_resourceManager->OnD3DCreateDevice(m_d3dDevice);

	D3DEngineImpl* engineImpl = new D3DEngineImpl();
	engineImpl->Init(m_resourceManager, ENGINE_IMPL_TEX_FILE);
	SetEngineImpl(engineImpl);
}

// 创建不同大小和粗细的字体
void D3DEngine::createHeightWeightFont(FONT_TYPE fontType, int height, int weight, D3DXFONT_DESC & fontDesc)
{
	fontDesc.Height = height;
	fontDesc.Weight = weight;
	
	ID3DXFont* font;
	HR(D3DXCreateFontIndirect(m_d3dDevice, &fontDesc, &font));
	m_fonts.emplace(fontType, font);
}

