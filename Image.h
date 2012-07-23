HDC newImage (char* fileName)
{
	HBITMAP handle = (HBITMAP) LoadImageA (NULL, fileName, NULL, NULL, NULL, LR_LOADFROMFILE);
	if ( !handle )
	{
		printf ("\nError with loading image:%d\n", GetLastError () );
		return NULL;
	}
	HDC result = CreateCompatibleDC (NULL);
	if ( !result )
	{
		printf ("\nError with creating hdc\n");
		return NULL;
	}
	SelectObject (result, (HGDIOBJ)handle);
	return result;
}
bool deleteImage (HDC hdcToDelete)
{
    DeleteObject ((void*)GetObject ((void*)hdcToDelete, 0 ,(void*) OBJ_BITMAP) );
    DeleteDC (hdcToDelete);
}