/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_options.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalliou <mgalliou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/28 13:58:06 by mgalliou          #+#    #+#             */
/*   Updated: 2017/07/21 13:05:19 by mgalliou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static void	illegal_opt(char c)
{
	ft_printf("ls: illegal option -- %c\n", c);
	ft_printf("usage: ft_ls [-%s] [file ...]\n", OPTIONS);
	exit(EXIT_FAILURE);
}

static char	*add_opt(char *opts, char opt)
{
	opts[opt] = opt;
	if (opt == 'f')
		opts['a'] = 'a';
	else if (opt == 'n')
		opts['l'] = 'l';
	return (opts);
}

static int	isopt(int c)
{
	if (ft_strchr(OPTIONS, c))
		return (1);
	return (0);
}

char		*get_options(char **av, int *i)
{
	char	*opts;
	int		j;

	opts = ft_strnew(128);
	while (av[*i] && ft_strcmp(av[*i], "--") && (av[*i][0] == '-' &&
		av[*i][1]))
	{
		j = 0;
		while (av[*i][++j])
		{
			if (isopt(av[*i][j]))
				opts = add_opt(opts, av[*i][j]);
			else
				illegal_opt(av[*i][j]);
		}
		*i += 1;
	}
	if (av[*i] && !(ft_strcmp(av[*i], "--")))
		*i += 1;
	return (opts);
}
