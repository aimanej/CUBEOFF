/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aijadid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 22:03:40 by aijadid           #+#    #+#             */
/*   Updated: 2024/12/10 15:45:45 by aijadid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

int	newline(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*extract_line_tmp_update(char **store, char **tmp, int r)
{
	int		newindex;
	char	*line;

	newindex = newline(*store);
	if (newindex >= 0)
	{
		*tmp = ft_substr(*store, newindex + 1, ft_strlen(*store) - newindex);
		line = ft_substr(*store, 0, newindex + 1);
		free(*store);
		*store = NULL;
		return (line);
	}
	if (r < BUFFER_SIZE && newindex < 0)
	{
		return (*store);
	}
	return (NULL);
}

int	read_and_store(int fd, char **buf, char **store)
{
	int		iread;
	char	*newstore;

	*buf = malloc(BUFFER_SIZE + 1);
	if (!*buf)
		return (-1);
	iread = read(fd, *buf, BUFFER_SIZE);
	if (iread > 0)
	{
		(*buf)[iread] = '\0';
		newstore = ft_strjoin(*store, *buf);
		free(*store);
		*store = newstore;
	}
	free(*buf);
	return (iread);
}

void	checker(char **tmp, char **store)
{
	if (*tmp)
	{
		*store = ft_strdup(*tmp);
		free(*tmp);
		*tmp = NULL;
	}
}

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*tmp;
	char		*store;
	char		*line;
	int			r;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	store = NULL;
	checker(&tmp, &store);
	r = BUFFER_SIZE;
	while (1)
	{
		line = extract_line_tmp_update(&store, &tmp, r);
		if (line)
			return (line);
		r = read_and_store(fd, &buf, &store);
		if (r < 1)
		{
			if (store && *store)
				return (store);
			free(store);
			return (NULL);
		}
	}
}

// int	main(void)
// {
// 	int		fd;
// 	char	*b;
// 	int		i;

// 	i = 0;
// 	fd = open("map.ber", O_CREAT | O_RDWR, 777);
// 	// b = get_next_line(fd);
// 	// printf("\nnew line ladies and gents -->  ''%s''   \n", b);
// 	// free(b);
// 	// b = get_next_line(fd);
// 	// printf("\nnew line ladies and gents -->  ''%s''   \n", b);
// 	// free(b);

// 		while ((b = get_next_line(fd)) != NULL)
// 		{
// 			printf("\nnew line ladies and gents -->  ''%s''   \n", b);
// 			free(b);
// 		}
// }
