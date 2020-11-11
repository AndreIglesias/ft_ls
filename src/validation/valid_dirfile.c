/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_dirfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 11:23:40 by ciglesia          #+#    #+#             */
/*   Updated: 2020/11/11 16:53:41 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		is_file(char *filename)
{
	int fd;

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

	ret = 0;
	if (!is_file(filename))
		ret++;
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
