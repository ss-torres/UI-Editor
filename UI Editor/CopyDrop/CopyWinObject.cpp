#include "CopyWinObject.h"

// 该函数默认传入的结构体为CopyWindowValue
bool CopyWinObject::GetDataHere(void* buf) const
{
	CopyWindowValue* value = reinterpret_cast<CopyWindowValue*>(buf);
	new (buf) CopyWindowValue;
	*value = m_data;
	return true;
}


size_t CopyWinObject::GetDataSize() const
{
	return sizeof(m_data);
}

// 设置的结构体默认为CopyWindowValue
bool CopyWinObject::SetData(size_t len, const void * buf)
{
	const CopyWindowValue* value = reinterpret_cast<const CopyWindowValue*>(buf);
	m_data = *value;
	return true;
}
