/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lsail.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:06:52 by ciglesia          #+#    #+#             */
/*   Updated: 2020/11/19 18:44:38 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sail.h"

int		main(int ac, char **av)
{
	if (ac <= 2)
	{
		if (valid_input(ac, av) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		display_files();
	}
	else
	{
		ft_printf_fd(2, ERROR": lsail takes only one parameter.\n"E0M);
		print_usage();
	}
	return (EXIT_SUCCESS);
}
