/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:23:50 by ciglesia          #+#    #+#             */
/*   Updated: 2020/11/20 16:28:44 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	print_content(t_list *content, char *dir, t_collection *info)
{
	char	*cont;
	t_list	*iscont;

	iscont = content;
	if (info->flags.files || info->flags.dirs->next || info->flags.big_r)
	{
		if (!ft_strcmp(".", info->flags.dirs->obj) && !info->flags.dirs->next &&
			info->flags.big_r && ft_strcmp(".", dir))
			ft_printf("./%s:\n", dir);
		else
			ft_printf("%s:\n", dir);
	}
	if (info->flags.l)
		ft_printf("total %d\n", info->total / 2);
	while (content)
	{
		cont = (char *)content->obj;
		print_element(cont, info);
		content = content->next;
	}
	if (next_notdot(iscont) && !info->flags.l)
		ft_printf("\n");
}

void	add_content(char *content, t_collection *info)
{
	t_list	*new;

	if (is_dir(content))
	{
		new = ft_lstnew2(ft_strdup(content), sizeof(char) * ft_strlen(content));
		ft_lstadd(&info->dirs, new);
	}
	new = ft_lstnew2(ft_strdup(content), sizeof(char) * ft_strlen(content));
	ft_lstadd(&info->dir_content, new);
}

int		content_measurements(char *path, t_collection *info)
{
	lstat(path, &info->buf);
	add_content(path, info);
	if (ft_sizei(info->buf.st_size) > info->size_spacing)
		info->size_spacing = ft_sizei(info->buf.st_size);
	if (!(is_dot(path) && !info->flags.a))
		return (info->buf.st_blocks);
	return (0);
}

void	dir_content(char *path, DIR *pdir, t_collection *info)
{
	t_dir	*d;
	char	*straux;
	char	*pathdir;
	int		total;

	total = 0;
	info->size_spacing = 0;
	while ((d = readdir(pdir)) != NULL)
	{
		if (path)
		{
			straux = ft_strjoin(path, "/");
			pathdir = ft_strjoin(straux, d->d_name);
			total += content_measurements(pathdir, info);
			free(straux);
			free(pathdir);
		}
		else
			total += content_measurements(d->d_name, info);
	}
	info->total = total;
}

void	print_dirs(char *path, t_list *dirs, t_collection *info)
{
	DIR		*pdir;
	char	*dir;
	t_list	*felem;

	felem = dirs;
	while (dirs)
	{
		dir = (char *)dirs->obj;
		if (!(is_dot(dir) > 0 && !info->flags.a && path) &&
		(!path || (path && is_dot(dir) != 2 && is_dot(dir) != 1)))
		{
			free_colldir(info);
			if ((pdir = opendir(dir)) == NULL)
				return ;
			if (path || (!path && dirs != felem))
				ft_printf("\n");
			dir_content((ft_strcmp(dir, ".") == 0) ? NULL : dir, pdir, info);
			sort_dirs(info->dirs, info->dir_content, info);
			print_content(info->dir_content, dir, info);
			closedir(pdir);
			if (info->flags.big_r && info->dirs && next_notdot(info->dirs))
				print_dirs(next_notdot(info->dirs), info->dirs, info);
		}
		dirs = dirs->next;
	}
}

void	execute_options(t_collection *info)
{
	sort_dirs(info->flags.files, info->flags.dirs, info);
	print_files(info->flags.files, info);
	if (info->flags.files && info->flags.dirs)
		ft_printf("\n");
	print_dirs(NULL, info->flags.dirs, info);
}
