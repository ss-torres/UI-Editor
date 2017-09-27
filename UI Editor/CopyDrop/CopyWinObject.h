#ifndef COPY_WIN_OBJECT_H
#define COPY_WIN_OBJECT_H

/*
 * 文件名：CopyWinObject
 * 作用：Drag & Drop中用来传递窗口属性值的数据
 * 注意事项：当前只考虑一个应用直接的拷贝，如果需要可以修改来实现不同项目之间的考虑
 */

#include <map>
#include <type_traits>
#include <wx/string.h>
#include <wx/dataobj.h>
#include "../EditorWindow/WindowFactoryDefine.h"

const wxString COPY_DATA_FORMAT = wxS("CopyWinValue");

// 获取一个自定义的DataFormat
inline wxDataFormat getCopyDataFormat()
{
	wxDataFormat format;
	format.SetId(COPY_DATA_FORMAT);
	return format;
}

class CopyWinObject : public wxDataObjectSimple
{
public:
	CopyWinObject(const wxDataFormat& format = wxFormatInvalid)
		: wxDataObjectSimple(format)
	{

	}

	// 该函数默认传入的结构体为CopyWindowInfo
	bool GetDataHere(void *buf) const override;
	
	size_t GetDataSize() const override;
	// 设置的结构体默认为CopyWindowInfo
	bool SetData(size_t len, const void* buf) override;

	// 用来获取存储的窗口属性信息
	const CopyWindowInfo& getWinValue() const { return m_data; }

private:
	CopyWindowInfo m_data;
};

#endif	// COPY_WIN_OBJECT_H