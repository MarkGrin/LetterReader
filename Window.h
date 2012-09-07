typedef void ThreadFunc (HWND hWnd, HDC image);

struct ThreadArguments
{
	bool* endSwitchPtr;
	HWND  hWnd;
    HDC   image;
    ThreadFunc* threadFuncPtr;
};

LRESULT CALLBACK MainWndProc  (HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam);

void Message             (HWND hWnd);
HWND openWindow          ();
bool registerWindowClass ();
bool startThread         (ThreadFunc* funcToStartInThread, HDC hdc, HWND hWnd);
HWND createWindow        ();
void windowThread        (void* args);



void windowThread (void* args)
{
    _logger_.EnterNote ("Thread started",
                        Logger_Mode_Time, 0);

    ThreadArguments* threadArgs = (ThreadArguments*)args;

    bool* endSwitchPtr = threadArgs->endSwitchPtr;
    HWND  hWnd         = threadArgs->hWnd;    
    HDC   image        = threadArgs->image;

    threadArgs->threadFuncPtr (hWnd, image);

    *endSwitchPtr = true;

    _logger_.EnterNote ("Thread ended",
                        Logger_Mode_Time, 0);
    return;
}

HWND createWindow ()
{
    if ( !registerWindowClass () )
    {
        _logger_.EnterError ("Window Class Register Failure",
                             Logger_Mode_Time, 0);
        return NULL;
    }
    HWND hWnd = openWindow ();
    if ( !hWnd )
    {
        _logger_.EnterError ("Window Open Failure",
                             Logger_Mode_Time, 0);
        return NULL;
    }
    return hWnd;
}

bool startThread (ThreadFunc* funcToStartInThread, HDC hdc, HWND hWnd)
{
    bool endSwitch = false;
    ThreadArguments arguments = {&endSwitch, hWnd, hdc, funcToStartInThread};

    uintptr_t thread = 0;
    thread = _beginthread (windowThread, sizeof (ThreadArguments*), (void*)&arguments);
    
    Sleep (100);

    if ( !thread )
    {
        _logger_.EnterError ("Thread start Failure",
                             Logger_Mode_Time, 0);
        return false;
    }
    
    while ( !endSwitch )
    {
        Message (hWnd);
        Sleep (250);
    }    
    return true;
}

LRESULT CALLBACK MainWndProc (HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam)
{
    if ( nMsg == WM_DESTROY )
    {
        PostQuitMessage (0);
        return 0;
    }
    return DefWindowProc (hwnd, nMsg, wParam, lParam);
}

bool registerWindowClass ()
{
    WNDCLASSEXA wndclass = {0};
    char szMainWndClass[] = "_____LETTER_READER______";

    memset (&wndclass, 0, sizeof(WNDCLASSEX));

    wndclass.lpszClassName = szMainWndClass;
    wndclass.cbSize = sizeof(WNDCLASSEX);
    wndclass.style = CS_HREDRAW | CS_VREDRAW;

    wndclass.lpfnWndProc   = MainWndProc;
    wndclass.hInstance     = (HINSTANCE) 5;
    wndclass.hIcon         = LoadIcon   (NULL, IDI_APPLICATION);
    wndclass.hIconSm       = LoadIcon   (NULL, IDI_APPLICATION);
    wndclass.hCursor       = LoadCursor (NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)    NULL;

    return RegisterClassExA (&wndclass);
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
void Message (HWND hWnd)
{
	MSG messages;
	GetMessage (&messages, NULL, 0, 0);
	TranslateMessage(&messages);
    DispatchMessage(&messages); 
}
