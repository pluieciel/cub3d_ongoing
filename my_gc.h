/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_gc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuzhao <yuzhao@student.42luxembou...>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:19:45 by yuzhao            #+#    #+#             */
/*   Updated: 2024/04/17 17:34:35 by yuzhao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_GC_H
# define MY_GC_H

# include <stdlib.h>
# include <stdio.h>

typedef struct s_gc
{
	void		*ptr;
	struct s_gc	*next;
}	t_gc;
void	*gc_malloc(size_t size, t_gc **head);
int		gc_free(t_gc *head, char *str, int stdout);
t_gc	*gc_insert(t_gc *head, void *ptr);

#endif
