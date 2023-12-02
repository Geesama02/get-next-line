/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:51:39 by oait-laa          #+#    #+#             */
/*   Updated: 2023/11/28 13:52:18 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

static int	has_endl(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if ((str[i] == '\n' && str[i + 1] != '\0') || str[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

static void	*cleaner(char **holder, char **save, char *tmp)
{
	free(*holder);
	*holder = NULL;
	if (save != NULL)
		free(*save);
	if (tmp != NULL)
		free(tmp);
	return (NULL);
}

static char	*fill_var(char *holder, char **tmp, int r_bytes)
{
	char	*tmp2;

	tmp2 = holder;
	(*tmp)[r_bytes] = '\0';
	if (holder == NULL)
	{
		holder = ft_strdup(*tmp);
		if (!holder)
			return (cleaner(tmp, NULL, NULL));
		free(*tmp);
		*tmp = NULL;
	}
	else
	{
		holder = ft_strjoin(tmp2, *tmp);
		if (!holder)
		{
			return (cleaner(tmp, &tmp2, NULL));
		}
		cleaner(tmp, &tmp2, NULL);
	}
	*tmp = malloc(BUFFER_SIZE + 1);
	if (*tmp == NULL)
		return (cleaner(&holder, NULL, NULL));
	return (holder);
}

static char	*send_line(char **holder, char *tmp)
{
	char	*save;
	char	*retu;

	save = ft_strdup(ft_strchr(*holder, '\n'));
	if (!save)
		return (cleaner(holder, &save, tmp));
	refill(*holder);
	retu = ft_strdup(*holder);
	if (!retu)
		return (cleaner(holder, &save, tmp));
	free(*holder);
	*holder = ft_strdup(save + 1);
	if (!*holder)
		return (cleaner(&retu, &save, tmp));
	if ((*holder)[0] == '\0')
	{
		free(*holder);
		*holder = NULL;
	}
	free(save);
	free(tmp);
	return (retu);
}

char	*get_next_line(int fd)
{
	static char	*holder;
	char		*tmp;
	char		*retu;
	int			r_bytes;

	tmp = malloc(BUFFER_SIZE + 1);
	if (fd < 0 || read(fd, tmp, 0) < 0 || fd > OPEN_MAX || !tmp)
		return (cleaner(&holder, &tmp, NULL));
	r_bytes = read(fd, tmp, BUFFER_SIZE);
	while (r_bytes > 0 || (has_endl(holder) && r_bytes == 0))
	{
		holder = fill_var(holder, &tmp, r_bytes);
		if (!holder)
			return (NULL);
		if (has_endl(holder) || holder[r_bytes - 1] == '\n')
			return (send_line(&holder, tmp));
		r_bytes = read(fd, tmp, BUFFER_SIZE);
	}
	if (holder != 0 && holder[0] != '\0')
	{
		retu = ft_strdup(holder);
		cleaner(&holder, &tmp, NULL);
		return (retu);
	}
	return (cleaner(&tmp, NULL, NULL));
}
