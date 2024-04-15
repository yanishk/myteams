/*
** EPITECH PROJECT, 2024
** test
** File description:
** redirect_print
*/

#include "client.h"
#include "struct_redirect_print.h"

static int display_msg(char *msg, int nb)
{
    char **tab = word_array(msg, "\n");

    if (nb == 0) {
        client_private_message_print_messages(tab[1],
        (time_t) atoi(tab[2]), tab[3]);
        return 1;
    }
    if (nb == 1) {
        client_event_thread_reply_received(tab[1], tab[2], tab[3], tab[4]);
        return 1;
    }
    return 0;
}

static int display_error(char *msg)
{
    char **tab = word_array(msg, "\n");
    char *first_word = word_array(tab[0], " ")[0];

    for (size_t y = 0; display_err_exist[y].str != NULL; y++) {
        if (strcmp(display_err_exist[y].str, first_word) == 0) {
            display_err_exist[y].ptr(tab[1]);
            return 1;
        }
    }
    for (size_t y = 0; display_err_access[y].str != NULL; y++) {
        if (strcmp(display_err_access[y].str, first_word) == 0) {
            display_err_access[y].ptr();
            return 1;
        }
    }
    return 0;
}

static void loop_display_users(char **tab, int y)
{
    for (int i = 1; tab[i] != NULL && strcmp(tab[i], CODE_101) != 0; i += 3) {
        display_users[y].ptr(tab[i], tab[i + 1], atoi(tab[i + 2]));
    }
}

static int display_team_user(char *msg)
{
    char **tab = word_array(msg, "\n");
    char *first_word = word_array(tab[0], " ")[0];

    for (size_t y = 0; display_team_channel[y].str != NULL; y++) {
        if (strcmp(display_team_channel[y].str, first_word) == 0) {
            display_team_channel[y].ptr(tab[1], tab[2], tab[3]);
            return 1;
        }
    }
    for (size_t y = 0; display_users[y].str != NULL; y++) {
        if (strcmp(display_users[y].str, first_word) == 0) {
            loop_display_users(tab, y);
            return 1;
        }
    }
    return 0;
}

static int display_thread_reply(char *msg)
{
    char **tab = word_array(msg, "\n");
    char *first_word = word_array(tab[0], " ")[0];

    for (size_t y = 0; display_thread[y].str != NULL; y++) {
        if (strcmp(display_thread[y].str, first_word) == 0) {
            display_thread[y].ptr(tab[1], tab[2],
            (time_t) atoi(tab[3]), tab[4], tab[5]);
            return 1;
        }
    }
    for (size_t y = 0; display_print_reply[y].str != NULL; y++) {
        if (strcmp(display_print_reply[y].str, first_word) == 0) {
            display_print_reply[y].ptr(tab[1], tab[2],
            (time_t) atoi(tab[3]), tab[4]);
            return 1;
        }
    }
    return 0;
}

static bool is_end(char *msg)
{
    char **tab = word_array(msg, "\n");

    if (strlen(msg) < 1) {
        return true;
    }
    for (int i = 0; tab[i] != NULL; i++) {
        if (strcmp(tab[i], CODE_101) == 0) {
            return true;
        }
    }
    return false;
}

static int display_help(char *msg)
{
    char **tab = word_array(msg, "\n");
    char *first_word = word_array(tab[0], " ")[0];

    if (strcmp(first_word, "224") == 0) {
        printf("%s\n", msg);
        return 1;
    }
    return 0;
}

static int redirect_print(char *msg)
{
    char **tab = word_array(msg, "\n");
    char *first_word = word_array(tab[0], " ")[0];
    int pass = 0;

    pass += display_error(strdup(msg));
    pass += display_team_user(strdup(msg));
    pass += display_thread_reply(strdup(msg));
    for (size_t y = 0; display_two_char_func[y].str != NULL; y++) {
        if (strcmp(display_two_char_func[y].str, first_word) == 0) {
            display_two_char_func[y].ptr(tab[1], tab[2]);
            pass += 1;
        }
    }
    for (size_t i = 0; i < NB_CODE; i++) {
        if (strcmp(other_code[i], first_word) == 0) {
            display_msg(strdup(msg), i);
            pass += 1;
        }
    }
    return pass;
}

int select_display_methode(char *msg)
{
    int return_status = is_end(strdup(msg));

    if (display_help(strdup(msg)) == 1) {
        return 1;
    }
    if (redirect_print(strdup(msg)) == 0) {
        return 1;
    }
    return return_status;
}
