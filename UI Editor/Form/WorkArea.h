#ifndef WORK_AREA_H
#define WORK_AREA_H

#include <wx/window.h>

class WorkArea
{
public:
	WorkArea(wxWindow* parent);
	virtual ~WorkArea();

protected:
	// 获取该工作区的主窗口对象
	virtual wxWindow* getBench() = 0;
};

#endif	// WORK_AREA_H
