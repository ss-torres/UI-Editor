#ifndef D3D_UTIL_H
#define D3D_UTIL_H

// Enable extra D3D debugging in debug builds if using the debug DirectX runtime.
// This makes D3D objects work well in the debugger watch window, but slows down
// performance slightly.
#if defined(DEBUG) | defined(_DEBUG)
#ifndef D3D_DEBUG_INFO
#define D3D_DEBUG_INFO
#endif
#endif

#include <d3d9.h>
#include <d3dx9.h>
#include <DxErr.h>

// Globals for convenient access
class D3DApp;
extern D3DApp* gd3dApp;
extern IDirect3DDevice9* gd3dDevice;

// Clean up
template <typename T>
void ReleaseCOM(T* p)
{
	if (p)
	{
		p->Release();
		p = nullptr;
	}
}

#if defined(DEBUG) | defined(_DEBUG)
	#ifndef HR
#define HR(x)		HR_impl(x, #x, __FILE__, __LINE__);
	#endif
#else
	#ifndef HR
	#define HR(x)	x;
	#endif
#endif

inline void HR_impl(HRESULT x, const char* const funcDesc, const char* const fileName, const int fileLine)
{
	HRESULT hr = x;
	if (FAILED(hr))
	{
		DXTraceA(fileName, fileLine, hr, funcDesc, TRUE);
	}
}

#endif	// D3D_UTIL_H
