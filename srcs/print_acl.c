/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_acl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalliou <mgalliou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/24 17:30:55 by mgalliou          #+#    #+#             */
/*   Updated: 2017/07/25 16:53:18 by mgalliou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <sys/acl.h>

static int	print_line(char *str, int i, int *field)
{
	field[1] = i;
	while (str[i] && str[i] != ':')
		i++;
	str[i++] = '\0';
	while (str[i] != ':')
		i++;
	field[2] = i++;
	while (str[i] && str[i] != ':')
		i++;
	str[i] = '\0';
	while (str[i] != ':')
		i++;
	field[3] = i++;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] == ':')
			str[i] = ' ';
		i++;
	}
	str[i++] = '\0';
	ft_printf("%2d: %s%s%s\n", field[0], &str[field[1]], &str[field[2]],
			&str[field[3]]);
	field[0]++;
	return (i);
}

void		print_acl(t_file *file, char *opts)
{
	acl_t	acl;
	char	*str;
	int		i;
	ssize_t	len;
	int		field[4];

	i = 0;
	if ((acl = acl_get_file(file->fullname, ACL_TYPE_EXTENDED)))
	{
		str = acl_to_text(acl, &len);
		while (str[i] && str[i] != '\n')
			i++;
		i++;
		field[0] = 0;
		while (i < len)
			i = print_line(str, i, field);
		acl_free((void*)acl);
		acl_free((void*)str);
	}
}
