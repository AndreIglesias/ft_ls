/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:20:15 by ciglesia          #+#    #+#             */
/*   Updated: 2020/11/20 17:55:09 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	free_dirs(t_list *dirs)
{
	t_list	*aux;

	while (dirs)
	{
		aux = dirs->next;
		free(dirs->obj);
		free(dirs);
		dirs = aux;
	}
	dirs = NULL;
}

void	free_colldir(t_collection *info)
{
//	if (info->dir_content)
//		free_dirs(info->dir_content);
//	if (info->dirs)
//		free_dirs(info->dirs);
	info->dir_content = NULL;
	info->dirs = NULL;
}

void		init_collection(t_flags *flags, t_collection *info)
{
	flags->l = 0;
	flags->a = 0;
	flags->r = 0;
	flags->big_r = 0;
	flags->t = 0;
	flags->files = NULL;
	flags->dirs = NULL;
	info->dir_content = NULL;
	info->dirs = NULL;
}

void			load_flags(char *options, t_flags *flags)
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

void			load_allf(int ac, char **av, t_flags *flags)
{
	int		i;

	i = 1;
	while (i < ac)
	{
		if (av[i][0] == '-')
			load_flags(&av[i][1], flags);
		i++;
	}
}


void			load_options(int ac, char **av, t_flags *flags, t_collection *c)
{
	int		i;
	t_list	*new;

	init_collection(flags, c);
	load_allf(ac, av, flags);
	i = 1;
	while (i < ac)
	{
		if (av[i][0] != '-')
		{
			lstat(av[i], &c->buf);
			new = ft_lstnew(av[i], sizeof(char) * ft_strlen(av[i]));
			if (!is_dir(av[i]) || (S_ISLNK(c->buf.st_mode) && c->flags.l))
				ft_lstadd(&flags->files, new);
			else
				ft_lstadd(&flags->dirs, new);
		}
		i++;
	}
	if (!flags->dirs && !flags->files)
	{
		new = ft_lstnew(".", sizeof(char *));
		ft_lstadd(&flags->dirs, new);
	}
}
