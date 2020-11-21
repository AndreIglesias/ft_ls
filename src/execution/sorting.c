/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:54:48 by ciglesia          #+#    #+#             */
/*   Updated: 2020/11/21 23:38:58 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		alpha_cmp(t_list *a, t_list *b)
{
	char	*lower;
	char	*lower_next;
	char	*tmp;
	int		ret;

	tmp = ft_lowercase(after_path(a->obj));
	lower = ft_emptydots(tmp);
	tmp = ft_lowercase(after_path(b->obj));
	lower_next = ft_emptydots(tmp);
	ret = (ft_strcmp(lower, lower_next) < 0);
	free(lower);
	free(lower_next);
	return (ret);
}

int		time_cmp(t_list *a, t_list *b)
{
	t_stat	buf;
	t_stat	buf_next;

	//lstat(aux->obj, &buf);
	if (lstat(a->obj, &buf) == -1)
		return (0);
	//lstat(aux->next->obj, &buf_next);
	if (lstat(b->obj, &buf_next) == -1)
		return (0);
	return (buf.st_mtime > buf_next.st_mtime);
}
/*
void	alpha_sort(t_list *list)
{
	ft_sorting(list, &alpha_cmp);
}

void	time_sort(t_list *list)
{
	ft_sorting(list, &time_cmp);
}
*/
