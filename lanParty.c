#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Player {
    char* firstName;
    char* secondName;
    int points;
};

struct Team {
    char* name;
    struct Player* players;
    int numPlayers;
    int score;
    struct Team* left;
    struct Team* right;
};

void removeExtraSpaces(FILE* inputFileName) {
    FILE* inputFile = fopen("d.in", "r");

    if (inputFile == NULL) {
        printf("Eroare la deschiderea fisierului.\n");
        exit;
    }
    char c;
    int spaceCount = 0;
    while ((c = fgetc(inputFile)) != EOF) {
        if (c == ' ') {
            spaceCount++;
        } else {
            spaceCount = 0;
        }

    }
    fclose(inputFile);

}

struct Player readPlayer(FILE* inputFile) {
    inputFile = fopen("d.in", "r");
    struct Player player;
    char *firstName;
    char *secondName;
    int points;

    fscanf(inputFile, "%s %s %d", firstName, secondName, &points);

    player.firstName = strdup(firstName);
    player.secondName = strdup(secondName);
    player.points = points;

    return player;
}

struct Team readTeam(FILE* inputFile) {
    inputFile = fopen("d.in", "r");
    struct Team team;
    char *name;
    int numPlayers;

    char* nameTeam = (char*)malloc(100 * sizeof(char));
    fscanf(inputFile, "%d %s", &numPlayers, &nameTeam);
    fgets(name, sizeof(name), inputFile);

    team.name = strdup(name);
    team.players = (struct Player*)malloc(numPlayers * sizeof(struct Player));
    team.numPlayers = numPlayers;
    team.score = 0;

    for (int i = 0; i < numPlayers; i++) {
        team.players[i] = readPlayer(inputFile);
    }

    return team;
}

void printTeams(FILE* outputFile, struct Team* teams, int numTeams) {
     outputFile = fopen("r.out", "w");
    for (int i = 0; i < numTeams; i++) {
        fprintf(outputFile, "%s\n", teams[i].name);
    }
    fprintf(outputFile, "\n");
}

void removeLowestScoreTeam(struct Team* teams, int numTeams) {
    int lowestScore = teams[0].score;
    int lowestScoreIndex = 0;

    for (int i = 1; i < numTeams; i++) {
        if (teams[i].score < lowestScore) {
            lowestScore = teams[i].score;
            lowestScoreIndex = i;
        }
    }

    free(teams[lowestScoreIndex].name);
    free(teams[lowestScoreIndex].players);

    for (int i = lowestScoreIndex; i < numTeams - 1; i++) {
        teams[i] = teams[i + 1];
    }
}

void printMatchQueue(FILE* outputFile, struct Team* matchQueue, int numTeams) {
    outputFile = fopen("r.out", "a");
    fprintf(outputFile, "--- ROUND NO:%d\n", numTeams / 2);
    for (int i = 0; i < numTeams; i += 2) {
        fprintf(outputFile, "%-30s - %30s\n", matchQueue[i].name, matchQueue[i + 1].name);
    }
    fprintf(outputFile, "\n");
}

void printWinnersStack(FILE* outputFile, struct Team* winnersStack, int numTeams) {
    outputFile = fopen("r.out", "a");
    fprintf(outputFile, "WINNERS OF ROUND NO:%d\n", numTeams / 2);
    for (int i = 0; i < numTeams; i++) {
        fprintf(outputFile, "%-30s - %5.2f\n", winnersStack[i].name, (float)winnersStack[i].score / winnersStack[i].numPlayers);
    }
    fprintf(outputFile, "\n");
}

void printStack(FILE* outputFile, struct Team* stack, int top) {
    outputFile = fopen("r.out", "a");
    for (int i = 0; i <= top; i++) {
        fprintf(outputFile, "%-30s - %5.2f\n", stack[i].name,(float)stack[i].score / stack[i].numPlayers);
    }
    fprintf(outputFile, "\n");
}

/* CERINTA 4 struct Team* createTeamNode(char* name, int numPlayers, struct Player* players, int score) {
    struct Team* newNode = (struct Team*)malloc(sizeof(struct Team));
    newNode->name = strdup(name);
    newNode->numPlayers = numPlayers;
    newNode->players = players;
    newNode->score = score;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void insertTeam(struct Team** root, struct Team* team) {
    if (*root == NULL) {
        *root = team;
        return;
    }

    if (team->score > (*root)->score || (team->score == (*root)->score && strcmp(team->name, (*root)->name) > 0)) {
        insertTeam(&(*root)->left, team);
    } else {
        insertTeam(&(*root)->right, team);
    }
}

void inOrderTraversal(struct Team* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("%-30s - %5.2f\n", root->name, (float)root->score / root->numPlayers);
        inOrderTraversal(root->right);
    }
}

void freeTeam(struct Team* team) {
    if (team != NULL) {
        free(team->name);
        for (int i = 0; i < team->numPlayers; i++) {
            free(team->players[i].firstName);
            free(team->players[i].secondName);
        }
        free(team->players);
        freeTeam(team->left);
        freeTeam(team->right);
        free(team);
    }
}
*/
int main() {
    FILE* inputFile = fopen("d.in", "r");
    FILE* outputFile = fopen("r.out", "w");
    if (inputFile == NULL || outputFile == NULL) {
        printf("Eroare la deschiderea fisierului.\n");
        return 1;
    }

    removeExtraSpaces(inputFile);

    int numTeams;
    struct Team* teams = (struct Team*)malloc(numTeams * sizeof(struct Team));
    for(int i = 0; i < numTeams; i++){
        teams[i]=readTeam(inputFile);
    }
    int Player;
    struct Player* player = (struct Player*)malloc(Player * sizeof(struct Player));
    for(int i = 0; i < numTeams; i++){
        player[i]=readPlayer(inputFile);
    }

    printTeams(outputFile, teams, numTeams);

    struct Team* matchQueue = teams;
    int numMatchTeams = numTeams;

    struct Team* winnersStack = (struct Team*)malloc(numTeams * sizeof(struct Team));
    int numWinners = 0;

    int numRounds = 0;
    int numTeamsRemaining = numTeams;
    while (numTeamsRemaining > 8) {

        printTeams(outputFile, teams, numTeamsRemaining);

        struct Team* matchQueue = (struct Team*)malloc(numTeamsRemaining * sizeof(struct Team));
        for (int i = 0; i < numTeamsRemaining; i++) {
            matchQueue[i] = teams[i];
        }

        int winnersTop = -1;
        struct Team* winnersStack = (struct Team*)malloc(numTeamsRemaining * sizeof(struct Team));
        struct Team* losersStack = (struct Team*)malloc(numTeamsRemaining * sizeof(struct Team));

        while (numTeamsRemaining > 1) {

            printMatchQueue(outputFile, matchQueue, numTeamsRemaining);

            for (int i = 0; i < numTeamsRemaining; i += 2) {
                if (matchQueue[i].score >= matchQueue[i + 1].score) {
                    winnersStack[++winnersTop] = matchQueue[i];
                    losersStack[winnersTop] = matchQueue[i + 1];
                } else {
                    winnersStack[++winnersTop] = matchQueue[i + 1];
                    losersStack[winnersTop] = matchQueue[i];
                }
            }
            removeLowestScoreTeam(matchQueue, numMatchTeams);
            numTeamsRemaining /= 2;
            matchQueue = (struct Team*)realloc(matchQueue, numMatchTeams * sizeof(struct Team));
            for (int i = 0; i < numTeamsRemaining; i++) {
                matchQueue[i] = winnersStack[i];
            }
        }


        printWinnersStack(outputFile, winnersStack, numTeamsRemaining * 2);
        printStack(outputFile, losersStack, winnersTop);

        numRounds++;
        removeLowestScoreTeam(teams, numTeamsRemaining * 2);
        numTeamsRemaining /= 2;}


  /* CERINTA 4 struct Team* root = NULL;
    for (int i = 0; i < numTeams; i++) {
        int score = 0;
        for (int j = 0; j < teams[i].numPlayers; j++) {
            score += teams[i].players[j].points;
        }
        teams[i].score = score;
        struct Team* teamNode = createTeamNode(teams[i].name, teams[i].numPlayers, teams[i].players, teams[i].score);
        insertTeam(&root, teamNode);
    }
 */
    fprintf(outputFile, "FINAL RANKING\n");
    for (int i = 0; i < numTeamsRemaining; i++) {
        fprintf(outputFile, "%-30s - %5.2f\n", teams[i].name, (float)teams[i].score / teams[i].numPlayers);
    }
    // inOrderTraversal(root);
    fprintf(outputFile, "\nTOTAL ROUNDS: %d", numRounds);
    fclose(outputFile);
    free(teams);
    free(player);
    free(matchQueue);
    free(winnersStack);
    free(teams);

   // freeTeam(root);

    return 0;
}
