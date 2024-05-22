/**
 * The entrypoint of the homework. Every initialization must be done here
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "users.h"
#include "friends.h"
#include "posts.h"
#include "feed.h"
#include "graph.h"

/**
 * Initializez every task based on which task we are running
*/
int init_tasks(void)
{
	#ifdef TASK_1
		return 1;
	#endif

	#ifdef TASK_2
		return 2;
	#endif

	#ifdef TASK_3
		return 3;
	#endif

	return 0;
}

/**
 * Entrypoint of the program, compiled with different defines for each task
*/
int main(void)
{
	init_users();
	// int task = init_tasks();
	void *social_media = NULL;
	void *posts = NULL;
		social_media = new_graph(get_users_number());
		posts = new_all_posts();

	char *input = (char *)malloc(MAX_COMMAND_LEN);
	while (1) {
		char *command = fgets(input, MAX_COMMAND_LEN, stdin);
		if (!command)
			break;
		
		#ifdef TASK_1
		handle_input_friends(input, social_media);
		#endif

		#ifdef TASK_2
		handle_input_posts(input, posts);
		#endif

		#ifdef TASK_3
		handle_input_feed(input, social_media, posts);
		#endif
	}

	free_users();
	free(input);

		free_graph(social_media);
		free(social_media);
	
	//TODO: free(posts)

		free_all_post(posts);
		free(posts);
	
	return 0;

}