/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:46:47 by jnunes            #+#    #+#             */
/*   Updated: 2024/05/10 21:15:08 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strcmp(char *s1, char *s2)
{
	int	length;

	length = 0;
	while (s1[length] != '\0' && s2[length] != '\0')
	{
		if (s1[length] != s2[length])
		{
			return (s1[length] - s2[length]);
		}
		length++;
	}
	return (s1[length] - s2[length]);
}
