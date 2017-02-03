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

int			ft_display_line(t_file *file, int l_len[])
{

	ft_set_permissions(file, l_len);
	return (1);
}

int			ft_display_result(t_file *file, int l_len[])
{
	t_file	*tmp;

	tmp = file;
	while (tmp)
	{
		ft_display_line(tmp, l_len);
		tmp = tmp->next;
	}
	if (ft_indexof(g_flags, 'l')>= 0)
	{
		tmp = file;
		while (tmp->next)
		{
			if (tmp->files && tmp->type == 4 && tmp->name[0] == 't')
			{
				ft_putchar(' ');
				ft_display_result(tmp->files, l_len);
			}
			tmp = tmp->next;
		}
	}
	return (1);
}

int			ft_display_error(char *s, int id)
{
	if (!errno)
		return (0);
	ft_putstr("ls: ");
	// if (errno == ENOENT)
		perror("moi");
	return (1);
}

int			ft_display_color(t_file *file)
{
	char	**r;

	if (file->type == 12 && file->l[0][10] == ' ')
		ft_putstr(ANSI_COLOR_BLACK);
	else if (file->type == 0)
		ft_putstr(ANSI_COLOR_RED);
	else if (file->type == 8)
		ft_putstr(ANSI_COLOR_RESET);
	else if (file->type == 4)
		ft_putstr(ANSI_COLOR_CYAN);
	else if (file->type == 10)
	{
		ft_putstr(ANSI_COLOR_MAGENTA);
		r = ft_strsplit(file->name, ' ');
		ft_putstr(r[0]);
		ft_putstr(ANSI_COLOR_RESET);
		ft_putstr(" -> ");
		ft_putstr(r[1]);
		return (1);
	}
	ft_putstr(file->name);
	return (1);
}