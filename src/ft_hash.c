/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 16:25:30 by npimenof          #+#    #+#             */
/*   Updated: 2020/11/02 12:56:48 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_hash.h"
#include <stdio.h>

// init_hash_table initiates the t_hash type, which
// represents our hash table
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

// ft_hash transforms a memory area to a hash, which
// fits into the initiated hash table.
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

// ft_insert inserts an element to the hash table. Insertion
// will return NULL if we attempt to add items with identical
// identifiers. Otherwise returns NULL
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

// ft_get returns a pointer to the found table element, otherwise NULL
void	*ft_get(t_hash *table, void *ptr, size_t size)
{
	size_t	i;

	if (!ptr || !table)
		return (NULL);
	i = table->hash(ptr, size);
	return (ft_unique((t_list *)table->arr[i], ptr, size));
}

void	*ft_update(t_hash *t, void *p, size_t s, void *(*f)(void *p))
{
	void	*item;
	// size_t	i;

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
	ft_del((t_list **)&t->arr[t->hash(p, s)], p , s);
	del(item);
}

// ft_ptable prints all elemets of a table to the stdout
void	ft_ptable(t_hash *table)
{
	size_t	i;
	t_list	*tmp;

	i = 0;
	while (i < TABLE_SIZE)
	{
		tmp = table->arr[i];
		while (tmp)
		{
			printf("index: %zu  -- '%s'\n", i, tmp->content);
			tmp = tmp->next;
		}
		i++;
	}
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

void	ft_converge(t_hash *t, void *p, void (*f)())
{
	int		i;
	t_list	*l;

	if (!t || !p)
		return ;
	i = 0;
	while (i < TABLE_SIZE)
	{
		l = t->arr[i];
		while (l)
		{
			f(p, l->content, l->content_size);
			l = l->next;
		}
		i++;
	}
}
