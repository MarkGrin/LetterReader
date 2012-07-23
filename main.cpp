# include <stdio.h>
# include <conio.h>
# include <windows.h>
# include "Window.h"

int main (int amount, char** lines)
{
	printf ("lines:%d\n\n", amount);
	
	for (int index = 0; index < amount; index++)
	    printf ("line[%3d]:%s\n", index, lines[index]);
	
    printf ("\n");
	
	WNDCLASSEX windowClass;
	
	bool classRegisterResult = registerClassBoringStuff (&windowClass);
	
	printf ("\nClass:%d\n", classRegisterResult);
	
	
	printf ("\nPress any bla bla bla...\n");
	getch ();
	return 0;
}