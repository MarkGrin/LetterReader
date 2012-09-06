/* namespace Lining for this file*/
namespace Lining
{
    /*Namespace Point describes three states of points*/
    namespace Point
    {
        const char WHITE = 0, BLACK = 1, MARKED = 2;
    };
};


/*Headers*/


       bool  lineThisHDC        (HDC hdcToLine, HDC hdcToShowProgress);
inline bool  isBlack            (int x, int y, HDC hdc);
inline void  deletePoint        (int x, int y, HDC hdc);
inline char* genStateTable      ();
inline void  fillMarkTable      (char* table, HDC hdc);
inline bool  putMarksInTable    (char* table);
inline void  filter             (char* markTable, HDC hdcToLine, HDC hdcToShowProgress);
inline void  collectInfo        (int x, int y, char* infoList, char* markTable);
inline bool  analyzInfo         (char* infoList);
inline bool  isSurrounded       (char* infoList);
inline bool  isDoubleSided      (char* infoList);
inline bool  isEnding           (char* infoList);
inline bool  isAlone            (char* infoList);
inline void  logPixelInfoList   (char* infoList);
inline void  deleteMarkedPixels (char* markTable, HDC hdc);

/* inline bool  isDoubleSided      (char* infoList)
 *
 * description
 *
 * this function checks if point is surrounded
 * by Black marks separeted with NonBlack marks
 *
 * args
 *
 * char* infoList - infoList to check
 *
 * return value
 *
 * It is separeted as in description     - bool = true
 * It is NOT separeted as in description - bool = false
 *
 */
inline bool  isDoubleSided      (char* infoList)
{
    bool OldIsWhite = infoList[0] != Lining::Point::BLACK;
    int changes = 0;
    for (int i = 1; i < 8; i++)
    {
        bool newIsWhite = infoList[i] != Lining::Point::BLAC;
        if (newIsWhite != OldIsWhite)
        {
            OldIsWhite = !OldIsWhite;
            changes++;
        }
    }
    if ( changes > 2 )
        return true;
    return false;
}

/* inline bool  isAlone            (char* infoList)
 *
 * description
 *
 * this function checks if infoList
 * contain any BLACK marks
 *
 * args
 *
 * char* infoList - infoList to check
 *
 * return value
 *
 * infoList have at least one BLACK 
 * mark - bool = false
 * infoList have NO BLACK marks - bool
 * = true
 *
 */
inline bool  isAlone            (char* infoList)
{
    for (int i = 0; i < 8; i++)
    {
        if ( infoList[i] == Lining::Point::BLACK )
            return false;
    }
    return true;
}

/* inline void  logPixelInfoList   (char* infoList)
 *
 * description
 *
 * this function logs pixelInfoList array
 * in file of _logger_
 *
 * args
 *
 * char* infoList - infoList to log
 *
 * return value
 *
 * NONE
 *
 */

void  logPixelInfoList   (char* infoList)
{
    _logger_.EnterNote ("%d:%d:%d:%d:%d:%d:%d:%d", NULL, 8,
                        infoList[0],
                        infoList[1],
                        infoList[2],
                        infoList[3],
                        infoList[4],
                        infoList[5],
                        infoList[6],
                        infoList[7]
                      );
}

/* inline bool  deleteMarkedPixels (char* markTable, HDC hdc)
 *
 * description 
 *
 * deletes all makred in markTable points
 *
 * args
 *
 * char* infoList - list
 *
 * return value
 *
 * NONE
 *
 */
void  deleteMarkedPixels (char* markTable, HDC hdc)
{
    int xMax = Screen::Size::X;
    int yMax = Screen::Size::Y;
    int index = 0;

    for (int y = 2; y < yMax; y++)
    {
        for (int x = 2; x < xMax; x++)
        {
            index = x + y * xMax;

            if ( markTable[index] == Lining::Point::MARKED )
            {
                markTable[index] = Lining::Point::WHITE;
                deletePoint (x, y, hdc);
            }
        }
    }
}

/* inline bool  isSurrounded      (char* infoList);
 *
 * description
 *
 * this function checks if point is surrounded
 * with other points
 *
 * args
 *
 * char* infoList - filled list with marks of
 * surroinding points by collect info function
 *
 * return value
 *
 * if surrounded -   bool = true
 * if NOT surrounded bool = false
 *
 * warning
 *
 * count BLACK and MARKED points. If point is MARKED
 * function will think it's BLACK
 *
 */
bool isSurrounded (char* infoList)
{
    for (int i = 0; i < 8; i++)
    {
        if ( infoList[i] == Lining::Point::WHITE )
            return false;
    }
    return true;
}

/* inline bool  isEnding (char* infoList)
 *
 * description
 *
 * this function checks if point is ending of line
 * in other words if it has only one neibhour point
 *
 * args
 *
 * char* infoList - filled list with marks of
 * surroinding points by collect info function
 *
 * return value
 *
 * if ending     - bool = true
 * if NOT ending - bool = false
 *
 * warning
 *
 * count WHITE and MARKED points as WHITE
 *
 */
bool isEnding (char* infoList)
{
    int neibhours = 8;
    for (int i = 0; i < 8; i++)
    {
        if ( infoList[i] != Lining::Point::BLACK )
            neibhours--;
    }
    if ( neibhours == 1 )
        return true;
    return false;
}

/* inline bool isBlack (int x, int y, HDC hdc) 
 *
 * descrition
 *
 * this function checks if point is black
 *
 * args
 *
 * int x   - x pos of point
 * int y   - y pos of point
 * HDC hdc - HDC where point is placed
 *
 * return value
 *
 * point IS black     - bool = true
 * point is NOT black - bool = false
 *
 * warning
 *
 * please check does hdc contain point
 *
 */
bool isBlack (int x, int y, HDC hdc)
{
    COLORREF Pixelcolor = GetPixel (hdc, x, y);
    
    int totalColor = 0;
    
    totalColor += GetRValue (Pixelcolor);
    totalColor += GetGValue (Pixelcolor);
    totalColor += GetBValue (Pixelcolor);
    
    if ( totalColor > 0 )
        return false;
    return true;
}

/* void deletePoint (int x, int y, HDC hdc)
 * 
 * description
 *
 * this function sets point color to white
 *
 * args
 *
 * int x   - x pos of point
 * int y   - y pos of point
 * HDC hdc - HDC where point is placed
 *
 * return value
 *
 * NONE
 *
 * warning
 *
 * check does hdc contain this point please
 *
 */
void deletePoint (int x, int y, HDC hdc)
{
    COLORREF white = RGB (255, 255, 255);
    
    SetPixel (hdc, x, y, white);
}

/* bool lineThisHDC (HDC hdcToLine, HDC hdcToShowProgress)
 *
 * description
 *
 * This function filtering contrasted hdc.
 * It left only 1 pixel length silhouette
 * of symbol
 *
 * args
 *
 * HDC hdcToLine         - hdc you want to filter
 * HDC hdcToShowProgress - hdc you want to show progess on.
 * you can make it zero to ignore the progress
 *
 * return value
 *
 * function success - bool = true
 * function fail    - bool = false
 *
 */
bool lineThisHDC (HDC hdcToLine, HDC hdcToShowProgress)
{
    char* stateTable = genStateTable ();
    if ( !stateTable )
        return false;

    fillMarkTable (stateTable, hdcToLine);

    filter (stateTable, hdcToLine, hdcToShowProgress);
}

/* char* genStateTable ();
 *
 * description
 *
 * This function creates array.
 * Array will be sized speacially
 * for the size in Constants.h file.
 * Array will be char.
 * Array is used to mark points
 * 
 * Points state see in Lining::Point
 * namespace
 *
 * args
 *
 * NONE
 *
 * return value
 *
 * function success - char* = address of the
 * newly created array
 * function fail    - char* = NULL
 *
 */
char* genStateTable ()
{
    char* table = NULL;

    try
    {
        int size = Screen::Size::X * Screen::Size::Y;

        table = new char[size];
        memset (table, 0, size);
    }
    catch ( ... )
    {
        table = NULL;
        return  NULL;
    }

    return table;
}

/* void fillMarkTable (char* table, HDC hdc)
 *
 * description
 *
 * this function fills table with stats
 * of hdc pixel's
 *
 * args
 *
 * char* table - table that was created with
 * genStateTable
 * HDC   hdc   - hdc you want to have stats of
 *
 * return value
 *
 * NONE
 *
 * warning
 *
 * hdc must be sized as in Constants.h file
 *
 */ 
void fillMarkTable (char* table, HDC hdc)
{
    int xMax = Screen::Size::X;
    int yMax = Screen::Size::Y;

    for (int x = 0; x < xMax; x++)
    {
        for (int y = 0; y < yMax; y++)
        {
            int currentIndex = x + y * xMax;
            if ( isBlack (x, y, hdc) )
                table[currentIndex] = Lining::Point::BLACK;
            else
                table[currentIndex] = Lining::Point::WHITE;  
        }
    }
}

/* void filter (char* stateTable, HDC hdcToLine, HDC hdcToShowProgress)
 *
 * description
 *
 * This function filtering contrasted hdc.
 * It left only 1 pixel length silhouette
 * of symbol
 *
 * args
 *
 * char* stateTable      - filled state table
 * HDC hdcToLine         - hdc you want to filter
 * HDC hdcToShowProgress - hdc you want to show progess on.
 * if u want u can put zero to show no progress
 * return value
 *
 * NONE
 *
 * warning
 *
 */ 
void filter (char* stateTable, HDC hdcToLine, HDC hdcToShowProgress)
{
    while ( true )
    {
        if ( !putMarksInTable (stateTable) )
            return ;
        deleteMarkedPixels (stateTable, hdcToLine);

        if ( hdcToShowProgress)
            BitBlt (hdcToShowProgress, 0, 0,
                    Screen::Size::X, Screen::Size::Y,
                    hdcToLine, 0, 0, SRCCOPY);
        getch ();
    }
}

/* bool putMarksInTable (char* table)
 *
 * description
 *
 * This function fills which points need to
 * be deleted
 *
 * args
 *
 * char* table - table to fill with marks
 *
 * return value
 *
 * marks were placed   - bool = true
 * mark weren't placed - bool = false
 *
 */
bool putMarksInTable (char* table)
{
    bool marksWerePutted = false;
    int xMax = Screen::Size::X;
    int yMax = Screen::Size::Y;
    int index = 0;
    char pixelInfo[8] = {0, 0, 0, 0, 0, 0, 0, 0};

    for (int y = 2; y < yMax - 2; y++)
    {
        for (int x = 2; x < xMax - 2; x++)
        {
            index = x + y * Screen::Size::X;

            if ( table[index] == Lining::Point::BLACK )
            {
                collectInfo (x, y, pixelInfo, table);
                if ( analyzInfo (pixelInfo) )
                {
                    marksWerePutted = true;
                    table[index] = Lining::Point::MARKED;
                }
            }
        }
    }
    return marksWerePutted;
}

/* void collectInfo (int x, int y, char* infoList, char* markTable)
 *
 * description
 *
 * this function collects info in infoList array
 * about surrounding pixel
 *
 * args
 *
 * int          x  - x pos of point
 * int          y  - y pos of point
 * char* infoList  - where to put info. must have 8 chars
 * char* markTable - table with marks of points
 *
 * return value
 *
 * NONE
 *
 */
void collectInfo (int x, int y, char* infoList, char* markTable)
{
    int xSize = Screen::Size::X;

    int index = x - 1  +  (y - 1) * xSize;

    infoList[0] = markTable[index];
    infoList[1] = markTable[index + 1];
    infoList[2] = markTable[index + 2];
    infoList[3] = markTable[index + xSize + 2];
    infoList[4] = markTable[index + xSize * 2 + 2];
    infoList[5] = markTable[index + xSize * 2 + 1];
    infoList[6] = markTable[index + xSize * 2];
    infoList[7] = markTable[index + xSize];
}


/* bool  analyzInfo        (char* infoList);
 *
 * description
 *
 * this funciton analyz infoList and decides is
 * this point need to be deleted.
 *
 * args
 *
 * char* infoList - infoList to analyz
 *
 * return value
 *
 * point needs to be DELETED         - bool = true
 * point does NOT need to be deleted - bool = false
 *
 */
bool  analyzInfo (char* infoList)
{
    if ( isAlone       (infoList) )
        return true;
    if ( isSurrounded  (infoList) )
        return false;
    if ( isDoubleSided (infoList) )
        return false;
    if ( isEnding      (infoList) )
        return false;
    return true;
}
