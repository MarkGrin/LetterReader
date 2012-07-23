# include <stdio.h>
# include <conio.h>
# include <windows.h>
# include "Constants.h"
# include "Window.h"

int main (int amount, char** lines)
{
	printf ("lines:%d\n\n", amount);
	
	for (int index = 0; index < amount; index++)
	    printf ("line[%3d]:%s\n", index, lines[index]);
	
    printf ("\n");
	
	WNDCLASSEX windowClass;
	
	if ( !registerClassBoringStuff (&windowClass) )
	{
		printf ("\nError Window class register");
		getch ();
		return 1;
	}
	printf ("Class register success\n");
	HWND hWindow = openWindow ();
	if ( !hWindow )
	{
		printf ("\nError with window openning");
		getch ();
		return 1;
	}
	printf ("Window opening success");
	printf ("\nPress any bla bla bla...\n");
	getch ();
	return 0;
}