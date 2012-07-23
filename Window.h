

LRESULT CALLBACK
MainWndProc (HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
    switch (nMsg)
    {
    case WM_DESTROY:
        PostQuitMessage (0);
        return 0;
	break;
	}
return DefWindowProc (hwnd, nMsg, wParam, lParam);
}
/*

int STDCALL
WinMain (HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmd, int nShow)
{
char*szMainWndClass = "WinTestWin";

memset (&wndclass, 0, sizeof(WNDCLASSEX));

wndclass.lpszClassName = szMainWndClass;

wndclass.cbSize = sizeof(WNDCLASSEX);

wndclass.style = CS_HREDRAW | CS_VREDRAW;

wndclass.lpfnWndProc = MainWndProc;

wndclass.hInstance = hInst;

wndclass.hIcon = LoadIcon (NULL, IDI_APPLICATION);
wndclass.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
wndclass.hCursor = LoadCursor (NULL, IDC_ARROW);

wndclass.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
sterClassEx (&wndclass);

hwndMain = CreateWindow (
szMainWndClass,
"Hello",
WS_OVERLAPPEDWINDOW,
CW_USEDEFAULT,
CW_USEDEFAULT,
CW_USEDEFAULT,
CW_USEDEFAULT,
NULL,
NULL,
hInst,
NULL
);

ShowWindow (hwndMain, nShow);
UpdateWindow (hwndMain);


while (GetMessage (&msg, NULL, 0, 0))
{
TranslateMessage (&msg);
DispatchMessage (&msg);
}
return msg.wParam;
}
*/






bool registerClassBoringStuff (WNDCLASSEXA* wndclass)
{
    char szMainWndClass[] = "_____LETTER_READER______";
    memset (wndclass, 0, sizeof(WNDCLASSEX));

    wndclass->lpszClassName = szMainWndClass;

    wndclass->cbSize = sizeof(WNDCLASSEX);

    wndclass->style = CS_HREDRAW | CS_VREDRAW;

    wndclass->lpfnWndProc = MainWndProc;
    wndclass->hInstance = (HINSTANCE) 5;
    wndclass->hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wndclass->hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wndclass->hCursor = LoadCursor (NULL, IDC_ARROW);
    wndclass->hbrBackground = (HBRUSH) NULL;
    return RegisterClassExA (wndclass);
}

HWND openWindow ()
{
	HWND result = CreateWindowA ("_____LETTER_READER______", "Letter Reader DEBUG     ", 
								 WS_OVERLAPPEDWINDOW       , 0                         ,
					             0                         , 300                       ,
                                 300                       , NULL                      ,
						         NULL                      , (HINSTANCE)5              ,
                                 NULL);
	if ( !result )
	    return NULL;
	ShowWindow (result, SW_SHOW);
	return result;
}