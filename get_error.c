#include "shell.h"

/**
 * get_error - get the error according the builtin, syntax or permission
 * @datash: the data structure that contains arguments
 * @eval: error value
 * Return: error
 */
int get_error(data_shell *datash, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
		error = env_err(datash);
		break;
	case 126:
		error = error_path_126(datash);
		break;
	case 127:
		error = err_not_found(datash);
		break;
	case 2:
		if (_strcmp("exit", datash->args[0]) == 0)
			error = err_exit_shell(datash);
		else if (_strcmp("cd", datash->args[0]) == 0)
			error = err_get_cd(datash);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	datash->status = eval;
	return (eval);
}
