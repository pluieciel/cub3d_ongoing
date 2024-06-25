/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lerp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/23 16:24:49 by jlefonde          #+#    #+#             */
/*   Updated: 2024/05/01 17:42:42 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_gc.h"

/**
 * @brief Performs linear interpolation between two integer.
 *
 * @param a The starting value.
 * @param b The ending value.
 * @param t The interpolation parameter.
 * @return The interpolated integer value.
 */
int	ft_lerp(int a, int b, float t)
{
	return ((int)(a + (b - a) * t));
}
