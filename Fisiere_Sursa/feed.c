#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "feed.h"
#include "users.h"
#include "graph.h"
void handle_input_feed(char *input, void *data1, void *data2)
{
	char *commands = strdup(input);
	char *cmd = strtok(commands, "\n ");
	graph_t *social_media = (graph_t *)data1;
	all_posts_t *posts = (all_posts_t *)data2;
	if (!cmd)
		return;

	if (!strcmp(cmd, "feed")){
		cmd = strtok(NULL, "\n ");
		unsigned int a = get_user_id(cmd);
		cmd = strtok(NULL, "\n");
		int feed_size = atoi(cmd);
		unsigned int latest_post_id = posts->nr_posts - 1;
		while(feed_size){
			node_t *post = find_node_in_tree(posts->root, latest_post_id, latest_post_id);
			if(!post){
				break;
			}
			post_info_t *post_info = ((tree_t *)(post->data))->info;
			if(is_friend(social_media, a, post_info->user_id) || a == post_info->user_id){
				if(post_info->title){
					printf("%s: %s\n", get_user_name(post_info->user_id), post_info->title);
					feed_size--;
				}
			}
			latest_post_id--;
		}
	}
	else if (!strcmp(cmd, "view-profile"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "friends-repost"))
		(void)cmd;
		// TODO: Add function
	else if (!strcmp(cmd, "common-groups"))
		(void)cmd;
		// TODO: Add function

	free(commands);
}
