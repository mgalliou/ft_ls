/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgalliou <mgalliou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/20 13:37:29 by mgalliou          #+#    #+#             */
/*   Updated: 2017/07/26 18:04:30 by mgalliou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static int			ft_ls(t_rb_node *files, char *opts,
							int (*cmpf)(void *a, void *b), int fst)
{
	t_rb_node		*newfiles;

	if (files)
	{
		if (opts['r'])
			ft_swap(&files->left, &files->right);
		fst = ft_ls(files->left, opts, cmpf, fst);
		if ((S_ISDIR(((t_file*)files->item)->stat.st_mode)) &&
			(!isrelative(((t_file*)files->item)->name) ||
			((t_file*)files->item)->name == ((t_file*)files->item)->fullname))
		{
			if (!fst)
				ft_printf("\n");
			if (!fst || files->parent || files->left || files->right)
				ft_printf("%s:\n", ((t_file*)files->item)->fullname);
			newfiles = get_files(((t_file*)files->item)->fullname, opts, cmpf);
			print_files(newfiles, opts);
			fst = 0;
			if (opts['R'])
				fst = ft_ls(newfiles, opts, cmpf, fst);
			rb_delete(&newfiles, &filedel);
		}
		fst = ft_ls(files->right, opts, cmpf, fst);
	}
	return (fst);
}

static t_rb_node	*get_args(char **av, char *opts,
							int (*cmpf)(void *a, void *b))
{
	t_rb_node		*files;
	t_pad			*pad;

	files = NULL;
	if (!(pad = ft_memalloc(sizeof(t_pad))))
		exit(EXIT_FAILURE);
	if (!*av)
		rb_insert(&files, filenew(NULL, ".", opts, pad), NULL);
	else
		while (*av)
			rb_insert(&files, filenew(NULL, *av++, opts, pad), cmpf);
	if (!files && pad)
		ft_memdel((void*)&pad);
	return (files);
}

int					main(int ac, char **av)
{
	char			*opts;
	int				i;
	t_rb_node		*files;
	t_rb_node		*args;
	int				(*cmpf)(void *a, void *b);

	i = 1;
	files = NULL;
	opts = get_options(av, &i);
	cmpf = get_cmpf(opts);
	args = get_args(av + i, opts, cmpf);
	if (opts['d'])
		print_files(args, opts);
	else if (args)
	{
		extract_files(&files, args, opts);
		print_files(files, opts);
		i = (files ? 0 : 1);
		ft_ls(args, opts, cmpf, i);
	}
}
