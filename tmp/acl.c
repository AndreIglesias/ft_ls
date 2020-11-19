/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   acl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 22:38:20 by ciglesia          #+#    #+#             */
/*   Updated: 2020/11/19 22:51:46 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <grp.h>

void printType(mode_t iMode)
{
    if(S_ISREG(iMode))
	{
        printf("regular file\n");
        return;
    }
    if(S_ISDIR(iMode))
	{
        printf("directory\n");
        return;
    }
    if(S_ISBLK(iMode))
	{
        printf("block device\n");
        return;
    }
    if(S_ISCHR(iMode))
	{
        printf("character device\n");
        return;
    }
    if(S_ISSOCK(iMode))
	{
        printf("socket\n");
        return;
    }
}

void	print_permissions(mode_t st_mode)
{
		printf("%c", (st_mode & S_IRUSR) ? 'r' : '-');
		printf("%c", (st_mode & S_IWUSR) ? 'w' : '-');
		printf("%c", (st_mode & S_IXUSR) ? 'x' : '-');
		printf("%c", (st_mode & S_IRGRP) ? 'r' : '-');
		printf("%c", (st_mode & S_IWGRP) ? 'w' : '-');
		printf("%c", (st_mode & S_IXGRP) ? 'x' : '-');
		printf("%c", (st_mode & S_IROTH) ? 'r' : '-');
		printf("%c", (st_mode & S_IWOTH) ? 'w' : '-');
		printf("%c", (st_mode & S_IXOTH) ? 'x' : '-');
		printf("\n");
}

void	print_user(uid_t st_uid)
{
	struct passwd *user;

	user = getpwuid(st_uid);
	printf("%s\n", user->pw_name);
}

void	print_grp(gid_t st_gid)
{
	struct group *grp;

	grp = getgrgid(st_gid);
	printf("%s\n", grp->gr_name);
}

int		main(int argc, char **argv)
{
	struct stat		buf;

	if (argc != 2)
		return (0);
	stat(argv[1], &buf);
	printf("Name: %s\n", argv[1]);
	printf("Type: ");
	printType(buf.st_mode);
	printf("Modes: ");
	print_permissions(buf.st_mode);
	printf("Number of links: %d\n", buf.st_nlink);
	printf("Owner: ");
	print_user(buf.st_uid);
	printf("Group: ");
	print_grp(buf.st_gid);
	printf("Size: %llu\n", buf.st_size);
	//printf("Last modification date: %s", ctime(&buf.st_mtimespec.tv_sec));
	printf("Last modification date: %s", ctime(&buf.st_mtim.tv_sec));
	return (0);
}
