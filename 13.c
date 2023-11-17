#include "myshell.h"

/**
 * my_custom_add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @data: str field of node
 * @index: node index used by history
 *
 * Return: size of list
 */

list_t *my_custom_add_node(list_t **head, const char *data, int index)
{
	list_t *new_node;

	if (!head)
		return (NULL);

	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->index = index;

	if (data)
	{
		new_node->data = _strdup(data);
		if (!new_node->data)
		{
			free(new_node);
			return (NULL);
		}
	}

	new_node->next = *head;
	*head = new_node;

	return (new_node);
}

/**
 * my_custom_add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @data: str field of node
 * @index: node index used by history
 *
 * Return: size of list
 */

list_t *my_custom_add_node_end(list_t **head, const char *data, int index)
{
	list_t *new_node, *current_node;

	if (!head)
		return (NULL);
	current_node = *head;
	new_node = malloc(sizeof(list_t));

	if (!new_node)
		return (NULL);

	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->index = index;

	if (data)
	{
		new_node->data = _strdup(data);
		if (!new_node->data)
		{
			free(new_node);
			return (NULL);
		}
	}

	if (current_node)
	{
		while (current_node->next)
			current_node = current_node->next;
		current_node->next = new_node;
	}
	else
	{
		*head = new_node;
	}

	return (new_node);
}


/**
 * my_custom_print_list_data - prints the str element of a list_t linked list
 * @head: pointer to first node
 *
 * Return: size of list
 */

size_t my_custom_print_list_data(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		puts(head->data ? head->data : "(nil)");
		puts("\n");
		head = head->next;
		count++;
	}

	return (count);
}


/**
 * my_custom_delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */

int my_custom_delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *current_node, *previous_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		current_node = *head;
		*head = (*head)->next;

		free(current_node->data);
		free(current_node);

		return (1);
	}

	current_node = *head;
	while (current_node)
	{
		if (i == index)
		{
			previous_node->next = current_node->next;

			free(current_node->data);
			free(current_node);

			return (1);
		}

		i++;
		previous_node = current_node;
		current_node = current_node->next;
	}

	return (0);
}


/**
 * my_custom_free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */

void my_custom_free_list(list_t **head_ptr)
{
	list_t *current_node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;

	head = *head_ptr;
	current_node = head;

	while (current_node)
	{
		next_node = current_node->next;
		free(current_node->data);
		free(current_node);
		current_node = next_node;
	}

	*head_ptr = NULL;
}
