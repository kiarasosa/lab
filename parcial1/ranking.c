/*
  @file ranking.c
  @brief Implements store structure and methods
*/
#include <stdlib.h>
#include "ranking.h"
#include <string.h>

static const int NUMBER_OF_RANKING_VARS = 6;

Ranking ranking_from_file(FILE *file) {

    Ranking ranking;
    unsigned int a;
    int b,c;
    char d[20], e[20];
    float f;

    int res = fscanf(file, EXPECTED_RANKING_FILE_FORMAT, &a, &b, &c, d, e, &f);

    if (res != NUMBER_OF_RANKING_VARS){
      fprintf(stderr, "Invalid ranking data.\n");
      exit(EXIT_FAILURE);
    }

    // Asignar los valores leídos a la estructura Ranking
    ranking.pos = a;
    ranking.pos_prev = b;
    ranking.diff = c; 
    strcpy(ranking.name,d);
    strcpy(ranking.team,e);
    ranking.points = f;
    
    return ranking;
}

float total_track_points_per_team(RankingTable a, char *team_name) {
    float sum = 0.0;
      for(unsigned int i = 0u; i < NO_PLAYERS; i++){
        if (strcmp(team_name, a[i][track].team) == 0) {             // compara el nombre del equipo en la posición actual con team_name. strcmp compara dos cadenas
            printf("Found team point for track %i: %f\n", i, a[i][track].points);
            sum += a[i][track].points;
        }
      }
    return sum;
}
