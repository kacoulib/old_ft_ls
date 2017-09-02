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

static int		ft_set_time(t_file *file)
{
	char		**r;
	char		**tmp;
	time_t		curtime;

	if (!(r = (char **)malloc(sizeof(char *) * 100)) ||
	!(*r = ctime(&file->sb->st_mtime)))
		return (0);
	r = ft_strsplit(*r, ' ');
	file->l[5] = r[1];
	file->l[5] = ft_freejoin(file->l[5], " ");
	file->l[5] = ft_freejoin(file->l[5],
		ft_padding(r[2], (ft_strlen(r[2]) > 1 ? 0 : 1), 'r'));
	file->l[5] = ft_freejoin(file->l[5], " ");
	tmp = r;
	if ((time(&curtime) - 15552000) > file->sb->st_mtime)
		file->l[5] = ft_freejoin(file->l[5], ft_padding(tmp[4], 1, 'r'));
	else
	{
		r = ft_strsplit(r[3], ':');
		file->l[5] = ft_freejoin(file->l[5], r[0]);
		file->l[5] = ft_freejoin(file->l[5], ":");
		file->l[5] = ft_freejoin(file->l[5], r[1]);
	}
	free(r);
	return (1);
}

static int		ft_set_user_name(t_file *file, int long_params[],
	struct passwd	*usr, struct group	*grp)
{
	if ((usr = getpwuid(file->sb->st_uid)) &&
	(grp = getgrgid(file->sb->st_gid)))
	{
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
	}
	return (ft_set_time(file));
}

static int		ft_set_acl(t_file *file)
{
	mode_t		mode;
	char		*r;
	acl_t		facl;
	acl_entry_t	ae;

	mode = file->sb->st_mode;
	r = ft_memalloc(101);
	if (mode & (S_ISUID | S_ISGID))
		file->l[0] = ft_strjoin(file->l[0],
			mode & (S_IXUSR | S_IXGRP) ? "x" : "-");
	else if (mode & S_ISVTX)
		file->l[0] = ft_freejoin(file->l[0], mode & S_IXGRP ? "t" : "T");
	else
		file->l[0] = ft_freejoin(file->l[0], (mode & S_IXOTH) ? "x" : "-");
	facl = acl_get_link_np(file->path, ACL_TYPE_EXTENDED);
	if (facl && (acl_get_entry(facl, ACL_FIRST_ENTRY, &ae) == -1))
		file->l[0] = ft_freejoin(file->l[0], " ");
	else if (listxattr(file->path, NULL, 5, XATTR_NOFOLLOW) > 0)
		file->l[0] = ft_freejoin(file->l[0], "@");
	else if (facl != NULL)
		file->l[0] = ft_freejoin(file->l[0], "+");
	else
		file->l[0] = ft_freejoin(file->l[0], " ");
	free(r);
	return (1);
}

static int		ft_set_permissions(t_file *file, int l_len[],
	mode_t mode)
{
	if (DT_FIFO == file->type)
		file->l[0] = ft_strdup("c");
	else if (DT_FIFO == file->type)
		file->l[0] = ft_strdup("p");
	else if (DT_DIR == file->type)
		file->l[0] = ft_strdup("d");
	else if (DT_LNK == file->type)
		file->l[0] = ft_strdup("l");
	else if (DT_BLK == file->type)
		file->l[0] = ft_strdup("b");
	else if (DT_SOCK == file->type)
		file->l[0] = ft_strdup("s");
	else
		file->l[0] = ft_strdup("-");
	file->l[0] = ft_freejoin(file->l[0], (mode & S_IRUSR) ? "r" : "-");
	file->l[0] = ft_freejoin(file->l[0], (mode & S_IWUSR) ? "w" : "-");
	file->l[0] = ft_freejoin(file->l[0], (mode & S_IXUSR) ? "x" : "-");
	file->l[0] = ft_freejoin(file->l[0], (mode & S_IRGRP) ? "r" : "-");
	file->l[0] = ft_freejoin(file->l[0], (mode & S_IWGRP) ? "w" : "-");
	file->l[0] = ft_freejoin(file->l[0], (mode & S_IXGRP) ? "x" : "-");
	file->l[0] = ft_freejoin(file->l[0], (mode & S_IROTH) ? "r" : "-");
	file->l[0] = ft_freejoin(file->l[0], (mode & S_IWOTH) ? "w" : "-");
	if (ft_set_acl(file) && (int)ft_strlen(file->l[0]) > l_len[0])
		l_len[0] = ft_strlen(file->l[0]);
	return (ft_set_user_name(file, l_len, NULL, NULL));
}

int				ft_set_extra_info(t_file *file, int long_params[])
{
	struct stat	*sb;
	char		tmp[256];

	sb = (struct stat *)malloc(sizeof(struct stat) + 1);
	if (!sb || ((file->type == 8) ? stat(file->path, sb) :
		lstat(file->path, sb)) == -1)
		return (0);
	file->sb = sb;
	if (file->type == 10)
	{
		ft_bzero(tmp, 256);
		readlink(file->path, tmp, 256);
		file->name = ft_freejoin(file->name, " ");
		file->name = ft_freejoin(file->name, tmp);
	}
	if (file->parent)
		file->parent->size += sb->st_blocks;
	file->next = NULL;
	return (ft_set_permissions(file, long_params, file->sb->st_mode));
}
