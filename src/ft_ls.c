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

static int			ft_set_sb_and_long(t_file *file, int l_len[])
{
	if (stat(file->path, file->sb) == -1 &&
		lstat(file->path, file->sb) == -1)
		return (0);
	if (ft_indexof(g_flags, 'l') > -1)
		ft_set_extra_info(file, l_len);
	return (1);
}

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
	if (tmp)
		current->type = tmp->d_type;
	ft_set_sb_and_long(current, l_len);
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
		file->path = (file->path) ? file->path : file->name;
		file->type = 4;
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
	return (!dir ? ft_set_error(file, file->name, NULL) : 1);
}

int					set_parse_params(t_file *master, char **av,
	int l_len[], int i)
{
	t_file			*tmp;

	if (!(tmp = ft_init_folder((!av[i]) ? "." : av[i], master, NULL)))
		return (ft_set_error(master, "error initialize folder", 0));
	if (!ft_is_dir(tmp->name) && !ft_is_file(tmp->name))
		return (ft_set_error(master, ft_strjoin(tmp->name, ": "), "open"));
	i = ft_strlen(tmp->name);
	tmp->path = tmp->name;
	if (ft_is_file(tmp->name) && (i = 1))
		ft_set_sb_and_long(tmp, l_len);
	else
	{
		if (tmp->name[i] != '/')
			tmp->path = ft_strjoin(tmp->name, "/");
		ft_parse_dir(tmp, NULL, l_len, NULL);
	}
	if (!master->files)
		master->files = tmp;
	else
		ft_push_file(master->files, tmp);
	return (1);
}

int					main(int ac, char **av)
{
	int				i;
	int				is_multi;
	int				l_len[7];
	t_file			*master;

	i = 0;
	is_multi = 0;
	master = ft_init_folder("master", NULL, NULL);
	if (ac < 1 || (i = ft_set_params(master, av, 0)) < -1)
		return (0);
	is_multi = (av[i] && av[i + 1]) ? 1 : 0;
	ac += (i > -1 && !av[i]) ? 1 : 0;
	while (i > -1 && i < ac)
	{
		set_parse_params(master, av, l_len, i);
		i++;
	}
	if (master->errors)
		ft_display_errors(master);
	if (master->files && ft_rev_list(&master->files))
	{
		ft_sort_settings(&master->files);
		ft_display_result(master->files, l_len, i, is_multi);
	}
	return (0);
}
