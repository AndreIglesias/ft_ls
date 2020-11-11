/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_dirfile.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 11:23:40 by ciglesia          #+#    #+#             */
/*   Updated: 2020/11/11 12:57:38 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls.h"

int		valid_dirfile(char *filename)
{
	int	fd;
	int ret;
	DIR	*pdir;

	ret = 0;
	if ((fd = open(filename, O_RDONLY) < 0) || read(fd, NULL, 0))
		ret++;
	close(fd);
	if ((pdir = opendir(filename)) == NULL)
		ret++;
	else
	{
		t_dir *d;

		while ((d = readdir(pdir)) != NULL)
			ft_printf("[%s]\n", d->d_name);
	}
	closedir(pdir);
	if (ret == 2)
	{
		ft_printf_fd(2, ERROR": ft_ls: Cannot access '%s': "BLINK"No such file \
or directory\n"E0M, filename);
		return (0);
	}
	return (1);
}
