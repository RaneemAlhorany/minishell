#include "builtin.h"



int    parse_exit_argument(const char *str, long long *value)
{
    return (ft_atoll(str, value));
}

int ft_atoll(const char *str, long long *value)
{
    int                 i;
    int                 sign;
    unsigned long long  res;

    i = skip_spaces_and_get_sign(str, &sign);
    if (!parse_digits(str, &i, &res, sign))
        return (0);
    return set_result(res, sign, value);
}




int skip_spaces_and_get_sign(const char *str, int *sign)
{
    int i;

    i = 0;
    while (ft_isspace(str[i]))
        i++;
    *sign = 1;
    if (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            *sign = -1;
        i++;
    }
    return i;
}

int parse_digits(const char *str, int *i, unsigned long long *res, int sign)
{
    *res = 0;
    if (!ft_isdigit(str[*i]))
        return (0);
    while (ft_isdigit(str[*i]))
    {
        if (!check_overflow(*res, str[*i] - '0', sign))
            return (0);
        *res = (*res) * 10 + (str[*i] - '0');
        (*i)++;
    }
    if (str[*i] != '\0')
        return (0);
    return (1);
}


int set_result(unsigned long long res, int sign, long long *value)
{
    if (sign == -1 && res == (unsigned long long)LLONG_MAX + 1ULL)
        *value = LLONG_MIN;
    else
        *value = (long long)(res * sign);
    return (1);
}

