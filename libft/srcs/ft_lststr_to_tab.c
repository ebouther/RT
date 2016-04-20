/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lststr_to_tab.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 12:34:38 by jbelless          #+#    #+#             */
/*   Updated: 2015/12/03 12:38:34 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_lststr_to_tab(t_list *lst)
{
	char	**tab;
	int		i;
	t_list	*tmp;

	i = 0;
	tab = NULL;
	if (lst == NULL)
		return (NULL);
	if ((tab = (char**)malloc(sizeof(char*) * ft_lstlen(lst) + 1)) == NULL)
		return (NULL);
	tmp = lst;
	while (tmp)
	{
		if ((tab[i] = (char*)malloc(tmp->content_size)) == NULL)
			return (NULL);
		ft_memcpy(tab[i], (char*)tmp->content, tmp->content_size);
		tmp = tmp->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
