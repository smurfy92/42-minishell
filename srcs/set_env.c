/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtranchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/03 11:20:05 by jtranchi          #+#    #+#             */
/*   Updated: 2016/05/02 15:30:49 by jtranchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minish.h"

t_env		*ft_parse_env(char **env)
{
	t_env		*lst;

	lst = NULL;
	while (*env)
	{
		lst = ft_add_lst(ft_create_lst(*env), lst);
		env++;
	}
	return (lst);
}

int			ft_get_val_exists(t_term *term, char *str)
{
	t_env		*lst;

	lst = term->lst;
	if (!lst)
		return (0);
	while (lst->next && ft_strcmp(lst->var, str))
		lst = lst->next;
	if (lst && ft_strcmp(lst->var, str) == 0)
		return (1);
	else
		return (0);
}

void		ft_check_env(t_term *term)
{
	char *buf;

	buf = NULL;
	if (!ft_get_val_exists(term, "HOME"))
		ft_process_setenv(term, "HOME", "/nfs/2015/j/jtranchi");
	if (!ft_get_val_exists(term, "SHLVL"))
		ft_process_setenv(term, "SHLVL", "1");
	if (!ft_get_val_exists(term, "PWD"))
		ft_process_setenv(term, "PWD", getwd(buf));
	if (!ft_get_val_exists(term, "OLDPWD"))
		ft_process_setenv(term, "OLDPWD", getwd(buf));
	if (!ft_get_val_exists(term, "PATH"))
		ft_process_setenv(term, "PATH",
"/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/bin:/opt/X11/bin:/usr/local/munki");
}

t_term		*ft_set_term(char **env, t_env *lst)
{
	t_term		*term;

	term = (t_term*)malloc(sizeof(t_term));
	term->u = NULL;
	term->i = 0;
	term->env = env;
	term->lst = lst;
	signal(SIGINT, ft_prompt);
	signal(SIGTSTP, ft_prompt);
	signal(SIGQUIT, ft_prompt);
	signal(SIGKILL, ft_prompt);
	signal(SIGHUP, ft_prompt);
	signal(SIGTERM, ft_prompt);
	return (term);
}

char		*ft_get_val(t_term *term, char *str)
{
	t_env		*lst;

	lst = term->lst;
	while (lst->next && ft_strcmp(lst->var, str))
		lst = lst->next;
	if (lst && ft_strcmp(lst->var, str) == 0)
		return (lst->val);
	else
		return (NULL);
}
