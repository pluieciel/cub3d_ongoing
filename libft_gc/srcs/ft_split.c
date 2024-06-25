/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:50:22 by jlefonde          #+#    #+#             */
/*   Updated: 2024/06/25 09:57:29 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_gc.h"

static void	find_next(const char *s, char c, size_t *start, size_t *end)
{
	while (s[*start] && s[*start] == c)
		(*start)++;
	*end = *start;
	while (s[*end] && s[*end] != c)
		(*end)++;
}

/**
 * @brief Splits a string into an arr of substrings based on a delimiter char.
 *
 * @param s The string to be split.
 * @param c The delimiter character.
 * @return The array of new strings resulting from the split or NULL if failed.
 */
char	**ft_split_gc(char const *s, char c, t_gc **gc)
{
	char	**result;
	int		word_count;
	int		i;
	size_t	start;
	size_t	end;

	if (s == NULL)
		return (NULL);
	word_count = ft_count_words(s, c);
	result = gc_malloc((word_count + 1) * sizeof(char *), gc);
	if (result == NULL)
		return (NULL);
	i = 0;
	start = 0;
	while (s[start] && i < word_count)
	{
		find_next(s, c, &start, &end);
		result[i] = ft_substr_gc(s, start, end - start, gc);
		if (result[i] == NULL)
			return (NULL);
		i++;
		start = end;
	}
	result[i] = NULL;
	return (result);
}
