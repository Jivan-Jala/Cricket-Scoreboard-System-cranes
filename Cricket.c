#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char team1[50], team2[50];
    int score1, score2;
    int wickets1, wickets2;
    int balls_left;
    int target;
    int total_overs;
    int current_inning;
} Match;

FILE *file;

void saveToFile(Match *match) {
    file = fopen("match_score.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "Match: %s vs %s\n", match->team1, match->team2);
    fprintf(file, "Inning: %d | Overs: %d\n", match->current_inning, match->total_overs);
    if (match->current_inning == 1) {
        fprintf(file, "Batting: %s | Score: %d/%d | Balls Left: %d\n", match->team1, match->score1, match->wickets1, match->balls_left);
    } else {
        fprintf(file, "Batting: %s | Score: %d/%d | Balls Left: %d | Target: %d\n", match->team2, match->score2, match->wickets2, match->balls_left, match->target);
    }
    fclose(file);
}

void displayScoreboard(Match *match) {
    printf("\n==================== Cricket Scoreboard ====================\n");
    printf("Match: %s vs %s\n", match->team1, match->team2);
    printf("Inning: %d | Overs: %d\n", match->current_inning, match->total_overs);
    if (match->current_inning == 1) {
        printf("Batting: %s | Score: %d/%d | Balls Left: %d\n", match->team1, match->score1, match->wickets1, match->balls_left);
    } else {
        printf("Batting: %s | Score: %d/%d | Balls Left: %d | Target: %d\n", match->team2, match->score2, match->wickets2, match->balls_left, match->target);
    }
    saveToFile(match);
}

void updateScore(Match *match, int runs, int is_wicket) {
    if (match->balls_left <= 0) return;
    if (match->current_inning == 1) {
        if (is_wicket) match->wickets1++;
        else match->score1 += runs;
    } else {
        if (is_wicket) match->wickets2++;
        else match->score2 += runs;
    }
    match->balls_left--;
    displayScoreboard(match);
}

int main() {
    Match match;
    printf("Enter Team 1 Name: "); scanf("%s", match.team1);
    printf("Enter Team 2 Name: "); scanf("%s", match.team2);
    printf("Enter Number of Overs: "); scanf("%d", &match.total_overs);
    match.score1 = match.score2 = 0;
    match.wickets1 = match.wickets2 = 0;
    match.balls_left = match.total_overs * 6;
    match.current_inning = 1;
    int choice, runs;
    while (1) {
        displayScoreboard(&match);
        printf("\n1. Add Runs\n2. Add Wicket\n3. Exit\nChoice: ");
        scanf("%d", &choice);
        if (choice == 1) {
            printf("Enter Runs: ");
            scanf("%d", &runs);
            updateScore(&match, runs, 0);
        } else if (choice == 2) {
            updateScore(&match, 0, 1);
        } else if (choice == 3) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Invalid Choice!\n");
        }
    }
    return 0;
}