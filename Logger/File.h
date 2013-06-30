# ifndef LOGGER_FILE_H

# define LOGGER_FILE_H

/*\
 * This is File.h file. It has class that is responsible for logging in
 * file. It is cross - platform and is inherited from Logger Interface.
\*/

class File : public Interface
{
    private:

    Interface ();

    protected:

    char* FileName_;

    bool ChangeFileName (const char* newName);

    public:

    virtual bool EnterNote (unsigned int line, const char* file,
                            const char*  note, ...             );

    Interface  (const char* newName);
    ~Interface ();
};

# endif /* LOGGER_FILE_H */
