inline int getToughnes (COLORREF color)
{
	return GetRValue (color) +
		   GetGValue (color) +
           GetBValue (color) ;
}

inline double getAverage (HDC dc)
{
	double average = 0;
	int index = 0;
	for (int x = 0; x < Screen::Size::X; x++)
	{
		for (int y = 0; y < Screen::Size::Y; y++)
		{
			index++;
		    COLORREF currentColor = GetPixel (dc, x, y);
			int currentToughnes = getToughnes (currentColor);
			average = average + (currentToughnes - average)/index;
		}
	}
	return average;
}
inline void setContrast (HDC dc, int toughness)
{
	COLORREF White = RGB (255, 255, 255);
	COLORREF black = RGB (0  , 0  , 0  );
	
	for (int x = 0; x < Screen::Size::X; x++)
	{
		for (int y = 0; y < Screen::Size::Y; y++)
		{
			int currentToughnes = getToughnes (GetPixel (dc, x, y) );
			if (toughness < currentToughnes)
				SetPixel (dc, x, y, White);
			else
				SetPixel (dc, x, y, black);
		}
	}
}

void contrast (HDC dc, int toughness)
{
	setContrast (dc, toughness);
}