#include "shell.h"

/**
 * cd_shell - changes current directory
 * @shell_data: data relevant to the shell
 * Return: 1 on success
 */
int cd_shell(data_shell *shell_data)
{
	char *directory;
	int is_home, is_home2, is_ddash;

	directory = shell_data->args[1];

	if (directory != NULL)
	{
		is_home = _strcmp("$HOME", directory);
		is_home2 = _strcmp("~", directory);
		is_ddash = _strcmp("--", directory);
	}

	if (directory == NULL || !is_home || !is_home2 || !is_ddash)
	{
		cd_to_home(shell_data);
		return (1);
	}

	if (_strcmp("-", directory) == 0)
	{
		cd_previous(shell_data);
		return (1);
	}

	if (_strcmp(".", directory) == 0 || _strcmp("..", directory) == 0)
	{
		cd_dot(shell_data);
		return (1);
	}

	cd_to(shell_data);

	return (1);
}
