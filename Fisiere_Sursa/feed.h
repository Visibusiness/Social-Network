#ifndef FEED_H
#define FEED_H

/**
 * Function that handles the calling of every command from task 3
 *
 * Please add any necessary parameters to the functions
 */

void search_user_reposts(void *data, unsigned int user_id, char *title);
void search_user_posts(void *data, unsigned int user_id);
void handle_input_feed(char *input, void *data1, void *data2);

#endif // FEED_H
