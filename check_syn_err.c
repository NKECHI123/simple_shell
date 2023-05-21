#include "shell.h"

/**
 * repeated_char - counts the repetitions of a char
 *
 * @input: input string
 * @count: count of repetitions
 * Return: repetitions
 */
int repeated_char(char *input, int count)
{
	if (*(input - 1) == *input)
		return (repeated_char(input - 1, count + 1));

	return (count);
}

/**
 * error_sep_op - finds syntax errors
 * @input: input string
 * @index: current index
 * @last: last char read
 * Return: index of error. 0 when there are no errors
 */
int error_sep_op(char *input, int index, char last)
{
	int count = 0;

	if (*input == '\0')
		return (0);
	if (*input == ' ' || *input == '\t')
		return (error_sep_op(input + 1, index + 1, last));
	if (*input == ';')
	{
		if (last == '|' || last == '&' || last == ';')
			return (index);
	}

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (index);

		if (last == '|')
		{
			count = repeated_char(input, 0);
			if (count == 0 || count > 1)
				return (index);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (index);

		if (last == '&')
		{
			count = repeated_char(input, 0);
			if (count == 0 || count > 1)
				return (index);
		}
	}

	return (error_sep_op(input + 1, index + 1, *input));
}

/**
 * first_char - finds index of the first char
 *
 * @input: input string
 * @index: index
 * Return: 1 if there is an error. 0 in other case.
 */
int first_char(char *input, int *index)
{
	for (*index = 0; input[*index]; *index += 1)
	{
		if (input[*index] == ' ' || input[*index] == '\t')
			continue;

		if (input[*index] == ';' || input[*index] == '|' || input[*index] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * print_syn_err - prints when a syntax error is found
 *
 * @shell_data: data structure
 * @in: input string
 * @idx: index of the error
 * @bool_val: to control msg error
 * Return: no return
 */
void print_syn_err(data_shell *shell_data, char *in, int idx, int bool_val)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (in[idx] == ';')
	{
		if (bool_val == 0)
			msg = (in[idx + 1] == ';' ? ";;" : ";");
		else
			msg = (in[idx - 1] == ';' ? ";;" : ";");
	}

	if (in[idx] == '|')
		msg = (in[idx + 1] == '|' ? "||" : "|");

	if (in[idx] == '&')
		msg = (in[idx + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = int_to_string(shell_data->counter);
	length = _strlen(shell_data->prog_name[0]) + _strlen(counter);
	length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == NULL)
	{
		free(counter);
		return;
	}
	_strcpy(error, shell_data->prog_name[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, msg2);
	_strcat(error, msg);
	_strcat(error, msg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}

/**
 * check_syn_err - intermediate function to
 * find and print a syntax error
 *
 * @shell_data: data structure
 * @input: input string
 * Return: 1 if there is an error. 0 in other case
 */
int check_syn_err(data_shell *shell_data, char *input)
{
	int begin = 0;
	int f_char = 0;
	int index = 0;

	f_char = first_char(input, &begin);
	if (f_char == -1)
	{
		print_syn_err(shell_data, input, begin, 0);
		return (1);
	}

	index = error_sep_op(input + begin, 0, *(input + begin));
	if (index != 0)
	{
		print_syn_err(shell_data, input, begin + index, 1);
		return (1);
	}

	return (0);
}
