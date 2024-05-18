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
	uint16_t a = get_user_id(name1);

	char *name2 = NULL;
	uint16_t b = 0;

	if(!strcmp(cmd, "add") || !strcmp(cmd, "distance") || !strcmp(cmd, "remove") || !strcmp(cmd, "common")) {
		cmds = strtok(NULL, "\n ");
		name2 = strdup(cmds);
		b = get_user_id(name2);
	}
	free(commands);

	if (!strcmp(cmd, "add")) {
		add_connection(social_media, a, b);
		printf("Added connection %s - %s\n", name1, name2);
	}
	else if (!strcmp(cmd, "distance")) {
		int distance = -1;
		distance = get_distance(social_media, a, b) - 1;
		if(distance != -1)
			printf("The distance between %s - %s is %d\n", name1, name2, distance);
		else
			printf("There is no way to get from %s to %s\n", name1, name2);
	} else if (!strcmp(cmd, "suggestions")) {
		unsigned int *v = suggestions(social_media, a);
		int there_are_suggestions = 0;
		for(unsigned i=0; i<social_media->nodes; i++) 
			if(v[i]) {
				if(!there_are_suggestions) {
					printf("Suggestions for %s:\n", name1); 
	 				there_are_suggestions = 1;
				}
				printf("%s\n", get_user_name(i));
			}
		if(!there_are_suggestions)
			printf("There are no suggestions for %s\n", name1);
		free(v);
	}
	else if (!strcmp(cmd, "remove")) {
		remove_connection(social_media, a, b);
		printf("Removed connection %s - %s\n", name1, name2);
	}
	else if (!strcmp(cmd, "common")) {
		unsigned int *v = common_friends(social_media, a, b);
		int there_are_friends = 0;
		for(unsigned i=0; i<social_media->nodes; i++) 
			if(v[i] == 2) {
				if(!there_are_friends) {
					printf("The common friends between %s and %s are:\n", name1, name2); 
	 				there_are_friends = 1;
				}
				printf("%s\n", get_user_name(i));
			}
		if(!there_are_friends)
			printf("No common friends for %s and %s\n", name1, name2);
		free(v);
	}
	else if (!strcmp(cmd, "friends")) {
		printf("%s has %u friends\n", name1, social_media->friends[a]->size);
	}
	else if (!strcmp(cmd, "popular")) {
		unsigned int friend = most_popular_friend(social_media, a);
		if(social_media->friends[a]->size >= social_media->friends[friend]->size)
			printf("%s is the most popular\n", name1);
		else
			printf("%s is the most popular friend of %s\n", get_user_name(friend), name1);
	}
	free(cmd);
	free(name1);
	if(name2)
		free(name2);
}
