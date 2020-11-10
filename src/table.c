/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 14:34:42 by npimenof          #+#    #+#             */
/*   Updated: 2020/11/10 13:18:22 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hash.h"

void	*ft_insert(t_hash *table, void *ptr, size_t size)
{
	size_t	i;

	if (!ptr || !table)
		return (NULL);
	i = table->hash(ptr, size);
	if (ft_unique((t_list *)table->arr[i], ptr, size))
		return (NULL);
	ft_lstadd((t_list **)&table->arr[i], ft_lstcontent(ptr));
	((t_list *)table->arr[i])->content_size = size;
	table->used++;
	return (ptr);
}

void	*ft_update(t_hash *t, void *p, size_t s, void *(*f)(void *p))
{
	void	*item;

	if (!(item = ft_get(t, p, s)))
		return (NULL);
	if (!(item = f(item)))
		return (NULL);
	ft_del((t_list **)&t->arr[t->hash(p, s)], p, s);
	ft_insert(t, item, s);
	return (item);
}

void	ft_delete(t_hash *t, void *p, size_t s, void (*del)(void *p))
{
	void	*item;

	if (!(item = ft_get(t, p, s)))
		return ;
	ft_del((t_list **)&t->arr[t->hash(p, s)], p, s);
	del(item);
}

void	ft_map(t_hash *t, void (*f)())
{
	int		i;
	t_list	*l;

	i = 0;
	while (i < TABLE_SIZE)
	{
		l = t->arr[i];
		while (l)
		{
			f(l->content, l->content_size);
			l = l->next;
		}
		i++;
	}
}
