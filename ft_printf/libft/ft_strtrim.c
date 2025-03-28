/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saslanya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:54:35 by saslanya          #+#    #+#             */
/*   Updated: 2025/01/19 15:54:39 by saslanya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*ptr;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		++start;
	end = ft_strlen(s1);
	while (ft_strchr(set, s1[end]) && start < end)
		--end;
	ptr = (char *)malloc((end - start + 2) * sizeof(char));
	if (ptr)
		ft_strlcpy(ptr, s1 + start, end - start + 2);
	return (ptr);
}
/* need test */
