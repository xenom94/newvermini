/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iabboudi <iabboudi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 17:05:45 by stakhtou          #+#    #+#             */
/*   Updated: 2024/11/16 22:27:14 by iabboudi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

char	*check_path(char **cmd, char **path)
{
	int		i;
	char	*new_cmd;
	char	*new_path;

	i = 0;
	while (path[i])
	{
		new_cmd = ft_strjoin("/", cmd[0]);
		new_path = ft_strjoin(path[i], new_cmd);
		free(new_cmd);
		if (access(new_path, F_OK) == 0)
		{
			ft_free(path);
			return (new_path);
		}
		free(new_path);
		i++;
	}
	ft_free(path);
	return (NULL);
}

char	*plo(char **cmd)
{
	if (access(cmd[0], F_OK) == 0)
		return (ft_strdup(cmd[0]));
	else
		return (NULL);
}

char	*get_path(char **cmd)
{
	int		i;
	char	**path;
	char	*env_path;
		if (!cmd[0])
		return (NULL);
	if(ft_strchr(cmd[0], '/'))
	{
		if(!cmd)
			return (NULL);
		return (plo(cmd));
	}
	env_path = NULL;
	i = 0;
	while (g_vars.env[i])
	{
		if (ft_strncmp(g_vars.env[i], "PATH=", 5) == 0)
		{
			env_path = g_vars.env[i] + 5;
			break ;
		}
		i++;
	}
	if (env_path == NULL || *env_path == '\0')
		return (NULL);
	path = ft_split(env_path, ":");
	return (check_path(cmd, path));
}
