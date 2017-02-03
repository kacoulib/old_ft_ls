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

#include "ft_ls.h"

int					ft_set_user_name(t_file *file, int l_len[])
{
	struct passwd	*usr;
	struct group 	*grp;

	usr = getpwuid(file->sb->st_uid);
	grp = getgrgid(file->sb->st_gid);
	if ((file->l[1] = ft_itoa(file->sb->st_nlink))
		&& ft_strlen(file->l[1]) >l_len[1])
		l_len[1] = ft_strlen(file->l[1]);
	if ((file->l[2] = usr->pw_name) && ft_strlen(file->l[2]) > l_len[2])
		l_len[2] = ft_strlen(file->l[2]);
	if ((file->l[3] = grp->gr_name) && ft_strlen(file->l[3]) > l_len[3])
		l_len[3] = ft_strlen(file->l[3]);
	if ((file->l[4] = ft_itoa(file->sb->st_size))
		&& ft_strlen(file->l[4]) > l_len[4])
		l_len[4] = ft_strlen(file->l[4]);
	if ((file->l[5] = ft_itoa(file->sb->st_mtime))
		&& ft_strlen(file->l[5]) > l_len[5])
		l_len[5] = ft_strlen(file->l[5]);
	if ((file->l[7] = file->name) && ft_strlen(file->l[7]) > l_len[7])
		l_len[7] = ft_strlen(file->l[7]);
	return (ft_set_time(file, l_len));
}

int					ft_set_time(t_file *file, int l_len[])
{
	char			**r;
	char			**tmp;
	time_t			curtime;

	if (!(*r = ctime(&file->sb->st_mtime)))
		return (0);
	r = ft_strsplit(*r, ' ');
	file->l[5] = r[1];
	file->l[5] = ft_strjoin(file->l[5], " ");
	file->l[5] = ft_strjoin(file->l[5],
		ft_padding(r[2], (ft_strlen(r[2]) > 1 ? 0 : 1), 'r'));
	file->l[5] = ft_strjoin(file->l[5], " ");
	tmp = r;
	if ((time(&curtime) - 15552000) > file->sb->st_mtime)
		file->l[5] = ft_strjoin(file->l[5], ft_padding(tmp[4], 1, 'r'));
	else
	{
		r = ft_strsplit(r[3], ':');
		file->l[5] = ft_strjoin(file->l[5], r[0]);
		file->l[5] = ft_strjoin(file->l[5], ":");
		file->l[5] = ft_strjoin(file->l[5], r[1]);
	}
	return (1);
}

int					ft_set_acl(t_file *file)
{
	char			r[1000];
	// printf("%d\n", getxattr(file->path, file->name, r, 1000));
	return (1);
}

int					ft_set_permissions(t_file *file, int l_len[])
{
	struct stat 	*sb;

	char *r;
	sb = file->sb;
	if ((file->type == 8 && (file->l[0] = ft_strdup("-"))) ||
		(file->type == 4 && (file->l[0] = ft_strdup("d"))) ||
		(file->type == 10 && (file->l[0] = ft_strdup("l"))))
		;
	file->l[0] = ft_strjoin(file->l[0], (sb->st_mode & S_IRUSR) ? "r" : "-");
	file->l[0] = ft_strjoin(file->l[0], (sb->st_mode & S_IWUSR) ? "w" : "-");
	file->l[0] = ft_strjoin(file->l[0], (sb->st_mode & S_IXUSR) ? "x" : "-");
	file->l[0] = ft_strjoin(file->l[0], (sb->st_mode & S_IRGRP) ? "r" : "-");
	file->l[0] = ft_strjoin(file->l[0], (sb->st_mode & S_IWGRP) ? "w" : "-");
	file->l[0] = ft_strjoin(file->l[0], (sb->st_mode & S_IXGRP) ? "x" : "-");
	file->l[0] = ft_strjoin(file->l[0], (sb->st_mode & S_IROTH) ? "r" : "-");
	file->l[0] = ft_strjoin(file->l[0], (sb->st_mode & S_IWOTH) ? "w" : "-");
	ft_set_permissions_last_part(file);
	if (ft_strlen(file->l[0]) > l_len[0])
		l_len[0] = ft_strlen(file->l[0]);
	return (ft_set_user_name(file, l_len));
}

int					ft_set_permissions_last_part(t_file *file)
{
	struct stat 	*sb;
	ssize_t			i;
	char			*r;

	sb = file->sb;
	r = ft_memalloc(101);
	if (sb->st_mode & S_ISVTX)
	{
		file->l[0] = ft_strjoin(file->l[0], "t");
		file->type = 12;
	}
	else
		file->l[0] = ft_strjoin(file->l[0], sb->st_mode & S_IXOTH ? "x" : "-");
	if ((i = listxattr(file->path, r, 100, 1)))
		file->l[0] = ft_strjoin(file->l[0], "@");
	else
		file->l[0] = ft_strjoin(file->l[0], " ");
	file->type = file->type == 8 && sb->st_mode & S_IXUSR ? 0 : file->type;
	return (1);
}

int					ft_set_file(t_file *file, char *path, char *name, int type)
{
	struct stat		*sb;
	char			tmp[256];
	int				usr_and_grp[2];

	file->name = name;
	file->path = path;
	file->type = type;
	if (ft_indexof(g_flags, 'l') >= 0 && ft_strcmp(name, ".") != 0 && ft_strcmp(name, "..") != 0) // if -l is ask
	{
		sb = (struct stat *)malloc(sizeof(struct stat) + 1);
		if (!sb || ((type == 8) ? stat(path, sb) : lstat(path, sb)) == -1)
			return (0);
		file->sb = sb;
		if (file->type == 10)
		{
			readlink(path, tmp, 256);
			file->name = ft_strjoin(file->name, " ");
			file->name = ft_strjoin(file->name, tmp);
		}
		if (file->parent)
			(*file->parent)->size += sb->st_blocks;
			// printf("%s %p %lld\n", file->name, file->parent, sb->st_blocks);
	}
	file->next = NULL;
	return (1);
}

int					ft_set_params(char **av)
{
	int				i;
	int				j;
	int				k;
	char			r[ft_strlen(g_flags)];

	i = 0;
	j = 0;
	k = -1;
	ft_memset(r, '\0', ft_strlen(g_flags));
	while (av[++i] && av[i][0] == '-' && av[i][1])
	{
		while (av[i][++j] != '\0')
		{
			if (ft_indexof(g_flags, av[i][j]) < 0)
				return (-1);
			if (ft_indexof(g_flags, av[i][j]) >= 0)
				if (ft_indexof(r, av[i][j]) < 0)
					r[++k] = av[i][j];
		}
		j = 0;
	}
	g_flags = ft_strdup(r);
	return (i);
}