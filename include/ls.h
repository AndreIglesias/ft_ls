/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 18:06:16 by ciglesia          #+#    #+#             */
/*   Updated: 2020/11/21 20:44:36 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_H
# define LS_H

# include "libft.h"
# include <dirent.h>
# include <sys/stat.h>
# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>

typedef struct dirent	t_dir;

typedef struct stat		t_stat;

typedef struct			s_flags
{
	int					l;
	int					big_r;
	int					a;
	int					r;
	int					t;
	t_list				*files;
	t_list				*dirs;
}						t_flags;

typedef struct			s_collection
{
	t_flags				flags;
	t_list				*dir_content;
	t_list				**dc;
	size_t				ndc;
	t_list				*dirs;
	t_list				**dd;
	size_t				ndd;
	int					total;
	size_t				size_spacing;
	size_t				links_spacing;
	struct stat 		buf;
}						t_collection;

/*
** validation
*/

int						valid_input(int ac, char **av);
int						print_usage(void);
int						option_unknown(char o);
int						valid_dirfile(char *filename);
int						is_dir(char *dirname);
int						is_file(char *filename);
int						can_openf(char *filename);

/*
** loading
*/

void					load_options(int ac, char **av, t_flags *flags,
														t_collection *info);
void					free_colldir(t_collection *info);
void					free_dirs(t_list *dirs);

/*
** execution
*/

void					execute_options(t_collection *info);
void					alpha_sort(t_list *list);
int		alpha_cmp(t_list *a, t_list *b);
int		time_cmp(t_list *a, t_list *b);
void					time_sort(t_list *list);
void					print_files(t_list *files, t_collection *info);
char					*after_path(char *path);
int						is_dot(char *path);
char					*next_notdot(t_list *dirs);
void					sort_dirs(t_list *d1, t_list *d2, t_collection *info);
void					print_element(char *cont, t_collection *info);
void					n_content(char *path, t_collection *info);

#endif
