#ifndef _H_FILE_
#define _H_FILE_

#include "seaofdevs.h"
#include "navalmap.h"

typedef struct file_s file_t;

/**
 * @brief Structure representant un fichier
 * 
 */
struct file_s
{
    int descriptor;
    const char *dir;
    int acces;
};

/**
 * @brief Ouverture du fichier
 * 
 * @param chemin Nom/Chemin du fichier à ouvrir
 * @param acces Accès au fichier (cf. flags de open())
 * @return file_t Structure file_t (le descripteur est mis à -1 si l'ouverture a échouée)
 */
file_t open_file(const char *chemin, int acces);

/**
 * @brief Fermeture du fichier
 * 
 * @param file 
 * @return int 
 */
int close_file(file_t file);

/**
 * @brief 
 * 
 * @param f 
 * @return ssize_t 
 */
game_t read_game_info(file_t f);

/**
 * @brief Get the map t object
 * 
 * @param game_info 
 * @return map_t 
 */
map_t getmap_t(game_t game_info);

/**
 * @brief Get the coord object
 * 
 * @param game_info 
 * @return coord_t 
 */
coord_t getcoord_t(game_t game_info);

#endif
