#include "EditorWorkArea.h"
#include "../DrawEngine/d3dEngine.h"
#include "../CopyDrop/CopyWinObject.h"
#include "../EditorWindow/WindowInterface.h"

class DropWinTarget : public wxDropTarget
{
public:
	DropWinTarget(EditorWorkArea *workArea)
		: wxDropTarget(new CopyWinObject(getCopyDataFormat()))
	{
		m_workArea = workArea;
	}

	~DropWinTarget(){ }

	wxDragResult OnEnter(wxCoord x, wxCoord y, wxDragResult defResult) override
	{
		return defResult;
	}

	wxDragResult OnDragOver(wxCoord x, wxCoord y, wxDragResult defResult) override
	{
		return defResult;
	}

	wxDragResult OnData(wxCoord x, wxCoord y, wxDragResult defResult) override
	{
		if (!GetData())
		{
			return wxDragNone;
		}

		auto rcvObj = dynamic_cast<CopyWinObject*>(GetDataObject());

		if (rcvObj == nullptr)
		{
			return wxDragNone;
		}

		m_workArea->onDrop(x, y, rcvObj->getWinValue());

		return defResult;
	}
private:
	EditorWorkArea* m_workArea;
};

EditorWorkArea::EditorWorkArea(wxMDIParentFrame* parent, const wxString& captionName = wxEmptyString, const wxPoint& position = wxDefaultPosition, const wxSize &size = wxDefaultSize)
	: WorkArea(parent)
{
	m_bench = new wxMDIChildFrame(parent, wxID_ANY, captionName, position, size);
	m_d3dEngine = new D3DEngine(getHandle(), D3DDEVTYPE_HAL, D3DCREATE_HARDWARE_VERTEXPROCESSING);

	getBench()->SetDropTarget(new DropWinTarget(this));
}

EditorWorkArea::~EditorWorkArea()
{
	delete m_d3dEngine;
}

wxWindow * EditorWorkArea::getBench()
{
	return m_bench;
}

// 用来每帧处理
void EditorWorkArea::updateFrame(float dt)
{
	// 查看设备是否丢失
	if (m_d3dEngine->checkDeviceLost())
	{
		return;
	}

	updateScene(dt);
	drawScene();
}

// 用来处理Drop事件
void EditorWorkArea::onDrop(wxCoord x, wxCoord y, const CopyWindowValue & winValue)
{
	
}

// 用来处理场景更新的计算
void EditorWorkArea::updateScene(float dt)
{
	
}

// 用来每帧绘制
void EditorWorkArea::drawScene()
{
	IDirect3DDevice9* d3dDevice = m_d3dEngine->getDevice();

	HR(d3dDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(255, 255, 255), 1.0f, 0));
	RECT formatRect;
	GetClientRect(getHandle(), &formatRect);

	HR(d3dDevice->BeginScene());

	//m_d3dEngine->getFont()->DrawText(0, _T("Hello Direct3D"), -1,
	//	&formatRect, DT_CENTER | DT_VCENTER,
	//	D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256));

	HR(d3dDevice->EndScene());
	HR(d3dDevice->Present(0, 0, 0, 0));
}

// 初始化D3D成员
void EditorWorkArea::initD3DMember()
{

}
