/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 18:06:16 by ciglesia          #+#    #+#             */
/*   Updated: 2020/11/10 22:57:33 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		LS_H
# define	LS_H

#include "libft.h"

typedef struct		s_flags
{
	int				l;
	int				big_r;
	int				a;
	int				r;
	int				t;
}					t_flags;

/*
** validation
*/

int					valid_input(int ac, char **av);
int					print_usage(void);
int					option_unknown(char o);

#endif
