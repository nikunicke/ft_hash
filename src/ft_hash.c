/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 16:25:30 by npimenof          #+#    #+#             */
/*   Updated: 2020/11/19 16:18:04 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_hash.h"

t_hash	*init_hash_table(size_t type, size_t (*hash_func)())
{
	t_hash	*table;

	if (!(table = ft_memalloc(sizeof(t_hash))))
		return (NULL);
	if (!(table->arr = ft_memalloc(type * TABLE_SIZE)))
		return (NULL);
	table->hash = hash_func;
	table->size = TABLE_SIZE;
	table->used = 0;
	return (table);
}

size_t	ft_hash(void *ptr, size_t size)
{
	size_t			hash_value;
	unsigned char	*c;

	c = (unsigned char *)ptr;
	hash_value = 0;
	while (size)
	{
		if (*c)
		{
			hash_value += *c;
			hash_value = (hash_value * *c) % (TABLE_SIZE);
		}
		size--;
		c++;
	}
	return (hash_value);
}

void	ft_del(t_list **list, void *p, size_t s)
{
	t_list	*tmp;
	t_list	*prev;

	if (!(*list) | !p)
		return ;
	if (!(*list)->next)
	{
		free(*list);
		*list = NULL;
		return ;
	}
	prev = *list;
	tmp = *list;
	while ((tmp = tmp->next))
	{
		if (!(ft_memcmp(tmp->content, p, s)))
		{
			prev->next = tmp->next;
			free(tmp);
			tmp = NULL;
			return ;
		}
		prev = tmp;
	}
}

void	*ft_unique(t_list *l, void *ptr, size_t s)
{
	while (l)
	{
		if (!(ft_memcmp(l->content, ptr, s)))
			return (l->content);
		l = l->next;
	}
	return (NULL);
}

void	*ft_get(t_hash *table, void *ptr, size_t size)
{
	size_t	i;

	if (!ptr || !table)
		return (NULL);
	i = table->hash(ptr, size);
	return (ft_unique((t_list *)table->arr[i], ptr, size));
}
