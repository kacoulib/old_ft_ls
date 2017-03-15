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

#include "../ft_ls.h"

int					ft_parse_dir_last_part(t_file *file, struct dirent *tmp,
	int long_params[])
{
	if (tmp)
		file->type = tmp->d_type;
	if (ft_indexof(g_flags, 'l') > -1)
		ft_set_extra_info(file, long_params);
	if (tmp && tmp->d_type == 4 && ft_indexof(g_flags, 'R') >= 0)
	{
		if (ft_strcmp(tmp->d_name, ".") != 0 && ft_strcmp(tmp->d_name, "..") != 0)
			if (!ft_parse_dir(file, long_params))
				return (0);
	}
	return (1);
}

int					ft_is_file(char *path)
{
	struct stat		path_stat;
	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}

int					ft_parse_dir(t_file *file, int long_params[])
{
	struct dirent	*tmp;
	DIR				*dir;
	t_file			*current;
	t_file			*parent;

	tmp = NULL;
	if ((dir = opendir(file->name)) || (dir = opendir(file->path)))
	{
		parent = file;
		file->type = 4;
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
				ft_parse_dir_last_part(current, tmp, long_params);
			}
		}
	}
	else
	{
		if (ft_is_file(file->name) && (file->path = file->name))
			return (ft_parse_dir_last_part(file, tmp, long_params));
		return (ft_set_error(file,
			ft_strjoin(file->name, ": No such file or directory"), "hello"));
	}
	
	return ((closedir(dir) == 0) ? 1 : 0);
}

int					set_parse_params(t_file *container, char **av, int long_params[], int i)
{
	t_file			*folder;

	if (!(folder = ft_init_folder(NULL, container, NULL)))
		return (ft_set_error(container, "error initialize folder", 0));
	folder->name = ft_strdup((!av[i]) ? "." : av[i]);
	i = 0;
	if ((i = ft_parse_dir(folder, long_params)))
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
	int				long_params[8];
	t_file			*container;
	t_file			*tmp;

	i = 0;
	container = ft_init_folder("master", NULL, NULL);
	if (ac < 1 || (i = ft_set_params(av)) < 1)
		return (0);
	i--;
	while (++i < (ac == 1 ? 2 : ac))
		set_parse_params(container, av, long_params, i);
	if (container->errors)
		ft_sort_lexico(&container->errors);
	while (container->errors)
	{
		ft_putendl(container->errors->name);
		container->errors = container->errors->next;
	}
	if (container->files && ft_rev_list(&container->files))
	{
		ft_sort_settings(&container->files);
		i = (container->files->next) ? 1 : 0;
		ft_display_result(&container->files, container->files, long_params, i);
	}
	return (0);
}
