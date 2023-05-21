#include "shell.h"

/**
 * env_err - error message for env in get_env.
 * @s_data: data relevant (counter, arguments)
 * Return: error message.
 */
char *env_err(data_shell *s_data)
{
	int length;
	char *error;
	char *line_str;
	char *msg;

	line_str = int_to_string(s_data->counter);
	msg = ": Unable to add/remove from environment\n";
	length = _strlen(s_data->prog_name[0]) + _strlen(line_str);
	length += _strlen(s_data->args[0]) + _strlen(msg) + 4;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(line_str);
		return (NULL);
	}

	_strcpy(error, s_data->prog_name[0]);
	_strcat(error, ": ");
	_strcat(error, line_str);
	_strcat(error, ": ");
	_strcat(error, s_data->args[0]);
	_strcat(error, msg);
	_strcat(error, "\0");
	free(line_str);

	return (error);
}

/**
 * error_path_126 - error message for path and failure denied permission.
 * @s_data: data relevant (counter, arguments).
 *
 * Return: The error string.
 */
char *error_path_126(data_shell *s_data)
{
	int length;
	char *line_str;
	char *error;

	line_str = int_to_string(s_data->counter);
	length = _strlen(s_data->prog_name[0]) + _strlen(line_str);
	length += _strlen(s_data->args[0]) + 24;
	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(error);
		free(line_str);
		return (NULL);
	}
	_strcpy(error, s_data->prog_name[0]);
	_strcat(error, ": ");
	_strcat(error, line_str);
	_strcat(error, ": ");
	_strcat(error, s_data->args[0]);
	_strcat(error, ": Permission denied\n");
	_strcat(error, "\0");
	free(line_str);
	return (error);
}
