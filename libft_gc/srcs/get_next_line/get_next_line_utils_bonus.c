/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 08:35:36 by jlefonde          #+#    #+#             */
/*   Updated: 2024/06/26 09:12:43 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft_gc.h"

/**
 * @brief Extracts a substring from a string.
 *
 * @param s The string from which to create the substring.
 * @param start The start index of the substring in the string 's'.
 * @param len The maximum length of the substring.
 * @return The substring or NULL if the allocation fails.
 *
 */
char	*ft_substr_gnl(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	i;

	if (!s || start > ft_strlen(s))
		return (NULL);
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	substr = (char *)malloc((len + 1) * sizeof(char));
	if (substr == NULL)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	if (i == 0)
	{
		free(substr);
		return (NULL);
	}
	substr[i] = '\0';
	return (substr);
}

/**
 * @brief Concatenates two strings.
 *
 * @param s1 The prefix string.
 * @param s2 The suffix string.
 * @return The new string or NULL if the allocation fails.
 */
char	*ft_strjoin_gnl(const char *s1, const char *s2)
{
	char	*s3;
	size_t	s1_len;
	size_t	s2_len;

	if (s1 != NULL)
		s1_len = ft_strlen(s1);
	else
		s1_len = 0;
	if (s2 != NULL)
		s2_len = ft_strlen(s2);
	else
		s2_len = 0;
	s3 = (char *)malloc(s1_len + s2_len + 1);
	if (s3 == NULL)
		return (NULL);
	if (s1 != NULL)
		ft_memcpy(s3, s1, s1_len);
	if (s2 != NULL)
		ft_memcpy(s3 + s1_len, s2, s2_len);
	s3[s1_len + s2_len] = '\0';
	return (s3);
}
