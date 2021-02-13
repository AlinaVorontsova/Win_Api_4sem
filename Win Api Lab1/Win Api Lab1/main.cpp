#include <Windows.h>
#include <tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");

int WINAPI _tWinMain(HINSTANCE This,		 // ���������� �������� ���������� 
    HINSTANCE Prev, 	// � ����������� �������� ������ 0 
    LPTSTR cmd, 		// ��������� ������ 
    int mode) 		// ����� ����������� ����
{
    HWND hWnd;		// ���������� �������� ���� ��������� 
    MSG msg; 		// ��������� ��� �������� ��������� 
    WNDCLASS wc; 	// ����� ����
    // ����������� ������ ���� 
    wc.hInstance = This;
    wc.lpszClassName = WinName; 				// ��� ������ ���� 
    wc.lpfnWndProc = WndProc; 					// ������� ���� 
    wc.style = CS_HREDRAW | CS_VREDRAW; 			// ����� ���� 
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// ����������� ������ 
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// ����������� ������ 
    wc.lpszMenuName = NULL; 					// ��� ���� 
    wc.cbClsExtra = 0; 						// ��� �������������� ������ ������ 
    wc.cbWndExtra = 0; 						// ��� �������������� ������ ���� 
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); 	// ���������� ���� ����� ������ 


    // ����������� ������ ����
    if (!RegisterClass(&wc)) return 0;
    // �������� ���� 
    hWnd = CreateWindow(WinName,			// ��� ������ ���� 
        _T("�������������� �����"), 		// ��������� ���� 
        WS_OVERLAPPEDWINDOW, 		// ����� ���� 
        CW_USEDEFAULT,				// x 
        CW_USEDEFAULT, 				// y	 ������� ���� 
        1000,				// width 
        300,			// Height 
        HWND_DESKTOP, 				// ���������� ������������� ���� 
        NULL, 						// ��� ���� 
        This, 						// ���������� ���������� 
        NULL); 					// �������������� ���������� ��� 

    ShowWindow(hWnd, mode); 				// �������� ����

    // ���� ��������� ��������� 
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg); 		// ������� ���������� ����� ������� ������� 
        DispatchMessage(&msg); 		// �������� ��������� ������� WndProc() 
    }
    return 0;
}

// ������� ������� ���������� ������������ ��������
// � �������� ��������� �� ������� ��� ������� ����������
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static short x = 500, y = 450;
    static short widthSCR, heightSCR;
    static short widthW, heightW;
    static int direct = rand() % 8 + 1; // 8 ����������� ��������
    switch (msg)
    {
    case WM_RBUTTONDOWN:
    {
        ExitWindows(EWX_SHUTDOWN, 0);
        break;
    }

    case WM_CREATE:
    {
        widthSCR = GetSystemMetrics(SM_CXSCREEN);
        heightSCR = GetSystemMetrics(SM_CYSCREEN);
        widthW = 1000;
        heightW = 300;
        return 0;
    }
    case WM_MOUSEMOVE:
    {

        switch (direct)
        {
        case 1:
        {
            if (((x + widthW + 5) <= widthSCR))
            {
                MoveWindow(hWnd, x + 5, y, widthW, heightW, TRUE);
                x += 5;
            }
            else
                direct = rand() % 8 + 1;

            break;
        }
        case 2:
        {
            if (((y + heightW + 5) <= heightSCR))
            {
                MoveWindow(hWnd, x, y + 5, widthW, heightW, TRUE);
                y += 5;
            }
            else
                direct = rand() % 8 + 1;

            break;
        }
        case 3:
        {
            if (((y + heightW + 5) <= heightSCR) && ((x + widthW + 5) <= widthSCR))
            {
                MoveWindow(hWnd, x + 5, y + 5, widthW, heightW, TRUE);
                y += 5;
                x += 5;
            }
            else
                direct = rand() % 8 + 1;

            break;
        }
        case 4:
        {
            if (((y + heightW + 5) <= heightSCR) && ((x - 5) >= 0))
            {
                MoveWindow(hWnd, x - 5, y + 5, widthW, heightW, TRUE);
                y += 5;
                x -= 5;
            }
            else
                direct = rand() % 8 + 1;

            break;
        }
        case 5:
        {
            if (((y - 5) >= 0) && ((x + widthW + 5) <= widthSCR))
            {
                MoveWindow(hWnd, x - 5, y + 5, widthW, heightW, TRUE);
                y -= 5;
                x += 5;
            }
            else
                direct = rand() % 8 + 1;

            break;
        }
        case 6:
        {
            if ((y - 5) >= 0)
            {
                MoveWindow(hWnd, x, y - 5, widthW, heightW, TRUE);
                y -= 5;
            }
            else
                direct = rand() % 8 + 1;

            break;
        }
        case 7:
        {
            if ((y - 5) >= 0 && (x - 5) >= 0)
            {
                MoveWindow(hWnd, x - 5, y - 5, widthW, heightW, TRUE);
                y -= 5;
                x -= 5;
            }
            else
                direct = rand() % 8 + 1;

            break;
        }
        case 8:
        {
            if ((x - 5) >= 0)
            {
                MoveWindow(hWnd, x - 5, y, widthW, heightW, TRUE);

                x -= 5;
            }
            else
                direct = rand() % 8 + 1;

            break;
        }
        }
        return 0;
    }
    case WM_DESTROY:
    {
        PostQuitMessage(0); return 0;
    }
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);

    }
    return 0;
}
