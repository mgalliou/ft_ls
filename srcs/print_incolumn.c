/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_incolumns.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalliou <mgalliou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/27 12:07:12 by mgalliou          #+#    #+#             */
/*   Updated: 2017/07/27 14:57:09 by mgalliou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <sys/ioctl.h>

static void	print_columns(t_rb_node *files, char *opts)
{
	if (files)
	{
		if (opts['r'])
			ft_swap(&files->left, &files->right);
		print_columns(files->left, opts);
		print_filename(((t_file*)files->item), opts);
		ft_printf("\n");
		print_columns(files->right, opts);
	}
}

void		print_incolumn(t_rb_node *files, char *opts)
{
	struct winsize	wsize;

	ioctl(0, TIOCGWINSZ, &wsize);
	print_columns(files, opts);
}
