/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:23:50 by ciglesia          #+#    #+#             */
/*   Updated: 2020/11/17 23:21:23 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

#if 0
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
#endif

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

char	*after_path(char *path)
{
	int i;
	int	slash_pos;

	if (!path || !path[0])
		return (NULL);
	i = 0;
	slash_pos = 0;
	while (path[i])
	{
		if (path[i] == '/' && path[i + 1])
			slash_pos = i;
		i++;
	}
	if (slash_pos == 0)
		slash_pos = -1;
	return (&path[slash_pos + 1]);
}

int		is_dot(char *path)
{
	char	*after;

	after = after_path(path);
	if (after && after[0] && after[0] == '.')
	{
		if (!after[1])
			return (1);
		if (after[1] == '.' && !after[2])
			return (2);
		return (3);
	}
	return (0);
}

char	*next_notdot(t_list *dirs)
{

	while (dirs && (is_dot((char *)dirs->obj) == 1 || is_dot((char *)dirs->obj) == 2))
		dirs = dirs->next;
	if (dirs)
		return ((char *)dirs->obj);
	return (NULL);
}

void	print_content(t_list *content, char *dir, t_collection *info)
{
	char	*cont;
	t_list	*iscont;

	iscont = content;
	if (info->flags.files || info->flags.dirs->next || info->flags.big_r)
	{
		if (!ft_strcmp(".", info->flags.dirs->obj) && !info->flags.dirs->next && info->flags.big_r)
			ft_printf("./%s:\n", dir);
		else
			ft_printf("%s:\n", dir);
	}
	while (content)
	{
		cont = (char *)content->obj;
		if (!is_dot(cont) || ((is_dot(cont) && info->flags.a)))
		{
			if (is_dir(cont))
				ft_printf(BOLD""CEL"%s  "E0M, after_path(cont));
			else
				ft_printf("%s  ", after_path(cont));
		}
		content = content->next;
	}
	if (next_notdot(iscont))
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
			if (is_dir(pathdir))
			{
				new = ft_lstnew2(ft_strdup(pathdir), sizeof(char) * ft_strlen(pathdir));
				ft_lstadd(&info->dirs, new);
			}
			new = ft_lstnew2(ft_strdup(pathdir), sizeof(char) * ft_strlen(pathdir));
			ft_lstadd(&info->dir_content, new);
			free(straux);
			free(pathdir);
			continue ;
		}
		if (is_dir(d->d_name))
		{
			new = ft_lstnew2(ft_strdup(d->d_name), sizeof(char) * ft_strlen(d->d_name));
			ft_lstadd(&info->dirs, new);
		}
		new = ft_lstnew2(ft_strdup(d->d_name), sizeof(char) * ft_strlen(d->d_name));
		ft_lstadd(&info->dir_content, new);
	}
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
			dir_content((ft_strcmp(dir, ".") == 0) ? NULL : dir, pdir, info);
			alpha_sort(info->dirs);
			alpha_sort(info->dir_content);
			if (dirs != felem)
				ft_printf("\n");
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
	alpha_sort(info->flags.files);
	alpha_sort(info->flags.dirs);
	print_files(info->flags.files, info);
	if (info->flags.files && info->flags.dirs)
		ft_printf("\n");
	print_dirs(NULL, info->flags.dirs, info);

	//if (info->flags.big_r)
	//	print_dirs(dirs->inner)
	//sort flags->files flags->dirs alphabetically, by time or reverse
	//obtain list & sort alphabetically, by time or reverse
}
