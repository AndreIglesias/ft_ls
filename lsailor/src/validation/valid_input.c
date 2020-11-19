/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 18:29:05 by ciglesia          #+#    #+#             */
/*   Updated: 2020/11/19 18:40:52 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sail.h"

int	print_usage(void)
{
	ft_printf_fd(2, BOLD"USAGE:\t"E0M"lsail [DIR]\n");
	return (0);
}

int		is_dir(char *dirname)
{
	DIR	*pdir;

	if ((pdir = opendir(dirname)) == NULL)
		return (0);
	closedir(pdir);
	return (1);
}

int		valid_input(int ac, char **av)
{
	if (ac > 1 && !is_dir(av[1]))
	{
		ft_printf_fd(2, ERROR": lsailor: The optional parameter has to be a\
 valid directory.\n"E0M);
		return (EXIT_FAILURE + print_usage());
	}
	return (EXIT_SUCCESS);
}
