/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hash.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npimenof <npimenof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 16:17:59 by npimenof          #+#    #+#             */
/*   Updated: 2020/09/28 14:30:50 by npimenof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_HASH_H
# define FT_HASH_H
# define TABLE_SIZE 1024
# include "libft.h"

typedef struct	s_hash
{
	void		**arr;
	size_t		(*hash)();
	size_t		used;
	size_t		size;
}				t_hash;



t_hash	*init_hash_table(size_t type, size_t (*hash_func)());
size_t	ft_hash(void *ptr, size_t size);

void	*ft_insert(void *ptr, t_hash *table);
void	*ft_get(void *ptr, t_hash *table);
void	ft_ptable(t_hash *table);


#endif