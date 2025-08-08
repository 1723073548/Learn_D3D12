#include <windows.h>

LPCTSTR gWindowClassName = L"BattleFire";

//点击窗口时的回调函数
LRESULT CALLBACK WindowProc(HWND inHWND, UINT inMSG, WPARAM inWParam, LPARAM inLParam) {
	// inMsg 表示输入事件类型
	// inWParam 和 inLParam 分别表示输入事件的附加信息(某键盘、鼠标按键 或 滚轮..)
	switch (inMSG) {
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return DefWindowProc(inHWND, inMSG, inWParam, inLParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	//窗口创建的步骤：
	// 1. 注册窗口类-register
	// 2. 创建窗口-creat
	// 3. 显示窗口-show
	// 4. 消息循环-loop
#pragma region 1. Register
	WNDCLASSEX wndClassEx;
	wndClassEx.cbSize = sizeof(WNDCLASSEX); // 窗口类结构体的大小，必须设置为sizeof(WNDCLASSEX)
	wndClassEx.style = CS_HREDRAW | CS_VREDRAW; // 重绘时采用的样式，HREDRAW表示水平重绘，VREDRAW表示垂直重绘
	
	wndClassEx.cbClsExtra = NULL; // 窗口类   是否有额外字节空间
	wndClassEx.cbWndExtra = NULL; // 窗口实例 是否有额外字节空间
	
	wndClassEx.hInstance = hInstance; // 窗口类所属的应用程序实例句柄

	wndClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION); // 窗口类的图标, IDI-IDIcon默认图标
	wndClassEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION); // 窗口类的小图标

	wndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW); // 窗口类的光标, IDC-IDCursor默认光标

	wndClassEx.hbrBackground = NULL; // 窗口类的背景色
	wndClassEx.lpszMenuName = NULL; // 窗口类的菜单名称
	wndClassEx.lpszClassName = gWindowClassName; // 窗口类的名称

	wndClassEx.lpfnWndProc = WindowProc; // 窗口类的回调函数指针. lp-long pointer | fn-function | WndProc-window procedure

	if (!RegisterClassExW(&wndClassEx)) {
		MessageBox(NULL, L"Register Class Faild", L"Error", MB_OK | MB_ICONERROR);
		return -1;
	}
#pragma endregion

#pragma region 2. Create
	//视口大小：宽800 高600
	int viewportWidth = 800;
	int viewportHeight = 600;

	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = viewportHeight;
	rect.bottom = viewportWidth;
	
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE); // 调整窗口大小以适应视口，一种风格。
	
	//坐标原点在屏幕左上角
	int windowWidth = rect.right - rect.left; // 计算调整后的窗口宽度
	int windowHeight = rect.bottom - rect.top; // 计算调整后的窗口高度

	HWND hwnd = CreateWindowEx(
		NULL,
		gWindowClassName,
		L"My Render Window",
		WS_OVERLAPPEDWINDOW, // 窗口风格
		CW_USEDEFAULT, // x坐标
		CW_USEDEFAULT, // y坐标
		windowWidth, // 窗口宽度
		windowHeight, // 窗口高度
		NULL, // 父窗口句柄
		NULL, // 菜单句柄
		hInstance, // 应用程序实例句柄
		NULL // 附加参数，会传递给窗口处理回调函数
		);
	if (hwnd == nullptr) {
		MessageBox(NULL, L"Creat Window Faild", L"Error", MB_OK | MB_ICONERROR);
		return -1;
	}
#pragma endregion

	return 0;
}