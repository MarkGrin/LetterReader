# ifndef LOGGER_FILEMETHODS_H

# define LOGGER_FILEMETHODS_H

bool File :: ChangeFileName (const char* newName)
{
    if ( !newName )
        return false;

    unsigned int size = strlen (newName);

    char* newPtr = nullptr;

    try
    {
        newPtr = new char[size + 1];
        memcpy (newPtr, newName, size);
        newPtr[size] = 0;
    }
    catch (...)
    {
        return false;
    }

    if ( FileName_ )
        delete[] FileName_;
    FileName_ = newPtr;

    return true;
}

# endif /* LOGGER_FILEMETHODS_H */
