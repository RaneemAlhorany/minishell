/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_method.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:20:18 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:25:14 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	is_redirection(t_token_type type)
{
	if (type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_REDIRECT_APPEND || type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

int	is_command_delimiter(t_token_type type)
{
	if (type == TOKEN_PIPE || type == TOKEN_AND || type == TOKEN_OR
		|| type == TOKEN_LPAREN || type == TOKEN_RPAREN)
		return (1);
	return (0);
}
