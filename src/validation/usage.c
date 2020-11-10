/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 22:00:10 by ciglesia          #+#    #+#             */
/*   Updated: 2020/11/10 22:58:10 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int	option_unknown(char o)
{
	if (o)
		ft_printf_fd(2, ERROR": "BLINK"Unknown option -%c\n"E0M, o);
	else
		ft_printf_fd(2, ERROR": "BLINK"Unknown option -(empty)\n"E0M);
	return (0);
}

int	print_usage(void)
{
	ft_printf_fd(2, BOLD"USAGE:\n\t\t"E0M"ls [OPTION]... [FILE]...\n");
	ft_printf_fd(2, BOLD"DESCRIPTION:\n\t\t"E0M"List information about the\
 FILEs (the current directory by default).\n");
	ft_printf_fd(2, "\t\tSort entries alphabetically if -t is not specified.");
	ft_printf_fd(2, BOLD"\nOPTIONS:\n"E0M);
	ft_printf_fd(2, BOLD"-l:\t\t"E0M"Use a long listing format\n");
	ft_printf_fd(2, BOLD"-a:\t\t"E0M"Do not ignore entries starting with .\n");
	ft_printf_fd(2, BOLD"-r:\t\t"E0M"Reverse order while sorting\n");
	ft_printf_fd(2, BOLD"-R:\t\t"E0M"List subdirectories recursively\n");
	ft_printf_fd(2, BOLD"-t:\t\t"E0M"Sort by modification time, newest\
 first\n");
	return (0);
}
