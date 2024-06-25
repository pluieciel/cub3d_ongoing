/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_gc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/11 17:25:51 by jlefonde          #+#    #+#             */
/*   Updated: 2024/05/13 19:26:33 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_gc.h"

void	ft_lstadd_back_gc(t_list **list, char *content, t_gc **gc)
{
	ft_lstadd_back(list, ft_lstnew_gc(ft_strdup_gc(content, gc), gc));
}
