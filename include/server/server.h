/*
** EPITECH PROJECT, 2024
** bs_myFTP_select
** File description:
** my
*/

    #include <stdbool.h>
    #include <netinet/ip.h>
    #include <sys/select.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <arpa/inet.h>


#ifndef SERVER_H_
    #define SERVER_H_

    #define MAX_USER 1024
    #define BUFFER_MAX_SIZE 1024
    #define NB_CMD 13 //14 commande dmd dans le pdf (enfin je croie)

    #define SUC_MSG_LOGIN "331 Username okay.\n"
    #define SUC_MSG_PASS "230 User logged in, proceed.\n"
    #define FAIL_MSG_LOGIN "530 Not logged in.\n"
    #define ALRD_LOGIN "531 Already logged in.\n"
    #define QUIT_MSG "221 Service closing control connection.\n"
    #define USER_CMD_OK "201 User command work\n"
    #define CODE_200 "200 Command okay.\n"
    #define CODE_150 "150 File status okay, about to open data connection.\n"
    #define CODE_226 "226 Closing data connection.\n"
    #define CODE_250 "250 Requested file action okay, completed.\n"
    #define CODE_214 "214 Help message.\n"
    #define CODE_227 "227 Entering Passive Mode (h1,h2,h3,h4,p1,p2).\n"

    #define FAIL_CMD_EXIST "500 Syntax error, command unrecognized.\n"
    #define BAD_CWD_USAGE "501 CWD  <SP> <pathname> <CRLF>\n"
    #define BAD_CWD "502 Bad directory path\n"
    #define ERR_NOT_ARG "503 Not enough arguments\n"
    #define ERR_BAD_ARG "504 Bad arguments\n"
    #define ANONYMOUS_USER "Anonymous"
    #define CODE_NOT_IMPLEMENTED "NOT YET IMPLEMENTED\n"

static char *const cmd_lst[NB_CMD] = {
    "/login",
    "/users",
    "/user",
    "/logout",
    "DELE",
    "PWD",
    "PASV",
    "PORT",
    "/help",
    "NOOP",
    "RETR",
    "STOR",
    "LIST"
};

static char *const help_msg[NB_CMD] = {
    "USER <SP> <username> <CRLF>   : Specify user for authentication\n",
    "CWD  <SP> <pathname> <CRLF>   : Change working directory\n",
    "CDUP <CRLF>                   : "
    "Change working directory to parent directory\n",
    "QUIT <CRLF>                   : Disconnection\n",
    "DELE <SP> <pathname> <CRLF>   : Delete file on the server\n",
    "PWD  <CRLF>                   : Print working directory\n",
    "PASV <CRLF>                   : "
    "Enable ”passive” mode for data transfer\n",
    "PORT <SP> <host-port> <CRLF>  : "
    "Enable ”active” mode for data transfer\n",
    "HELP [<SP> <string>] <CRLF>   : List available commands\n",
    "NOOP <CRLF>                   : Do nothing\n",
    "RETR <SP> <pathname> <CRLF>   : Download file from server to client\n",
    "STOR <SP> <pathname> <CRLF>   : Upload file from client to server\n",
    "LIST [<SP> <pathname>] <CRLF> : "
    "List files in the current working directory\n"
};

enum cmd_status {
    NO_CMD,
    WIN_CMD,
    ERR_CMD
};

typedef struct clients_s {
    struct sockaddr_in sock_addr;
    int client_fd;
    bool is_connected;
    bool has_been_closed;
    char *username;
    char *my_uuid;
} clients_t;

typedef struct cmd_s {
    char **tab;
    int len;
} cmd_t;

typedef struct server_s {
    struct sockaddr_in sock_addr;
    int port;
    int server_fd;
    int *fd_array;
    int size;
    int max_fd_set;
    int user_index;
    fd_set readfds;
    clients_t **clients;
    cmd_t cmd_arg;
} server_t;

#endif /* !SERVER_H_ */
