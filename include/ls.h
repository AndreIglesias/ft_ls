/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 18:06:16 by ciglesia          #+#    #+#             */
/*   Updated: 2020/11/11 13:06:11 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include "libft.h"
# include <dirent.h>

typedef struct dirent	t_dir;

typedef struct			s_flags
{
	int					l;
	int					big_r;
	int					a;
	int					r;
	int					t;
	t_list				*options;
}						t_flags;
/*
typedef struct		s_file
{
	char			*name;

}					t_file;
*/

typedef struct			s_collection
{
	t_flags				flags;
}						t_collection;

/*
** validation
*/

int						valid_input(int ac, char **av);
int						print_usage(void);
int						option_unknown(char o);
int						valid_dirfile(char *filename);

/*
** loading
*/

void					load_flags(int ac, char **av, t_flags *flags);

#endif
