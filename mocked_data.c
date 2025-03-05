#include "include/minishell.h"

// delete this before eval

t_token	*mocked_token_echo(void)
{
	t_token			*token;
	
	token = NULL;
	token = token_append(token, "echo", TOKEN_COMMAND);
	token_append(token, "-n", TOKEN_ARG);
	token_append(token, "-nnnn", TOKEN_ARG);
	token_append(token, "-nnnnna", TOKEN_WORD_NVAR);	// this should be returned from parser, that this is TOKEN_NVAR and not TOKEN_ARG
	token_append(token, "Hello", TOKEN_WORD_NVAR);
	token_append(token, "$USER", TOKEN_WORD_VAR);
	token_append(token, "!", TOKEN_WORD_NVAR);
	token_append(token, "How is ur day?", TOKEN_WORD_NVAR);
	return (token);
}

t_token	*mocked_token_cd(void)
{
	t_token			*token;
	
	token = NULL;
	token = token_append(token, "cd", TOKEN_COMMAND);
	// token_append(token, "../../../", TOKEN_WORD_NVAR);
	// token_append(token, "../../../qwe", TOKEN_WORD_NVAR); // doesnt exists
	return (token);
}

t_token	*mocked_token_pwd(void)
{
	t_token			*token;

	token = NULL;
	token = token_append(token, "pwd", TOKEN_COMMAND);
	return (token);
}

t_token	*mocked_token_env(void)
{
	t_token			*token;
	
	token = NULL;
	token = token_append(token, "env", TOKEN_COMMAND);
	return (token);
}

t_token	*mocked_token_export(void)
{
	t_token			*token;
	
	token = NULL;
	token = token_append(token, "export", TOKEN_COMMAND);
	token_append(token, "ASDW=testing", TOKEN_WORD_NVAR);

	// token_append(token, "EMPTYTWO", TOKEN_WORD_NVAR);	
	
	// Test case 2: Variable with empty value
	// token_append(token, "EMPTYTWO=", TOKEN_WORD_NVAR);
	
	// // Test case 3: Variable with spaces in value
	// token_append(token, "GREETINGTWO=hello world", TOKEN_WORD_NVAR);
	//  TODO for Tym, just send me "GREETINGTWO=hello" as a token, not "GREETINGTWO=hello world"

	// // Test case 4: Multiple equal signs
	// token_append(token, "PATHTWO=/usr/bin=/local/bin", TOKEN_WORD_NVAR);
	
	// // Test case 5: Just variable name (marks for export)
	// token_append(token, "EXPORTONLYTWO", TOKEN_WORD_NVAR);	
	return (token);
}

t_token	*mocked_token_unset(void)
{
	t_token			*token;
	
	token = NULL;
	token = token_append(token, "unset", TOKEN_COMMAND);
	token_append(token, "TESTMINISHELL", TOKEN_WORD_NVAR);
	return (token);
}

t_token	*mocked_token_exit(void)
{
	t_token			*token;
	
	token = NULL;
	token_append(token, "exit", TOKEN_COMMAND);
	return (token);
}