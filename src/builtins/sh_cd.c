#include "../../include/minishell.h"

/**
 * @brief Allocates a new token with the oldpwd variable
 * @return The new token OLDPWD=...
 */
static t_token	*set_var_oldpwd()
{
	char	*cwd;
	char	*tmp;
	char	*curr_pwd_text;
	t_token	*curr_pwd;

	p(Y"testing set_var_oldpwd\n" RST);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	tmp = ft_strdup("OLDPWD=");
	if (!tmp)
		return (free(cwd), NULL);
	curr_pwd_text = ft_strjoin(tmp, cwd);
	p(Y"curr_pwd_text: %s\n" RST, curr_pwd_text);
	free(cwd);
	free(tmp);
	if (!curr_pwd_text)
		return (NULL);
	curr_pwd = token_append(NULL, curr_pwd_text, TOKEN_WORD_NVAR);
	p(Y"curr_pwd: %s\n" RST, curr_pwd->data);
	free(curr_pwd_text);
	if (!curr_pwd)
		return (NULL);
	return (curr_pwd);
}

// Function to change the current working directory
int	sh_cd(t_app *app, t_token *token)
{
	char	*path;
	t_token	*old_pwd;

	(void)token;
	//TESTING
	if (sh_pwd(app, token) == -1)
		return (-1);
	//END TESTING

	old_pwd = set_var_oldpwd();
	if (!old_pwd)
		return (-1); // malloc failed
	if (!token->next || strncmp(token->next->data, "~", 1) == 0)
		path = get_env_var("HOME", app->env);
	else
		path = token->next->data;
	if (chdir(path) == -1)
	{
		p(RED "cd: %s: No such file or directory\n" RST, token->next->data);
		app->exit_status = 1;
		return (1);
	}

	//TESTING
	// the exit status of cd is now comming from pwd - because of this test
	if (sh_pwd(app, token) == -1)
		return (-1);
	//END TESTING

	if (get_env_var("OLDPWD", app->env))
		handle_replace_export(app, old_pwd);
	else
		handle_append_export(app, old_pwd); // if there is no OLDPWD, append it
	return (0);
}
