#include "../lib/include/seaofdevs.h"
#include "../lib/include/file.h"
#include "../lib/include/board.h"
#include "../lib/include/action.h"

message_t toServer;
message_t toPlayer;

void *playerjob(void *arg)
{
    /* Cast thread arg */
    ship_t *ship = (ship_t *)arg;
    /* Print thread Info */
    printf("[\x1b[33mPlayer\x1b[0m] : ship #%d %dC %dK at (%d;%d) \n", ship->id, ship->coque, ship->kerosene, ship->coord.x, ship->coord.y);

    coord_t pos_adv;
    pos_adv.x = -1;
    pos_adv.y = -1;

    /* Position adverse non connue ou radar obselete */
    if ((pos_adv.x == -1) || (pos_adv.y == -1))
    {
        printf("[\x1b[33mPlayer\x1b[0m] : ship #%d call radar action\n", ship->id);
        pthread_mutex_lock(&toServer.mut);
        /* Demande de radar */
        toServer.action = SCN;
        toServer.a_ship = ship;
        write(toServer.fd[1], &toServer, sizeof(toServer));
        /* Update information ship adv from radar */
        // read(toPlayer.fd[0], &toPlayer, sizeof(toPlayer));
        // pos_adv.x = toPlayer.a_ship->coord.x;
        // pos_adv.y = toPlayer.a_ship->coord.y;
        pthread_mutex_unlock(&toServer.mut);
    }
    else if (isRangeAttack(ship, pos_adv))
    {
        printf("[\x1b[33mPlayer\x1b[0m] : ship #%d call attack action\n", ship->id);
        pthread_mutex_lock(&toServer.mut);
        /* Attaque adversaire */
        toServer.action = ATK;
        toServer.a_ship = toPlayer.a_ship;
        write(toServer.fd[1], &toServer, sizeof(toServer));
        pthread_mutex_unlock(&toServer.mut);
    }
    else
    {
        printf("[\x1b[33mPlayer\x1b[0m] : ship #%d call move action\n", ship->id);
        pthread_mutex_lock(&toServer.mut);
        /* Deplacement vers position adverse */
        toServer.action = MOV;
        toServer.a_ship = ship;
        write(toServer.fd[1], &toServer, sizeof(toServer));
        pthread_mutex_unlock(&toServer.mut);
    }
    pthread_exit(NULL);
}

void *managerjob(void *arg)
{
    seaofdevs_t *sod_man = (void *)arg;
    pthread_exit(NULL);
}

int main(int argc, char **argv)
{
    /* Seed */
    srand(time(NULL));
    initNavalMapLib();

    /* Variables */
    file_t fichier;
    game_t game_info;
    navalmap_t *sod_map = NULL;
    int i;

    printf("[\x1b[32mServer\x1b[0m] : welcome to the sea of devs !\n");

    /* File Parse */
    fichier = open_file(argv[1], O_RDONLY);
    printf("[\x1b[32mServer\x1b[0m] : reading %s\n", argv[1]);
    game_info = read_game_info(fichier);

    /* Navalmap */
    map_t map = getmap_t(game_info);
    coord_t size_map = getcoord_t(game_info);
    sod_map = init_navalmap(map, size_map, game_info.nbJoueurs);

    /* Place ships */
    sod_map->initEntityMap(sod_map);
    placeRemainingShipsAtRandom(sod_map);

    /* Draw Navalmap */
    draw_navalmap(sod_map);

    /* Threads */
    pthread_t manager;
    pthread_t players[game_info.nbJoueurs];
    /* Navires */
    ship_t ships[game_info.nbJoueurs];

    /* Pipes */
    pipe(toServer.fd);
    pipe(toPlayer.fd);

    /* Initialize threads */
    for (i = 0; i < game_info.nbJoueurs; i++)
    {
        /* Initialize Default Sihp */
        ships[i].id = i;
        ships[i].coque = game_info.Cmax;
        ships[i].kerosene = game_info.Kmax;
        ships[i].coord = sod_map->shipPosition[i];
        printf("[\x1b[32mServer\x1b[0m] : initialize threaded player ship #%d\n", ships[i].id);
        pthread_create(&players[i], NULL, playerjob, (void *)&ships[i]);
    }

    /* Initialize thread manager */
    seaofdevs_t sod_manager;
    sod_manager.nm = sod_map;
    sod_manager.ships = ships;
    sod_manager.game_info = game_info;
    pthread_create(&manager, NULL, managerjob, (void *)&sod_manager);

    /* Wait for the threads */
    for (i = 0; i < game_info.nbJoueurs; i++)
    {
        pthread_join(players[i], NULL);
        printf("[\x1b[32mServer\x1b[0m] : completed join with ship #%d\n", ships[i].id);
    }
    /* Wait for the manager threads */
    pthread_join(manager, NULL);
    printf("[\x1b[32mServer\x1b[0m] : completed join manager\n");

    /* End Routines */
    free_navalmap(sod_map);
    close_file(fichier);
    printf("[\x1b[32mServer\x1b[0m] : program completed exiting\n");
    return 0;
}
