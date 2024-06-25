/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstart.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:45:20 by jlefonde          #+#    #+#             */
/*   Updated: 2024/05/07 18:27:10 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_gc.h"

/**
 * @brief Check if a string start with another
 *
 * @param s1 Pointer to the first string.
 * @param s2 Pointer to the second string.
 * @return An integer 0 if s1 = s2, negative if s1 < s2, positive if s1 > s2.
 */
int	ft_strstart(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] && s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	if (s2[i] != '\0')
		return (1);
	return (0);
}
