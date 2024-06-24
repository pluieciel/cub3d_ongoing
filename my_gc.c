/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_gc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuzhao <yuzhao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:23:58 by yuzhao            #+#    #+#             */
/*   Updated: 2024/06/24 16:02:05 by yuzhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_gc.h"
#include <unistd.h>
#include <string.h>

t_gc	*gc_new(void *ptr)
{
	t_gc	*newhead;

	newhead = (t_gc *)malloc(sizeof(t_gc));
	if (!newhead)
		return (NULL);
	newhead->ptr = ptr;
	newhead->next = NULL;
	return (newhead);
}

t_gc	*gc_insert(t_gc *head, void *ptr)
{
	t_gc	*node;

	node = gc_new(ptr);
	if (!node)
		return (NULL);
	node->next = head;
	return (node);
}

void	*gc_malloc(size_t size, t_gc **head)
{
	void	*ptr;
	t_gc	*temp;

	ptr = malloc(size);
	if (!ptr)
	{
		gc_free(*head, "failed", 2);
		*head = NULL;
		return (NULL);
	}
	temp = gc_insert(*head, ptr);
	if (!temp)
	{
		gc_free(*head, "failed", 2);
		*head = NULL;
		return (NULL);
	}
	*head = temp;
	return (ptr);
}

int	gc_free(t_gc *head, char *str, int stdout)
{
	t_gc	*temp;

	write(stdout, str, strlen(str));
	temp = head;
	while (temp)
	{
		head = temp->next;
		free(temp->ptr);
		free(temp);
		temp = head;
	}
	return (1);
}
