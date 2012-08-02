inline int getMediumColor (double Toughness, int one, int two)
{
	int result = two - (two - ((one + two)/2))*Toughness;
	return (result > two) ? two : result;
}
bool smoothScreen (double Toughness, int times, HDC dc)
{
	for (int index = 0; index < times; index++)
	{
		printf ("\r%d/%d", index + 1, times);
	    for (int x = 0; x < Screen::Size::X - 1; x++)
	    {
	    	for (int y = 0; y < Screen::Size::Y; y++)
	    	{
    			COLORREF  firstColor = GetPixel (dc, x    , y);
    			COLORREF secondColor = GetPixel (dc, x + 1, y);
	    		
	    		COLORREF mediumColor = RGB ( getMediumColor (Toughness, GetRValue (firstColor), GetRValue (secondColor)),
	    		                             getMediumColor (Toughness, GetGValue (firstColor), GetGValue (secondColor)),
                                             getMediumColor (Toughness, GetBValue (firstColor), GetBValue (secondColor)));
	    	    SetPixel (dc, x + 1, y, mediumColor);
	    	}
	    }
    	for (int x = 0; x < Screen::Size::X; x++)
    	{
	    	for (int y = 0; y < Screen::Size::Y - 1; y++)
	    	{
	    		COLORREF  firstColor = GetPixel (dc, x , y);
	    		COLORREF secondColor = GetPixel (dc, x , y + 1);
	    		
	    		COLORREF mediumColor = RGB ( getMediumColor (Toughness, GetRValue (firstColor), GetRValue (secondColor)),
	    		                             getMediumColor (Toughness, GetGValue (firstColor), GetGValue (secondColor)),
                                             getMediumColor (Toughness, GetBValue (firstColor), GetBValue (secondColor)));
	    	    SetPixel (dc, x, y + 1, mediumColor);
	        }
	    }
		for (int x = 600; x >= 1; x--)
    	{
	    	for (int y = 600; y >= 1; y--)
	    	{
	    		COLORREF  firstColor = GetPixel (dc, x , y);
	    		COLORREF secondColor = GetPixel (dc, x , y - 1);
	    		
	    		COLORREF mediumColor = RGB ( getMediumColor (Toughness, GetRValue (firstColor), GetRValue (secondColor)),
	    		                             getMediumColor (Toughness, GetGValue (firstColor), GetGValue (secondColor)),
                                             getMediumColor (Toughness, GetBValue (firstColor), GetBValue (secondColor)));
	    	    SetPixel (dc, x, y - 1, mediumColor);
	        }
	    }
		for (int x = 600; x >= 1; x--)
    	{
	    	for (int y = 600; y >= 1; y--)
	    	{
	    		COLORREF  firstColor = GetPixel (dc, x , y);
	    		COLORREF secondColor = GetPixel (dc, x - 1, y);
	    		
	    		COLORREF mediumColor = RGB ( getMediumColor (Toughness, GetRValue (firstColor), GetRValue (secondColor)),
	    		                             getMediumColor (Toughness, GetGValue (firstColor), GetGValue (secondColor)),
                                             getMediumColor (Toughness, GetBValue (firstColor), GetBValue (secondColor)));
	    	    SetPixel (dc, x - 1, y, mediumColor);
	        }
	    }
	}
}