#include "shell.h"

/**
 * add_variable_node - adds a variable at the end
 * of a variable list.
 * @head: head of the linked list.
 * @length_var: length of the variable.
 * @value: value of the variable.
 * @length_val: length of the value.
 * Return: address of the head.
 */
variable *add_variable_node(variable
**head, int length_var, char *value, int length_val)
{
	variable *new_variable, *temp_variable;

	new_variable = malloc(sizeof(variable));
	if (new_variable == NULL)
		return (NULL);

	new_variable->length_var = length_var;
	new_variable->value = value;
	new_variable->length_val = length_val;

	new_variable->next = NULL;
	temp_variable = *head;

	if (temp_variable == NULL)
	{
		*head = new_variable;
	}
	else
	{
		while (temp_variable->next != NULL)
			temp_variable = temp_variable->next;
		temp_variable->next = new_variable;
	}

	return (*head);
}

/**
 * free_variable_list - frees a variable list
 * @head: head of the linked list.
 * Return: no return.
 */
void free_variable_list(variable **head)
{
	variable *temp_variable;
	variable *curr_variable;

	if (head != NULL)
	{
		curr_variable = *head;
		while ((temp_variable = curr_variable) != NULL)
		{
			curr_variable = curr_variable->next;
			free(temp_variable);
		}
		*head = NULL;
	}
}
