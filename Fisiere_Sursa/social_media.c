/**
	Copyright Popa Filip-Andrei & Visanescu Bogdan
				~ 313CAb 2023-2024 ~
*/
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
#include "structures.h"

/**
 * Initializez every task based on which task we are running
 */
void init_tasks(void)
{
	#ifdef TASK_1
	#endif

	#ifdef TASK_2
	#endif

	#ifdef TASK_3
	#endif
}

/**
 * Entrypoint of the program, compiled with different defines for each task
 */
int main(void)
{
	init_users();
	init_tasks();
	graph_t *social_media = new_graph(get_users_number());
	all_posts_t *posts = new_all_posts();

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

	free_graph(&social_media);
	free_all_post(&posts);
	free_users();
	free(input);

	return 0;
}
