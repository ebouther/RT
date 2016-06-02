/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 10:36:51 by ebouther          #+#    #+#             */
/*   Updated: 2016/06/02 10:53:46 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char		*ft_get_matching_end(char *str, char *obj_start_tag,
				char *obj_end_tag)
{
	int			count;
	int			i;
	size_t		end_len;
	size_t		start_len;

	start_len = ft_strlen(obj_start_tag);
	end_len = ft_strlen(obj_end_tag);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_strncmp(str + i, obj_start_tag, start_len) == 0)
			count++;
		if (ft_strncmp(str + i, obj_end_tag, end_len) == 0)
		{
			if (count != 0)
				count--;
			else
				return (str + i);
		}
		i++;
	}
	return (NULL);
}

static char	*ft_inner(int *end_tag, size_t len, char *ptr[2], char *str)
{
	char	*ret;

	if (end_tag != NULL)
		*end_tag = (int)ptr[1] - (int)str + len + 1;
	if (ptr[1] - (ptr[0] + len + 1) >= 0)
	{
		if (end_tag != NULL)
			*end_tag = (int)ptr[1] - (int)str + len + 1;
		if ((ret = malloc(ptr[1] - (ptr[0] + len) + 1)) == NULL)
			exit(-1);
		ft_strncpy(ret, ptr[0] + len, ptr[1] - (ptr[0] + len));
		ret[ptr[1] - (ptr[0] + len)] = '\0';
		return (ret);
	}
	return (NULL);
}

char		*ft_get_inner(char *str, char *obj, int *end_tag, int *start_tag)
{
	char	*obj_start_tag;
	char	*obj_end_tag;
	char	*ptr[2];
	char	*ret;

	ret = NULL;
	obj_start_tag = ft_strjoin_free(ft_strdup("<"),
			ft_strjoin_free(ft_strdup(obj), ft_strdup(">")));
	obj_end_tag = ft_strjoin_free(ft_strdup("</"),
			ft_strjoin_free(ft_strdup(obj), ft_strdup(">")));
	if ((ptr[0] = ft_strstr(str, obj_start_tag)) != NULL
		&& (ptr[1] = ft_get_matching_end(ptr[0] + 1,
			obj_start_tag, obj_end_tag)) != NULL)
	{
		if (start_tag)
			*start_tag = ptr[0] - str;
		ret = ft_inner(end_tag, ft_strlen(obj_start_tag), ptr, str);
	}
	if (ret == NULL && start_tag)
		*start_tag = -1;
	ft_strdel(&obj_start_tag);
	ft_strdel(&obj_end_tag);
	return (ret);
}
