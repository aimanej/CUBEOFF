/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayboudya <ayboudya@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 22:12:30 by ayboudya          #+#    #+#             */
/*   Updated: 2025/11/19 05:06:37 by ayboudya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*ft_strchr(char *str, int c);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strcmp(char *str1, char *str2);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strdup(char *str);
size_t	ft_strlen(char *str);
char	*get_next_line(int fd);
char	*test2(char *line);
char	*test(char *line);
char	*read_f(int fd, char *holder);
#endif