# include <stdio.h>
# include <conio.h>
# include <windows.h>
# include <process.h>
# include <time.h>

# include "Constants.h"

# include "Logger.h"

Logger _logger_ ("Log.h", "Error.h");

# include "Window.h"
# include "Image.h"
# include "Graph.h"

void mainFunction (HWND hWnd, HDC image);

int main (int amount, char** lines)
{
    _logger_.EnterNote ("Programm started",
                        Logger_Mode_Time, 0);
		
	HDC image = newImage (lines[1]);
	if ( !image )
        return 1;
    HWND hwnd = createWindow ();
    if ( !hwnd )
        return 1;

    startThread (mainFunction, image, hwnd);

    DestroyWindow (hwnd);
    deleteImage (image);
    
    printf ("\nFINISHED\n");
    getch ();

    _logger_.EnterNote ("Programm ended",
                        Logger_Mode_Time, 0);

	return 0;
}

void mainFunction (HWND hWindow, HDC image)
{
    HDC drawDC = GetDC (hWindow);

    draw (drawDC, image);

	smoothScreen (0.3, 5, image);
    draw (drawDC, image);

	contrast (image, 5);
    draw (drawDC, image);

	lineThisHDC (image, drawDC);
    draw (drawDC, image);

    ReleaseDC (hWindow, drawDC);
}

