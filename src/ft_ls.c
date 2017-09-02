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

#include "global_flags.h"
#include "ft_ls.h"

static int			ft_parse_dir_last_part(t_file *current, struct dirent *tmp,
	int l_len[])
{
	if (tmp)
	{		
		if (current->path[ft_strlen(current->path) - 1] != '/')
			current->path = ft_strjoin(current->path, "/");
		else
			current->path = current->path;
		current->path = ft_strjoin(current->path, current->name);
	}
	if (stat(current->path, current->sb) == -1 &&
		lstat(current->path, current->sb) == -1)
		return (0);
	if (tmp)
		current->type = tmp->d_type;
	if (ft_indexof(g_flags, 'l') > -1)
		ft_set_extra_info(current, l_len);
	if (tmp && tmp->d_type == 4 && ft_indexof(g_flags, 'R') >= 0)
	{
		if (ft_strcmp(tmp->d_name, ".") != 0 &&
			ft_strcmp(tmp->d_name, "..") != 0)
			if (!ft_parse_dir(current, NULL, l_len, NULL))
				return (0);
	}
	return (1);
}

int					ft_parse_dir(t_file *file, t_file *current,
	int l_len[], struct dirent *tmp)
{
	DIR				*dir;

	if ((dir = opendir(file->path)))
	{
		file->type = 4;
		file->path = (file->path) ? file->path : file->name;
		while ((tmp = readdir(dir)))
		{
			if (tmp->d_name[0] != '.' || (ft_indexof(g_flags, 'a') >= 0))
			{
				if (!(file->files) &&
					((file->files = ft_init_folder(tmp->d_name, file, NULL))))
					current = file->files;
				else if ((current->next =
					ft_init_folder(tmp->d_name, file, current)))
					current = current->next;
				current->path = file->path;
				ft_parse_dir_last_part(current, tmp, l_len);
			}
		}
		closedir(dir);
	}
	else if (ft_is_file(file->name) && (file->path = file->name))
		return (ft_parse_dir_last_part(file, NULL, l_len));
	return (1);
}

int					set_parse_params(t_file *container, char **av,
	int l_len[], int i)
{
	t_file			*folder;

	if (!(folder = ft_init_folder(NULL, container, NULL)))
		return (ft_set_error(container, "error initialize folder", 0));
	folder->name = ft_strdup((!av[i]) ? "." : av[i]);
	if (opendir(folder->name) == NULL && !ft_is_file(folder->name))
		return (ft_set_error(folder, ft_strjoin(folder->name, ": "), "open"));
	i = ft_strlen(folder->name);
	if (folder->name[i] != '/')
		folder->path = ft_strjoin(folder->name, "/");
	i = 0;
	if ((i = ft_parse_dir(folder, NULL, l_len, NULL)))
	{
		if (!container->files)
			container->files = folder;
		else
		{
			folder->prev = container->files;
			container->files->next = folder;
			container->files = container->files->next;
		}
	}
	return (i);
}

int					main(int ac, char **av)
{
	int				i;
	int				is_multi;
	int				l_len[7];
	t_file			*container;

	i = 0;
	is_multi = 0;
	container = ft_init_folder("master", NULL, NULL);
	if (ac < 1 || (i = ft_set_params(container, av, 0)) < -1)
		return (0);
	is_multi = (av[i] && av[i + 1]) ? 1 : 0;
	ac += (i > -1 && !av[i]) ? 1 : 0;
	while (i > -1 && i < ac)
	{
		set_parse_params(container, av, l_len, i);
		i++;
	}
	if (container->errors && ft_sort_lexico(&container->errors))
		ft_display_folder(container->errors, l_len);
	if (container->files && ft_rev_list(&container->files))
	{
		ft_sort_settings(&container->files);
		ft_display_result(container->files, l_len, i, is_multi);
	}
	return (0);
}
