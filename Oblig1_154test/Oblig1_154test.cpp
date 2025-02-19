// Oblig1_154test.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include <windows.h>
#include "Oblig1_154test.h"
#include "bil.h"
#include "vector"
#include <queue>


#define MAX_LOADSTRING 100

enum bytteLys { RED, REDYELLOW, GREEN, YELLOW };
bytteLys status = RED;


struct Car{
    int x = 0, y = 0;
    int hastighet;
    bool erHorisontal;
};
std::queue<Car> cars;

double pw = 0.80;
double pn = 0.60;


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    Probability(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.



    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_OBLIG1154TEST, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OBLIG1154TEST));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OBLIG1154TEST));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_OBLIG1154TEST);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int maksantall = 30;
    RECT horisontaltlysvindu = { 280, 310, 440, 380 };
    RECT vertikaltlysvindu = { 370, 80, 440, 240 };
    RECT horisontalvei = { 0, 250, 2000, 300 };
    RECT vertikalvei = { 450, 0, 500, 1000 };
    static int bilHorisontalX = 0; 
    static int bilVertikalY = 0;   
    const int bilHastighet = 10;   




    switch (message)
    {
    case WM_CREATE:
        SetTimer(hWnd, 1, 4000, NULL);
        SetTimer(hWnd, 5, 100, NULL); // Timer for bilene, 100ms
		SetTimer(hWnd, 6, 1000, NULL); // Timer for spawne biler, 1000ms





        break;


    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case IDM_PROBABILITY:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_PROBABILITY), hWnd, Probability);
				break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps); //handle device context, fungerer som peker
        // TODO: Add any drawing code that uses hdc here...

        HBRUSH hBrushGreyRamme = CreateSolidBrush(RGB(105, 105, 105));
        HGDIOBJ hOrgRektangel = SelectObject(hdc, hBrushGreyRamme);
        Rectangle(hdc, 280, 310, 440, 380); //horisontalt lys, 160 left/right, 70 top/bot

        Rectangle(hdc, 370, 80, 440, 240); //vertikalt lys, 160 top/bot, 70 left/right
        //Rectangle(hdc, 90, 90, 210, 430);
        DeleteObject(hBrushGreyRamme);




        HBRUSH hBrushVei = CreateSolidBrush(RGB(50, 50, 50));
        HGDIOBJ hOrgVei = SelectObject(hdc, hBrushVei);
        Rectangle(hdc, 450, 0, 500, 1000); //vertikal vei

        Rectangle(hdc, 0, 250, 2000, 300); //horisontal vei
        DeleteObject(hBrushVei);

        // Lage bevegende objekt:
        // Rectangle(hdc, pos.x - 25, pos.y - 25, pos.x + 25, pos.y + 25);


        HBRUSH hBrushGreyLys = NULL;
        HGDIOBJ hOrgGråLys = NULL;

        HBRUSH aktivbrush = NULL;
        HGDIOBJ hOrg = NULL;


        // ----------------------


        switch (status) {

        case RED:
            // VERTIKAL RED

            aktivbrush = CreateSolidBrush(RGB(255, 0, 0)); //Oppretter brush med rød farge
            hOrg = SelectObject(hdc, aktivbrush); //Legger den røde brushen inn i tegneflaten og returnerer brushen som 
            //var der originalt. Sånn at vi kan legge den tilbake før vi sletter 
            // den røde brushen
            // Rectangle(hdc, 370, 80, 440, 240);
            Ellipse(hdc, 385, 90, 425, 130); //rød vertikal

            hBrushGreyLys = CreateSolidBrush(RGB(169, 169, 169));
            hOrgGråLys = SelectObject(hdc, hBrushGreyLys);

            Ellipse(hdc, 385, 140, 425, 180); //gul vertikal
            Ellipse(hdc, 385, 190, 425, 230); // grønn vertikal


            //HORISONTAL GRØNN:
            aktivbrush = CreateSolidBrush(RGB(0, 255, 0));
            hOrg = SelectObject(hdc, aktivbrush);
            // Rectangle(hdc, 280, 310, 440, 380); horisontal lys
            Ellipse(hdc, 390, 325, 430, 365); // grønn horisontal

            hBrushGreyLys = CreateSolidBrush(RGB(169, 169, 169));
            hOrgGråLys = SelectObject(hdc, hBrushGreyLys);
            Ellipse(hdc, 290, 325, 330, 365); //rød horisontal
            Ellipse(hdc, 340, 325, 380, 365); //gul horisontal


            break;



        case REDYELLOW:
            //VERTIKAL REDYELLOW
            aktivbrush = CreateSolidBrush(RGB(255, 0, 0));
            hOrg = SelectObject(hdc, aktivbrush);
            Ellipse(hdc, 385, 90, 425, 130); //Koordinater for left, top, right, bottom - dette lager en vanlig sirkel, //rød vertikal

            aktivbrush = CreateSolidBrush(RGB(255, 255, 0));
            hOrg = SelectObject(hdc, aktivbrush);
            Ellipse(hdc, 385, 140, 425, 180); //gul vertikal

            hBrushGreyLys = CreateSolidBrush(RGB(169, 169, 169));
            hOrgGråLys = SelectObject(hdc, hBrushGreyLys);
            Ellipse(hdc, 385, 190, 425, 230); // grønn vertikal


            // HORISONTAL YELLOW

            aktivbrush = CreateSolidBrush(RGB(255, 255, 0));
            hOrg = SelectObject(hdc, aktivbrush);
            Ellipse(hdc, 340, 325, 380, 365); //gul horisontal

            hBrushGreyLys = CreateSolidBrush(RGB(169, 169, 169));
            hOrgGråLys = SelectObject(hdc, hBrushGreyLys);
            Ellipse(hdc, 290, 325, 330, 365); //rød horisontal
            Ellipse(hdc, 390, 325, 430, 365); // grønn horisontal

            break;


        case GREEN:
            // VERTIKAL GREEN
            aktivbrush = CreateSolidBrush(RGB(0, 255, 0));
            hOrg = SelectObject(hdc, aktivbrush);
            Ellipse(hdc, 385, 190, 425, 230); // grønn vertikal

            hBrushGreyLys = CreateSolidBrush(RGB(169, 169, 169));
            hOrgGråLys = SelectObject(hdc, hBrushGreyLys);
            Ellipse(hdc, 385, 90, 425, 130); //rød vertikal
            Ellipse(hdc, 385, 140, 425, 180); //gul vertikal


            // HORISONTAL RED:

            aktivbrush = CreateSolidBrush(RGB(255, 0, 0));
            hOrg = SelectObject(hdc, aktivbrush);

            Ellipse(hdc, 290, 325, 330, 365); //rød horisontal


            hBrushGreyLys = CreateSolidBrush(RGB(169, 169, 169));
            hOrgGråLys = SelectObject(hdc, hBrushGreyLys);

            Ellipse(hdc, 340, 325, 380, 365); //gul horisontal
            Ellipse(hdc, 390, 325, 430, 365); // grønn horisontal

            break;


        case YELLOW:
            // VERTIKAL YELLOW
            aktivbrush = CreateSolidBrush(RGB(255, 255, 0));
            hOrg = SelectObject(hdc, aktivbrush);
            Ellipse(hdc, 385, 140, 425, 180); //gul vertikal

            hBrushGreyLys = CreateSolidBrush(RGB(169, 169, 169));
            hOrgGråLys = SelectObject(hdc, hBrushGreyLys);
            Ellipse(hdc, 385, 90, 425, 130); //rød vertikal
            Ellipse(hdc, 385, 190, 425, 230); // grønn vertikal


            //HORISONTAL REDYELLOW:

            aktivbrush = CreateSolidBrush(RGB(255, 0, 0));
            hOrg = SelectObject(hdc, aktivbrush);
            Ellipse(hdc, 290, 325, 330, 365); //rød horisontal

            aktivbrush = CreateSolidBrush(RGB(255, 255, 0));
            hOrg = SelectObject(hdc, aktivbrush);
            Ellipse(hdc, 340, 325, 380, 365); //gul horisontal

            hBrushGreyLys = CreateSolidBrush(RGB(169, 169, 169));
            hOrgGråLys = SelectObject(hdc, hBrushGreyLys);
            Ellipse(hdc, 390, 325, 430, 365); // grønn horisontal


            break;
        }
        
        HBRUSH bilBrush = CreateSolidBrush(RGB(255, 0, 0));

                SelectObject(hdc, bilBrush);
				std::queue<Car> tempQueue = cars;
                while (!tempQueue.empty()) {
					Car car = tempQueue.front();
					tempQueue.pop();
                    if (car.erHorisontal) {
                        Rectangle(hdc, car.x, car.y, car.x + 30, car.y + 20);
                    }
                    else {
                        Rectangle(hdc, car.x + 20, car.y + 30, car.x, car.y);
                    }
                }


                DeleteObject(bilBrush);
               

             
            



            SelectObject(hdc, hOrg); //Må fjerne brushen fra tegneflaten før den slettes
            if (aktivbrush) DeleteObject(aktivbrush); //Må slette for å rydde minnet i C++
           
            
            DeleteObject(hBrushGreyLys);

            EndPaint(hWnd, &ps); //Avslutter tegning
        }
        break;

    case WM_TIMER:
    {
        
        switch (wParam) {
        case 1:
            status = REDYELLOW;
            KillTimer(hWnd, 1);
            SetTimer(hWnd, 2, 1000, NULL);
            break;
        case 2:
            status = GREEN;
            KillTimer(hWnd, 2);
            SetTimer(hWnd, 3, 5000, NULL);
            break;
        case 3:
            status = YELLOW;
            KillTimer(hWnd, 3);
            SetTimer(hWnd, 4, 1000, NULL);
            break;
        case 4:
            status = RED;
            KillTimer(hWnd, 4);
            SetTimer(hWnd, 1, 5000, NULL);
            break;
        case 5:
            if (wParam == 5) {
                std::queue<Car> tempQueue;
                while (!cars.empty()) {
                    Car car = cars.front();
                    cars.pop();
                    bool canMove = true;

                    // Sjekker om bilen kolliderer med en annen bil for reset
                    std::queue<Car> checkQueue = tempQueue;
                    while (!checkQueue.empty()) {
                        Car otherCar = checkQueue.front();
                        checkQueue.pop();
                        if (car.erHorisontal && otherCar.erHorisontal) {
                            if (car.x + 40 >= otherCar.x && car.x < otherCar.x + 40 && car.y == otherCar.y) {
                                canMove = false;
                                break;
                            }
                        }
                        else if (!car.erHorisontal && !otherCar.erHorisontal) {
                            if (car.y + 40 >= otherCar.y && car.y < otherCar.y + 40 && car.x == otherCar.x){
                                canMove = false;
                                break;
                            }
                        }
                        }
                    
                    if (canMove) {
                        if (car.erHorisontal) {
                            if (car.x + 40 < vertikalvei.left && (status == RED || car.x + 40 < vertikalvei.left - 10)) {
                                car.x += car.hastighet;
                            }
                            else if (car.x + 40 >= vertikalvei.left) {
                                car.x += car.hastighet;
                            }
                        }
                        else {
                            if (car.y + 40 < horisontalvei.top && (status == GREEN || car.y + 40 < horisontalvei.top - 10)) {
                                car.y += car.hastighet;
                            }
                            else if (car.y + 40 >= horisontalvei.top) {
                                car.y += car.hastighet;
                            }
                        }
                    }
                    if (car.x <= 1300 && car.y <= 1000) {
                        tempQueue.push(car);
                    }
                }
                cars = tempQueue;
            }


            InvalidateRect(hWnd, &horisontalvei, TRUE);
            InvalidateRect(hWnd, &vertikalvei, TRUE);


            break;

		case 6:
            if (cars.size() < maksantall) {
                if (rand() / (double)RAND_MAX < pw) { // gir tilfeldig verdi og sjekker om denne er innenfor pw
                    cars.push({ 0, 265, 10, true });
                }
                if (rand() / (double)RAND_MAX < pn) {
                    cars.push({ 465, 0, 10, false });
                }
				InvalidateRect(hWnd, NULL, TRUE);
            }

            break;
        }
       

        InvalidateRect(hWnd, &horisontaltlysvindu, TRUE); 
        InvalidateRect(hWnd, &vertikaltlysvindu, TRUE);



    }
    break;

    case WM_DESTROY:

        PostQuitMessage(0);
        break;

    case WM_KEYDOWN:
        switch (wParam) {
        case VK_UP:
            pn += 0.1;
            break;
        case VK_DOWN:
            pn -= 0.1;
            break;
        case VK_LEFT:
            pw -= 0.1;
            break;
        case VK_RIGHT:
            pw += 0.1;
            break;
        }

    break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
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

INT_PTR CALLBACK Probability(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
    {
		HWND pw1 = GetDlgItem(hDlg, IDC_pw1);
		HWND pn1 = GetDlgItem(hDlg, IDC_pn1);
		SetWindowText(pw1, L"0.1");
		SetWindowText(pn1, L"0.1");
        return (INT_PTR)TRUE;
    }
    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK) {
            wchar_t buffer[100];

            // Get text from the input box
            GetDlgItemText(hDlg, IDC_pw1, buffer, sizeof(buffer) / sizeof(buffer[0]));

            // Convert text to double
            double pw = wcstod(buffer, NULL);

            // Check if conversion was successful
            if (pw != 0 || buffer[0] == '0') {
                ::pw = pw; // Assign to the global variable
            }

            // Repeat for pn
            GetDlgItemText(hDlg, IDC_pn1, buffer, sizeof(buffer) / sizeof(buffer[0]));
            double pn = wcstod(buffer, NULL);
            if (pn != 0 || buffer[0] == '0') {
                ::pn = pn; // Assign to the global variable
            }

            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        else if (LOWORD(wParam) == IDCANCEL) {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        break;
    }
    return (INT_PTR)FALSE;
}
}
