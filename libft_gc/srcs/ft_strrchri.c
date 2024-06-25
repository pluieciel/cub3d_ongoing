/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:49:11 by jlefonde          #+#    #+#             */
/*   Updated: 2024/05/02 09:51:44 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_gc.h"

/**
 * @brief Locates the last occurrence of a character in a string.
 *
 * @param s Pointer to the null-terminated string to search.
 * @param c The character to search for.
 * @return The index of the found character, otherwise -1.
 */
int	ft_strrchri(const char *s, int c)
{
	unsigned char	ch;
	int				i;

	ch = (unsigned char)c;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == ch)
			return (i);
		i--;
	}
	return (-1);
}
