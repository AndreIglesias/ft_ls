/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:23:50 by ciglesia          #+#    #+#             */
/*   Updated: 2020/11/12 00:56:37 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void	print_files(t_list *files, t_collection *info)
{
	while (files)
	{
		ft_printf("%s  ", (char *)files->obj);
		files = files->next;
	}
	if (info->flags.files)
		ft_printf("\n");
}

int		is_dot(char *path)
{
	int i;
	int	slash_pos;

	i = 0;
	slash_pos = 0;
	while (path[i])
	{
		if (path[i] == '/')
			slash_pos = i;
		i++;
	}
	if (slash_pos == 0)
		slash_pos = -1;
	if (path[slash_pos + 1] && path[slash_pos + 1] == '.')
	{
		if (!path[slash_pos + 2])
			return (1);
		if ((path[slash_pos + 2] && path[slash_pos + 2] == '.') &&
			!path[slash_pos + 3])
			return (2);
		return (3);
	}
	return (0);
}

void	dir_content(char *path, DIR *pdir, t_collection *info)
{
	t_dir	*d;
	t_list	*new;
	char	*straux;
	char	*pathdir;

	while ((d = readdir(pdir)) != NULL)
	{
		if (is_dot(d->d_name) == 2)//////////////////////////////
			continue ;
		if (path)
		{
			straux = ft_strjoin(path, "/");
			pathdir = ft_strjoin(straux, d->d_name);
			new = ft_lstnew(pathdir, sizeof(char) * ft_strlen(pathdir));
			if (is_dir(pathdir))
				ft_lstadd(&info->dirs, new);
			ft_lstadd(&info->dir_content, new);
			free(straux);
			free(pathdir);
			continue ;
		}
		new = ft_lstnew(d->d_name, sizeof(char) * ft_strlen(d->d_name));
		if (is_dir(d->d_name))
			ft_lstadd(&info->dirs, new);
		ft_lstadd(&info->dir_content, new);
	}
}

void	print_content(t_list *content, char *dir, t_collection *info)
{
	char	*path;
	char	*straux;

	if (info->flags.files || info->flags.dirs->next || info->flags.big_r)
		ft_printf("%s:\n", dir);
	while (content)
	{
		if (!is_dot((char *)content->obj) || ((is_dot((char *)content->obj) && info->flags.a)))
		{
			straux = ft_strjoin(dir, "/");
			path = ft_strjoin(straux, (char *)content->obj);
			if (is_dir(path))
				ft_printf(BLUE"%s  "E0M, (char *)content->obj);
			else
				ft_printf("%s  ", (char *)content->obj);
			free(straux);
			free(path);
		}
		content = content->next;
	}
}
void	print_dirs(char *path, t_list *dirs, t_collection *info)
{
	DIR		*pdir;

	while (dirs)
	{
		info->dir_content = NULL;
		info->dirs = NULL;
		if ((pdir = opendir((char *)dirs->obj)) == NULL)
			return ;
		dir_content(path, pdir, info);
		print_content(info->dir_content, (char *)dirs->obj, info);
		closedir(pdir);
		ft_printf("\n");
		if (dirs->next || info->flags.big_r)
			ft_printf("\n");
		if (is_dot((char *)info->dirs->obj) != 1 && is_dot((char *)info->dirs->obj) != 2 && info->flags.big_r)
		{
			ft_printf("{%s - %s}\n", (char*)info->dirs->obj, (char *)dirs->obj);
			print_dirs((char *)info->dirs->obj, info->dirs, info);
		}
		dirs = dirs->next;
	}
}

void	execute_options(t_collection *info)
{
	print_files(info->flags.files, info);
	//while for each dirs path (not NULL)
	print_dirs(NULL, info->flags.dirs, info);

	//if (info->flags.big_r)
	//	print_dirs(dirs->inner)
	//sort flags->files flags->dirs alphabetically, by time or reverse
	//obtain list & sort alphabetically, by time or reverse
}
