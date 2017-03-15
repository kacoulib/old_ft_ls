/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_displays_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 18:50:15 by kacoulib          #+#    #+#             */
/*   Updated: 2017/02/20 18:50:20 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../ft_ls.h"

int			ft_display_result_third_part(t_file *file,
	int long_params[], int i)
{
	while (++i < 6)
	{
		if ((int) ft_strlen(file->l[i]) < long_params[i])
			ft_display_result_fourth_part(file, long_params, i);
		else
		{
			ft_putstr(file->l[i]);
			ft_putchar(' ');
		}
		if (i == 2 || i == 3)
			ft_putchar(' ');
	}
	return (0);
}

int			ft_display_result_fourth_part(t_file *file, int long_params[], int i)
{
	char	*tmp;

	if (i == 2 || i == 3)
	{
		tmp = ft_padding(file->l[i], (long_params[i] -
			ft_strlen(file->l[i])) + 1, 'l');
		ft_putstr(tmp);
		ft_putchar(' ');
		return (1);
	}
	tmp = ft_padding(file->l[i], long_params[i] - ft_strlen(file->l[i]), 'r');
	ft_putstr(tmp);
	ft_putchar(' ');
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

