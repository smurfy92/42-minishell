/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aymeric.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 14:19:02 by jtranchi          #+#    #+#             */
/*   Updated: 2016/03/03 14:19:05 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"
#include <errno.h>

void		ft_create_process(t_term *term)
{
	int		y;
	int		buf;

	ft_refresh_env(term);
	term->father = fork();
	if (term->father > 0)
		waitpid(term->father, &buf, 0);
	if (term->father == 0)
	{
		ft_check_cmds(term);
		if (term->i)
			ft_env_i(term);
		y = -1;
		while (term->cmds[++y])
			(ft_strcmp(term->cmds[y], term->path) == 0) ?\
			term->cmds = &term->cmds[y] : 0;
		execve(term->path, term->cmds, term->env);
		term->path = NULL;
	}
}

int			ft_check_in_path(t_term *term)
{
	char		**tab;
	int			i;

	i = -1;
	tab = ft_strsplit(ft_get_env_by_name(term, "PATH"), ':');
	while (tab && tab[++i] && !term->path)
	{
		tab[i] = ft_strjoin(tab[i], "/");
		tab[i] = ft_strjoin(tab[i], term->cmds[0]);
		if (access(tab[i], X_OK) == 0)
			term->path = ft_strdup(tab[i]);
	}
	if (term->cmds[0][0] == '.' && term->cmds[0][1] == '/')
		(access(&term->cmds[0][2], X_OK) == 0) ? term->path =\
		ft_strdup(&term->cmds[0][2]) : ft_permission_denied(term->cmds[0]);
	(access(term->cmds[0], X_OK) == 0) ? \
	term->path = ft_strdup(term->cmds[0]) : 0;
	if (term->path)
	{
		ft_create_process(term);
		return (1);
	}
	else
		ft_putendl(ft_strjoin("minish: command not found: ", term->cmds[0]));
	return (0);
}

void		ft_refresh_env(t_term *term)
{
	t_env		*lst;
	int			i;

	lst = term->lst;
	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	lst = term->lst;
	i = -1;
	while (lst)
	{
		if (ft_strcmp(lst->var, "SHLVL") == 0)
			lst->val = ft_itoa(ft_atoi(lst->val) + 1);
		term->env[++i] = ft_strdup(
		ft_strjoin(ft_strjoin(lst->var, "="), lst->val));
		lst = lst->next;
	}
}

void		ft_prompt(int nb)
{
	nb = 0;
	ft_putstr("\n$> ");
}

char		*ft_get_env_by_name(t_term *term, char *name)
{
	t_env	*lst;

	lst = term->lst;
	while (lst)
	{
		if (ft_strcmp(lst->var, name) == 0)
			return (lst->val);
		lst = lst->next;
	}
	return (NULL);
}
