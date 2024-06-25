/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 10:19:37 by jlefonde          #+#    #+#             */
/*   Updated: 2024/05/01 17:42:42 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_gc.h"

/**
 * @brief Converts a lowercase letter to uppercase.
 *
 * @param c The character to convert.
 * @return The uppercase equivalent of the character, otherwise the character.
 */
int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	return (c);
}
