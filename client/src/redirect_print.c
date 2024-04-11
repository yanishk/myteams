/*
** EPITECH PROJECT, 2024
** test
** File description:
** redirect_print
*/

#include "client.h"
#include "struct_redirect_print.h"

static void display_msg(char *msg, int nb)
{
    char **tab = word_array(msg, "\n");

    if (nb == 0) {
        client_private_message_print_messages(tab[0], (time_t) 10, "s2\n");
    }
    if (nb == 1) {
        client_event_thread_reply_received(tab[0], "s2\n", "s3\n", "s4\n");
    }
}

static void display_error(char *msg)
{
    char *new_msg = strdup(msg);
    char **tab = word_array(new_msg, "\n");
    char *first_word = word_array(tab[0], " ")[0];

    for (size_t y = 0; display_err_exist[y].str != NULL; y++) {
        if (strcmp(display_err_exist[y].str, first_word) == 0) {
            display_err_exist[y].ptr("uuid error unknown\n");
            return;
        }
    }
    for (size_t y = 0; display_err_access[y].str != NULL; y++) {
        if (strcmp(display_err_access[y].str, first_word) == 0) {
            display_err_access[y].ptr();
            return;
        }
    }
}

static void display_team_user(char *msg)
{
    char *new_msg = strdup(msg);
    char **tab = word_array(new_msg, "\n");
    char *first_word = word_array(tab[0], " ")[0];

    for (size_t y = 0; display_team_channel[y].str != NULL; y++) {
        if (strcmp(display_team_channel[y].str, first_word) == 0) {
            display_team_channel[y].ptr("s1\n", "s2\n", "s3\n");
            return;
        }
    }
    for (size_t y = 0; display_users[y].str != NULL; y++) {
        if (strcmp(display_users[y].str, first_word) == 0) {
            display_users[y].ptr(tab[2], tab[1], 1);
            return;
        }
    }
}

static void display_thread_reply(char *msg)
{
    char *new_msg = strdup(msg);
    char **tab = word_array(new_msg, "\n");
    char *first_word = word_array(tab[0], " ")[0];

    for (size_t y = 0; display_thread[y].str != NULL; y++) {
        if (strcmp(display_thread[y].str, first_word) == 0) {
            display_thread[y].ptr("s1\n", "s2\n", (time_t) 4, "s3\n", "s4\n");
            return;
        }
    }
    for (size_t y = 0; display_print_reply[y].str != NULL; y++) {
        if (strcmp(display_print_reply[y].str, first_word) == 0) {
            display_print_reply[y].ptr("s1\n", "s2\n", (time_t) 4, "s3\n");
            return;
        }
    }
}

void select_display_methode(char *msg)
{
    char *new_msg = strdup(msg);
    char **tab = word_array(new_msg, "\n");
    char *first_word = word_array(tab[0], " ")[0];

    write(1, "Enter the command : ", strlen("Enter the command : "));
    display_error(strdup(msg));
    display_team_user(strdup(msg));
    display_thread_reply(strdup(msg));
    for (size_t y = 0; display_two_char_func[y].str != NULL; y++) {
        if (strcmp(display_two_char_func[y].str, first_word) == 0) {
            display_two_char_func[y].ptr("[uuid client]", "[nom client]");
            return;
        }
    }
    for (size_t i = 0; i < NB_CODE; i++) {
        if (strcmp(other_code[i], first_word) == 0) {
            display_msg(strdup(msg), i);
        }
    }
}
