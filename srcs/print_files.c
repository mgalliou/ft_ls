/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalliou <mgalliou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/05 12:32:28 by mgalliou          #+#    #+#             */
/*   Updated: 2017/07/27 14:56:31 by mgalliou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static void	print_oneperline(t_rb_node *files, char *opts)
{
	if (files)
	{
		if (opts['r'])
			ft_swap(&files->left, &files->right);
		print_oneperline(files->left, opts);
		if (opts['l'])
			print_long_format(((t_file*)files->item), opts);
		print_filename(((t_file*)files->item), opts);
		ft_printf("\n");
		if (opts['@'] && (opts['l']))
			print_xattr(((t_file*)files->item), opts);
		if (opts['e'] && (opts['l']))
			print_acl((t_file*)files->item, opts);
		print_oneperline(files->right, opts);
	}
}

static int	print_acrosspage(t_rb_node *files, char *opts, int fst)
{
	if (files)
	{
		if (opts['r'])
			ft_swap(&files->left, &files->right);
		fst = print_acrosspage(files->left, opts, fst);
		if (!fst)
			ft_printf(", ");
		print_filename(((t_file*)files->item), opts);
		fst = 0;
		fst = print_acrosspage(files->right, opts, fst);
	}
	return (fst);
}

static int	get_totalblock(t_rb_node *files, int nbr)
{
	if (files)
	{
		nbr = get_totalblock(files->left, nbr);
		nbr += ((t_file*)files->item)->stat.st_blocks;
		nbr = get_totalblock(files->right, nbr);
	}
	return (nbr);
}

void		print_files(t_rb_node *files, char *opts)
{
	if (files)
	{
		if (opts['l'] && ((t_file*)files->item)->name !=
				((t_file*)files->item)->fullname)
			ft_printf("total %d\n", (get_totalblock(files, 0)));
		if (!opts['m'] && (opts['l'] || opts['1']))
			print_oneperline(files, opts);
		else if (opts['m'])
		{
			print_acrosspage(files, opts, 1);
			ft_printf("\n");
		}
		else
			print_incolumn(files, opts);
		ft_memdel((void*)&((t_file*)files->item)->pad);
	}
}
