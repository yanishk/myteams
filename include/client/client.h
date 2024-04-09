/*
** EPITECH PROJECT, 2024
** test
** File description:
** client
*/

#ifndef CLIENT_H_
    #define CLIENT_H_

    #include <netinet/ip.h>
    #include <arpa/inet.h>
    #include <string.h>
    #include <unistd.h>
    #include "./logging_client.h"
    #include <stdio.h>
    #include <stdlib.h>
    #include <stdbool.h>

    #define NB_CODE 6

static char *const code_lst[NB_CODE] = {
    "200",
    "331",
    "201",
    "500",
    "530",
    "531"
};

int array_size(char **array);
void print_array(char **array);
void free_array(char **array);
char *concat_strings(char *str1, char *str2, char *delim);
char *does_path_exists(char *str);
bool does_file_exists(char *str);
bool array_is_number(char **array);
char **word_array(char const *str, char *delim);

#endif /* !CLIENT_H_ */
