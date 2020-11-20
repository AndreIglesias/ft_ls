/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_dirfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 11:23:40 by ciglesia          #+#    #+#             */
/*   Updated: 2020/11/20 18:52:22 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		can_openf(char *filename)
{
	int fd;

	if ((fd = open(filename, O_RDONLY) < 0) || read(fd, NULL, 0))
		return (0);
	close(fd);
	return (1);
}

int		is_file(char *filename)
{
	int		fd;
	t_stat	buf;

	lstat(filename, &buf);
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
	if ((fd = open(filename, O_RDONLY) < 0) || read(fd, NULL, 0))
		return (0);
	close(fd);
	return (1);
}

int		is_dir(char *dirname)
{
	DIR	*pdir;

	if ((pdir = opendir(dirname)) == NULL)
		return (0);
	closedir(pdir);
	return (1);
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
