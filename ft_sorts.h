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

int			ft_sort_lexico(t_file **file)
{
	t_file	*current;
	t_file	*tmp;

	current = *file;
	tmp = *file;
	while (current->next)
	{
		if (ft_strcmp(current->name, current->next->name) > 0)
		{
			current = current->next;
			while (tmp->next)
			{
				if (ft_strcmp(current->name, tmp->name) < 0)
					return (ft_swap_file(file, current, tmp) &&
						ft_sort_lexico(file));
				tmp = tmp->next;
			}
		}
		current = current->next;
	}
	return (1);
}


int			ft_swap_file(t_file **file, t_file *current, t_file *tmp)
{
	current->prev->next = current->next;
	current->next = current->prev;
	if (tmp->prev)
		tmp->prev->next = current;
	current->prev = tmp->prev;
	current->next = tmp;
	if (tmp == *file)
		*file = current;
	return (0);
}


int			ft_sort_by_last_modify(t_file **file)
{
	t_file	*current;
	t_file	*tmp;

	current = *file;
	tmp = *file;
	while (current->next)
	{
		if (ft_strcmp(current->name, current->next->name) < 0)
		{
			current = current->next;
			while (tmp->next)
			{
				if (ft_strcmp(current->name, tmp->name) < 0)
				{
					return (ft_swap_file(file, current, tmp) &&
						ft_sort_lexico(file));
				}
				tmp = tmp->next;
			}
		}
		current = current->next;
	}
	return (1);
}

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