/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_to_str_array.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 14:51:54 by mprofett          #+#    #+#             */
/*   Updated: 2023/11/28 14:26:03 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_add_to_str_array(char **src, char *str_to_add)
{
	char	**result;
	int		str_array_len;
	int		i;

	str_array_len = ft_strarraylen(src);
	result = malloc(sizeof(char *) * (str_array_len + 2));
	if (!result)
		return (NULL);
	i = 0;
	while (i < str_array_len)
	{
		result[i] = *(src + i);
		++i;
	}
	if (str_to_add)
		result[i] = str_to_add;
	result[++i] = NULL;
	free(src);
	return (result);
}
