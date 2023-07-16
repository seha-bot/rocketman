#include "rocketman.h"
#include <stdio.h>
#include <stdlib.h>
#include "nec.h"

sector* load_sectors(void)
{
    FILE* file = fopen("data.wall", "r");
    if(file == NULL) return NULL;

    sector* sectors = NULL;

    while(1)
    {
        size_t temp;
        char* line = NULL;
        ssize_t size = getline(&line, &temp, file);
        if(size == -1) break;

        if(line[0] == 's')
        {
            sector s = { NULL, atof(line + 2) };
            nec_push(sectors, s);
            free(line);
            line = NULL;
            continue;
        }

        float vals[7];
        int valId = 0;
        char buffer[50];
        int bufferLen = 0;
        for(int i = 0; i < size; i++)
        {
            if(line[i] == ' ' || i == size - 1)
            {
                buffer[bufferLen] = '\0';
                vals[valId++] = atof(buffer);
                bufferLen = 0;
            }
            buffer[bufferLen++] = line[i];
        }
        free(line);
        line = NULL;

        wall w = {
            (v2){ vals[0], vals[1] },
            (v2){ vals[2], vals[3] },
            (v3){ vals[4], vals[5], vals[6] }
        };
        nec_push(sectors[nec_size(sectors) - 1].walls, w);
    }

    fclose(file);
    return sectors;
}

