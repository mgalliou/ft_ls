/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalliou <mgalliou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 14:45:22 by mgalliou          #+#    #+#             */
/*   Updated: 2017/07/26 16:24:05 by mgalliou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

char			*create_path(char *dir, char *filename)
{
	char	*new;
	int		dlen;

	if (!dir)
		new = ft_strdup(filename);
	else
	{
		dlen = ft_strlen(dir);
		if (!(new = ft_strnew(dlen + ft_strlen(filename) + 1)))
			return (NULL);
		ft_strcpy(new, dir);
		new[dlen] = '/';
		ft_strcpy(&new[dlen + 1], filename);
	}
	return (new);
}
