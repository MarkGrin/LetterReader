# include <stdio.h>
# include <conio.h>
# include <windows.h>

# include "Constants.h"

# include "Window.h"

HWND allWindowBoringStuff ();

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