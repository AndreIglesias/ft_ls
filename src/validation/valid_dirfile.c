/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_dirfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 11:23:40 by ciglesia          #+#    #+#             */
/*   Updated: 2020/11/21 12:14:03 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		can_openf(char *filename)
{
	t_stat	buf;
    int		exist;

	ft_memset(&exist, 0, sizeof(struct stat));
	exist = lstat(filename, &buf);
	if(exist == 0)
		return (1);
	return (0);
}

int		is_file(char *filename)
{
	t_stat	buf;

	if (lstat(filename, &buf) == -1)
		return (0);
	if (S_ISLNK(buf.st_mode))
		return (1);
	if (S_ISREG(buf.st_mode))
		return (1);
	if (S_ISCHR(buf.st_mode))
		return (1);
	if (S_ISSOCK(buf.st_mode))
		return (1);
	if (S_ISFIFO(buf.st_mode))
		return (1);
	if (!can_openf(filename))
		return (0);
	return (0);
}

int		is_dir(char *dirname)
{
	//DIR		*pdir;
	t_stat	buf;

	if (lstat(dirname, &buf) == -1)
		return (0);
	if (S_ISDIR(buf.st_mode))
		return (1);
	return (0);
	/*
	if ((pdir = opendir(dirname)) == NULL)
		return (0);
	closedir(pdir);
	return (1);
	*/
}

int		valid_dirfile(char *filename)
{
	int ret;
	t_stat	buf;

	ret = 0;
	if (!is_file(filename))
		ret++;
	lstat(filename, &buf);
	if (!is_dir(filename))
		ret++;
	if (ret == 2)
	{
		ft_printf_fd(2, ERROR": ft_ls: Cannot access '%s': "BLINK"No such file \
or directory\n"E0M, filename);
		return (0);
	}
	return (1);
}
