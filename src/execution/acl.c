/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 23:21:00 by ciglesia          #+#    #+#             */
/*   Updated: 2020/11/21 12:14:41 by ciglesia         ###   ########.fr       */
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

void	color_nonlink(char *cont, t_collection *info, int apath)
{
	if (apath == -1 || (!is_dir(cont) && !can_openf(cont) && !apath))
		ft_printf(BOLD""RED"%s"E0M"  ", (apath > 0) ? after_path(cont) : cont);
	else if (S_ISLNK(info->buf.st_mode))
		ft_printf(BOLD""CYAN"%s  "E0M, (apath) ? after_path(cont) : cont);
	else if (info->buf.st_nlink > 1)
		ft_printf(BOLD""GREEN"%s  "E0M, (apath) ? after_path(cont) : cont);
	else if (is_dir(cont))
		ft_printf(BOLD""CEL"%s  "E0M, (apath) ? after_path(cont) : cont);
	else
		ft_printf("%s  ", (apath) ? after_path(cont) : cont);
}

void	color_element(char *cont, t_collection *info, int apath)
{
	char	*buf;
	ssize_t	bufsiz;
	ssize_t	nbytes;

	if (S_ISLNK(info->buf.st_mode) && info->flags.l)
	{
		bufsiz = info->buf.st_size + 1;
		if (info->buf.st_size == 0)
			bufsiz = PATH_MAX;
		buf = malloc(bufsiz);
		nbytes = readlink(cont, buf, bufsiz);
		buf[nbytes] = '\0';
		if (lstat(buf, &info->buf) == -1) {
			ft_printf(BOLD""RED"%s"E0M""BOLD" -> "REVER, after_path(cont));
			color_nonlink(buf, info, -1);
			return ;
		}
		ft_printf(BOLD""CYAN"%s"E0M""BOLD" -> "E0M, after_path(cont));
		color_nonlink(buf, info, 0);
	}
	else
		color_nonlink(cont, info, apath);
}

void	print_element(char *cont, t_collection *info)
{
	int apath;

	if (!is_dot(cont) || ((is_dot(cont) && info->flags.a)))
	{
		apath = 1;
		if (lstat(cont, &info->buf) == -1)
			apath = -1;
		if (info->flags.l)
		{
			print_type(info->buf.st_mode);
			print_permissions(info->buf.st_mode);
			ft_repet(' ', info->links_spacing - ft_sizei(info->buf.st_nlink));
			ft_printf("%lu ", info->buf.st_nlink);
			print_user(info->buf.st_uid);
			print_grp(info->buf.st_gid);
			ft_repet(' ', info->size_spacing - ft_sizei(info->buf.st_size));
			ft_printf("%lu ", info->buf.st_size);
			ft_printf("%.12s ", &ctime(&info->buf.st_mtime)[4]);
		}
		color_element(cont, info, apath);
		if (info->flags.l)
			ft_printf("\n");
	}
}
