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

int			ft_display_extra_l_first_part(t_file *folder, t_file *file,
	int l_len[])
{
	if (!file->parent->size)
		return (0);
	ft_putstr("total ");
	ft_putstr(ft_itoa(file->parent->size));
	ft_putchar('\n');
	while (file)
	{
		if (ft_indexof(g_flags, 'R') >= 0 && file->type == 4)
			ft_display_result(&folder, file->files, l_len);
		ft_putstr(file->l[0]);
		ft_putchar(' ');
		ft_display_extra_l_second_part(file, l_len, 0);
		ft_display_color(file);
		ft_putchar('\n');
		file = file->next;
	}
	return (1);
}

int			ft_display_result(t_file **folder, t_file *file, int l_len[])
{
	t_file	*tmp;

	tmp = file;
	if (ft_indexof(g_flags, 'f') < 0)
	{
		if (ft_indexof(g_flags, 'u') >= 0)
			ft_sort_by_last_modify(folder);
		else
			ft_sort_lexico(folder);
		// tmp = (*folder);
	}
	if (ft_indexof(g_flags, 'r') >= 0)
		ft_rev_file((*folder));
	if (ft_indexof(g_flags, 'l') < 0)
	{
		while (tmp)
		{
			if (ft_indexof(g_flags, 'R') >= 0 && tmp->type == 4)
				ft_display_result(folder, tmp->files, l_len);
			ft_display_color(tmp);
			ft_putstr("\n");
			tmp = tmp->next;
		}
		return (1);
	}
	return (ft_display_extra_l_first_part(*folder, tmp, l_len));
}
	
int			ft_display_error(char *s, char *err)
{
	// if (!errno)
	// 	return (0);
	ft_putstr("ft_ls: ");
	ft_putstr(s);
	ft_putstr("\n");
	// ft_putstr(err);
	// printf("%d %s\n", ft_strcmp(err, "wrong flag"), err);
	if (ft_strcmp(err, "wrong flag") == 0)
	{
		ft_putstr("illegal option -- ");
		ft_putstr(s);
		ft_putchar('\n');
		ft_putstr("usage: ./ft_ls [");
		ft_putstr(g_flags);
		ft_putstr("] [file ...]\n");
		return (0);
	}
	// else
	// 	perror(s);
	return (1);
}

int			ft_display_color(t_file *file)
{
	if (file->type == 12 && file->l[0][10] == ' ')
		ft_putstr(ANSI_COLOR_BLACK);
	else if (file->type == 0)
		ft_putstr(ANSI_COLOR_RED);
	else if (file->type == 4)
		ft_putstr(ANSI_COLOR_CYAN);
	else if (file->type == 10)
	{
		ft_putstr(ANSI_COLOR_MAGENTA);
		if (ft_indexof(g_flags, 'l') > -1 && ft_display_color_extra(file))
			return (1);
	}
	ft_putstr(file->name);
	ft_putstr(ANSI_COLOR_RESET);
	return (1);
}

int			ft_display_color_extra(t_file *file)
{
	char	**r;

	if (ft_indexof(g_flags, 'l') > -1)
	{
		r = ft_strsplit(file->name, ' ');
		ft_putstr(r[0]);
		ft_putstr(ANSI_COLOR_RESET);
		ft_putstr(" -> ");
		ft_putstr(r[1]);
	}
	ft_putstr(ANSI_COLOR_RESET);
	return (1);
}
