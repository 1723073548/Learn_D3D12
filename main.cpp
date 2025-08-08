#include <windows.h>

LPCTSTR gWindowClassName = L"BattleFire";

//�������ʱ�Ļص�����
LRESULT CALLBACK WindowProc(HWND inHWND, UINT inMSG, WPARAM inWParam, LPARAM inLParam) {
	// inMsg ��ʾ�����¼�����
	// inWParam �� inLParam �ֱ��ʾ�����¼��ĸ�����Ϣ(ĳ���̡���갴�� �� ����..)
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
	//���ڴ����Ĳ��裺
	// 1. ע�ᴰ����-register
	// 2. ��������-creat
	// 3. ��ʾ����-show
	// 4. ��Ϣѭ��-loop
#pragma region 1. Register
	WNDCLASSEX wndClassEx;
	wndClassEx.cbSize = sizeof(WNDCLASSEX); // ������ṹ��Ĵ�С����������Ϊsizeof(WNDCLASSEX)
	wndClassEx.style = CS_HREDRAW | CS_VREDRAW; // �ػ�ʱ���õ���ʽ��HREDRAW��ʾˮƽ�ػ棬VREDRAW��ʾ��ֱ�ػ�
	
	wndClassEx.cbClsExtra = NULL; // ������   �Ƿ��ж����ֽڿռ�
	wndClassEx.cbWndExtra = NULL; // ����ʵ�� �Ƿ��ж����ֽڿռ�
	
	wndClassEx.hInstance = hInstance; // ������������Ӧ�ó���ʵ�����

	wndClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION); // �������ͼ��, IDI-IDIconĬ��ͼ��
	wndClassEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION); // �������Сͼ��

	wndClassEx.hCursor = LoadCursor(NULL, IDC_ARROW); // ������Ĺ��, IDC-IDCursorĬ�Ϲ��

	wndClassEx.hbrBackground = NULL; // ������ı���ɫ
	wndClassEx.lpszMenuName = NULL; // ������Ĳ˵�����
	wndClassEx.lpszClassName = gWindowClassName; // �����������

	wndClassEx.lpfnWndProc = WindowProc; // ������Ļص�����ָ��. lp-long pointer | fn-function | WndProc-window procedure

	if (!RegisterClassExW(&wndClassEx)) {
		MessageBox(NULL, L"Register Class Faild", L"Error", MB_OK | MB_ICONERROR);
		return -1;
	}
#pragma endregion

#pragma region 2. Create
	//�ӿڴ�С����800 ��600
	int viewportWidth = 800;
	int viewportHeight = 600;

	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = viewportHeight;
	rect.bottom = viewportWidth;
	
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE); // �������ڴ�С����Ӧ�ӿڣ�һ�ַ��
	
	//����ԭ������Ļ���Ͻ�
	int windowWidth = rect.right - rect.left; // ���������Ĵ��ڿ��
	int windowHeight = rect.bottom - rect.top; // ���������Ĵ��ڸ߶�

	HWND hwnd = CreateWindowEx(
		NULL,
		gWindowClassName,
		L"My Render Window",
		WS_OVERLAPPEDWINDOW, // ���ڷ��
		CW_USEDEFAULT, // x����
		CW_USEDEFAULT, // y����
		windowWidth, // ���ڿ��
		windowHeight, // ���ڸ߶�
		NULL, // �����ھ��
		NULL, // �˵����
		hInstance, // Ӧ�ó���ʵ�����
		NULL // ���Ӳ������ᴫ�ݸ����ڴ���ص�����
		);
	if (hwnd == nullptr) {
		MessageBox(NULL, L"Creat Window Faild", L"Error", MB_OK | MB_ICONERROR);
		return -1;
	}
#pragma endregion

	return 0;
}