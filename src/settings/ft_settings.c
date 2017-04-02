/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_settings.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 19:42:17 by kacoulib          #+#    #+#             */
/*   Updated: 2017/01/23 19:42:20 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_ls.h"

int					ft_set_extra_info(t_file *file, int long_params[])
{
	struct stat		*sb;
	char			tmp[256];

	sb = (struct stat *)malloc(sizeof(struct stat) + 1);
	if (!sb || ((file->type == 8) ? stat(file->path, sb) :
		lstat(file->path, sb)) == -1)
		return (0);
	file->sb = sb;
	if (file->type == 10)
	{
		readlink(file->path, tmp, 256);
		file->name = ft_strjoin(file->name, " ");
		file->name = ft_strjoin(file->name, tmp);
	}
	if (file->parent)
		file->parent->size += sb->st_blocks;
	file->next = NULL;
	return (ft_set_permissions(file, long_params, file->sb));
}

int					ft_set_params(t_file *file, char **av, int i)
{
	int				j;
	int				k;
	char			r[ft_strlen(g_flags)];

	j = 0;
	k = -1;
	ft_memset(r, '\0', ft_strlen(g_flags));
	while (av[++i] && av[i][0] == '-' && av[i][1])
	{
		while (av[i][++j] != '\0')
		{
			if (ft_indexof(g_flags, av[i][j]) < 0)
			{
				ft_set_error(file, ft_strsub(av[i], j, 1), "wrong flag");
				return (-1);
			}
			if (ft_indexof(g_flags, av[i][j]) >= 0)
				if (ft_indexof(r, av[i][j]) < 0)
					r[++k] = av[i][j];
		}
		j = 0;
	}
	g_flags = ft_strdup(r);
	return (i);
}

int					ft_set_permissions(t_file *file, int l_len[],
	struct stat *sb)
{
	if (S_IFCHR >> 9 == (sb->st_mode >> 9))
		file->l[0] = ft_strdup("c");
	else if (S_IFIFO >> 9 == (sb->st_mode >> 9))
		file->l[0] = ft_strdup("p");
	else if (S_IFDIR >> 9 == (sb->st_mode >> 9))
		file->l[0] = ft_strdup("d");
	else if (S_IFLNK >> 9 == (sb->st_mode >> 9))
		file->l[0] = ft_strdup("l");
	else if (S_IFBLK >> 9 == (sb->st_mode >> 9))
		file->l[0] = ft_strdup("b");
	else if (S_IFSOCK >> 9 == (sb->st_mode >> 9))
		file->l[0] = ft_strdup("s");
	else
		file->l[0] = ft_strdup("-");
	file->l[0] = ft_strjoin(file->l[0], (sb->st_mode & S_IRUSR) ? "r" : "-");
	file->l[0] = ft_strjoin(file->l[0], (sb->st_mode & S_IWUSR) ? "w" : "-");
	file->l[0] = ft_strjoin(file->l[0], (sb->st_mode & S_IXUSR) ? "x" : "-");
	file->l[0] = ft_strjoin(file->l[0], (sb->st_mode & S_IRGRP) ? "r" : "-");
	file->l[0] = ft_strjoin(file->l[0], (sb->st_mode & S_IWGRP) ? "w" : "-");
	file->l[0] = ft_strjoin(file->l[0], (sb->st_mode & S_IXGRP) ? "x" : "-");
	file->l[0] = ft_strjoin(file->l[0], (sb->st_mode & S_IROTH) ? "r" : "-");
	file->l[0] = ft_strjoin(file->l[0], (sb->st_mode & S_IWOTH) ? "w" : "-");
	if (ft_set_acl(file) && (int)ft_strlen(file->l[0]) > l_len[0])
		l_len[0] = ft_strlen(file->l[0]);
	return (ft_set_user_name(file, l_len));
}

int					ft_set_acl(t_file *file)
{
	struct stat		*sb;
	ssize_t			i;
	char			*r;

	sb = file->sb;
	r = ft_memalloc(101);
	if (sb->st_mode & (S_ISUID | S_ISGID))
	{
		file->l[0] = ft_strjoin(file->l[0], sb->st_mode & (S_IXUSR | S_IXGRP)? "x" : "-");
	}
	else if (sb->st_mode & S_ISVTX)
	{
		if (sb->st_mode & S_IXGRP)
		{
			file->type = 12;
			file->l[0] = ft_strjoin(file->l[0], "t");
		}
		else
			file->l[0] = ft_strjoin(file->l[0], "T");
	}
	else
		file->l[0] = ft_strjoin(file->l[0], "-");
	if ((i = listxattr(file->path, r, 100, 1)))
		file->l[0] = ft_strjoin(file->l[0], "@");
	else
		file->l[0] = ft_strjoin(file->l[0], " ");
	file->type = file->type == 8 && sb->st_mode & S_IXUSR ? 0 : file->type;
	free(r);
	return (1);
}

int					ft_set_user_name(t_file *file, int long_params[])
{
	struct passwd	*usr;
	struct group	*grp;

	usr = getpwuid(file->sb->st_uid);
	grp = getgrgid(file->sb->st_gid);
	if ((file->l[1] = ft_itoa(file->sb->st_nlink))
		&& (int)ft_strlen(file->l[1]) > long_params[1])
		long_params[1] = ft_strlen(file->l[1]);
	if ((file->l[2] = ft_strjoin(usr->pw_name, " ")) &&
		(int)ft_strlen(file->l[2]) > long_params[2])
		long_params[2] = ft_strlen(file->l[2]);
	if ((file->l[3] = grp->gr_name) &&
		(int)ft_strlen(file->l[3]) > long_params[3])
		long_params[3] = ft_strlen(file->l[3]);
	if ((file->l[4] = ft_itoa(file->sb->st_size))
		&& (int)ft_strlen(file->l[4]) > long_params[4])
		long_params[4] = ft_strlen(file->l[4]);
	if ((file->l[5] = ft_itoa(file->sb->st_mtime))
		&& (int)ft_strlen(file->l[5]) > long_params[5])
		long_params[5] = ft_strlen(file->l[5]);
	if ((file->l[7] = file->name) &&
		(int)ft_strlen(file->l[7]) > long_params[7])
		long_params[7] = ft_strlen(file->l[7]);
	return (ft_set_time(file));
}
