/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 18:10:30 by amanchon          #+#    #+#             */
/*   Updated: 2020/01/16 19:56:34 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# define BUFFER_SIZE 64

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>

unsigned long long int	ft_atoull(char *str);
int						get_next_line(const int fd, char **line);
int						ft_strlen(const char *str);
int						ft_atoi(const char *str);
int						ft_isalnum(int c);
int						ft_isalpha(int c);
int						ft_isascii(int c);
int						ft_isdigit(int c);
int						ft_isprint(int c);
char					*ft_itoa(int n);
void					ft_putchar_fd(int c, int fd);
void					ft_putendl_fd(char *s, int fd);
void					ft_putnbr_fd(int n, int fd);
void					ft_putstr_fd(char *s, int fd);
char					**ft_split(char const *s, char *charset);
char					*ft_strchr(const char *s, int c);
char					*ft_strdup(const char *s);
char					*ft_strjoin(char const *s1, char const *s2);
size_t					ft_strlcat(char *dest, const char *src, size_t size);
size_t					ft_strlcpy(char *dest, const char *src, size_t size);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					*ft_strrchr(const char *s, int c);
char					*ft_strtrim(char const *s1, char const *set);
char					*ft_substr(char const *s, int start, int len);
int						ft_tolower(int c);
int						ft_toupper(int c);
void					*ft_calloc(size_t nmemb, size_t size);
void					ft_bzero(void *s, size_t n);
void					*ft_memccpy(void *d, const void *src, int c, size_t n);
void					*ft_memchr(const void *s, int c, size_t n);
int						ft_memcmp(const void *s1, const void *s2, size_t n);
void					*ft_memcpy(void *dest, const void *src, size_t n);
void					*ft_memmove(void *dst, const void *src, size_t len);
void					*ft_memset(void *s, int c, size_t n);
char					*ft_strmapi(char const *s,
							char (*f)(unsigned int, char));
char					*ft_strnstr(const char *s1, const char *s2, size_t len);
int						ft_strcmp(const char *s1, const char *s2);
char					*ft_strmcat(char *src, char *add);
char					*ft_strmcatn(int n, char *s1, char *s2, ...);
long long int			ft_atoll(char *str);
void					free_dtab(char **dtab);
char					*ft_insert_str(char *str, int i, int k, char *insert);
char					*ft_ctostr(int size, char c);
char					**ft_dtabdup(char **src);

#endif
