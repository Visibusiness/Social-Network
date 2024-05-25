#ifndef POSTS_H
#define POSTS_H

/**
 * Function that handles the calling of every command from task 2
 *
 * Please add any necessary parameters to the functions
 */

void print_reposts(void *data, int must_print);
void get_id(unsigned int *post_id, unsigned int *repost_id);
void handle_input_posts_continue(char *cmd, void *data);
void handle_input_posts(char *input, void *data);

#endif // POSTS_H
