/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebouther <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 10:36:51 by ebouther          #+#    #+#             */
/*   Updated: 2016/04/25 12:03:49 by ebouther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

char		*ft_get_inner(char	*str, char *obj)
{
	char	*obj_start_tag;
	char	*obj_end_tag;
	char	*ptr;
	char	*ptr2;
	size_t	len;
	char	*ret;

	ptr = NULL;
	len = ft_strlen(obj_start_tag);
	obj_start_tag = ft_strjoin_free(ft_strdup("<"),
		ft_strjoin_free(ft_strdup(obj), ft_strdup(">")));
	obj_end_tag = ft_strjoin_free(ft_strdup("</"),
		ft_strjoin_free(ft_strdup(obj), ft_strdup(">")));
	if ((ptr = ft_strstr(str, obj_start_tag)) != NULL
		&& (ptr2 = ft_strstr(str, obj_end_tag)) != NULL)
	{
		if ((ret = malloc(sizeof(char) * (ptr2 - (ptr + len) + 1))) == NULL)
			exit(-1);
		ft_strncpy(ret, ptr + len + 1,	ptr2 - (ptr + len + 1));
		ret[ptr2 - (ptr + len + 1)] = '\0';
		return (ret);
	}
	return (NULL);
}

int			ft_parse_scene(char *file, t_env *e)
{
	int	i;

	i = 0;
	(void)e;
	ft_putstr(ft_get_inner(file, "scene"));
	return (0);
}
