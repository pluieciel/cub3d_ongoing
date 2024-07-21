/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 09:50:14 by jlefonde          #+#    #+#             */
/*   Updated: 2024/03/18 09:50:16 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft_gc.h"

/**
 * @brief Frees multiple pointers passed as arguments.
 *
 * @param count The number of pointers to free.
 * @param ... The pointers to free.
 */
static void	ft_free_multiple(t_gc **gc, int count, ...)
{
	va_list	args;
	int		i;

	va_start(args, count);
	i = 0;
	while (i++ < count)
		gc_free_ptr(gc, va_arg(args, void *));
	va_end(args);
}

/**
 * @brief Reads data from a file descriptor and stores it in a buffer.
 *
 * @param fd The file descriptor to read from.
 * @param buffer The buffer to store the read data.
 * @param p_remainder Pointer to remaining data from previous reads.
 * @param line Pointer to store the read data.
 * @return The read data.
 */
static char	*ft_read_buffer(int fd, t_gnl *g, char **p_remainder, t_gc **gc)
{
	int		bytes_read;
	char	*temp;
	char	*temp_line;
	char	*old_line;

	bytes_read = read(fd, g->buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		g->buffer[bytes_read] = '\0';
		temp = ft_strchr(g->buffer, '\n');
		if (temp != NULL)
		{
			*p_remainder = ft_substr_gnl(temp, 1, ft_strlen(temp), gc);
			temp_line = ft_substr_gnl(g->buffer, 0, temp - g->buffer + 1, gc);
			old_line = g->line;
			g->line = ft_strjoin_gnl(old_line, temp_line, gc);
			ft_free_multiple(gc, 2, old_line, temp_line);
			return (g->line);
		}
		old_line = g->line;
		g->line = ft_strjoin_gnl(old_line, g->buffer, gc);
		gc_free_ptr(gc, old_line);
		bytes_read = read(fd, g->buffer, BUFFER_SIZE);
	}
	return (g->line);
}

/**
 * @brief Reads the remainder of a line from a buffer.
 *
 * @param temp Pointer to the newline character in the buffer.
 * @param buffer The buffer containing the read data.
 * @param p_remainder Pointer to remaining data from previous reads.
 * @param line Pointer to store the read line.
 * @return The read line.
 */
static char	*ft_read_remainder(char *temp, t_gnl *gnl, char **p_remainder,
	t_gc **gc)
{
	char	*new_remainder;

	gnl->line = ft_substr_gnl(*p_remainder, 0, temp - *p_remainder + 1, gc);
	new_remainder = ft_substr_gnl(temp, 1, ft_strlen(temp), gc);
	ft_free_multiple(gc, 2, *p_remainder, gnl->buffer);
	*p_remainder = new_remainder;
	return (gnl->line);
}

/**
 * @brief Retrieves the next line from a file descriptor.
 *
 * @param fd The file descriptor to read from.
 * @return The next line read from the file descriptor.
 */
char	*get_next_line(int fd, t_gc **gc)
{
	static char	*remainder = NULL;
	char		*temp;
	t_gnl		gnl;

	gnl.line = NULL;
	gnl.buffer = gc_malloc((BUFFER_SIZE + 1) * sizeof(char), gc);
	if (gnl.buffer == NULL || fd < 0 || BUFFER_SIZE <= 0)
	{
		gc_free_ptr(gc, gnl.buffer);
		return (NULL);
	}
	if (remainder != NULL)
	{
		temp = ft_strchr(remainder, '\n');
		if (temp != NULL)
			return (ft_read_remainder(temp, &gnl, &remainder, gc));
		gnl.line = ft_strjoin_gnl("", remainder, gc);
		gc_free_ptr(gc, remainder);
		remainder = NULL;
	}
	gnl.line = ft_read_buffer(fd, &gnl, &remainder, gc);
	gc_free_ptr(gc, gnl.buffer);
	return (gnl.line);
}
