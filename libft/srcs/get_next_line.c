/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 12:44:26 by jbelless          #+#    #+#             */
/*   Updated: 2016/02/25 10:54:09 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define BUFF_SIZE 1

static char	*ft_strjoin_free(char *line, char *buff)
{
	char *vid;

	vid = ft_strjoin(line, buff);
	free(line);
	return (vid);
}

static int	ft_cop(char *str1, char **line, char *str2)
{
	*(ft_strchr(str1, '\n')) = '\0';
	*line = ft_strjoin_free(*line, str1);
	ft_strcpy(str2, str1 + ft_strlen(str1) + 1);
	if (str1 != str2)
		free(str1);
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	char		*buff;
	int			tete;
	static char	*rest;

	buff = ft_strnew(BUFF_SIZE + 1);
	if (fd < 0 || line == NULL)
		return (-1);
	free(*line);
	*line = ft_strnew(1);
	if (rest == NULL)
		rest = ft_strnew(BUFF_SIZE);
	if (ft_strchr(rest, '\n') != NULL)
		return (ft_cop(rest, line, rest));
	*line = ft_strjoin_free(*line, rest);
	while ((tete = read(fd, buff, BUFF_SIZE)) && tete != -1)
	{
		buff[tete] = 0;
		if (ft_strchr(buff, '\n') != NULL)
			return (ft_cop(buff, line, rest));
		else
			*line = ft_strjoin_free(*line, buff);
	}
	free(buff);
	return (tete);
}
