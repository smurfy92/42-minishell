/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/15 17:39:35 by jtranchi          #+#    #+#             */
/*   Updated: 2016/02/15 17:39:36 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

void		ft_process_unsetenv(t_term *term, char *s1)
{
	t_env *lst;

	lst = term->lst;
	if (!s1)
	{
		ft_putendl("minish: unsetenv: Invalid option");
		ft_putendl("unsetenv NAME");
	}
	else
	{
		if (ft_strcmp(lst->var, s1) == 0)
			term->lst = lst->next;
		while (lst->next && ft_strcmp((lst->next)->var, s1) != 0)
			lst = lst->next;
		(lst->next) ? (lst->next = lst->next->next) : 0;
	}
}

void		ft_process_setenv(t_term *term, char *s1, char *s2)
{
	t_env *lst;

	lst = term->lst;
	if (!s1 || !s2)
	{
		ft_putendl("minish: setenv: Invalid option");
		ft_putendl("setenv NAME VALUE");
	}
	else
	{
		lst = (t_env*)malloc(sizeof(t_env));
		lst->var = s1;
		lst->val = s2;
		lst->next = NULL;
		term->lst = ft_add_lst(lst, term->lst);
	}
}

void		ft_cd(t_term *term)
{
	struct stat			bufstat;

	if (term->cmds[1] && ft_strcmp(term->cmds[1], "-") == 0)
	{
		if (!ft_get_val_exists(term, "OLDPWD"))
			return (ft_putendl("NO OLDPWD"));
		chdir(ft_get_env_by_name(term, "OLDPWD"));
	}
	else if (!term->cmds[1] || (term->cmds[1] &&
	ft_strcmp(term->cmds[1], "~") == 0))
		return (ft_cd_home(term));
	else
	{
		if (!ft_get_val_exists(term, "PWD"))
			return (ft_putendl("NO PWD"));
		if (lstat(term->cmds[1], &bufstat) == -1 && term->cmds[1])
			return (ft_putendl(ft_strjoin(
			"cd: no such file or directory: ", term->cmds[1])));
	}
	ft_cd_reset(term);
}

int			ft_check_builtin(t_term *term)
{
	if (ft_strequ(term->cmds[0], "cd") == 1)
		ft_cd(term);
	else if (ft_strequ(term->cmds[0], "env") == 1)
		(!term->cmds[1]) ? ft_display_env(term) : ft_env_options(term);
	else if (ft_strequ(term->cmds[0], "setenv") == 1)
		ft_process_setenv(term, term->cmds[1], term->cmds[2]);
	else if (ft_strequ(term->cmds[0], "unsetenv") == 1)
		ft_process_unsetenv(term, term->cmds[1]);
	else if (ft_strequ(term->cmds[0], "exit") == 1)
		exit(0);
	else
		return (0);
	term->i = 0;
	term->u = NULL;
	return (1);
}

int			main(int argc, char **argv, char **env)
{
	t_term		*term;

	term = ft_set_term(env, ft_parse_env(env));
	ft_check_env(term);
	while (42)
	{
		argc = -1;
		write(1, "$> ", 3);
		argv[0] = NULL;
		get_next_line(0, &argv[0]);
		term->cmdsplit = NULL;
		term->path = NULL;
		term->cmdsplit = ft_strsplit(argv[0], ';');
		if (!argv[0])
			ft_exit();
		while (term->cmdsplit && term->cmdsplit[++argc])
		{
			term->cmds = NULL;
			term->cmdsplit[argc] = ft_tab_replace(&term->cmdsplit[argc]);
			term->cmds = ft_strsplit(term->cmdsplit[argc], ' ');
			if (term->cmds[0])
				(!ft_check_builtin(term)) ? ft_check_in_path(term) : 0;
		}
	}
	return (0);
}
