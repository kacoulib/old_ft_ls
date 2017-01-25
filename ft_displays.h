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

int			ft_rev_file(t_file **file)
{
	t_file	*prev;
	t_file	*tmp;

	prev = NULL;
	while (*file)
	{
		tmp = *file;
		*file = (*file)->next;
		tmp->next = prev;
		prev = tmp;
	}
	*file = tmp;
	return (0);
}

int			ft_display_line(t_file *file, int l_len[])
{

	ft_set_permissions(file, l_len);
	return (1);
}

int			ft_display_result(t_file *file, int l_len[])
{
	t_file	*tmp;

// printf("---%p\n", file);
	tmp = file;
	while (tmp)
	{
		if (tmp->type == 8)
			ft_putstr(ANSI_COLOR_RESET);
		else if (tmp->type == 4)
			ft_putstr(ANSI_COLOR_CYAN);
		else if (tmp->type == 10)
			ft_putstr(ANSI_COLOR_MAGENTA);

		// printf("%s\n", tmp->path);
		ft_display_line(tmp, l_len);
		// if (tmp->next)
		// 	ft_putchar(' ');
		// else
		// 	ft_putchar('\n');
		tmp = tmp->next;
	}
	if (ft_indexof(g_flags, 'l')>= 0)
	{
		tmp = file;
		while (tmp->next)
		{
			if (tmp->files && tmp->type == 4 && tmp->name[0] == 't')
			{
// printf("+++%p %s\n", tmp, tmp->name);
				// printf("\n%s: %p\n", tmp->path, tmp);
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
	if (errno == ENOENT)
		perror(s);
	return (1);
}
