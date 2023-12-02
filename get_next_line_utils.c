/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 20:05:28 by oait-laa          #+#    #+#             */
/*   Updated: 2023/11/20 15:34:36 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s1)
{
	char	*pntr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1[i])
		i++;
	pntr = malloc(i + 1);
	if (!pntr)
		return (NULL);
	while (j < i)
	{
		pntr[j] = s1[j];
		j++;
	}
	pntr[j] = '\0';
	return (pntr);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		s1_len;
	int		s2_len;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = malloc(s1_len + s2_len + 1);
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

void	refill(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			str[i + 1] = '\0';
		}
		i++;
	}
}

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	c2;

	i = 0;
	c2 = (unsigned char)c;
	while (s[i])
	{
		if (c2 == s[i])
			return ((char *)(s + i));
		i++;
	}
	if (c2 == '\0')
		return ((char *)(s + i));
	return (NULL);
}
