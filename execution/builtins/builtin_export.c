/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:15:44 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:32:27 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	builtin_export(t_cmd *cmd, t_shell *shell)
{
	int	i;
	int	flag_p;
	int	flag_n;

	i = 1;
	if (!cmd || !shell)
		return (1);
	if (!cmd->args[1])
	{
		print_export_list(shell->env);
		return (0);
	}
	if (!parse_export_options(cmd->args, &i, &flag_p, &flag_n))
		return (error_export_arg(cmd, i));
	if (!cmd->args[i] && (flag_p || (!flag_p && !flag_n)))
	{
		print_export_list(shell->env);
		return (0);
	}
	return (handle_export_flow(cmd, shell, i, flag_n));
}
