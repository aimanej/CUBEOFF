/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aijadid <aijadid@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 22:12:13 by ayboudya          #+#    #+#             */
/*   Updated: 2025/12/04 19:02:09 by aijadid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_strdup(char *str)
{
	int		i;
	char	*res;

	i = 0;
	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	while (str[i])
	{
		res[i] = str[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	p = malloc(len + 1);
	if (!p)
		return (NULL);
	while (i < len)
	{
		p[i] = s[start];
		i++;
		start++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*p;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1)
		s1 = "";
	if (!s1 || !s2)
		return (NULL);
	p = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!p)
		return (NULL);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		p[i] = s2[j];
		i++;
		j++;
	}
	return (p[i] = '\0', p);
}

char	*ft_strchr(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return ((char *)&str[i + 1]);
		i++;
	}
	if (str[i] == c)
		return ((char *)&str[i + 1]);
	return (NULL);
}