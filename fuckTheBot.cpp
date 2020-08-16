// fuckBot.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "fuckTheBot.h"
#include<string>
#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
const int WGrid = 30;
const int NGrid = 16;
MAP TMAP;
int M[5][2] = { {0,0},{0,-1},{0,1},{-1,0},{1,0} };
Bot rygb[5]{
    Bot(0,0,0),Bot(3,8,1),Bot(4,14,2),Bot(9,3,3),Bot(3,3,4)
};
HPEN BorderPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
HPEN StopPen = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
HPEN wPen= CreatePen(PS_SOLID, 25, RGB(255,255,255));
HPEN rPen = CreatePen(PS_SOLID, 25, RGB(255 ,48 ,48));
HPEN yPen = CreatePen(PS_SOLID, 25, RGB(238 ,238 ,0));
HPEN gPen = CreatePen(PS_SOLID, 25, RGB(0 ,255 ,127));
HPEN bPen = CreatePen(PS_SOLID, 25, RGB(0,245,255));
HPEN Pens[5]{ wPen,rPen,yPen,gPen,bPen };
HPEN wPen1 = CreatePen(PS_SOLID, 5, RGB(255, 255, 255));
HPEN rPen1 = CreatePen(PS_SOLID, 5, RGB(255, 48, 48));
HPEN yPen1 = CreatePen(PS_SOLID, 5, RGB(238, 238, 0));
HPEN gPen1 = CreatePen(PS_SOLID, 5, RGB(0, 255, 127));
HPEN bPen1 = CreatePen(PS_SOLID, 5, RGB(0, 245, 255));
HPEN Pens1[5]{ wPen1,rPen1,yPen1,gPen1,bPen1 };
int NOWPLAYER = 0;//NOWPLAYER^1;
int NOWCOLOR = 0;
int sp[3] = { 0,0,0 };
int NOWSTEP = 0;
TCHAR b5[20] = TEXT(" "); TCHAR a1[20] = TEXT("祝黄志豪前程似锦"); TCHAR a2[20] = TEXT("嘿嘿");
TCHAR b7[5][20] = { TEXT(" "),  TEXT("NOW : red") , TEXT("NOW : yellow")  ,TEXT("NOW : green ")  ,TEXT("NOW : blue") };
TCHAR d1[20] = TEXT("选择p1"); TCHAR d2[20] = TEXT("选择p2");
TCHAR e[3][20] = { TEXT(" "),TEXT("NOW :1P"),TEXT("NOW :2P") };
// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
void INITPAINT(HWND hWnd);
HWND bhwnd;
HWND thwnd;
Pos tranPosToPos(int x, int y);
Pos TranPosToPos(Pos a);
void MOVE(Pos S, Pos T, HWND hWnd, int color,HDC hdc);
Pos getTarPos(int dir);
//
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。
    /*int x;
    x = MessageBox(GetForegroundWindow(),a1,a2, 1);
    printf("%d\n", x);*/
    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_FUCKTHEBOT, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }
    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_FUCKTHEBOT));

    MSG msg;

    // 主消息循环:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);
    //wcex.cbSize = 190;


    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_FUCKTHEBOT));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_FUCKTHEBOT);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // 将实例句柄存储在全局变量中

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    TCHAR a[20] = TEXT("Button");
    TCHAR b1[20] = TEXT("选取红色");//1231
    TCHAR b2[20] = TEXT("选取黄色");//1232
    TCHAR b3[20] = TEXT("选取绿色");//1233
    TCHAR b4[20] = TEXT("选取蓝色");//1234
    TCHAR c1[20] = TEXT("up"); TCHAR c2[20] = TEXT("down");
    TCHAR c4[20] = TEXT("right"); TCHAR c3[20] = TEXT("left");

    bhwnd = CreateWindow(a, b1, WS_CHILDWINDOW, 17*WGrid, 30, 100, 50, hWnd,(HMENU)1231, hInstance, NULL);
    ShowWindow(bhwnd, SW_SHOWNORMAL);
    bhwnd = CreateWindow(a, b2, WS_CHILDWINDOW, 17 * WGrid, 90, 100, 50, hWnd, (HMENU)1232, hInstance, NULL);
    ShowWindow(bhwnd, SW_SHOWNORMAL); 
    bhwnd = CreateWindow(a, b3, WS_CHILDWINDOW, 17 * WGrid, 150, 100, 50, hWnd, (HMENU)1233, hInstance, NULL);
    ShowWindow(bhwnd, SW_SHOWNORMAL);
    bhwnd = CreateWindow(a, b4, WS_CHILDWINDOW, 17 * WGrid, 210, 100, 50, hWnd, (HMENU)1234, hInstance, NULL);
    ShowWindow(bhwnd, SW_SHOWNORMAL);
    bhwnd = CreateWindow(a, b5, WS_CHILDWINDOW, 17 * WGrid+120, 30, 100, 50, hWnd, (HMENU)1000, hInstance, NULL);
    ShowWindow(bhwnd, SW_SHOWNORMAL);
    bhwnd = CreateWindow(a, b7[0], WS_CHILDWINDOW, 17 * WGrid + 120, 90, 100, 50, hWnd, (HMENU)1001, hInstance, NULL);
    ShowWindow(bhwnd, SW_SHOWNORMAL);
    bhwnd = CreateWindow(a, c1, WS_CHILDWINDOW, 17 * WGrid + 240, 30, 100, 50, hWnd, (HMENU)101, hInstance, NULL);
    ShowWindow(bhwnd, SW_SHOWNORMAL);
    bhwnd = CreateWindow(a, c2, WS_CHILDWINDOW, 17 * WGrid + 240, 90, 100, 50, hWnd, (HMENU)102, hInstance, NULL);
    ShowWindow(bhwnd, SW_SHOWNORMAL);
    bhwnd = CreateWindow(a, c3, WS_CHILDWINDOW, 17 * WGrid + 240, 150, 100, 50, hWnd, (HMENU)103, hInstance, NULL);
    ShowWindow(bhwnd, SW_SHOWNORMAL);
    bhwnd = CreateWindow(a, c4, WS_CHILDWINDOW, 17 * WGrid + 240, 210, 100, 50, hWnd, (HMENU)1042, hInstance, NULL);
    ShowWindow(bhwnd, SW_SHOWNORMAL);
    bhwnd = CreateWindow(a,d1, WS_CHILDWINDOW, 17 * WGrid , 270, 100, 50, hWnd, (HMENU)1235, hInstance, NULL);
    ShowWindow(bhwnd, SW_SHOWNORMAL); 
    bhwnd = CreateWindow(a, d2, WS_CHILDWINDOW, 17 * WGrid, 330, 100, 50, hWnd, (HMENU)1236, hInstance, NULL);
    ShowWindow(bhwnd, SW_SHOWNORMAL);
    bhwnd = CreateWindow(a,b5, WS_CHILDWINDOW, 17 * WGrid+120, 330, 300, 50, hWnd, (HMENU)12345, hInstance, NULL);
    ShowWindow(bhwnd, SW_SHOWNORMAL);
    bhwnd = CreateWindow(a, b5, WS_CHILDWINDOW, 17 * WGrid + 120, 270, 150, 50, hWnd, (HMENU)12346, hInstance, NULL);
    ShowWindow(bhwnd, SW_SHOWNORMAL);
    bhwnd = CreateWindow(a, b5, WS_CHILDWINDOW, 17 * WGrid + 280, 270, 150, 50, hWnd, (HMENU)12347, hInstance, NULL);
    ShowWindow(bhwnd, SW_SHOWNORMAL);
    return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // 分析菜单选择:
        switch (wmId)
        {
        case IDM_ABOUT: //娘的,你也是104??
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case 1231:
            {
                SetDlgItemText(hWnd,1001, b7[1]);
                NOWCOLOR = 1;
            }
            break;
        case 1232:
            {
                SetDlgItemText(hWnd, 1001, b7[2]);
                NOWCOLOR = 2;

            }
            break;
        case 1233:
            {
                SetDlgItemText(hWnd, 1001, b7[3]);  
                NOWCOLOR = 3;

            }
            break;
        case 1234:
            {   
                NOWCOLOR = 4;
                SetDlgItemText(hWnd, 1001, b7[4]);
            }
            break;//TODO 处理上下左右1234
        case 1235: {
            NOWPLAYER = 1;
            SetDlgItemText(hWnd, 1000, e[1]);
        }break;
        case 1236: {
            NOWPLAYER = 2;
            SetDlgItemText(hWnd, 1000, e[2]);
        }break;
        case 101: {
            NOWSTEP++;

            Pos nowPos = rygb[NOWCOLOR].getPos();
            Pos tarPos = getTarPos(1); HDC hdc = GetDC(hWnd);
            MOVE(nowPos, tarPos, hWnd, NOWCOLOR, hdc);
            ReleaseDC(hWnd, hdc);
            rygb[NOWCOLOR] = Bot(tarPos.x, tarPos.y, NOWCOLOR);
            if ((TMAP.Point[NOWCOLOR*2-2][0] == tarPos.x && TMAP.Point[NOWCOLOR * 2-2][1] == tarPos.y) ||
                (TMAP.Point[NOWCOLOR * 2-1][0] == tarPos.x && TMAP.Point[NOWCOLOR * 2-1][1] == tarPos.y)) {
                NOWSTEP = 0;
                sp[NOWPLAYER] += 1;
            }
        }break;
        case 102: {//down
            NOWSTEP++;
            Pos nowPos = rygb[NOWCOLOR].getPos();
            Pos tarPos = getTarPos(2); HDC hdc = GetDC(hWnd);
            MOVE(nowPos, tarPos, hWnd, NOWCOLOR, hdc);
            ReleaseDC(hWnd, hdc);
            rygb[NOWCOLOR] = Bot(tarPos.x, tarPos.y, NOWCOLOR);
            if ((TMAP.Point[NOWCOLOR * 2 - 2][0] == tarPos.x && TMAP.Point[NOWCOLOR * 2 - 2][1] == tarPos.y) ||
                (TMAP.Point[NOWCOLOR * 2 - 1][0] == tarPos.x && TMAP.Point[NOWCOLOR * 2 - 1][1] == tarPos.y)) {
                NOWSTEP = 0;
                sp[NOWPLAYER] += 1;
            }
        }break;
        case 103: {
            NOWSTEP++;

            Pos nowPos = rygb[NOWCOLOR].getPos();
            Pos tarPos = getTarPos(3); HDC hdc = GetDC(hWnd);
            MOVE(nowPos, tarPos, hWnd, NOWCOLOR, hdc);
            ReleaseDC(hWnd, hdc);
            rygb[NOWCOLOR] = Bot(tarPos.x, tarPos.y, NOWCOLOR);
            if ((TMAP.Point[NOWCOLOR * 2 - 2][0] == tarPos.x && TMAP.Point[NOWCOLOR * 2 - 2][1] == tarPos.y) ||
                (TMAP.Point[NOWCOLOR * 2 - 1][0] == tarPos.x && TMAP.Point[NOWCOLOR * 2 - 1][1] == tarPos.y)) {
                NOWSTEP = 0;
                sp[NOWPLAYER] += 1;
            }
        }break;
        case 1042: {
            NOWSTEP++;

            Pos nowPos = rygb[NOWCOLOR].getPos();
            Pos tarPos = getTarPos(4); HDC hdc = GetDC(hWnd);
            MOVE(nowPos, tarPos, hWnd, NOWCOLOR, hdc);
            ReleaseDC(hWnd, hdc);
            rygb[NOWCOLOR] = Bot(tarPos.x, tarPos.y, NOWCOLOR);
            if ((TMAP.Point[NOWCOLOR * 2 - 2][0] == tarPos.x && TMAP.Point[NOWCOLOR * 2 - 2][1] == tarPos.y) ||
                (TMAP.Point[NOWCOLOR * 2 - 1][0] == tarPos.x && TMAP.Point[NOWCOLOR * 2 - 1][1] == tarPos.y)) {
                NOWSTEP = 0;
                sp[NOWPLAYER] += 1;
            }
        }break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }


    }{
    HDC ndc = GetDC(hWnd);
    WCHAR sts[20]; memset(sts, 0, sizeof(sts));
    WCHAR sts1[20]; memset(sts, 0, sizeof(sts1));
    WCHAR sts2[20]; memset(sts, 0, sizeof(sts2));

    std::string str="本次尝试步数:"+std::to_string(NOWSTEP);
    std::string str1 = "1p分数" + std::to_string(sp[1]);
    std::string str2 = "2p分数" + std::to_string(sp[2]);

    MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.size() + 1, sts,
        sizeof(sts) / sizeof(sts[0]));
    MultiByteToWideChar(CP_ACP, 0, str1.c_str(), str1.size() + 1, sts1,
        sizeof(sts1) / sizeof(sts1[0]));
    MultiByteToWideChar(CP_ACP, 0, str2.c_str(), str2.size() + 1, sts2,
        sizeof(sts2) / sizeof(sts2[0]));
    SetDlgItemText(hWnd, 12345, sts);
    SetDlgItemText(hWnd, 12346, sts1);
    SetDlgItemText(hWnd, 12347, sts2);
    }
    break;
    
    case WM_PAINT:
        INITPAINT(hWnd);
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
    break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

void INITPAINT(HWND hWnd){
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    HPEN BorderPen = CreatePen(PS_SOLID,1,RGB(0,0,0));
    HPEN StopPen = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
    
    SelectObject(hdc, BorderPen);
    MoveToEx(hdc, 0, 0, NULL);
    for (int i = 0; i <= 16; ++i) {
        MoveToEx(hdc, 0, WGrid * i, NULL);
        LineTo(hdc, NGrid * WGrid, WGrid * i);
    }
    for (int i = 0; i <= 16; ++i) {
        MoveToEx(hdc, WGrid * i, 0, NULL);
        LineTo(hdc, WGrid * i, WGrid * NGrid);
    }
    ////现在绘制 挡板
    SelectObject(hdc, StopPen);
    for (int i = 1; i <= TMAP.NLines; ++i) {
        long long now = TMAP.GetLine(i);
        if (i % 2 == 1) {//此时为墙
            for (int j = 1; j <= 32; j+=2) {
                if (!((now >> j) & 1)) {
                    MoveToEx(hdc, (j / 2) * WGrid, (i / 2) * WGrid,NULL);
                    LineTo(hdc, (j / 2 + 1) * WGrid, (i / 2) * WGrid);
                }
            }
        }
        else {//此时为边
            for (int j = 0; j <= 32; j+=2) {
                if (!((now >> j) & 1)) {
                    MoveToEx(hdc, (j / 2) * WGrid, (i / 2-1) * WGrid, NULL);
                    LineTo(hdc, (j / 2) * WGrid, (i / 2) * WGrid);
                }
            }
        }
    }
    //EndPaint(hWnd, &ps);
    //绘制棋子
    for (int i = 1; i <= 4; ++i) {
        Pos tmp = rygb[i].getPos();
        int tmpp = rygb[i].getColor();
        MOVE(tmp, tmp, hWnd, tmpp,hdc);
    }
    //现在绘制得分点
    for (int i = 0; i <= 7; ++i) {
        int cl = i / 2 + 1; Pos tmp(TMAP.Point[i][0], TMAP.Point[i][1]);
        Pos t = TranPosToPos(tmp);
        SelectObject(hdc, Pens1[cl]);
        MoveToEx(hdc, t.x+11, t.y-11, NULL);
        LineTo(hdc, t.x+11, t.y-11);
        MoveToEx(hdc, t.x -11, t.y - 11, NULL);
        LineTo(hdc, t.x -11, t.y - 11);
        MoveToEx(hdc, t.x + 11, t.y + 11, NULL);
        LineTo(hdc, t.x + 11, t.y + 11);
        MoveToEx(hdc, t.x -11, t.y +11, NULL);
        LineTo(hdc, t.x - 11, t.y +11);
    }
    EndPaint(hWnd, &ps);
}
Pos tranPosToPos(int x, int y)
{
    return Pos(x * WGrid - WGrid / 2, y * WGrid - WGrid / 2 );
}
Pos TranPosToPos(Pos a)
{
    return Pos(a.x * WGrid - WGrid / 2, a.y * WGrid - WGrid / 2);
}
void MOVE(Pos S, Pos T,HWND hWnd,int color,HDC hdc)
{
    Pos s = TranPosToPos(S);
    Pos t = TranPosToPos(T);
    MoveToEx(hdc, 1000, 1000, NULL);
    SelectObject(hdc, Pens[0]);
    MoveToEx(hdc, s.x, s.y, NULL);
    LineTo(hdc, s.x, s.y);
    SelectObject(hdc, Pens[color]);
    MoveToEx(hdc, t.x, t.y, NULL);
    LineTo(hdc, t.x, t.y);
}
Pos getTarPos(int dir)
{
    Pos now = rygb[NOWCOLOR].getPos();
    Pos ans(-1, -1);
    switch(dir){
    case 1: {//up
        ans.x = now.x;
        for (int i = now.y; i >=1; --i) {
            ans.y = i;
            if (((TMAP.GetLine(i * 2 -1) >> (ans.x * 2 - 1)) & 1) == 0)
                break;
        }
        for (int i = 1; i <= 4; ++i) {
            Pos gan = rygb[i].getPos();
            if (gan.x == now.x && gan.y < now.y&& gan.y >=ans.y) {
                ans.y = gan.y +1;
            }
        }
    }break;
    case 2: {
        ans.x = now.x;

        for (int i = now.y; i <=16 ; ++i) {
            ans.y = i;
            if (((TMAP.GetLine(i * 2 + 1) >> (ans.x * 2 - 1))&1) == 0)
                break;
        }
        for (int i = 1; i <= 4; ++i) {
            Pos gan = rygb[i].getPos();
            if (gan.x == now.x && gan.y>now.y && gan.y<=ans.y) {
                ans.y = gan.y - 1;
            }
        }
    }break;
    case 3: {
        long long line = TMAP.GetLine(now.y * 2);
        ans.y = now.y;
        for (int i = now.x ; i >= 1; --i) {
            ans.x = i;
            if (((line >> (i * 2 - 2)) & 1 )== 0) {
                break;
            }
        }
        for (int i = 1; i <= 4; ++i) {
            Pos gan = rygb[i].getPos();
            if (gan.y == now.y && gan.x<now.x && gan.x>=ans.x) {
                ans.x = gan.x + 1;
            }
        }
    }break;
    case 4: {
        long long line = TMAP.GetLine(now.y * 2);
        ans.y = now.y;
        for (int i = now.x ; i <=16; ++i) {
            ans.x = i;
            if (((line >> (i * 2)) & 1) == 0) {
                break;
            }
        }
        for (int i = 1; i <= 4; ++i) {
            Pos gan = rygb[i].getPos();
            if (gan.y == now.y && gan.x>now.x && gan.x<=ans.x) {
                ans.x = gan.x -1;
            }
        }
    }
    break;
    }

    return ans;
}