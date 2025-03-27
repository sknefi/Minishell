
#ifndef MOCKED_H
#define MOCKED_H

#include "structs.h"
// this will be delete before evaluation
// I am just testing exec. Filip :)

t_token		*mocked_token_pwd(void);
t_token		*mocked_token_env(void);
t_token		*mocked_token_export(void);
t_token		*mocked_token_unset(void);
t_token		*mocked_token_exit(void);
t_token		*mocked_token_echo(void);
t_token		*mocked_token_invalid_command(void);
t_token		*mocked_token_invalid_command_input(void);
t_token		*mocked_token_cd_01(void);
t_token		*mocked_token_cd_02(void);
t_token		*mocked_token_cd_03(void);
t_token		*mocked_token_cd_04(void);
t_token		*mocked_token_cd_05(void);
#endif