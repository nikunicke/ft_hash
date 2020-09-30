/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 16:17:59 by npimenof          #+#    #+#             */
/*   Updated: 2020/09/30 18:22:22 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HASH_H
# define FT_HASH_H
# define TABLE_SIZE 1024
# include "libft.h"

// t_hash represents a hash table
//	- arr: The location of our memory area
//	- hash: The hash function used for this hash table
//	- used: How many items the hash table includes
//	- size: The size of the memory area
// Note that every index in the memory area can be pointed
// to a linked list.
typedef struct	s_hash
{
	void		**arr;
	size_t		(*hash)();
	size_t		used;
	size_t		size;
}				t_hash;



t_hash	*init_hash_table(size_t type, size_t (*hash_func)());
size_t	ft_hash(void *ptr, size_t size);

void	*ft_insert(t_hash *table, void *ptr, size_t size);
void	*ft_update(t_hash *t, void *ptr, size_t size, void *(*f)(void *p));
void	ft_delete(t_hash *t, void *p, size_t s, void (*del)(void *p));
void	*ft_get(t_hash *table, void *ptr, size_t size);
void	ft_ptable(t_hash *table);


#endif