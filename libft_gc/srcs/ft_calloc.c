/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 12:53:01 by jlefonde          #+#    #+#             */
/*   Updated: 2024/06/25 09:55:26 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_gc.h"

/**
 * @brief Allocates memory for an arr of elements and initializes them to zero.
 *
 * @param nmemb Number of elements to allocate.
 * @param size Size of each element in bytes.
 * @return Pointer to the allocated memory or NULL if allocation fails.
 */
void	*ft_calloc_gc(size_t nmemb, size_t size, t_gc **gc)
{
	size_t	total_size;
	void	*res;

	total_size = nmemb * size;
	if (nmemb != 0 && (total_size / nmemb) != size)
		return (NULL);
	res = gc_malloc(total_size, gc);
	if (res == NULL)
		return (NULL);
	ft_bzero(res, total_size);
	return (res);
}
