/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_displays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 19:57:55 by kacoulib          #+#    #+#             */
/*   Updated: 2017/01/23 19:57:57 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_ls.h"

int			ft_display_result(t_file **folder, t_file *file, int long_params[], int is_multiple_folder)
{
	t_file	*tmp;

	if (!file && (tmp = file))
		return (0);

	if (ft_indexof(g_flags, 'f') < 0)
	{
		if (ft_indexof(g_flags, 'u') >= 0)
			ft_sort_by_last_modify(folder);
		else
			ft_sort_lexico(folder);
		tmp = (*folder);
	}
	if (ft_indexof(g_flags, 'r') >= 0)
		ft_rev_file((*folder));
	if (ft_indexof(g_flags, 'l') < 0)
	{
		// ft_display_folder(tmp);
		if (ft_indexof(g_flags, 'R') >= 0)
		{
			while (file)
			{
				tmp = file->next;
				if (file->type == 4 && (ft_strcmp(tmp->name, ".") != 0 && ft_strcmp(tmp->name, "..") != 0))
				{
					ft_putstr("\n");
					ft_putstr(ft_strsub(tmp->path, 0, (ft_strlen(tmp->path) - 1)));
					ft_putendl(":");
					ft_display_result(&file->files, file->files, long_params, is_multiple_folder);
				}
				file = tmp;
			}
		}
	}
	return (1);
}

int			ft_display_result_second_part(t_file *file, int long_params[], int is_multiple_folder)
{
	t_file *tmp;

	tmp = file;
	// printf("%s %d\n", file->name, file->type);
	if (file->type == 4)
	{
		if (is_multiple_folder)
			ft_putendl(ft_strjoin(file->name, ":"));
		ft_putstr("total ");
		ft_putendl(ft_itoa(file->size));
		tmp = file->files;
		// return (ft_display_result_second_part(file->files, long_params, is_multiple_folder));
	}
	while (tmp)
	{
		ft_putstr(tmp->l[0]);
		ft_display_result_third_part(tmp, long_params, 0);
		ft_display_color(tmp);
		ft_putchar('\n');
		tmp = tmp->next;
	}
	if (ft_indexof(g_flags, 'R') >= 0)
	{
		tmp = file;
		while (tmp)
		{
			file = tmp->next;
			if (tmp->type == 4)
			{
				ft_putstr("\n");
				ft_putstr(ft_strsub(tmp->path, 0, (ft_strlen(tmp->path) - 1)));
				ft_putendl(":");
				if (tmp->files)
					ft_display_result(&tmp->files, tmp->files, long_params, is_multiple_folder);
			}
			tmp = file;
		}
	}
	return (1);
}

