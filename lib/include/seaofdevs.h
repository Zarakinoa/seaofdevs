#ifndef _H_SEAOFDEVS_
#define _H_SEAOFDEVS_

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>

#include "navalmap.h"

#define BUFFER 256

typedef struct game_s game_t;
typedef struct ship_s ship_t;
typedef struct pipe_s pipe_t;
typedef struct message_s message_t;
typedef struct seaofdevs_s seaofdevs_t;

typedef enum action action_t;
typedef enum direction direction_t;

struct game_s
{
    char *typeCarte;
    int tailleX;
    int tailleY;
    int nbJoueurs;
    int Cmax;
    int Kmax;
    int nbTours;
};

struct ship_s
{
    int id;
    coord_t coord;
    int coque;
    int kerosene;
};

enum action
{
    ATK,
    MOV,
    SCN,
    NONE
};

enum direction
{
    HAUT,
    BAS,
    DROITE,
    GAUCHE
};

struct message_s
{
    pthread_mutex_t mut;
    int fd[2];
    action_t action;
    ship_t *a_ship;
};

struct seaofdevs_s
{
    navalmap_t *nm;
    ship_t *ships;
    game_t game_info;
};

#endif