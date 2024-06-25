/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:09:03 by jlefonde          #+#    #+#             */
/*   Updated: 2024/06/25 09:57:40 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_gc.h"

/**
 * @brief Duplicates a string.
 *
 * @param s Pointer to the null-terminated string to duplicate.
 * @return Pointer to the newly allocated string, identical to str.
 *         Returns NULL if allocation fails.
 */
char	*ft_strdup_gc(const char *s, t_gc **gc)
{
	size_t	s_len;
	char	*dest;

	s_len = ft_strlen(s) + 1;
	dest = gc_malloc(s_len, gc);
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, s, s_len);
	return (dest);
}
