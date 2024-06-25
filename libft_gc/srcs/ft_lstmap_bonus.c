/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:05:46 by jlefonde          #+#    #+#             */
/*   Updated: 2024/05/02 09:50:36 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_gc.h"

/**
 * @brief Iterates the list and applies a function on the content of each node.
 *        Creates a new list resulting from the applications of the function.
 *
 * @param lst The address of a pointer to a node.
 * @param f The address of the function used to iterate on the list.
 * @param del The address of the fun used to del the content of a node if need.
 * @return The new list or NULL if the allocation fails.
 */
t_list	*ft_lstmap_gc(t_list *lst, void *(*f)(void *), void (*del)(void *),
		t_gc **gc)
{
	t_list	*result;
	t_list	*new;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	result = NULL;
	while (lst != NULL)
	{
		new = ft_lstnew_gc((*f)(lst->content), gc);
		if (new == NULL)
		{
			ft_lstclear(&result, del);
			return (NULL);
		}
		ft_lstadd_back(&result, new);
		lst = lst->next;
	}
	return (result);
}
