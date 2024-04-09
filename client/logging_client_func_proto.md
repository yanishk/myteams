``` c
int client_event_logged_in(char const *user_uuid, const char *user_name);

int client_event_logged_out(char const *user_uuid, const char *user_name);

int client_event_private_message_received(char const *user_uuid, char const *message_body);

int client_event_thread_reply_received(char const *team_uuid, char const *thread_uuid, char const *user_uuid, char const *reply_body);

int client_event_team_created(char const *team_uuid, char const *team_name, char const *team_description);

int client_event_channel_created(char const *channel_uuid, char const *channel_name, char const *channel_description);

int client_event_thread_created(char const *thread_uuid, char const *user_uuid, time_t thread_timestamp, char const *thread_title, char const *thread_body);

int client_print_users(char const *user_uuid, char const *user_name, int user_status);

int client_print_teams(char const *team_uuid, char const *team_name, char const *team_description);

int client_team_print_channels(char const *channel_uuid, char const *channel_name, char const *channel_description);

int client_channel_print_threads(char const *thread_uuid, char const *user_uuid, time_t thread_timestamp, char const *thread_title, char const *thread_body);

int client_thread_print_replies(char const *thread_uuid, char const *user_uuid, time_t reply_timestamp, char const *reply_body);

int client_private_message_print_messages(char const *sender_uuid, time_t message_timestamp, char const *message_body);

int client_error_unknown_team(char const *team_uuid);

int client_error_unknown_channel(char const *channel_uuid);

int client_error_unknown_thread(char const *thread_uuid);

int client_error_unknown_user(char const *user_uuid);

int client_error_unauthorized(void);

int client_error_already_exist(void);

int client_print_user(char const *user_uuid, char const *user_name, int user_status);

int client_print_team(char const *team_uuid, char const *team_name, char const *team_description);

int client_print_channel(char const *channel_uuid, char const *channel_name, char const *channel_description);

int client_print_thread(char const *thread_uuid, char const *user_uuid, time_t thread_timestamp, char const *thread_title, char const *thread_body);

int client_print_team_created(char const *team_uuid, char const *team_name, char const *team_description);

int client_print_channel_created(char const *channel_uuid, char const *channel_name, char const *channel_description);

int client_print_thread_created(char const *thread_uuid, char const *user_uuid, time_t thread_timestamp, char const *thread_title, char const *thread_body);

int client_print_reply_created(char const *thread_uuid, char const *user_uuid, time_t reply_timestamp, char const *reply_body);

int client_print_subscribed(char const *user_uuid, char const *team_uuid);

int client_print_unsubscribed(char const *user_uuid, char const *team_uuid);
```
#
#

• /login [“user_name”] : set the user_name used by client
- client_event_logged_in

#

• /logout : disconnect the client from the server
- client_event_logged_out

#

• /users : get the list of all users that exist on the domain
- client_print_users

#

• /user [“user_uuid”] : get details about the requested user
- client_error_unknown_user
- client_print_user

#

• /send [“user_uuid”] [“message_body”] : send a message to specific user
- client_event_private_message_received
- client_error_unknown_user

#

• /messages [“user_uuid”] : list all messages exchanged with the specified user
- client_private_message_print_messages
- client_error_unknown_user

#

• /subscribe [“team_uuid”] : subscribe to the events of a team and its sub directories (enable reception
of all events from a team)
- client_error_unknown_team
- client_print_subscribed

#

• /subscribed ?[“team_uuid”] : list all subscribed teams or list all users subscribed to a team
- client_print_users
- client_error_unknown_team
- client_print_teams

#

• /unsubscribe [“team_uuid”] : unsubscribe from a team
- client_error_unknown_team
- client_print_unsubscribed

#

• /use ?[“team_uuid”] ?[“channel_uuid”] ?[“thread_uuid”] : Sets the command context to a team/chan-
nel/thread
- client_error_unknown_team
- client_error_unknown_channel
- client_error_unknown_thread

#

• /create : based on the context, create the sub resource (see below)
- client_event_thread_reply_received
- client_event_team_created
- client_event_channel_created
- client_event_thread_created
- client_error_unauthorized
- client_error_already_exist
- client_print_team_created
- client_print_channel_created
- client_print_thread_created
- client_print_reply_created

#

• /list : based on the context, list all the sub resources (see below)
- client_print_teams
- client_team_print_channels
- client_channel_print_threads
- client_thread_print_replies
- client_error_unknown_team
- client_error_unknown_channel
- client_error_unknown_thread

#

• /info : based on the context, display details of the current resource (see below)
- client_error_unknown_team
- client_error_unknown_channel
- client_error_unknown_thread
- client_print_user
- client_print_team
- client_print_channel
- client_print_thread
