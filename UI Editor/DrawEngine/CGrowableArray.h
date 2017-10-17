#ifndef CGROWABLE_ARRAY_H
#define CGROWABLE_ARRAY_H

/*
* 文件名：CGrowableArray
* 作用：类似于vector的作用
* 说明：该部分文件的实现，使用了Microsoft的DXUT中的相关实现，并加以修改
* 使用者可以移除该部分代码，同时增加自己的主工作区的渲染代码
*/

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <winnt.h>
#include <winerror.h>
#include <assert.h>
#include "../Util/ArithmeticUtil.h"

template <typename TYPE>
class CGrowableArray
{
public:
	CGrowableArray() {}
	CGrowableArray(const CGrowableArray<TYPE>& a) : m_arrayData(a.m_arrayData) { }
	CGrowableArray(CGrowableArray<TYPE>&& a) : m_arrayData(std::move(a.m_arrayData)) { }
	~CGrowableArray() {}

	const TYPE& operator[](int nIndex) const { return GetAt(nIndex); }
	TYPE& operator[](int nIndex) { return GetAt(nIndex); }

	// 用来获取Iterator
	auto begin() { return m_arrayData.begin(); }
	auto end() { return m_arrayData.end(); }
	auto cbegin() { return m_arrayData.cbegin(); }
	auto cend() { return m_arrayData.cend(); }

	CGrowableArray& operator=(const CGrowableArray<TYPE>& a) { m_arrayData = a.m_arrayData; return *this; }
	CGrowableArray& operator=(CGrowableArray<TYPE>&& a) { m_arrayData = std::move(a.m_arrayData); return *this; }

	HRESULT SetSize(int nNewMaxSize);
	HRESULT Add(const TYPE& value);
	HRESULT Insert(int nIndex, const TYPE& value);
	HRESULT SetAt(int nIndex, const TYPE& value);
	TYPE& GetAt(int nIndex) { assert(nIndex >= 0 && nIndex < narrow_cast<int>(m_arrayData.size())); return m_arrayData[nIndex]; }
	const TYPE& GetAt(int nIndex) const { assert(nIndex >= 0 && nIndex < m_arrayData.size()); return m_arrayData[nIndex]; }
	int GetSize() const { return m_arrayData.size(); }
	TYPE* GetData() { if (m_arrayData.empty()) return nullptr; else return &m_arrayData[0]; }
	bool Contains(const TYPE& value);

	int IndexOf(const TYPE& value) { return Indexof(value, 0); }
	int IndexOf(const TYPE& value, int iStart) { return IndexOf(value, iStart, m_arrayData.size() - iStart); }
	int IndexOf(const TYPE& value, int iStart, int nNumElements);

	int LastIndexOf(const TYPE& value) { return LastIndexOf(value, m_arrayData.size() - 1, m_arrayData.size()); }
	int LastIndexOf(const TYPE& value, int nIndex) { return LastIndexOf(value, nIndex, nIndex + 1); }
	int LastIndexOf(const TYPE& value, int nIndex, int nNumElements);

	HRESULT Remove(int nIndex);
	void RemoveAll() { m_arrayData.clear(); }
	void Reset() { m_arrayData.clear(); }

private:
	std::vector<TYPE> m_arrayData;

	HRESULT SetSizeInternal(int nNewMaxSize);
};

template <typename TYPE>
HRESULT CGrowableArray<TYPE>::SetSize(int nNewMaxSize)
{
	HRESULT hr = SetSizeInernal(nNewMaxSize);
	if (FAILED(hr))
	{
		return hr;
	}
	m_arrayData.resize(nNewMaxSize);
	return hr;
}

template <typename TYPE>
HRESULT CGrowableArray<TYPE>::Add(const TYPE& value)
{
	HRESULT hr = SetSizeInternal(m_arrayData.size() + 1);
	if (FAILED(hr))
	{
		return hr;
	}

	m_arrayData.push_back(value);
	return hr;
}

template <typename TYPE>
HRESULT CGrowableArray<TYPE>::Insert(int nIndex, const TYPE& value)
{
	// Validate index
	if (nIndex < 0 ||
		nIndex > m_arrayData.size())
	{
		assert(false);
		return E_INVALIDARG;
	}

	HRESULT hr = SetSizeInternal(m_arrayData.size() + 1);
	if (FAILED(hr))
	{
		return hr;
	}

	m_arrayData.insert(m_arrayData.cbegin() + nIndex, value);
	return hr;
}

template <typename TYPE>
HRESULT CGrowableArray<TYPE>::SetAt(int nIndex, const TYPE& value)
{
	// Validate arguments
	if (nIndex < 0 ||
		nIndex >= m_arrayData.size())
	{
		assert(false);
		return E_INVALIDARG;
	}

	m_arrayData[nIndex] = value;
	return S_OK;
}

template <typename TYPE>
bool CGrowableArray<TYPE>::Contains(const TYPE& value)
{
	auto it = std::find(m_arrayData.cbegin(), m_arrayData.cend(), value);
	if (it != m_arrayData.cend())
	{
		return true;
	}

	return false;
}

template <typename TYPE>
int CGrowableArray<TYPE>::IndexOf(const TYPE& value, int iStart, int nNumElements)
{
	if (iStart < 0 ||
		iStart >= m_arrayData.size() ||
		nNumElements < 0 ||
		iStart + nNumElements > m_arrayData.size())
	{
		assert(false);
		return -1;
	}

	auto endIter = m_arrayData.cbegin() + iStart + nNumElements;
	auto it = find(endIter - nNumElements, endIter, value);
	if (it != endIter)
	{
		return it - m_arrayData.cbegin();
	}
	return -1;
}

template <typename TYPE>
int CGrowableArray<TYPE>::LastIndexOf(const TYPE& value, int nIndex, int nNumElements)
{
	if (nIndex < 0 ||
		nIndex >= m_arrayData.size() ||
		nNumElements < 0 ||
		nIndex - nNumElements < 0)
	{
		assert(false);
		return -1;
	}

	auto endIter = m_arrayData.begin() + nIndex + 1;
	auto it = find_end(endIter - nNumElements, endIter, value);
	if (it != endIter)
	{
		return it - m_arrayData.cbegin();
	}
	return -1;
}

template <typename TYPE>
HRESULT CGrowableArray<TYPE>::Remove(int nIndex)
{
	if (nIndex < 0 ||
		nIndex >= m_arrayData.size())
	{
		assert(false);
		return E_INVALIDARG;
	}

	m_arrayData.remove(m_arrayData.cbegin() + nIndex);
	return S_OK;
}

template <typename TYPE>
HRESULT CGrowableArray<TYPE>::SetSizeInternal(int nNewMaxSize)
{
	try
	{
		m_arrayData.reserve(nNewMaxSize);
	}
	catch (const std::length_error&/* e*/)
	{
		return E_INVALIDARG;
	}
	catch (const std::bad_alloc&/* e*/)
	{
		return E_OUTOFMEMORY;
	}
	catch (...)
	{
		return E_UNEXPECTED;
	}

	return S_OK;
}

#endif	// CGROWABLE_ARRAY_H
