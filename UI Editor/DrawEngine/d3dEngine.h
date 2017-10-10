#ifndef D3D_ENGINE_H
#define D3D_ENGINE_H

#include <map>
#include "d3dUtil.h"
#include "GameTimer.h"
#include "../Settings/WindowEnumAttrDefine.h"
#include "../ErrorHandle/ErrorHandle.h"

class D3DEngine
{
public:
	D3DEngine(HWND mainWndId, D3DDEVTYPE devType, DWORD requestedVP);
	~D3DEngine();

	// 获取D3D引擎对应窗口
	HWND getMainWnd() const;
	// 处理对应窗口大小改变
	void handlgeSizeChange(UINT width, UINT height);

	// 获取设备
	IDirect3DDevice9* getDevice() { return m_d3dDevice;  }
	// 获取对应的字体
	ID3DXFont* getFont(FONT_TYPE fontType) const;

	// 处理可能的设备丢失
	bool checkDeviceLost();

private:
	// 重设设备前的清理
	void onLostDevice();
	// 重设设备后的处理
	void onResetDevice();
	// 计算设备帧数信息
	void CalculateFrameStats();

	// 完成D3D基本初始化
	void initDirect3D();
	// 初始化D3D字体
	void initD3DFont();
	// 创建不同大小和粗细的字体
	void createHeightWeightFont(FONT_TYPE fontType, int height, int weight, D3DXFONT_DESC& fontDesc);

private:
	// D3D引擎对应的窗口ID
	HWND m_mainWnd;
	// D3D设备类型
	D3DDEVTYPE m_devType;
	// D3D要求的顶点处理
	DWORD m_requestedVP;
	// D3D对象
	IDirect3D9* m_d3dObject;
	// D3D表现参数
	D3DPRESENT_PARAMETERS m_d3dPP;
	// D3D设备
	IDirect3DDevice9* m_d3dDevice;
	// 用来进行输入的字体
	std::map<FONT_TYPE, ID3DXFont*> m_fonts;

	// 时间计数器
	GameTimer m_timer;
	// 每秒帧数
	float m_fps;
	// 每帧所用毫秒数
	float m_mspf;
};

// 获取D3D对应窗口
inline HWND D3DEngine::getMainWnd() const
{
	return m_mainWnd;
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

#endif	// D3D_ENGINE_H
