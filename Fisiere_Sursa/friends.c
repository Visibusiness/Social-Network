#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "friends.h"
#include "users.h"
#include "graph.h"

void handle_input_friends(char *input, void *data)
{
	graph_t *social_media = (graph_t *)data;
	if(!social_media)
		return;
	
	char *commands = strdup(input);
	if (!commands)
		return;

	char *cmds = strtok(commands, "\n ");	
 	char *cmd = strdup(cmds);
	cmds = strtok(NULL, "\n ");
	char *name1 = strdup(cmds);
	cmds = strtok(NULL, "\n ");
	char *name2 = strdup(cmds);
	uint16_t a = get_user_id(name1);
	uint16_t b = get_user_id(name2);

	if (!strcmp(cmd, "add")) {	
		add_connection(social_media, a, b);
		printf("Added connection %s - %s\n", name1, name2);
	}
	else if (!strcmp(cmd, "distance")) {
		int distance = get_distance(social_media, a, b);
		if(distance != -1)
			printf("The distance between %s - %s is %d\n", name1, name2, distance);
	} else if (!strcmp(cmd, "suggestions"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "remove"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "common"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "friends"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "popular"))
		(void)cmd;
		// TODO: Add function

	free(cmd);
	free(name1);
	free(name2);
	free(commands);
}
