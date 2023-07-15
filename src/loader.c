#include "rocketman.h"
#include <stdio.h>
#include <stdlib.h>
#include "nec.h"

wall* load_walls(void)
{
    FILE* file = fopen("data.wall", "r");
    if(file == NULL) return NULL;

    wall* walls = NULL;
    float vals[9];
    char buffer[50];

    while(1)
    {
        size_t n;
        char* line = NULL;
        ssize_t size = getline(&line, &n, file);
        if(size == -1) break;

        int valId = 0;
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
            (v3){ vals[0], vals[1], vals[2] },
            (v3){ vals[3], vals[4], vals[5] },
            (v3){ vals[6], vals[7], vals[8] }
        };
        nec_push(walls, w);
    }

    fclose(file);
    return walls;
}

