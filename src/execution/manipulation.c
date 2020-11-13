/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 21:57:51 by ciglesia          #+#    #+#             */
/*   Updated: 2020/11/13 15:10:27 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	alpha_cmp(char *lower, char *lower_next, t_list *aux)
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

void	alpha_sort(t_list *list)
{
	t_list	*iter;
	t_list	*aux;
	char	*lower;
	char	*lower_next;

	iter = list;
	while (iter && iter->next)
	{
		aux = list;
		while (aux && aux->next)
		{
			lower = ft_lowercase(aux->obj);
			lower_next = ft_lowercase(aux->next->obj);
			alpha_cmp(lower, lower_next, aux);
			free(lower);
			free(lower_next);
			aux = aux->next;
		}
		iter = iter->next;
	}
}

/*
void	reverse_sort(t_list *list)
{

}
*/
