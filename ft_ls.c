/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 16:37:25 by kacoulib          #+#    #+#             */
/*   Updated: 2017/01/18 16:38:00 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file				*ft_init_folder(char *name, t_file *parent, t_file *prev)
{
	t_file			*file;
	struct stat		*sb;

	file = (t_file *)malloc(sizeof(t_file) + 1);
	sb = (struct stat*)malloc(sizeof(struct stat) + 1);
	if (!file || !sb)
		return (NULL);
	file->name = ft_strdup(name);
	file->path = NULL;
	file->info = NULL;
	file->size = 0;
	file->type = 8;
	file->sb = sb;
	file->files = NULL;
	file->folders = NULL;
	file->next_folder = NULL;
	file->parent = parent;
	file->next = NULL;
	file->prev = prev;
	return (file);
}

int					ft_parse_dir_last_part(t_file *file, struct dirent *tmp,
	int l_len[])
{
	file->type = tmp->d_type;
	if (ft_indexof(g_flags, 'l') > -1)
		ft_set_extra_info(file, l_len);
	if (tmp->d_type == 4 && ft_indexof(g_flags, 'R') >= 0)
	{
		if (ft_strcmp(tmp->d_name, ".") != 0 && ft_strcmp(tmp->d_name, "..") != 0)
		{
			if (!file->parent->folders)
				file->parent->folders = file;
			else
				ft_push_folder(file->parent->folders, file);
			if (!ft_parse_dir(file, l_len))
				return (0);
		}
	}
	return (1);
}

int					ft_is_file(char *path)
{
	struct stat		path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}


// int					ft_parse_dir_second(t_file *file, int l_len[])
// {
// 	return (1);
// }

int					ft_parse_dir(t_file *file, int l_len[])
{
	struct dirent	*tmp;
	DIR				*dir;
	t_file			*current;
	t_file			*parent;

	tmp = NULL;
	if ((dir = opendir(file->name)) || (dir = opendir(file->path)))
	{
		parent = file;
		file->path = (file->path) ? ft_strjoin(file->path, "/") : ft_strjoin(file->name, "/");
		while ((tmp = readdir(dir)))
		{
			if ((tmp->d_name[0] != '.' || (ft_indexof(g_flags, 'a') >= 0) ? 1 : 0))
			{
				if (!(file->files) && ((file->files = ft_init_folder(tmp->d_name, parent, file))))
					current = file->files;
				else if ((current->next = ft_init_folder(tmp->d_name, parent, current)))
					current = current->next;
				current->path = ft_strjoin(file->path, current->name);
				ft_parse_dir_last_part(current, tmp, l_len);
			}
		}
	}
	else
	{
		if (ft_is_file(file->name))
		{
			current = ft_init_folder(file->name, NULL, NULL);
			ft_parse_dir_last_part(current, tmp, l_len);
			printf("%s\n", file->name);
		}
		else
			ft_display_error(file->name, "opening folder");
		return (0);
	}
	
	return ((closedir(dir) == 0) ? 1 : 0);
}

int					main(int ac, char **av)
{
	int				i;
	int				l_params_length[8];
	char			*folder_name;
	t_file			*folder;

	i = 0;
	folder = NULL;
	folder_name = NULL;
	if (ac < 1 || (i = ft_set_params(av)) < 0)
			return (ft_display_error(folder_name, 0));
	folder_name = (av[i]) ? ft_strdup(av[i]) : ft_strdup(".");
	if (!(folder = ft_init_folder(folder_name, NULL, NULL)))
		return (ft_display_error(folder_name, 0));
	ft_parse_dir(folder, l_params_length);
	// ft_display_result(&folder->files, folder->files, l_params_length);
	// ft_sort_lexico(&folder->folders);
	while (folder->folders)
	{
		printf("%s\n", folder->folders->name);
		folder->folders = folder->folders->next_folder;
	}
	return (0);
}
