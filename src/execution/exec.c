/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:23:50 by ciglesia          #+#    #+#             */
/*   Updated: 2020/11/20 00:09:09 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

void print_type(mode_t imode)
{
	if (S_ISLNK(imode))
		ft_printf("l");
	if (S_ISREG(imode))
		ft_printf("-");
	if (S_ISDIR(imode))
		ft_printf("d");
	if (S_ISBLK(imode))
		ft_printf("b");
	if (S_ISCHR(imode))
		ft_printf("c");
	if (S_ISSOCK(imode))
		ft_printf("s");
	if (S_ISFIFO(imode))
		ft_printf("p");
}

void	print_user(uid_t st_uid)
{
	struct passwd *user;

	user = getpwuid(st_uid);
	ft_printf("%s ", user->pw_name);
}

void	print_grp(gid_t st_gid)
{
	struct group *grp;

	grp = getgrgid(st_gid);
	ft_printf("%s ", grp->gr_name);
}

void	print_permissions(mode_t st_mode)
{
		ft_printf("%c", (st_mode & S_IRUSR) ? 'r' : '-');
		ft_printf("%c", (st_mode & S_IWUSR) ? 'w' : '-');
		ft_printf("%c", (st_mode & S_IXUSR) ? 'x' : '-');
		ft_printf("%c", (st_mode & S_IRGRP) ? 'r' : '-');
		ft_printf("%c", (st_mode & S_IWGRP) ? 'w' : '-');
		ft_printf("%c", (st_mode & S_IXGRP) ? 'x' : '-');
		ft_printf("%c", (st_mode & S_IROTH) ? 'r' : '-');
		ft_printf("%c", (st_mode & S_IWOTH) ? 'w' : '-');
		ft_printf("%c", (st_mode & S_IXOTH) ? 'x' : '-');
		ft_printf(". ");
}

void	print_element(char *cont, t_collection *info)
{
	if (!is_dot(cont) || ((is_dot(cont) && info->flags.a)))
	{
		if (info->flags.l)
		{
			stat(cont, &info->buf);
			print_type(info->buf.st_mode);
			print_permissions(info->buf.st_mode);
			ft_printf("%d ", info->buf.st_nlink);
			print_user(info->buf.st_uid);
			print_grp(info->buf.st_gid);
			ft_printf("%5d ", info->buf.st_size);
			ft_printf("%.12s ", &ctime(&info->buf.st_mtim.tv_sec)[4]);
		}
		if (is_dir(cont))
			ft_printf(BOLD""CEL"%s  "E0M, after_path(cont));
		else
			ft_printf("%s  ", after_path(cont));
		if (info->flags.l)
			ft_printf("\n");
	}
}

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
	while (content)
	{
		cont = (char *)content->obj;
		print_element(cont, info);
		content = content->next;
	}
	if (next_notdot(iscont) && !info->flags.l)
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
			sort_dirs(info->dirs, info->dir_content, info);
			if (path || (!path && dirs != felem))
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
	if (info->flags.l)
		ft_printf("total\n");
	sort_dirs(info->flags.files, info->flags.dirs, info);
	print_files(info->flags.files, info);
	if (info->flags.files && info->flags.dirs)
		ft_printf("\n");
	print_dirs(NULL, info->flags.dirs, info);
}
