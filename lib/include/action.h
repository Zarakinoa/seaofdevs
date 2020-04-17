#ifndef _H_ACTION_
#define _H_ACTION_

#include "seaofdevs.h"

int a_attaque_atk(ship_t *source, ship_t *cible);

coord_t s_radar_scn(ship_t *source, navalmap_t *nm);

void m_deplacer_mov(ship_t *source, navalmap_t *nm, direction_t dir);

int isRangeAttack(ship_t *source, coord_t cible);

#endif