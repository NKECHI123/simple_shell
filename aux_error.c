#include "shell.h"

/**
 * concat_err_msg - function that concatenates the error message
 *
 * @s_data: shell data containing relevant information
 * @msg: message to print
 * @err: output err message
 * @line_str: counter lines
 * Return: err message
 */
char *concat_err_msg(data_shell *s_data, char *msg, char *err, char *line_str)
{
	char *illegal_flag;

	_strcpy(err, s_data->prog_name[0]);
	_strcat(err, ": ");
	_strcat(err, line_str);
	_strcat(err, ": ");
	_strcat(err, s_data->args[0]);
	_strcat(err, msg);
	if (s_data->args[1][0] == '-')
	{
		illegal_flag = malloc(3);
		illegal_flag[0] = '-';
		illegal_flag[1] = s_data->args[1][1];
		illegal_flag[2] = '\0';
		_strcat(err, illegal_flag);
		free(illegal_flag);
	}
	else
	{
		_strcat(err, s_data->args[1]);
	}

	_strcat(err, "\n");
	_strcat(err, "\0");
	return (err);
}

/**
 * err_get_cd - err message for cd command
 * @s_data: data relevant (directory)
 * Return: err message
 */
char *err_get_cd(data_shell *s_data)
{
	int length, len_id;
	char *err, *line_str, *msg;

	line_str = int_to_string(s_data->counter);
	if (s_data->args[1][0] == '-')
	{
		msg = ": Illegal option ";
		len_id = 2;
	}
	else
	{
		msg = ": can't cd to ";
		len_id = _strlen(s_data->args[1]);
	}

	length = _strlen(s_data->prog_name[0]) + _strlen(s_data->args[0]);
	length += _strlen(line_str) + _strlen(msg) + len_id + 5;
	err = malloc(sizeof(char) * (length + 1));

	if (err == 0)
	{
		free(line_str);
		return (NULL);
	}

	err = concat_err_msg(s_data, msg, err, line_str);

	free(line_str);

	return (err);
}

/**
 * err_not_found - generic err message for command not found
 * @s_data: data relevant (counter, arguments)
 * Return: err message
 */
char *err_not_found(data_shell *s_data)
{
	int length;
	char *err;
	char *line_str;

	line_str = int_to_string(s_data->counter);
	length = _strlen(s_data->prog_name[0]) + _strlen(line_str);
	length += _strlen(s_data->args[0]) + 16;
	err = malloc(sizeof(char) * (length + 1));
	if (err == 0)
	{
		free(err);
		free(line_str);
		return (NULL);
	}
	_strcpy(err, s_data->prog_name[0]);
	_strcat(err, ": ");
	_strcat(err, line_str);
	_strcat(err, ": ");
	_strcat(err, s_data->args[0]);
	_strcat(err, ": not found\n");
	_strcat(err, "\0");
	free(line_str);
	return (err);
}

/**
 * err_exit_shell - generic err message for exit command
 * @s_data: data relevant (counter, arguments)
 *
 * Return: err message
 */
char *err_exit_shell(data_shell *s_data)
{
	int length;
	char *err;
	char *line_str;

	line_str = int_to_string(s_data->counter);
	length = _strlen(s_data->prog_name[0]) + _strlen(line_str);
	length += _strlen(s_data->args[0]) + _strlen(s_data->args[1]) + 23;
	err = malloc(sizeof(char) * (length + 1));
		if (err == 0)
	{
		free(line_str);
		return (NULL);
	}
	_strcpy(err, s_data->prog_name[0]);
	_strcat(err, ": ");
	_strcat(err, line_str);
	_strcat(err, ": ");
	_strcat(err, s_data->args[0]);
	_strcat(err, ": Illegal number: ");
	_strcat(err, s_data->args[1]);
	_strcat(err, "\n\0");
	free(line_str);

	return (err);
}
