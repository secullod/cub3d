/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: secullod <secullod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 17:43:31 by secullod          #+#    #+#             */
/*   Updated: 2020/07/19 17:43:56 by secullod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*arr;

	i = 0;
	while (s[i])
		i++;
	if (!(arr = malloc((i + 1) * sizeof(char))))
		return (NULL);
	i = -1;
	while (s[++i])
		arr[i] = s[i];
	arr[i] = '\0';
	return (arr);
}

char	*ft_strchr(char *s, int c)
{
	int i;

	i = -1;
	while (s[++i])
		if (s[i] == c)
			return (&s[i]);
	if (!c && s[i] == '\0')
		return ((char *)s + i);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	int		x;
	int		y;
	char	*arr;

	x = -1;
	y = 0;
	len = 0;
	while (s1[len])
		len++;
	while (s2[y++])
		len++;
	if (!(arr = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	while (s1[++x])
		arr[x] = s1[x];
	y = 0;
	while (s2[y])
		arr[x++] = s2[y++];
	arr[x] = '\0';
	return (arr);
}

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*arr;
	size_t	i;

	if (!s || len <= 0 || start >= ft_strlen(s))
		return (ft_strdup(""));
	i = 0;
	if (!(arr = (char *)malloc((len + 1) * sizeof(char))))
		return (NULL);
	while (s[start] && i < len)
	{
		arr[i++] = s[start];
		start++;
	}
	arr[i] = '\0';
	return (arr);
}
