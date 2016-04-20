/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbelless <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/30 11:41:47 by jbelless          #+#    #+#             */
/*   Updated: 2015/12/03 11:30:08 by jbelless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *))
{
	t_list	*res;

	res = NULL;
	if (lst == NULL || f == NULL)
		return (NULL);
	res = ft_lstnew(f(lst)->content, f(lst)->content_size);
	if (!res)
		return (NULL);
	if (lst->next == NULL)
		res->next = NULL;
	else
		res->next = ft_lstmap(lst->next, f);
	return (res);
}
