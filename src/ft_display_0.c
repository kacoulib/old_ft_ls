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

#include "ft_ls.h"

int			ft_display_errors(t_file *file)
{
	if (!file || !file->errors)
		return (1);
	ft_sort_lexico(&file->errors);
	while (file->errors)
	{
		ft_putendl(file->errors->name);
		file->errors = file->errors->next;
	}
	return (1);
}

int			ft_display_recursive(t_file *file, int l_len[], int is_multi,
	int first)
{
	int		i;
	t_file	*tmp;

	if (!(tmp = file))
		return (0);
	i = -1;
	while (tmp)
	{
		if (++i > -1 && tmp->type == 4)
		{
			if ((ft_strcmp(tmp->name, ".") != 0 && ft_strcmp(tmp->name, "..")
				!= 0) || (first))
			{
				if (is_multi)
					ft_print(first && i == 0 ? "" : "\n", tmp->path, ":", NULL);
				if (ft_indexof(g_flags, 'l') > -1 && tmp->files)
					ft_print("total ", ft_itoa(tmp->size), NULL, NULL);
				ft_display_folder(tmp->files, l_len);
			}
			ft_display_errors(tmp);
			ft_display_recursive(tmp->files, l_len, 1, 0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int			ft_display_result(t_file *file, int l_len[], int i, int is_multi)
{
	t_file	*tmp;

	if (!(tmp = file))
		return (0);
	i = ft_display_folder_files(tmp, l_len);
	if (ft_indexof(g_flags, 'R') < 0)
	{
		while (tmp)
		{
			if (tmp->type == 4)
			{
				if (++i > 1)
					ft_putchar('\n');
				if (is_multi)
					ft_print(tmp->path, ":", NULL, NULL);
				if (ft_indexof(g_flags, 'l') > -1)
					ft_print("total ", ft_itoa(tmp->size), NULL, NULL);
				ft_display_folder(tmp->files, l_len);
			}
			tmp = tmp->next;
		}
	}
	else
		ft_display_recursive(file, l_len, is_multi, 1);
	return (1);
}
