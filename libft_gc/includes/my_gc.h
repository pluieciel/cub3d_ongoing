/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_gc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:19:45 by yuzhao            #+#    #+#             */
/*   Updated: 2024/06/26 08:45:16 by jlefonde         ###   ########.fr       */
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
void gc_free_ptr(t_gc **head, void *ptr);

#endif
