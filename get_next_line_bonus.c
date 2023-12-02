/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-laa <oait-laa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 12:51:39 by oait-laa          #+#    #+#             */
/*   Updated: 2023/11/27 20:25:24 by oait-laa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

static void	*cleaner(char **holder, char **save, char *tmp, int fd)
{
	if (fd >= 0)
	{
		free(*holder);
		*holder = NULL;
	}
	if (save != NULL)
	{
		free(*save);
		*save = NULL;
	}
	if (tmp != NULL)
	{
		free(tmp);
		tmp = NULL;
	}
	return (NULL);
}

static char	*fill_var(char *holder, char **tmp, int r_bytes, int fd)
{
	char	*tmp2;

	tmp2 = holder;
	(*tmp)[r_bytes] = '\0';
	if (holder == NULL)
	{
		holder = ft_strdup(*tmp);
		if (!holder)
			return (cleaner(tmp, NULL, NULL, fd));
		free(*tmp);
		*tmp = NULL;
	}
	else
	{
		holder = ft_strjoin(tmp2, *tmp);
		if (!holder)
		{
			return (cleaner(tmp, &tmp2, NULL, fd));
		}
		cleaner(tmp, &tmp2, NULL, fd);
	}
	*tmp = malloc(BUFFER_SIZE + 1);
	if (*tmp == NULL)
		return (cleaner(&holder, NULL, NULL, fd));
	return (holder);
}

static char	*send_line(char **holder, char *tmp, int fd)
{
	char	*save;
	char	*retu;

	save = ft_strdup(ft_strchr(*holder, '\n'));
	if (!save)
		return (cleaner(holder, &save, tmp, fd));
	refill(*holder);
	retu = ft_strdup(*holder);
	if (!retu)
		return (cleaner(holder, &save, tmp, fd));
	free(*holder);
	*holder = ft_strdup(save + 1);
	if (!*holder)
		return (cleaner(&retu, &save, tmp, fd));
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
	static char	*holder[OPEN_MAX];
	char		*tmp;
	char		*retu;
	int			r_bytes;

	tmp = malloc(BUFFER_SIZE + 1);
	if (fd < 0 || read(fd, tmp, 0) < 0 || fd > OPEN_MAX || !tmp)
		return (cleaner(&holder[fd], &tmp, NULL, fd));
	r_bytes = read(fd, tmp, BUFFER_SIZE);
	while (r_bytes > 0 || (has_endl(holder[fd]) && r_bytes == 0))
	{
		holder[fd] = fill_var(holder[fd], &tmp, r_bytes, fd);
		if (!holder[fd])
			return (NULL);
		if (has_endl(holder[fd]) || holder[fd][r_bytes - 1] == '\n')
			return (send_line(&holder[fd], tmp, fd));
		r_bytes = read(fd, tmp, BUFFER_SIZE);
	}
	if (holder[fd] != 0 && holder[fd][0] != '\0')
	{
		retu = ft_strdup(holder[fd]);
		cleaner(&holder[fd], &tmp, NULL, fd);
		return (retu);
	}
	return (cleaner(&tmp, NULL, NULL, fd));
}
