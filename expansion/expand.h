/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 16:18:55 by babo-sai          #+#    #+#             */
/*   Updated: 2026/04/29 16:18:56 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include "../env/env.h"
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>

typedef struct s_env	t_env;

typedef struct s_buffer
{
	char				*data;
	size_t				len;
	size_t				capacity;
}						t_buffer;

typedef struct s_expand
{
	char				*input;
	int					i;
	int					in_single;
	int					in_double;
	t_env				*env;
	int					last_status;
	t_buffer			buf;
}						t_expand;

// expand

int						handle_regular_char(t_expand *ex);
int						handle_expansion(t_expand *ex);
int						handle_quotes(t_expand *ex);
int						process_expand(t_expand *ex);
char					*expand_string(char *input, t_env *env,
							int last_status);
// buffer

int						buffer_init(t_buffer *buf);
int						buffer_append_str(t_buffer *buf, char *str);
int						buffer_grow(t_buffer *buf, size_t needed);
int						buffer_append_char(t_buffer *buf, char c);
// utils

int						init_expand(t_expand *ex, char *input, t_env *env,
							int last_status);
char					*expand_var(char *input, int *i, t_env *env,
							int last_status);
char					*handle_special_dollar(char *input, int *i,
							int last_status);
char					*handle_env_variable(char *input, int *i, t_env *env);
#endif
