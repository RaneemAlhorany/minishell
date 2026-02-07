/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: babo-sai <babo-sai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/16 11:58:32 by babo-sai          #+#    #+#             */
/*   Updated: 2025/08/19 20:06:53 by babo-sai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_word(char const *s, char c)
{
	size_t	count;
	int		in_word;
	size_t	i;
	size_t	len;

	count = 0;
	in_word = 0;
	i = 0;
	len = ft_strlen(s);
	while (i < len)
	{
		if (s[i] != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (s[i] == c)
			in_word = 0;
		i++;
	}
	return (count);
}

static char	*word_dup(char const *start, size_t len)
{
	char	*word;

	word = (char *)ft_calloc(len + 1, sizeof(char));
	if (!word)
		return (NULL);
	ft_strlcpy(word, start, len + 1);
	return (word);
}

static int	fill_array(char **res, char const *s, char c)
{
	size_t		i;
	size_t		len;
	size_t		total_len;

	i = 0;
	total_len = ft_strlen(s);
	while (*s && 0 < total_len)
	{
		if (*s != c)
		{
			len = 0;
			while (s[len] && s[len] != c)
				len++;
			res[i] = word_dup(s, len);
			if (!(res[i]))
				return (0);
			i++;
			s += len;
		}
		else
			s++;
	}
	res[i] = NULL;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	size_t	words;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	words = count_word(s, c);
	res = malloc((words + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	if (!fill_array(res, s, c))
	{
		while (res[i])
		{
			free(res[i]);
			i++;
		}
		free(res);
		return (NULL);
	}
	return (res);
}
/*int main(void)
{
	char **arr;
	int i = 0;

	arr = ft_split("   salam   baybars   asaaaa   ", ' ');
	while (arr[i])
	{
		printf("[%s]\n", arr[i]);
		free(arr[i]);
		i++;
	}
	free(arr);
	return (0);
}*/