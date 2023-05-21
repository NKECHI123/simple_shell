#include "shell.h"

/**
 * add_rvar_node - adds a variable at the end
 * of a r_var list.
 * @head: head of the linked list.
 * @var_len: length of the variable.
 * @value: value of the variable.
 * @val_len: length of the value.
 * Return: address of the head.
 */
r_var *add_rvar_node(r_var **head, int var_len, char *value, int val_len)
{
	r_var *new_node, *temp;

	new_node = malloc(sizeof(r_var));
	if (new_node == NULL)
		return (NULL);

	new_node->len_var = var_len;
	new_node->val = value;
	new_node->len_val = val_len;

	new_node->go_next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new_node;
	}
	else
	{
		while (temp->go_next != NULL)
			temp = temp->go_next;
		temp->go_next = new_node;
	}

	return (*head);
}

/**
 * free_rvar_list - frees a r_var list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_rvar_list(r_var **head)
{
	r_var *temp;
	r_var *current;

	if (head != NULL)
	{
		current = *head;
		while ((temp = current) != NULL)
		{
			current = current->go_next;
			free(temp);
		}
		*head = NULL;
	}
}
