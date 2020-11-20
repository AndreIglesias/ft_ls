/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 17:57:14 by ciglesia          #+#    #+#             */
/*   Updated: 2020/11/20 17:31:13 by ciglesia         ###   ########.fr       */
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
		//ft_printf("%s  ", (char *)files->obj);
		print_element(files->obj, info);
		files = files->next;
	}
	if (info->flags.files && !info->flags.l)
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

	while (dirs && (is_dot((char *)dirs->obj) == 1 ||
					is_dot((char *)dirs->obj) == 2))
		dirs = dirs->next;
	if (dirs)
		return ((char *)dirs->obj);
	return (NULL);
}

void	sort_dirs(t_list *d1, t_list *d2, t_collection *info)
{
	alpha_sort(d1);
	alpha_sort(d2);
	if (info->flags.r)
	{
		ft_lstrev(&d1);
		ft_lstrev(&d2);
	}
}
