#include "WindowControl.h"
#include "../d3dEngine/d3dEngineImpl.h"

WindowControl::WindowControl()
	: m_bEnabled(true)
{
	ZeroMemory(&m_rcBoundingBox, sizeof(m_rcBoundingBox));
}

WindowControl::~WindowControl()
{
	for (auto pElement : m_Elements)
	{
		delete pElement;
	}

	m_Elements.RemoveAll();
}

void WindowControl::Refresh()
{
	for (auto pElement : m_Elements)
	{
		pElement->Refresh();
	}
}

void WindowControl::SetTextColor(D3DCOLOR Color)
{
	auto pElement = m_Elements.GetAt(0);
	if (pElement)
		pElement->FontColor.States[STATE_NORMAL] = Color;
}

HRESULT WindowControl::SetElement(UINT iElement, FontTexElement * pElement)
{
	HRESULT hr = S_OK;

	if (pElement == nullptr)
		return E_INVALIDARG;

	// Make certain the array is this large
	for (UINT i = m_Elements.GetSize(); i <= iElement; ++i)
	{
		auto pNewElement = new (std::nothrow) FontTexElement();
		if (pNewElement == nullptr)
			return E_OUTOFMEMORY;

		hr = m_Elements.Add(pNewElement);
		if (FAILED(hr))
		{
			SAFE_DELETE(pNewElement);
			return hr;
		}
	}

	// Update the data
	FontTexElement* pCurElement = m_Elements.GetAt(iElement);
	*pCurElement = *pElement;

	return S_OK;
}
