/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 12:42:20 by ciglesia          #+#    #+#             */
/*   Updated: 2020/11/11 13:30:19 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

static void		init_flags(t_flags *flags)
{
	flags->l = 0;
	flags->a = 0;
	flags->r = 0;
	flags->big_r = 0;
	flags->t = 0;
	flags->options = NULL;
}

void			load_options(char *options, t_flags *flags)
{
	unsigned int i;

	i = 0;
	while (i < ft_strlen(options))
	{
		if (options[i] == 'l')
			flags->l = 1;
		if (options[i] == 'a')
			flags->a = 1;
		if (options[i] == 'r')
			flags->r = 1;
		if (options[i] == 'R')
			flags->big_r = 1;
		if (options[i] == 't')
			flags->t = 1;
		i++;
	}
}

void			load_flags(int ac, char **av, t_flags *flags)
{
	int		i;
	t_list	*new;

	init_flags(flags);
	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '-')
			load_options(&av[i][1], flags);
		if (av[i][0] != '-')
		{
			new = ft_lstnew(av[i], sizeof(char *));
			ft_lstadd(&flags->options, new);
		}
		i++;
	}
}
