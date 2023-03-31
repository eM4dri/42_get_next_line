/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emadriga <emadriga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/12 18:51:46 by emadriga          #+#    #+#             */
/*   Updated: 2023/03/31 00:45:26 by emadriga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}


char	*ft_strchr(const char *s, int c)
{
	char	*mem;

	if (!s)
		return (NULL);
	mem = (char *)s;
	while (*mem != '\0')
	{
		if (*mem == (char)c)
			return (mem);
		mem++;
	}
	return (NULL);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*out;
	char	*mem;
	size_t	len;

	len = count * size;
	out = malloc(len);
	if (!out)
		return (0);
	mem = out;
	while (len-- > 0)
		*mem++ = '\0';
	return (out);
}
