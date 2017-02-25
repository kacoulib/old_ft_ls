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

#include "ft_ls.h"

int			ft_display_extra_l_second_part(t_file *file,
	int l_len[], int i)
{
	while (++i < 6)
	{
		if ((int) ft_strlen(file->l[i]) < l_len[i])
			ft_display_extra_l_third_part(file, l_len, i);
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

int			ft_display_extra_l_third_part(t_file *file,
	int l_len[], int i)
{
	char	*tmp;

	if (i == 2 || i == 3)
	{
		tmp = ft_padding(file->l[i], (l_len[i] -
			ft_strlen(file->l[i])) + 1, 'l');
		ft_putstr(tmp);
		ft_putchar(' ');
	}
	else
	{
		tmp = ft_padding(file->l[i], l_len[i] - ft_strlen(file->l[i]), 'r');
		ft_putstr(tmp);
		ft_putchar(' ');
	}
	return (1);
}

int			ft_push_folder(t_file *file, t_file *new_file)
{
	t_file	*tmp;

	if (!file && (file = new_file))
		return (1);
	tmp = file;
	while (tmp->next_folder)
		tmp = tmp->next_folder;
	tmp->next_folder = new_file;
	new_file->next_folder = NULL;
	return (1);	
}
