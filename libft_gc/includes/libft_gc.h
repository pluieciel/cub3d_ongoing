/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_gc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlefonde <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 11:43:46 by jlefonde          #+#    #+#             */
/*   Updated: 2024/07/21 15:24:03 by jlefonde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_GC_H
# define LIBFT_GC_H

# include "gc.h"
# include <stdarg.h>
# include <stdio.h>
# include <string.h>
# include <strings.h>
# include <unistd.h>

extern int	g_strlen;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_toupper(int c);
int					ft_tolower(int c);
int					ft_strcmp(char *s1, char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strstart(const char *s1, const char *s2);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
int					ft_atoi(const char *nptr);
int					ft_atoi_base(char *str, char *base);
int					ft_lstsize(t_list *lst);
int					ft_lerp(int a, int b, float t);
int					ft_isvalid_extension(char *file, char *ext);
int					ft_count_words(const char *s, char c);
int					ft_inset(char c, char *set);
int					ft_strchri(const char *s, int c);
int					ft_strrchri(const char *s, int c);
size_t				ft_strlen(const char *s);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
void				ft_bzero(void *s, size_t n);
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
void				ft_lstadd_front(t_list **lst, t_list *new);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstadd_back_gc(t_list **list, char *content, t_gc **gc);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
void				ft_putnbr_base(int nbr, char *base);
void				*ft_memset(void *s, int c, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
void				*ft_calloc_gc(size_t nmemb, size_t size, t_gc **gc);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*ft_strdup_gc(const char *s, t_gc **gc);
char				*ft_substr_gc(char const *s, unsigned int start, size_t len,
						t_gc **gc);
char				*ft_strjoin_gc(char const *s1, char const *s2, t_gc **gc);
char				*ft_strtrim_gc(char const *s1, char const *set, t_gc **gc);
char				*ft_strmapi_gc(char const *s, char (*f)(unsigned int, char),
						t_gc **gc);
char				*ft_itoa_gc(int n, t_gc **gc);
char				*ft_itoa_base_gc(int nbr, char *base, t_gc **gc);
char				**ft_split_gc(char const *s, char c, t_gc **gc);
t_list				*ft_lstnew_gc(void *content, t_gc **gc);
t_list				*ft_lstlast(t_list *lst);
t_list				*ft_lstmap_gc(t_list *lst, void *(*f)(void *),
						void (*del)(void *), t_gc **gc);
long				ft_atol(const char *nptr);

# ifndef FT_PRINTF_H
#  define FT_PRINTF_H

void				ft_put_space(va_list args, int *len, int *i);
void				ft_put_plus(va_list args, int *len, int *i);
void				ft_put_sharp(va_list args, int *len, int *i, char c);
int					ft_putchar(char c);
int					ft_putstr(char *s);
int					ft_putnbr(long long n, int is_signed);
int					ft_puthex(unsigned long int n, int is_upper);
int					ft_putptr(void *p);
int					ft_printf(const char *format, ...);

# endif // FT_PRINTF_H

# ifndef FT_FPRINTF_H
#  define FT_FPRINTF_H

void				ft_put_space_fd(va_list args, int *i, int fd);
void				ft_put_plus_fd(va_list args, int *i, int fd);
void				ft_put_sharp_fd(va_list args, int *i, char c, int fd);
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putnbr_fd(long long n, int is_signed, int fd);
void				ft_puthex_fd(unsigned long int n, int is_upper, int fd);
void				ft_putptr_fd(void *p, int fd);
int					ft_fprintf(int fd, const char *format, ...);

# endif // FT_FPRINTF_H

# ifndef GET_NEXT_LINE_BONUS_H
#  define GET_NEXT_LINE_BONUS_H

#  ifndef BUFFER_SIZE
#   define BUFFER_SIZE 42
#  endif

#  ifndef FD_MAX
#   define FD_MAX 4096
#  endif

typedef struct s_gnl
{
	char		*line;
	char		*buffer;
}				t_gnl;

char				*ft_substr_gnl(char const *s, unsigned int start,
						size_t len, t_gc **gc);
char				*ft_strjoin_gnl(const char *s1, const char *s2, t_gc **gc);
char				*get_next_line(int fd, t_gc **gc);

# endif // GET_NEXT_LINE_BONUS_H

#endif // LIBFT_GC_H
