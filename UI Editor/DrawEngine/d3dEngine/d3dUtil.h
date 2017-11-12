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
inline void SAFE_DELETE(T& p)
{
	if (p)
	{
		delete p;
		p = nullptr;
	}
}

template <typename T>
inline void SAFE_DELETE_ARRAY(T* p)
{
	if (p)
	{
		delete[] p;
		p = nullptr;
	}
}

template <typename T>
inline void ReleaseCOM(T* p)
{
	if (p)
	{
		p->Release();
		p = nullptr;
	}
}

template<typename T>
inline void SAFE_RELEASE(T* p)
{
	ReleaseCOM(p);
}

#if defined(DEBUG) | defined(_DEBUG)
	#ifndef HR
	#define HR(x)		HR_impl(x, L#x, __FILE__, __LINE__, true)
	#define HR_RETURN(x)	{ HRESULT hr = HR_impl(x, L#x, __FILE__, __LINE__, true); if (FAILED(hr)) return hr; }
	#endif
	#ifndef HR_ERR
	#define HR_ERR(str, hr)		HR_impl(hr, str, __FILE__, __LINE__, false)
	#define HR_ERR_MSGBOX(str, hr)	HR_impl(hr, str, __FILE__, __LINE__, true)
	#endif
#else
	#ifndef HR
	#define HR(x)	x;
	#endif
#endif

inline HRESULT HR_impl(HRESULT x, const TCHAR* funcDesc, const char* const fileName, 
	const int fileLine, bool showBox = true)
{
	HRESULT hr = x;
	if (FAILED(hr))
	{
		DXTrace(fileName, fileLine, hr, funcDesc, showBox);
	}

	return hr;
}

#endif	// D3D_UTIL_H
