#include "CopyWinObject.h"

// 该函数默认传入的结构体为CopyWindowInfo
bool CopyWinObject::GetDataHere(void* buf) const
{
	CopyWindowInfo* value = reinterpret_cast<CopyWindowInfo*>(buf);
	new (buf) CopyWindowInfo;
	*value = m_data;
	return true;
}


size_t CopyWinObject::GetDataSize() const
{
	return sizeof(m_data);
}

// 设置的结构体默认为CopyWindowInfo
bool CopyWinObject::SetData(size_t len, const void * buf)
{
	const CopyWindowInfo* value = reinterpret_cast<const CopyWindowInfo*>(buf);
	m_data = *value;
	return true;
}
