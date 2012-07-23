# include <stdio.h>
# include <conio.h>
# include <windows.h>

int main (int amount, char** lines)
{
	printf ("lines:%d\n\n", amount);
	
	for (int index = 0; index < amount; index++)
	    printf ("line[%3d]:%s\n", index, lines[index]);
		
	getch ();
	return 0;
}