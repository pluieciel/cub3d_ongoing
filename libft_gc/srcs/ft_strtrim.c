/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:06:35 by jlefonde          #+#    #+#             */
/*   Updated: 2024/05/01 17:53:18 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_gc.h"

/**
 * @brief Trims the specified characters from the beginning and end of a string.
 *
 * @param s1 The string to be trimmed.
 * @param set The reference set of characters to trim.
 * @return The trimmed string or NULL if the allocation fails.
 */
char	*ft_strtrim_gc(char const *s1, char const *set, t_gc **gc)
{
	int		start;
	int		end;
	size_t	s1_len;

	if (s1 == NULL || set == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = s1_len;
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	return (ft_substr_gc(s1, start, end - start, gc));
}
