#include "builtin.h"


// int	parse_exit_argument(const char *str, long long *value)
// {
//     int					i;
//     int					sign;
//     unsigned long long	result;
//     unsigned long long	limit;

//     i = 0;
//     sign = 1;
//     result = 0;
//     if (str[i] == '+' || str[i] == '-')
//     {
//         if (str[i] == '-')
//             sign = -1;
//         i++;
//     }
//     if (!ft_isdigit(str[i]))
//         return (0);
//     if (sign == -1)
//         limit = (unsigned long long)LLONG_MAX + 1ULL;
//     else
//         limit = (unsigned long long)LLONG_MAX;
//     while (ft_isdigit(str[i]))
//     {
//         if (result > (limit - (unsigned long long)(str[i] - '0')) / 10ULL)
//             return (0);
//         result = result * 10ULL + (unsigned long long)(str[i] - '0');
//         i++;
//     }
//     if (str[i] != '\0')
//         return (0);
//     if (sign == -1 && result == (unsigned long long)LLONG_MAX + 1ULL)
//         *value = LLONG_MIN;
//     else if (sign == -1)
//         *value = -(long long)result;
//     else
//         *value = (long long)result;
//     return (1);
// }






// int    ft_atoll(const char *str, long long *value)
// {
//     int                    i;
//     int                    sign;
//     unsigned long long    res;

//     i = 0;
//     res = 0;
//     while (ft_isspace(str[i]))
//         i++;
//     sign = 1;
//     if (str[i] == '+' || str[i] == '-')
//     {
//         if (str[i] == '-')
//             sign = -1;
//         i++;
//     }
//     if (!ft_isdigit(str[i]))
//         return (0);
//     while (ft_isdigit(str[i]))
//     {
//         if (!check_overflow(res, str[i] - '0', sign))
//             return (0);
//         res = res * 10 + (str[i] - '0');
//         i++;
//     }
//     if (str[i] != '\0')
//         return (0);
//     if (sign == -1 && res == (unsigned long long)LLONG_MAX + 1ULL)
//         *value = LLONG_MIN;
//     else
//         *value = (long long)(res * sign);
//     return (1);
// }




int builtin_exit(t_cmd *cmd, t_shell *shell)
{
    char *trimmed;
    long long value;

    print_exit_if_interactive();

    if (!cmd->args[1])
        return (handle_no_args(shell));

    trimmed = ft_strtrim(cmd->args[1], " \t\n\"");
    if (!trimmed || !is_numeric(trimmed) || !parse_exit_argument(trimmed, &value))
        return (handle_numeric_error(cmd->args[1], trimmed, shell));

    if (cmd->args[2])
        return (handle_too_many_args(shell, trimmed));

    return (get_exit_status(trimmed, value, shell));
}

