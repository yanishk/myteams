/*
** EPITECH PROJECT, 2024
** test
** File description:
** struct_redirect_print
*/

#ifndef STRUCT_REDIRECT_PRINT_H_
    #define STRUCT_REDIRECT_PRINT_H_

    #include "logging_client.h"

    #define NB_CODE 2
    #define CODE_101 "101 End of transmmission"

typedef struct {
    char *str;
    int (*ptr)(const char *str);
} display_err_exist_t;

typedef struct {
    char *str;
    int (*ptr)(void);
} display_err_access_t;

typedef struct {
    char *str;
    int (*ptr)(const char *str, const char *str2);
} display_two_char_func_t;

typedef struct {
    char *str;
    int (*ptr)(const char *str, const char *str2, const char *str3);
} display_team_channel_t;

typedef struct {
    char *str;
    int (*ptr)(char const *user_uuid, char const *user_name, int user_status);
} display_users_t;

typedef struct {
    char *str;
    int (*ptr)(
        char const *thread_uuid,
        char const *user_uuid,
        time_t thread_timestamp,
        char const *thread_title,
        char const *thread_body);
} display_thread_t;

typedef struct {
    char *str;
    int (*ptr)(
        char const *thread_uuid,
        char const *user_uuid,
        time_t reply_timestamp,
        char const *reply_body);
} print_reply_t;

display_err_exist_t display_err_exist[] = {
    {"401", &client_error_unknown_user},
    {"402", &client_error_unknown_team},
    {"403", &client_error_unknown_channel},
    {"404", &client_error_unknown_thread},
    {'\0', NULL}
};

display_err_access_t display_err_access[] = {
    {"301", &client_error_unauthorized},
    {"302", &client_error_already_exist},
    {'\0', NULL}
};

display_two_char_func_t display_two_char_func[] = {
    {"201", &client_event_logged_in},
    {"202", &client_event_logged_out},
    {"205", &client_event_private_message_received},
    {"207", &client_print_subscribed},
    {"209", &client_print_unsubscribed},
    {'\0', NULL}
};

display_team_channel_t display_team_channel[] = {
    {"208", &client_print_teams},
    {"211", &client_event_team_created},
    {"212", &client_event_channel_created},
    {"214", &client_print_team_created},
    {"215", &client_print_channel_created},
    {"218", &client_team_print_channels},
    {"221", &client_print_team},
    {"222", &client_print_channel},
    {'\0', NULL}
};

display_users_t display_users[] = {
    {"203", &client_print_users},
    {"204", &client_print_user},
    {'\0', NULL}
};

display_thread_t display_thread[] = {
    {"213", &client_event_thread_created},
    {"216", &client_print_thread_created},
    {"219", &client_channel_print_threads},
    {"223", &client_print_thread},
    {'\0', NULL}
};

print_reply_t print_reply[] = {
    {"217", &client_print_reply_created},
    {"220", &client_thread_print_replies},
    {'\0', NULL}
};

#endif /* !STRUCT_REDIRECT_PRINT_H_ */
