LRESULT CALLBACK MainWndProc (HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
bool registerClassBoringStuff (WNDCLASSEXA* wndclass);
HWND openWindow ();


LRESULT CALLBACK MainWndProc (HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
    switch (nMsg)
    {
    case WM_DESTROY:
        PostQuitMessage (0);
        return 0;
	case WM_PAINT:
	    //ha ha
	break;
	break;
	}
return DefWindowProc (hwnd, nMsg, wParam, lParam);
}

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
					             0                         , Screen::Size::X           ,
                                 Screen::Size::Y           , NULL                      ,
						         NULL                      , (HINSTANCE)5              ,
                                 NULL);
	if ( !result )
	    return NULL;
	ShowWindow (result, SW_SHOW);
	return result;
}