/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 18:05:57 by ciglesia          #+#    #+#             */
/*   Updated: 2020/11/12 22:02:03 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int main(int ac, char **av)
{
	t_collection	info;

	if (valid_input(ac, av) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	load_options(ac, av, &info.flags, &info);
	execute_options(&info);
	return (EXIT_SUCCESS);
}
