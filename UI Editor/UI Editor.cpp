#include "EditorApp.h"

//IMPLEMENT_APP(EditorApp)

wxIMPLEMENT_WX_THEME_SUPPORT

extern "C" int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	wxCmdLineArgType WXUNUSED(lpCmdLine),
	int nCmdShow)
{
	wxDISABLE_DEBUG_SUPPORT();

	/* NB: We pass NULL in place of lpCmdLine to behave the same as  */
	/*     Borland-specific wWinMain() above. If it becomes needed   */
	/*     to pass lpCmdLine to wxEntry() here, you'll have to fix   */
	/*     wWinMain() above too.                                     */
	return wxEntry(hInstance, hPrevInstance, NULL, nCmdShow);
}
wxIMPLEMENT_WXWIN_MAIN_BORLAND_NONSTANDARD

wxIMPLEMENT_APP_NO_MAIN(EditorApp);