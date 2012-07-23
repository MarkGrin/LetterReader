# include <stdio.h>
# include <conio.h>
# include <windows.h>

# include "Constants.h"

# include "Window.h"
# include "Image.h"

HWND allWindowBoringStuff ();
void getFileName (char* whereToWrite);
int main (int amount, char** lines)
{
	printf ("lines:%d\n\n", amount);
	
	for (int index = 0; index < amount; index++)
	    printf ("line[%3d]:%s\n", index, lines[index]);
	
    printf ("\n");
	
	HWND hWindow = allWindowBoringStuff ();
	
	if ( !hWindow )
	{
		printf ("\nError with creating Window");
		getch ();
		return 1;
	}
	printf ("\nWindow openning success\n");
	
	if ( amount != 2 )
	{
		printf ("\nWrong arguments\n");
		getch ();
		return 1;
	}
	HDC image = newImage (lines[1]);
	if ( !image )
	{
		printf ("Image was not loaded\n");
		getch ();
		return 1;
	}
	BitBlt (GetDC (hWindow), 0, 0, Screen::Size::X, Screen::Size::Y, image, 0, 0, SRCCOPY);
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

void getFileName (char* whereToWrite)
{
	
}