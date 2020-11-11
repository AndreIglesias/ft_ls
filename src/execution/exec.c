/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:23:50 by ciglesia          #+#    #+#             */
/*   Updated: 2020/11/11 23:41:19 by ciglesia         ###   ########.fr       */
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
			new = ft_lstnew(pathdir, sizeof(char) * ft_strlen(d->d_name));
			if (is_dir(pathdir))
				ft_lstadd(&info->dirs, new);
			ft_lstadd(&info->dir_content, new);
			free(straux);
			free(pathdir);
			return ;
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

	if (info->flags.files || info->flags.dirs->next)
		ft_printf("%s:\n", dir);
	while (content)
	{
		if (((char *)content->obj)[0] != '.' ||
			(((char *)content->obj)[0] == '.' && info->flags.a))
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
		if (dirs->next)
			ft_printf("\n");
		ft_printf("{%s}\n", (char*)info->dirs->obj);
		//print_dirs((char *)info->dirs->obj, info->dirs, info);
		dirs = dirs->next;
	}
}

void	execute_options(t_collection *info)
{
	print_files(info->flags.files, info);
	print_dirs(NULL, info->flags.dirs, info);

	//if (info->flags.big_r)
	//	print_dirs(dirs->inner)
	//sort flags->files flags->dirs alphabetically, by time or reverse
	//obtain list & sort alphabetically, by time or reverse
}
