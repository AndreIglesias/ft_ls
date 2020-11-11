/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 21:38:53 by ciglesia          #+#    #+#             */
/*   Updated: 2020/11/11 11:28:07 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		are_options(char *options)
{
	unsigned int i;

	if (!ft_strlen(options))
		return (0 + option_unknown(0));
	i = 0;
	while (i < ft_strlen(options))
	{
		if (ft_countchr("larRt", options[i]) == 0)
			return (0 + option_unknown(options[i]));
		i++;
	}
	return (1);
}

int		verify_options(int ac, char **av)
{
	int i;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '-' && !are_options(&av[i][1]))
			return (EXIT_FAILURE);
		if (av[i][0] != '-' && !valid_dirfile(av[i]))
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int		valid_input(int ac, char **av)
{
	if (verify_options(ac, av) == EXIT_FAILURE)
		return (EXIT_FAILURE + print_usage());
	return (EXIT_SUCCESS);
}
