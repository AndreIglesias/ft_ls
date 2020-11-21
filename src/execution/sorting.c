/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:54:48 by ciglesia          #+#    #+#             */
/*   Updated: 2020/11/21 13:10:03 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	alpha_cmp(t_list *aux)
{
	char	*swap;
	char	*lower;
	char	*lower_next;
	char	*tmp;

	tmp = ft_lowercase(after_path(aux->obj));
	lower = ft_emptydots(tmp);
	tmp = ft_lowercase(after_path(aux->next->obj));
	lower_next = ft_emptydots(tmp);
	if (ft_strcmp(lower, lower_next) > 0)
	{
		swap = aux->obj;
		aux->obj = aux->next->obj;
		aux->next->obj = swap;
	}
	free(lower);
	free(lower_next);
}

void	time_cmp(t_list *aux)
{
	char	*swap;
	t_stat	buf;
	t_stat	buf_next;

	//lstat(aux->obj, &buf);
	if (lstat(aux->obj, &buf) == -1)
		return ;
	//lstat(aux->next->obj, &buf_next);
	if (lstat(aux->next->obj, &buf_next) == -1)
		return ;
	if (buf.st_mtime < buf_next.st_mtime)
	{
		swap = aux->obj;
		aux->obj = aux->next->obj;
		aux->next->obj = swap;
	}
}

void	alpha_sort(t_list *list)
{
	ft_sorting(list, &alpha_cmp);
}

void	time_sort(t_list *list)
{
	ft_sorting(list, &time_cmp);
}
