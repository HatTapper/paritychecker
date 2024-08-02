#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

typedef struct User
{
    char* username;
    char* password;
} User;

int main(void)
{
    initscr();
    raw();
    noecho();
    attron(A_BOLD);
    printw("Welcome, new user! Please create an account! Start with your username.\n");
    attroff(A_BOLD);
    refresh();

    char username[1024];
    getstr(username);
    move(2,0);
    printw("Now, make a password.\n");
    char password[1024];
    getstr(password);
    move(2,0);

    User* user = malloc(sizeof(User) + 2048);
    user->username = username;
    user->password = password;

    printw("Great! Now, repeat your username!\n");
    char testUsername[1024];
    getstr(testUsername);
    if(strncmp(testUsername, user->username, strlen(user->username)) != 0)
    {
        mvprintw(3, 0, "Incorrect. Username is %s, you entered %s.\n", user->username, testUsername);
        getch();
        goto endProgram;
    }

    printw("Okay, now your password!\n");
    char testPassword[1024];
    getstr(testPassword);
    if(strncmp(testPassword, user->password, strlen(user->password)) != 0)
    {
        printw("Incorrect. Password is %s, you entered %s.\n", user->password, testPassword);
        getch();
        goto endProgram;
    }

    attron(A_UNDERLINE);
    printw("Nice work! You remembered your username and password!\n");
    attroff(A_UNDERLINE);
    getch();

    endProgram:
        endwin();
        free(user);
        return 0;
}