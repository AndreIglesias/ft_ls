/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sail.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:06:28 by ciglesia          #+#    #+#             */
/*   Updated: 2020/11/19 20:51:12 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SAIL_H
# define SAIL_H

# include "libft.h"
# include <dirent.h>
# include <ncurses.h>
# include <locale.h>

/*
** interface
*/

void	display_files(void);

/*
** validation
*/

int		valid_input(int ac, char **av);
int		print_usage(void);

#endif
