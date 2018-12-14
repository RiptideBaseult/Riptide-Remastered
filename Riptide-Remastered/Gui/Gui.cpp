#include "Gui.h"

using namespace Client;

//[enc_string_enable /]
//[junk_enable /]

bool bIsGuiInitalize = false;
bool bIsGuiVisible = false;
WNDPROC WndProc_o = nullptr;

#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))

LRESULT WINAPI GUI_WndProc( HWND hwnd , UINT uMsg , WPARAM wParam , LPARAM lParam );

CGui::CGui() {}

ImFont* main;
ImFont* icons;

CGui::~CGui()
{
	ImGui_ImplDX9_Shutdown();
}

void CGui::GUI_Init( IDirect3DDevice9 * pDevice )
{
	HWND hWindow = FindWindowA("Valve001", 0);

	ImGui_ImplDX9_Init(hWindow, pDevice);

	ImGuiIO& io = ImGui::GetIO();
	ImGuiStyle& style = ImGui::GetStyle();

	io.IniFilename = GuiFile.c_str();

	main = io.Fonts->AddFontFromMemoryCompressedTTF(font_compressed_data, font_compressed_size, 16.f);
	icons = io.Fonts->AddFontFromMemoryCompressedTTF(icon_compressed_data, icon_compressed_size, 18.f); // make this font a bit bigger for bigger icons

	style.WindowMinSize = ImVec2( 200 , 200 );
	style.FramePadding = ImVec2( 4 , 2 );
	style.ItemSpacing = ImVec2( 6 , 3 );
	style.ItemInnerSpacing = ImVec2( 6 , 4 );
	style.Alpha = 1.f;
	style.WindowRounding = 10.f;
	style.FrameRounding = 10.f;
	style.IndentSpacing = 6.0f;
	style.ItemInnerSpacing = ImVec2( 3 , 4 );
	style.ColumnsMinSpacing = 50.0f;
	style.GrabMinSize = 14.0f;
	style.GrabRounding = 16.0f;
	style.ScrollbarSize = 12.0f;
	style.ScrollbarRounding = 16.0f;
	style.AntiAliasedLines = true;
	style.AntiAliasedFill = true;

	Default();

	ImGui_ImplDX9_CreateDeviceObjects();

	WndProc_o = (WNDPROC)SetWindowLongA( hWindow , GWL_WNDPROC , (LONG)(LONG_PTR)GUI_WndProc );

	bIsGuiInitalize = true;
}

void CGui::GUI_Begin_Render()
{
	ImGui_ImplDX9_NewFrame();
}

void CGui::GUI_End_Render()
{
	ImGui::Render();
}

LRESULT WINAPI GUI_WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static bool bDown = false;
	static bool bClicked = false;
	static bool bPrevMenuState = bIsGuiVisible;
	static ConVar * men = Interfaces::GetConVar()->FindVar("cl_mouseenable");
	if (GUI_KEY_DOWN(VK_INSERT))
	{
		bClicked = false;
		bDown = true;
	}
	else if (!GUI_KEY_DOWN(VK_INSERT) && bDown)
	{
		bClicked = true;
		bDown = false;
	}
	else
	{
		bClicked = false;
		bDown = false;
	}

	if (bClicked)
	{
		bIsGuiVisible = !bIsGuiVisible;
		men->SetValue(bIsGuiVisible);
	}

	if (bPrevMenuState != bIsGuiVisible)
	{
		men->SetValue(!bIsGuiVisible);
	}
	bPrevMenuState = bIsGuiVisible;

	if (bIsGuiVisible && ImGui_ImplDX9_WndProcHandler(hwnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProcA(WndProc_o, hwnd, uMsg, wParam, lParam);
}


void CGui::GUI_Draw_Elements()
{
	if (!bIsGuiInitalize || Interfaces::Engine()->IsTakingScreenshot() || !Interfaces::Engine()->IsActiveApp())
		return;

	g_pGui->GUI_Begin_Render();

	bool bOpenTimer = (bIsGuiVisible || (bC4Timer && iC4Timer));

	if (Settings::Misc::misc_Spectators) g_pMisc->OnRenderSpectatorList();

	if (g_pEsp && Settings::Esp::esp_BombTimer && bOpenTimer && Interfaces::Engine()->IsInGame())
	{
		if (g_pEsp && Settings::Esp::esp_BombTimer && bOpenTimer)
		{
			g_pRender->Text(15, 480, false, true, Color::Red(), C4_TIMER_STRING, g_pEsp->fC4Timer);
			g_pRender->Text(15, 481, false, true, Color::Red(), "_____________");
		}
		else
		{
			//off
		}
	}
	if (Interfaces::Engine()->IsInGame())
	{
		if (Settings::Radar::rad_InGame && GetKeyState(Settings::Radar::rad_InGameKey))
		{
			g_pRender->Text(15, 465, false, true, Color::Aqua(), "RADAR: ON");
		}
		else if (Settings::Radar::rad_InGame)
		{
			g_pRender->Text(15, 465, false, true, Color::Aqua(), "RADAR: OFF");
		}
	}

	if ( g_pEsp && Settings::Esp::esp_BombTimer && bOpenTimer )
	{
		ImVec2 OldMinSize = ImGui::GetStyle().WindowMinSize;

		ImGui::GetStyle().WindowMinSize = ImVec2( 0.f , 0.f );

		ImGui::SetNextWindowSize( ImVec2( 125.f , 30.f ) );
		
		ImGui::GetStyle().WindowMinSize = OldMinSize;
	}

	if ( bIsGuiVisible )
	{
		int pX , pY;
		Interfaces::InputSystem()->GetCursorPosition( &pX , &pY );

		ImGui::GetIO().MousePos.x = (float)pX;
		ImGui::GetIO().MousePos.y = (float)pY;

		Client::OnRenderGUI();
	}
	
	if ( g_pRadar )
		g_pRadar->OnRender();

	if (Settings::Misc::misc_Spectators) g_pMisc->OnRenderSpectatorList();

	g_pGui->GUI_End_Render();
}

void CGui::Default()
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.Alpha = 1.f;
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.WindowMinSize = ImVec2(200, 200);
	style.FramePadding = ImVec2(4, 2);
	style.ItemSpacing = ImVec2(6, 3);
	style.ItemInnerSpacing = ImVec2(6, 4);
	style.WindowRounding = 10.f;
	style.FrameRounding = 10.f;
	style.ColumnsMinSpacing = 50.0f;
	style.GrabMinSize = 14.0f;
	style.GrabRounding = 10.f;
	style.ScrollbarSize = 12.0f;
	style.ScrollbarRounding = 10.0f;
	style.AntiAliasedLines = true;
	style.AntiAliasedFill = true;

	style.Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(0.40f, 0.39f, 0.38f, 0.16f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
}

void CGui::IconsFont()
{
	ImGui::PushFont(icons);
	ImGuiStyle& style = ImGui::GetStyle();

	style.Alpha = 1.f;
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.WindowMinSize = ImVec2(200, 200);
	style.FramePadding = ImVec2(4, 2);
	style.ItemSpacing = ImVec2(6, 3);
	style.ItemInnerSpacing = ImVec2(6, 4);
	style.WindowRounding = 10.f;
	style.FrameRounding = 10.f;
	style.ColumnsMinSpacing = 50.0f;
	style.GrabMinSize = 14.0f;
	style.GrabRounding = 10.f;
	style.ScrollbarSize = 12.0f;
	style.ScrollbarRounding = 10.0f;
	style.AntiAliasedLines = true;
	style.AntiAliasedFill = true;

	style.Colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 0.86f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 0.86f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.30f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.87f, 0.87f, 0.87f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.82f, 0.82f, 0.83f, 0.40f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.82f, 0.82f, 0.84f, 0.40f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.94f, 0.94f, 0.94f, 0.53f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 0.80f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.49f, 0.49f, 0.49f, 0.80f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
	style.Colors[ImGuiCol_CheckMarkBg] = ImVec4(0.87f, 0.87f, 0.87f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f); //main half
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.5f, 0.f, 0.1f, 2.f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.87f, 0.87f, 0.87f, 1.00f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.82f, 0.82f, 0.82f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.94f, 0.94f, 0.94f, 0.51f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.67f, 0.67f, 0.67f, 0.40f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.67f, 0.67f, 0.67f, 0.40f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.40f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.67f, 0.67f, 0.67f, 0.40f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.67f, 0.67f, 0.67f, 0.40f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.40f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.80f, 0.80f, 0.80f, 0.56f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.80f, 0.80f, 0.80f, 0.56f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.80f, 0.80f, 0.80f, 0.56f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.45f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.69f, 0.69f, 0.69f, 0.35f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.87f, 0.87f, 0.87f, 0.98f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
}

void CGui::MainFont()
{
	ImGui::PushFont(main);
	ImGuiStyle& style = ImGui::GetStyle();

	static int hue = 140;
	ImVec4 col_text = ImColor::HSV(hue / 255.f, 20.f / 255.f, 235.f / 255.f);
	ImVec4 col_theme = ImColor(17, 17, 17);
	ImVec4 col_main = ImColor(9, 82, 128);
	ImVec4 col_back = ImColor(35, 35, 35);
	ImVec4 col_area = ImColor(4, 32, 41);

	style.Colors[ImGuiCol_Text] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 0.86f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 0.86f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 0.00f, 0.00f, 0.30f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.87f, 0.87f, 0.87f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.82f, 0.82f, 0.83f, 0.40f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.82f, 0.82f, 0.84f, 0.40f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.86f, 0.86f, 0.86f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.94f, 0.94f, 0.94f, 0.53f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.69f, 0.69f, 0.69f, 0.80f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.49f, 0.49f, 0.49f, 0.80f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.49f, 0.49f, 0.49f, 1.00f);
	style.Colors[ImGuiCol_CheckMarkBg] = ImVec4(0.87f, 0.87f, 0.87f, 1.00f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.67f, 0.67f, 0.67f, 0.32f); //main half
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.67f, 0.67f, 0.67f, 2.f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.67f, 0.67f, 0.67f, 0.40f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.67f, 0.67f, 0.67f, 0.40f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.40f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.67f, 0.67f, 0.67f, 0.40f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.67f, 0.67f, 0.67f, 0.40f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.67f, 0.67f, 0.67f, 0.40f);
	style.Colors[ImGuiCol_Column] = ImVec4(col_text.x, col_text.y, col_text.z, 0.32f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(col_text.x, col_text.y, col_text.z, 0.78f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(col_text.x, col_text.y, col_text.z, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.80f, 0.80f, 0.80f, 0.56f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.80f, 0.80f, 0.80f, 0.56f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.80f, 0.80f, 0.80f, 0.56f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(col_text.x, col_text.y, col_text.z, 0.f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(col_text.x, col_text.y, col_text.z, 0);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(col_text.x, col_text.y, col_text.z, 0);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.80f, 0.80f, 0.80f, 0.56f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.80f, 0.80f, 0.80f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.69f, 0.69f, 0.69f, 0.35f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.87f, 0.87f, 0.87f, 0.98f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);



	style.WindowPadding = ImVec2(8, 8);
	style.WindowMinSize = ImVec2(32, 32);
	style.WindowRounding = 10.f;
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	//style.ChildRounding = 0.0f;
	style.FramePadding = ImVec2(4, 2);
	style.FrameRounding = 10.f;

	style.ItemSpacing = ImVec2(8, 4);
	style.ItemInnerSpacing = ImVec2(4, 4);
	style.TouchExtraPadding = ImVec2(0, 0);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 3.0f;
	style.ScrollbarSize = 12.0f;
	style.ScrollbarRounding = 0.0f;
	style.GrabMinSize = 7.0f;
	style.GrabRounding = 3.0f;
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.DisplayWindowPadding = ImVec2(22, 22);
	style.DisplaySafeAreaPadding = ImVec2(4, 4);
	style.AntiAliasedLines = true;
	//style.AntiAliasedShapes = true;
	style.CurveTessellationTol = 1.25f;
}

namespace ImGui
{
	static auto vector_getter = []( void* vec , int idx , const char** out_text )
	{
		auto& vector = *static_cast<std::vector<std::string>*>( vec );
		if ( idx < 0 || idx >= static_cast<int>( vector.size() ) ) { return false; }
		*out_text = vector.at( idx ).c_str();
		return true;
	};

	IMGUI_API bool ListBoxConfigArray(const char* label, int* currIndex, std::vector<std::string>& values)
	{
		return ListBox(label, currIndex, vector_getter,
			static_cast<void*>(&values), values.size(), 10);
	}

	IMGUI_API bool ComboBoxArray( const char* label , int* currIndex , std::vector<std::string>& values )
	{
		if ( values.empty() ) { return false; }
		return Combo( label , currIndex , vector_getter ,
					  static_cast<void*>( &values ) , values.size() );
	}

	IMGUI_API bool TabLabels( const char **tabLabels , int tabSize , int &tabIndex , int *tabOrder )
	{
		ImGuiStyle& style = ImGui::GetStyle();

		const ImVec2 itemSpacing = style.ItemSpacing;
		const ImVec4 color = style.Colors[ImGuiCol_Button];
		const ImVec4 colorActive = style.Colors[ImGuiCol_ButtonActive];
		const ImVec4 colorHover = style.Colors[ImGuiCol_ButtonHovered];
		const ImVec4 colorText = style.Colors[ImGuiCol_Text];
		style.ItemSpacing.x = 1;
		style.ItemSpacing.y = 1;
		const ImVec4 colorSelectedTab = ImVec4( color.x , color.y , color.z , color.w*0.5f );
		const ImVec4 colorSelectedTabHovered = ImVec4( colorHover.x , colorHover.y , colorHover.z , colorHover.w*0.5f );
		const ImVec4 colorSelectedTabText = ImVec4( colorText.x*0.8f , colorText.y*0.8f , colorText.z*0.8f , colorText.w*0.8f );

		if ( tabSize>0 && ( tabIndex<0 || tabIndex >= tabSize ) )
		{
			if ( !tabOrder )
			{
				tabIndex = 0;
			}
			else
			{
				tabIndex = -1;
			}
		}

		float windowWidth = 0.f , sumX = 0.f;
		windowWidth = ImGui::GetWindowWidth() - style.WindowPadding.x - ( ImGui::GetScrollMaxY()>0 ? style.ScrollbarSize : 0.f );

		static int draggingTabIndex = -1; int draggingTabTargetIndex = -1;
		static ImVec2 draggingtabSize( 0 , 0 );
		static ImVec2 draggingTabOffset( 0 , 0 );

		const bool isMMBreleased = ImGui::IsMouseReleased( 2 );
		const bool isMouseDragging = ImGui::IsMouseDragging( 0 , 2.f );
		int justClosedTabIndex = -1 , newtabIndex = tabIndex;

		bool selection_changed = false; bool noButtonDrawn = true;

		for ( int j = 0 , i; j < tabSize; j++ )
		{
			i = tabOrder ? tabOrder[j] : j;
			if ( i == -1 ) continue;

			if ( sumX > 0.f )
			{
				sumX += style.ItemSpacing.x;
				sumX += ImGui::CalcTextSize( tabLabels[i] ).x + 2.f*style.FramePadding.x;
				
				if ( sumX>windowWidth )
				{
					sumX = 0.f;
				}
				else
				{
					ImGui::SameLine();
				}
			}

			if ( i != tabIndex )
			{
				// Push the style
				style.Colors[ImGuiCol_Button] = colorSelectedTab;
				style.Colors[ImGuiCol_ButtonActive] = colorSelectedTab;
				style.Colors[ImGuiCol_ButtonHovered] = colorSelectedTabHovered;
				style.Colors[ImGuiCol_Text] = colorSelectedTabText;
			}
			// Draw the button
			ImGui::PushID( i );   // otherwise two tabs with the same name would clash.
			if ( ImGui::Button( tabLabels[i] , ImVec2( 216.f , 50.f ) ) ) { selection_changed = ( tabIndex != i ); newtabIndex = i; } //216, 50 //165,30
			ImGui::PopID();
			if ( i != tabIndex )
			{
				// Reset the style
				style.Colors[ImGuiCol_Button] = color;
				style.Colors[ImGuiCol_ButtonActive] = colorActive;
				style.Colors[ImGuiCol_ButtonHovered] = colorHover;
				style.Colors[ImGuiCol_Text] = colorText;
			}
			noButtonDrawn = false;

			if ( sumX == 0.f ) sumX = style.WindowPadding.x + ImGui::GetItemRectSize().x; // First element of a line

			if ( ImGui::IsItemHoveredRect() )
			{
				if ( tabOrder )
				{
					// tab reordering
					if ( isMouseDragging )
					{
						if ( draggingTabIndex == -1 )
						{
							draggingTabIndex = j;
							draggingtabSize = ImGui::GetItemRectSize();
							const ImVec2& mp = ImGui::GetIO().MousePos;
							const ImVec2 draggingTabCursorPos = ImGui::GetCursorPos();
							draggingTabOffset = ImVec2(
								mp.x + draggingtabSize.x*0.5f - sumX + ImGui::GetScrollX() ,
								mp.y + draggingtabSize.y*0.5f - draggingTabCursorPos.y + ImGui::GetScrollY()
							);

						}
					}
					else if ( draggingTabIndex >= 0 && draggingTabIndex<tabSize && draggingTabIndex != j )
					{
						draggingTabTargetIndex = j; // For some odd reasons this seems to get called only when draggingTabIndex < i ! (Probably during mouse dragging ImGui owns the mouse someway and sometimes ImGui::IsItemHovered() is not getting called)
					}
				}
			}

		}

		tabIndex = newtabIndex;


		// Reset draggingTabIndex if necessary
		if ( !isMouseDragging ) draggingTabIndex = -1;

		// Change selected tab when user closes the selected tab
		if ( tabIndex == justClosedTabIndex && tabIndex >= 0 )
		{
			tabIndex = -1;
			for ( int j = 0 , i; j < tabSize; j++ )
			{
				i = tabOrder ? tabOrder[j] : j;
				if ( i == -1 )
				{
					continue;
				}
				tabIndex = i;
				break;
			}
		}

		// Restore the style
		style.Colors[ImGuiCol_Button] = color;
		style.Colors[ImGuiCol_ButtonActive] = colorActive;
		style.Colors[ImGuiCol_ButtonHovered] = colorHover;
		style.Colors[ImGuiCol_Text] = colorText;
		style.ItemSpacing = itemSpacing;

		return selection_changed;
	}
}