#ifndef EXECUTION_H
#define EXECUTION_H

#include "./builtins/builtin.h"

typedef enum e_builtin_type
{
    BUILTIN_NONE,
    BUILTIN_ECHO,
    BUILTIN_CD,
    BUILTIN_PWD,
    BUILTIN_EXPORT,
    BUILTIN_UNSET,
    BUILTIN_ENV,
    BUILTIN_EXIT
} t_builtin_type;


#endif