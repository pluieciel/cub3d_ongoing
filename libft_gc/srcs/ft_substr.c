/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 09:25:20 by jlefonde          #+#    #+#             */
/*   Updated: 2024/06/25 10:00:03 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_gc.h"

/**
 * @brief Extracts a substring from a string.
 *
 * @param s The string from which to create the substring.
 * @param start The start index of the substring in the string 's'.
 * @param len The maximum length of the substring.
 * @return The substring or NULL if the allocation fails.
 *
 */
char	*ft_substr_gc(char const *s, unsigned int start, size_t len, t_gc **gc)
{
	char	*substr;
	size_t	i;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		substr = gc_malloc(sizeof(char), gc);
		if (substr == NULL)
			return (NULL);
		substr[0] = '\0';
		return (substr);
	}
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	substr = gc_malloc((len + 1) * sizeof(char), gc);
	if (substr == NULL)
		return (NULL);
	i = -1;
	while (++i < len && s[i + start] != '\0')
		substr[i] = s[i + start];
	substr[i] = '\0';
	return (substr);
}
