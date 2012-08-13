void kickPoint (int x, int y, HDC hdc)
{
	COLORREF white = RGB (255, 255, 255);
	SetPixel (hdc, x, y, white);
}
void collectData (int x, int y, int* whereToPut, HDC hdc)
{
	whereToPut[0] = GetRValue (GetPixel (hdc, x - 1, y - 1));
	whereToPut[1] = GetRValue (GetPixel (hdc, x    , y - 1));
	whereToPut[2] = GetRValue (GetPixel (hdc, x + 1, y - 1));
	whereToPut[3] = GetRValue (GetPixel (hdc, x + 1, y    ));
	whereToPut[4] = GetRValue (GetPixel (hdc, x + 1, y + 1));
	whereToPut[5] = GetRValue (GetPixel (hdc, x    , y + 1));
	whereToPut[6] = GetRValue (GetPixel (hdc, x - 1, y + 1));
	whereToPut[7] = GetRValue (GetPixel (hdc, x - 1, y    ));
}
bool fullyPlaced (int* list)
{
	for (int i = 0; i < 8; i++)
	{
		if ( list[i] )
		    return false;
	}
	return true;
}
int firstZeroIndex (int* list)
{
	int firstZeroIndex = -1;
	for (int i = 0; i < 8; i++)
	{
		if ( list[i] )
		    firstZeroIndex = i;
	}
	return firstZeroIndex;
}
bool doubleSided (int* list)
{
	int index = firstZeroIndex (list);
	if (index == -1)
		return false;
	bool wasBlack = false;
	bool inRow    = false;
	for (int i = 0; i < 8; i++)
	{
		index = (index + 1)%8;
		if ( !wasBlack )
		{
			if ( !(list[index]) )
			{
			    wasBlack = true;
				inRow    = true;
			}
		}
		if ( wasBlack )
		{
			if ( list[index] )
			{
				if ( inRow )
					inRow = false;
			}
			else
			{
				if ( !inRow )
				   return true;
			}
		}
	}
	return false;
}
bool ending (int* list)
{
	int neibhors = 0;
	for (int i = 0; i < 8; i++)
	{
		if ( !(list[i]) )
		    neibhors++;
	}
	if ( neibhors == 1)
	    return true;
	return false;
}
bool doDelete (int x, int y, HDC hdc)
{
	int list[8] = {0};
	collectData (x, y, list, hdc);
	if ( fullyPlaced (list) )
        return false;
	if ( doubleSided (list) )
	    return false;
	if ( ending (list) )
		return false;
	return true;
}

bool oneMove (bool* pointList, HDC hdc, HDC hdcToDraw)
{
	bool wasChanged = false;
	int currentIndex = 2 * Screen::Size::Y + 2;
	for (int y = 2; y < Screen::Size::Y - 2; y++)
	{
		for (int x = 2; x < Screen::Size::X - 2; x++)
		{
			if ( !pointList[currentIndex] )
			{
				if ( doDelete (x, y, hdc) )
				{
				    kickPoint (x, y, hdc);
					wasChanged = true;
					pointList[currentIndex] = true;
				}
			}
			BitBlt (hdcToDraw, 0, 0, Screen::Size::X, Screen::Size::Y, hdc, 0, 0, SRCCOPY);
		 currentIndex++;
		}
	}
	return wasChanged;
}

bool lineThisHDC (HDC HDCToLine, HDC hdcToDraw)
{
	bool* pointList = NULL;
	try
	{
		int totalPoints = Screen::Size::X * Screen::Size::Y;
		pointList = new bool[totalPoints];
		memset (pointList, totalPoints, 0);
	}
	catch ( ... )
	{
		pointList = NULL;
		return false;
	}
	while ( oneMove (pointList, HDCToLine, hdcToDraw) )
	{
		printf ("\nhey");
	}
	delete[] pointList;
	return true;
}