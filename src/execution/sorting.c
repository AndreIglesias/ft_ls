/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:54:48 by ciglesia          #+#    #+#             */
/*   Updated: 2020/11/20 12:05:33 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	alpha_cmp(char *lower, char *lower_next, t_list *aux)
{
	char	*swap;

	if (ft_strcmp(lower, lower_next) > 0)
	{
		swap = aux->obj;
		aux->obj = aux->next->obj;
		aux->next->obj = swap;
	}
}
/*
void	time_cmp(char *lower, char *lower_next, t_list *aux)
{
	char	*swap;
	int		lp;
	int		lnp;

	lp = 0;
	lnp = 0;
	if (lower[0] == '.' && lower[1])
		lp = 1;
	if (lower_next[0] == '.' && lower_next[1])
		lnp = 1;
	if (ft_strcmp(&lower[lp], &lower_next[lnp]) > 0)
	{
		swap = aux->obj;
		aux->obj = aux->next->obj;
		aux->next->obj = swap;
	}
}
*/
void	sorting(t_list *list, void f(char *, char *, t_list *))
{
	t_list	*iter;
	t_list	*aux;
	char	*lower;
	char	*lower_next;
	char	*tmp;

	iter = list;
	while (iter && iter->next)
	{
		aux = list;
		while (aux && aux->next)
		{
			tmp = ft_lowercase(after_path(aux->obj));
			lower = ft_emptydots(tmp);
			tmp = ft_lowercase(after_path(aux->next->obj));
			lower_next = ft_emptydots(tmp);
			f(lower, lower_next, aux);
			free(lower);
			free(lower_next);
			aux = aux->next;
		}
		iter = iter->next;
	}
}

void	alpha_sort(t_list *list)
{
	sorting(list, &alpha_cmp);
}
/*
void	time_sort(t_list *list)
{

}
*/
