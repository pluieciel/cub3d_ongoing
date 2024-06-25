/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 14:07:47 by jlefonde          #+#    #+#             */
/*   Updated: 2024/06/25 09:57:19 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_gc.h"

/**
 * @brief Creates a new node with the specified content.
 *
 * @param content The content to create the node with.
 * @return The new node or NULL if the allocation fails.
 */
t_list	*ft_lstnew_gc(void *content, t_gc **gc)
{
	t_list	*lst;

	lst = gc_malloc(sizeof(t_list), gc);
	if (lst == NULL)
		return (NULL);
	lst->content = content;
	lst->next = NULL;
	return (lst);
}
