#include "execution.h"




 void handle_star(const char **pattern,const char **star,const char **match,const char **name)
{
    *star = *pattern;
    *match = *name;
    (*pattern)++;
}

 int handle_match(const char **pattern, const char **name)
{
    if (**pattern == **name)
    {
        (*pattern)++;
        (*name)++;
        return (1);
    }
    return (0);
}

 int handle_backtrack(const char **pattern,const char **name,const char **star,const char **match)
{
    if (*star)
    {
        *pattern = *star + 1;
        (*match)++;
        *name = *match;
        return (1);
    }
    return (0);
}

 int skip_stars(const char *pattern)
{
    while (*pattern == '*')
        pattern++;
    return (*pattern == '\0');
}



int wildcard_match(const char *pattern, const char *name)
{
    const char  *star;
    const char  *match;

    star = NULL;
    match = NULL;

    while (*name)
    {
        if (*pattern == '*')
            handle_star(&pattern, &star, &match, &name);
        else if (handle_match(&pattern, &name))
            ;
        else if (handle_backtrack(&pattern, &name, &star, &match))
            ;
        else
            return (0);
    }
    return (skip_stars(pattern));
}
