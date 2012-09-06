# define END_ASSERT  __FILE__, __LINE__

class NonCopy
{
    NonCopy (NonCopy&);
    NonCopy operator = (NonCopy&);
public:
    NonCopy (){}
};

const int Logger_Error_CantOpenFile  = 0X4,
          Logger_Error_FileIsClosed  = 0x5,
          Logger_Error_CantCreatSect = 0x6;

const int Logger_Type_ReWrite = 0,
          Logger_Type_Append  = 1;

const int Logger_Mode_Time = 0x1;

struct Logger : NonCopy
{
    CRITICAL_SECTION FileSemafore;
    int Error;
    
    FILE * LogFile;
    FILE * ErrorFile;
    
    public:
    
    HWND ErrorHWND;
    
    void EnterNote   (char * What, char Flag = 0, int Count = 0, ...);
    void EnterError  (char * What, char Flag = 0, int Count = 0, ...);
    void Assert (bool Statement, char * Description, char * File, int Line);
    
    Logger  (char * FileName, char * ErrorFile, HWND hwnd = 0, short int Type = 0);
    ~Logger (                                   );
    
    int GetLastError () {return Error;}
};

Logger :: Logger (char * Name, char * ErrorName, HWND hwnd /* = 0 */,
                  short int Type /* = 0*/):
       
       Error     (  0 ),
       ErrorHWND (hwnd)
{
    if (Type == Logger_Type_ReWrite)
    {   
        if (!LogFile)
            LogFile   = fopen (Name, "w");
        if (!ErrorFile)
        ErrorFile     = fopen (ErrorName, "w");
    }
    
    if (Type == Logger_Type_Append)
    {  
        if (!LogFile) 
            LogFile   = fopen (Name, "a");
        if (!ErrorFile)
            ErrorFile = fopen (ErrorName, "a");
    }
    
    if (!LogFile || !LogFile)
    {   Error = Logger_Error_CantOpenFile; return; MessageBox (0, "Log error", 0, 0);}
    
    if (!InitializeCriticalSectionAndSpinCount(&FileSemafore, 0x00000400))
    {   Error = Logger_Error_CantCreatSect; return; MessageBox (0, "Log error", 0, 0);}
}

Logger :: ~Logger ()
{
    if (LogFile)
        fclose (LogFile);
    if (ErrorFile)
        fclose (ErrorFile);
        
    DeleteCriticalSection(&FileSemafore);
}

void Logger :: EnterNote (char * What, char Flag /* = 0 */, int Count /* = 0 */, ... )
{
      if (!LogFile)
      {    Error = Logger_Error_FileIsClosed; return;}
      
      if (Error)
         return;
      
      EnterCriticalSection(&FileSemafore);
      
      va_list Varibles;
      va_start (Varibles, Count); 
      
      fprintf (LogFile,"\nLOG ENTRY:\n");
      if (Flag & Logger_Mode_Time)
      {
          time_t Time = time (0);
          tm * LocalTime = localtime ( &Time );;
          fprintf (LogFile, "TIME: %2d:%2d:%2d\n", LocalTime->tm_hour,
                                                   LocalTime->tm_min,
                                                   LocalTime->tm_sec);
      }
      
      while (*What)
      {
          if (*What == '%')
          {    
              What++;
              
              if (!What) return;
              
              if (Count == 0) continue;
              
              if (*What == 'd')
              {   fprintf (LogFile, "%d", va_arg (Varibles, int)); Count--;}
                  
              if (*What == 'f')
              {   fprintf (LogFile, "%f", va_arg (Varibles, long)); Count--;}
                  
              if (*What == 'c')
              {   fprintf (LogFile, "%c", va_arg (Varibles, int)); Count--;}
                  
              if (*What == 's')
              {   fprintf (LogFile, "%s", va_arg (Varibles, char *)); Count--;}
              
              What++;
          }
          else
          {
              fprintf (LogFile, "%c", *What);
              What++;
          } 
      }
      va_end(Varibles);
      
      LeaveCriticalSection(&FileSemafore);
}
void Logger :: EnterError (char * What, char Flag /* = 0 */, int Count /* = 0 */, ... )
{
     if (Error)
         return;
         
      if (!ErrorFile)
      {    Error = Logger_Error_FileIsClosed; return;}
      
      EnterCriticalSection(&FileSemafore);
      
      va_list Varibles;
      va_start (Varibles, Count); 
      
      fprintf (ErrorFile,"\nERROR ENTRY:\n");
      
      if (Flag & Logger_Mode_Time)
      {
          time_t Time = time (0);
          tm * LocalTime = localtime ( &Time );;
          fprintf (ErrorFile, "TIME: %2d:%2d:%2d\n", LocalTime->tm_hour,
                                                   LocalTime->tm_min,
                                                   LocalTime->tm_sec);
      }
      
      while (*What)
      {
          if (*What == '%')
          {    
              What++;
              
              if (!What) return;
              
              if (Count == 0) continue;
              
              if (*What == 'd')
              {   fprintf (ErrorFile, "%d", va_arg (Varibles, int)); Count--;}
                  
              if (*What == 'f')
              {   fprintf (ErrorFile, "%f", va_arg (Varibles, long)); Count--;}
                  
              if (*What == 'c')
              {   fprintf (ErrorFile, "%c", va_arg (Varibles, int)); Count--;}
                  
              if (*What == 's')
              {   fprintf (ErrorFile, "%s", va_arg (Varibles, char *)); Count--;}
              
              What++;
          }
          else
          {
              fprintf (ErrorFile, "%c", *What);
              What++;
          } 
      }
      va_end(Varibles);
      
      LeaveCriticalSection(&FileSemafore);
}
void Logger :: Assert (bool Statement, char * Description, char * File, int Line)
{
     if (!LogFile || !ErrorFile)
     {    Error = Logger_Error_FileIsClosed; return;}
     
     if (Error)
         return;
     FILE * FileToLog = 0;
     if (Statement)
         FileToLog = LogFile;
     else
         FileToLog = ErrorFile;
         
     EnterCriticalSection(&FileSemafore);
     
     fprintf (FileToLog,"\nLOG ENTRY:\n");
     time_t Time = time (0);
          tm * LocalTime = localtime ( &Time );
          fprintf (FileToLog, "TIME: %2d:%2d:%2d\n", LocalTime->tm_hour,
                                                   LocalTime->tm_min,
                                                   LocalTime->tm_sec);
     if (Statement)
         fprintf (FileToLog, "ASSERTION SUCCEEDED: %s\n", Description);
     else
     {
         fprintf (FileToLog, "ASSERTION FAILED: %s\n", Description);
         MessageBox (ErrorHWND, Description, "Assertion Failed (It is bad)", MB_OK);
         fprintf (FileToLog, "FILE:%s\n", File);
         fprintf (FileToLog, "LINE:%d\n", Line);
         fclose (LogFile);
         fclose (ErrorFile);
         exit ( 0 );
     }
     fprintf (FileToLog, "FILE:%s\n", File);
     fprintf (FileToLog, "LINE:%d\n", Line);
     
     LeaveCriticalSection(&FileSemafore);
     
}
