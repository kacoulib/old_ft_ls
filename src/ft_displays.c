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

int			ft_display_recursive(t_file *file, int l_len[], int is_multi,
	int first)
{
	t_file	*tmp;
	int		i;

	if (!(tmp = file))
		return (0);
	i = 0;
	while (tmp)
	{
		if (tmp->type == 4)
		{
			if ((ft_strcmp(tmp->name, ".") != 0 && ft_strcmp(tmp->name, "..")
				!= 0) || (first))
			{
				if (is_multi)
					ft_print(first && i == 0 ? "" : "\n", tmp->path, ":", NULL);
				if (ft_indexof(g_flags, 'l') > -1 && !first && file->files)
					ft_print("total ", ft_itoa(file->size), NULL, NULL);
				ft_display_folder(tmp->files, l_len);
			}
			ft_display_recursive(tmp->files, l_len, 1, 0);
		}
		i++;
		tmp = tmp->next;
	}
	return (1);
}

int			ft_display_result(t_file *file, int l_len[], int i, int is_multi)
{
	t_file	*tmp;

	if (!(tmp = file))
		return (0);
	if (ft_indexof(g_flags, 'R') < 0)
	{
		i = ft_display_folder_files(tmp);
		while (tmp)
		{
			if (tmp->type == 4)
			{
				if (++i > 1)
					ft_putchar('\n');
				if (is_multi)
					ft_print(tmp->path, ":", NULL, NULL);
				if (ft_indexof(g_flags, 'l') > -1)
					ft_print("total ", ft_itoa(file->size), NULL, NULL);
				ft_display_folder(tmp->files, l_len);
			}
			tmp = tmp->next;
		}
	}
	else
		ft_display_recursive(file, l_len, is_multi, 1);
	return (1);
}

int			ft_display_folder(t_file *file, int l_len[])
{
	char	*tmp;
	int		i;

	while (file)
	{
		if (ft_indexof(g_flags, 'l') > -1 && file->type != -1)
		{
			i = -1;
			while (file->l[++i] && l_len[i])
			{
				if (i == 4)
					tmp = ft_padding(file->l[i],
						(l_len[i] - ft_strlen(file->l[i])) + 1, 'r');
				else
					tmp = ft_padding(file->l[i],
						(l_len[i] - ft_strlen(file->l[i])) + 1, 'l');
				ft_putstr(ft_strjoin(tmp, " "));
			}
			ft_display_color(file);
		}
		else
			ft_display_color(file);
		file = file->next;
	}
	return (1);
}

int			ft_display_folder_files(t_file *folder)
{
	t_file	*tmp;
	int		i;

	tmp = folder;
	i = 0;
	while (tmp)
	{
		if (tmp->type == 8 && ++i)
			ft_display_color(tmp);
		tmp = tmp->next;
	}
	return (i);
}
