#include "../lib/include/seaofdevs.h"

char entitytochar(entity_t e)
{
    if (e == ENT_SEA)
    {
        return '.';
    }
    else if (e == ENT_SHIP)
    {
        return '*';
    }
    else
    {
        perror("[\x1b[31mError\x1b[0m] : entity type");
        exit(EXIT_FAILURE);
    }
}

void draw_navalmap(navalmap_t *nm)
{
    printf("[\x1b[32mServer\x1b[0m] : drawing %dx%d map with %d players\n", nm->size.y, nm->size.x, nm->nbShips);

    for (int i = 0; i < nm->size.y; i++)
    {
        for (int j = 0; j < nm->size.x; j++)
        {
            printf("\x1B[37;7m %c \x1b[0m", entitytochar(nm->map[i][j].type));
        }
        printf("\n");
    }
}