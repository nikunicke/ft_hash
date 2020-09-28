/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 16:25:30 by npimenof          #+#    #+#             */
/*   Updated: 2020/09/28 14:31:53 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_hash.h"
#include <stdio.h>

t_hash	*init_hash_table(size_t type, size_t (*hash_func)())
{
	t_hash	*table;

	if (!(table = malloc(sizeof(t_hash))))
		return (NULL);
	if (!(table->arr = malloc(type * TABLE_SIZE)))
		return (NULL);
	ft_bzero(table->arr, TABLE_SIZE);
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
			hash_value = (hash_value * *c) % TABLE_SIZE;
		}
		size--;
		c++;
	}
	return (hash_value); 
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

void	*ft_insert(void *ptr, t_hash *table)
{
	size_t	i;

	if (!ptr || !table)
		return (NULL);
	i = table->hash(ptr, 7);
	if (ft_unique((t_list *)table->arr[i], ptr, 7))
		return (NULL);
	ft_lstadd_sorted((t_list **)&table->arr[i], ft_lstcontent(ptr));
	table->used++;
	return (ptr);
}

void	*ft_get(void *ptr, t_hash *table)
{
	size_t	i;

	if (!ptr || !table)
		return (NULL);
	i = table->hash(ptr, 5);
	return (ft_unique((t_list *)table->arr[i], ptr, 5));
}

void	ft_ptable(t_hash *table)
{
	int		i;
	t_list	*tmp;

	i = 0;
	while (i < TABLE_SIZE)
	{
		tmp = table->arr[i];
		while (tmp)
		{
			printf("index: %d  -- '%s'\n", i, tmp->content);
			tmp = tmp->next;
		}
		i++;
	}
}
