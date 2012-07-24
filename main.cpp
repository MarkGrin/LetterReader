# include <stdio.h>
# include <conio.h>
# include <windows.h>
# include <process.h>

# include "Constants.h"

# include "Window.h"
# include "Image.h"
# include "Graph.h"

struct ThreadArguments
{
	bool* ptr;
	HDC hdc;
	HWND hWnd;
};

HWND allWindowBoringStuff ();
void getFileName   (char* whereToWrite);
HWND prepareWindow (int amount);

void graphThread (void* endSwitchPtr);

int main (int amount, char** lines)
{
	printf ("lines:%d\n\n", amount);
	
	for (int index = 0; index < amount; index++)
	    printf ("line[%3d]:%s\n", index, lines[index]);
		
	HWND hWindow = prepareWindow (amount);
	if ( !hWindow )
		return 1;
	
    printf ("\n");
	
	HDC image = newImage (lines[1]);
	if ( !image )
	{
		printf ("Image was not loaded\n");
		getch ();
		return 1;
	}
	bool endSwitch = false;
	ThreadArguments arguments {&endSwitch, image, hWindow};
	
	long unsigned int thread_handle = _beginthread (graphThread, sizeof (ThreadArguments*), &arguments);
	
	if ( !thread_handle )
	{
		printf ("\nThead didn't started:ERROR\n");
		getch ();
		return 1;
	}
	
	while ( !GetAsyncKeyState (VK_ESCAPE) && !endSwitch)
	{
		Message ();
	}
	printf ("\n\nPress any bla bla bla...\n");
	getch ();
	return 0;
}
HWND allWindowBoringStuff ()
{
	WNDCLASSEX windowClass;
	
	if ( !registerClassBoringStuff (&windowClass) )
	{
		printf ("\nError Window class register");
		return NULL;
	}
	printf ("Class register success\n");
	
	return openWindow ();
}

HWND prepareWindow (int amount)
{
	HWND hWindow = allWindowBoringStuff ();
	
	if ( !hWindow )
	{
		printf ("\nError with creating Window");
		getch ();
		return NULL;
	}
	printf ("\nWindow openning success\n");
	
	if ( amount != 2 )
	{
		printf ("\nWrong arguments\n");
		getch ();
		return NULL;
	}
	return hWindow;
}

void graphThread (void* ptr)
{
	bool* endSwitchPtr = ((ThreadArguments*)ptr)->ptr ;
	HDC image          = ((ThreadArguments*)ptr)->hdc ;
	HWND hWindow       = ((ThreadArguments*)ptr)->hWnd;
	HDC drawDC = GetDC (hWindow);
	BitBlt (drawDC, 0, 0, Screen::Size::X, Screen::Size::Y, image, 0, 0, SRCCOPY);
	ReleaseDC (hWindow, drawDC);
	smoothScreen (1.2, 5, image);
	drawDC = GetDC (hWindow);
	BitBlt (drawDC, 0, 0, Screen::Size::X, Screen::Size::Y, image, 0, 0, SRCCOPY);
	ReleaseDC (hWindow, drawDC);
	
	*endSwitchPtr = true;
}