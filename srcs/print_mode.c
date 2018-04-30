/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_mode.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalliou <mgalliou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/11 15:17:09 by mgalliou          #+#    #+#             */
/*   Updated: 2017/07/24 12:03:57 by mgalliou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static char	get_execpermi(mode_t mode, int id)
{
	if ((id == 1 && S_IXUSR & mode) || (id == 2 && S_IXGRP & mode) ||
			(id == 3 && S_IXOTH & mode))
	{
		if ((id == 1 && S_ISUID & mode) || (id == 2 && S_ISGID & mode))
			return ('s');
		if (id == 3 && S_ISVTX & mode)
			return ('t');
		return ('x');
	}
	if ((id == 1 && S_ISUID & mode) || (id == 2 && S_ISGID & mode))
		return ('S');
	if (id == 3 && S_ISVTX & mode)
		return ('T');
	return ('-');
}

static char	get_writepermi(mode_t mode, int id)
{
	if ((id == 1 && S_IWUSR & mode) || (id == 2 && S_IWGRP & mode) ||
			(id == 3 && S_IWOTH & mode))
		return ('w');
	return ('-');
}

static char	get_readpermi(mode_t mode, int id)
{
	if ((id == 1 && S_IRUSR & mode) || (id == 2 && S_IRGRP & mode) ||
			(id == 3 && S_IROTH & mode))
		return ('r');
	return ('-');
}

static char	get_type(mode_t mode)
{
	if (S_ISBLK(mode))
		return ('b');
	if (S_ISCHR(mode))
		return ('c');
	if (S_ISDIR(mode))
		return ('d');
	if (S_ISSOCK(mode))
		return ('s');
	if (S_ISLNK(mode))
		return ('l');
	if (S_ISFIFO(mode))
		return ('p');
	return ('-');
}

char		*get_mode(mode_t mode, char *str)
{
	str[0] = get_type(mode);
	str[1] = get_readpermi(mode, 1);
	str[2] = get_writepermi(mode, 1);
	str[3] = get_execpermi(mode, 1);
	str[4] = get_readpermi(mode, 2);
	str[5] = get_writepermi(mode, 2);
	str[6] = get_execpermi(mode, 2);
	str[7] = get_readpermi(mode, 3);
	str[8] = get_writepermi(mode, 3);
	str[9] = get_execpermi(mode, 3);
	str[10] = '\0';
	return (str);
}
