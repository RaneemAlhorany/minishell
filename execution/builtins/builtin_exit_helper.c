/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_helper.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:15:05 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:15:09 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	handle_numeric_error(char *arg, char *trimmed, t_shell *shell)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
	free(trimmed);
	shell->is_running = 0;
	return (2);
}

int	handle_too_many_args(t_shell *shell, char *trimmed)
{
	ft_putendl_fd("exit: too many arguments", 2);
	shell->last_exit_status = 1;
	free(trimmed);
	return (1);
}
