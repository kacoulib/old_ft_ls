/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sorts.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 10:17:33 by kacoulib          #+#    #+#             */
/*   Updated: 2017/02/03 10:17:34 by kacoulib         ###   ########.fr       */
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
		tmp = (*file);
		*file = (*file)->next;
		tmp->next = prev;
		prev = tmp;
	}
	*file = tmp;
	return (0);
}

int			ft_sort_by_last_modify(t_file **file)
{
	t_file	*current;
	t_file	*tmp;

	current = (*file);
	tmp = (*file);
	while (current->next)
	{
		if (current->sb->st_mtime < current->next->sb->st_mtime)
		{
			current = current->next;
			while (tmp->next)
			{
				if (current->sb->st_mtime > tmp->sb->st_mtime)
				{
					ft_swap_file(file, current, tmp);
					return (ft_sort_by_last_modify(file));
				}
				tmp = tmp->next;
			}
		}
		current = current->next;
	}
	return (1);
}

int			ft_sort_lexico(t_file **file)
{
	t_file	*current;
	t_file	*head;

	current = (*file);
	head = (*file);
	while (current->next)
	{
		if (ft_strcmp(current->name, current->next->name) > 0)
		{
			current = current->next;
			while (head->next)
			{
				if ((ft_strcmp(current->name, head->name) < 0) &&
					(ft_swap_file(file, current, head)))
					return (ft_sort_lexico(file));
				head = head->next;
			}
		}
		current = current->next;
	}
	return (1);
}

int			ft_sort_settings(t_file **folder)
{
	t_file	*tmp;

	if (!folder || !(*folder))
		return (0);
	if (ft_indexof(g_flags, 't') >= 0)
		ft_sort_by_last_modify(folder);
	else
		ft_sort_lexico(folder);
	if (ft_indexof(g_flags, 'r') >= 0)
		ft_rev_file(folder);
	tmp = *folder;
	while (tmp)
	{
		if (tmp->type == 4)
			ft_sort_settings(&tmp->files);
		tmp = tmp->next;
	}
	return (1);
}

int			ft_swap_file(t_file **file, t_file *current, t_file *head)
{
	if (current->prev)
		current->prev->next = current->next;
	if (current->next)
		current->next->prev = current->prev;
	if (head->prev)
		head->prev->next = current;
	current->prev = head->prev;
	head->prev = current;
	current->next = head;
	if (head == (*file))
		(*file) = current;
	return (1);
}
