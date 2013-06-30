# ifndef LOGGER_INTERFACE_H

# define LOGGER_INTERFACE_H

/*\
 * This is Interface.h file. It has interface of Logger.
\*/
class Interface
{
    bool EnterNote (unsigned int line  , const char* file,
                    const char* message, ...             );
};

# endif /* LOGGER_BASE_H */
