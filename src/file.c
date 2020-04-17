#include "../lib/include/file.h"

/**
 * @brief Ouverture du fichier.
 * 
 * @param chemin 
 * @param acces 
 * @return file_t 
 */
file_t open_file(const char *chemin, int acces)
{
    file_t file_1;

    file_1.dir = chemin;
    file_1.acces = acces;

    if ((file_1.descriptor = open(chemin, acces)) == -1)
    {
        perror("[\x1b[31mError\x1b[0m] : opening file");
        exit(EXIT_FAILURE);
    }

    return file_1;
}

/**
 * @brief Lecture du fichier.
 * 
 * @param f Fichier a lire.
 * @return game_t Retourne une structure contenant les données du jeu.
 */
game_t read_game_info(file_t f)
{
    game_t game_info;
    char buffer[BUFFER];

    read(f.descriptor, buffer, sizeof(buffer));

    /* La caractérisation de la carte */
    char *typeCarte = strtok(buffer, ";");
    char *tailleX = strtok(NULL, ";");
    char *tailleY = strtok(NULL, "\n");

    /* La caractérisation de la partie */
    char *nbJoueurs = strtok(NULL, ";");
    char *Cmax = strtok(NULL, ";");
    char *Kmax = strtok(NULL, ";");
    char *nbTours = strtok(NULL, "\0");

    /* Initialisation de des informations de seaofdevs */
    game_info.typeCarte = typeCarte;
    game_info.tailleX = atoi(tailleX);
    game_info.tailleY = atoi(tailleY);
    game_info.nbJoueurs = atoi(nbJoueurs);
    game_info.Cmax = atoi(Cmax);
    game_info.Kmax = atoi(Kmax);
    game_info.nbTours = atoi(nbTours);

    if (game_info.nbJoueurs <= 1)
    {
        printf("[\x1b[31mError\x1b[0m] : check nbPlayers !\n");
        exit(EXIT_FAILURE);
    }

    return game_info;
}

/**
 * @brief Fermeture du fichier
 * 
 * @param file 
 * @return int 
 */
int close_file(file_t file)
{
    return close(file.descriptor);
}

/**
 * @brief Get the map object
 * 
 * @param game_info 
 * @return map_t 
 */
map_t getmap_t(game_t game_info)
{
    map_t map;
    if (!strcmp(game_info.typeCarte, "rectangle"))
    {
        map = MAP_RECT;
    }
    else if (!strcmp(game_info.typeCarte, "total"))
    {
        map = MAP_TOTAL;
    }
    else
    {
        printf("[\x1b[31mError\x1b[0m] : check map type please !\n");
        exit(EXIT_FAILURE);
    }

    return map;
}

/**
 * @brief Get the coord object
 * 
 * @param game_info 
 * @return coord_t 
 */
coord_t getcoord_t(game_t game_info)
{
    coord_t coord;
    coord.x = game_info.tailleX;
    coord.y = game_info.tailleY;
    return coord;
}