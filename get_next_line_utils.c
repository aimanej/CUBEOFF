/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aijadid <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 22:11:26 by aijadid           #+#    #+#             */
/*   Updated: 2024/12/09 23:40:34 by aijadid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	int	t;

	t = 0;
	while (str[t])
		t++;
	return (t);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	size_t	t;
	int		i;

	i = 0;
	t = ft_strlen(s);
	str = malloc(t + 1);
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s) - start)
		ret = malloc(ft_strlen(s) - start + 1);
	else
		ret = malloc(len + 1);
	if (!ret)
		return (NULL);
	while (s[start] && len > 0)
	{
		ret[i] = s[start];
		start++;
		i++;
		len--;
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	t;
	size_t	i;

	i = 0;
	if (!s1)
		return (ft_substr(s2, 0, ft_strlen(s2)));
	t = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = malloc(t);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	t = 0;
	while (s2[t])
	{
		str[i] = s2[t];
		i++;
		t++;
	}
	str[i] = '\0';
	return (str);
}
