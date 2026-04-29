/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:15:13 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:32:35 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	parse_digits(const char *str, int *i, unsigned long long *res, int sign)
{
	*res = 0;
	if (!ft_isdigit(str[*i]))
		return (0);
	while (ft_isdigit(str[*i]))
	{
		if (sign == 1 && (*res > (((unsigned long long)LLONG_MAX - (str[*i]
							- '0')) / 10)))
			return (0);
		if (sign == -1 && *res > ((unsigned long long)LLONG_MAX + 1ULL
				- (str[*i] - '0')) / 10)
			return (0);
		*res = (*res) * 10 + (str[*i] - '0');
		(*i)++;
	}
	if (str[*i] != '\0')
		return (0);
	return (1);
}

int	skip_spaces_and_get_sign(const char *str, int *sign)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	*sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	return (i);
}

int	ft_atoll(const char *str, long long *value)
{
	int					i;
	int					sign;
	unsigned long long	res;

	i = skip_spaces_and_get_sign(str, &sign);
	if (!parse_digits(str, &i, &res, sign))
		return (0);
	if (sign == -1 && res == (unsigned long long)LLONG_MAX + 1ULL)
		*value = LLONG_MIN;
	else
		*value = (long long)(res * sign);
	return (1);
}

int	check_digits(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (!str[i + 1])
			return (0);
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(t_cmd *cmd, t_shell *shell)
{
	char		*trimmed;
	long long	value;

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO))
		ft_putendl_fd("exit", 1);
	if (!cmd->args[1])
	{
		shell->is_running = 0;
		return (shell->last_exit_status);
	}
	trimmed = ft_strtrim(cmd->args[1], " \t\n\"");
	if (!trimmed || !check_digits(trimmed) || !ft_atoll(trimmed, &value))
		return (handle_numeric_error(cmd->args[1], trimmed, shell));
	if (cmd->args[2])
		return (handle_too_many_args(shell, trimmed));
	free(trimmed);
	shell->is_running = 0;
	return ((unsigned char)value);
}
