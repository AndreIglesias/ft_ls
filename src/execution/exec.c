/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:23:50 by ciglesia          #+#    #+#             */
/*   Updated: 2020/11/12 20:02:28 by ciglesia         ###   ########.fr       */
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

	if (!path)
		return (-1);
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
	ft_printf("\n");
}

void	dir_content(char *path, DIR *pdir, t_collection *info)
{
	t_dir	*d;
	t_list	*new;
	char	*straux;
	char	*pathdir;

	while ((d = readdir(pdir)) != NULL)
	{
		if (path)
		{
			straux = ft_strjoin(path, "/");
			pathdir = ft_strjoin(straux, d->d_name);
			//ft_printf(RED"ispath %s %s\n", path, d->d_name);
			if (is_dir(pathdir))
			{
				new = ft_lstnew(pathdir, sizeof(char) * ft_strlen(pathdir));
				ft_lstadd(&info->dirs, new);
			}
			new = ft_lstnew(pathdir, sizeof(char) * ft_strlen(pathdir));
			ft_lstadd(&info->dir_content, new);
//			if (is_dir(pathdir))
//				ft_printf(BLUE "%s is dir\n"E0M, pathdir);
//			else
//				ft_printf(RED "%s is not dir\n"E0M, pathdir);
			free(straux);
			free(pathdir);
			continue ;
		}
		if (is_dir(d->d_name))
		{
			new = ft_lstnew(d->d_name, sizeof(char) * ft_strlen(d->d_name));
			ft_lstadd(&info->dirs, new);
		}
		new = ft_lstnew(d->d_name, sizeof(char) * ft_strlen(d->d_name));
		ft_lstadd(&info->dir_content, new);
//		if (is_dir(d->d_name))
//				ft_printf(BLUE "%s is dir\n"E0M, d->d_name);
//		else
//			ft_printf(RED "%s is not dir\n"E0M, d->d_name);
	}
}

void	free_colldir(t_collection *info)
{
	info->dir_content = NULL;
	info->dirs = NULL;
}

void	see_dirs(t_list	*dirs)
{
	ft_printf(GREEN"[");
	while (dirs)
	{
		ft_printf("%s ", (char*)dirs->obj);
		dirs = dirs->next;
	}
	ft_printf("]\n"E0M);
}

char	*next_notdot(t_list *dirs)
{

	while (dirs && (is_dot((char *)dirs->obj) == 1 || is_dot((char *)dirs->obj) == 2))
		dirs = dirs->next;
	if (dirs)
		return ((char *)dirs->obj);
	return (NULL);
}

void	print_dirs(char *path, t_list *dirs, t_collection *info)
{
	DIR		*pdir;
	char	*dir;

	while (dirs)
	{
		dir = (char *)dirs->obj;
		if (!(is_dot(dir) > 0 && !info->flags.a && path))
		{
			free_colldir(info);
			if ((pdir = opendir(dir)) == NULL)
				return ;
			if (ft_strcmp(dir, ".") == 0)
				path = NULL;
			else
				path = dir;
			dir_content(path, pdir, info);
//		see_dirs(info->dir_content);
//		see_dirs(info->dirs);
			print_content(info->dir_content, dir, info);
			closedir(pdir);
			if (dirs->next || info->flags.big_r)
				ft_printf("\n");
			if (info->flags.big_r && info->dirs && next_notdot(info->dirs))
			{
				print_dirs(next_notdot(info->dirs), info->dirs, info);
//				info->dirs = info->dirs->next;
			}
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
