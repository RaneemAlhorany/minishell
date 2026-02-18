/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ralhoura <ralhoura@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 16:25:13 by ralhoura          #+#    #+#             */
/*   Updated: 2025/11/23 14:50:26 by ralhoura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	num_of_substrings(const char *s, char c)
{
	size_t	count;
	char	*next;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s == '\0')
			break ;
		count++;
		next = ft_strchr(s, c);
		if (next)
			s = next;
		else
			break ;
	}
	return (count);
}

static char	*extract_word(const char *s, char c, size_t *len)
{
	char	*next;

	next = ft_strchr(s, c);
	if (next != NULL)
		*len = (size_t)(next - s);
	else
		*len = ft_strlen(s);
	return (ft_substr(s, 0, *len));
}

static int	fill_split_array(char **arr, const char *s, char c)
{
	size_t	i;
	size_t	len;
	char	*word;

	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s == '\0')
			break ;
		word = extract_word(s, c, &len);
		if (!word)
		{
			while (i > 0)
				free(arr[--i]);
			return (-1);
		}
		arr[i++] = word;
		s += len;
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**split_array;
	size_t	num_words;

	if (!s)
		return (NULL);
	num_words = num_of_substrings(s, c);
	split_array = ft_calloc(num_words + 1, sizeof(char *));
	if (!split_array)
		return (NULL);
	if (fill_split_array(split_array, s, c) == -1)
	{
		free(split_array);
		return (NULL);
	}
	split_array[num_words] = NULL;
	return (split_array);
}
