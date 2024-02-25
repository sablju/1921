#include <stdio.h>
#include <stdlib.h>

#define MAX_ROWS 10
#define MAX_COLS 10

char map[MAX_ROWS][MAX_COLS];
int playerRow, playerCol;
int startRow, startCol;

void initializeMap(const char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    char line[MAX_COLS + 2]; // Additional space for '\n' and '\0'
    int row = 0;

    while (fgets(line, sizeof(line), file) && row < MAX_ROWS) {
        strncpy(map[row], line, MAX_COLS); // Copy line to map[row]
        row++;
    }

    // Find player and start position in the map
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            if (map[i][j] == 'S') {
                startRow = i;
                startCol = j;
                playerRow = i;
                playerCol = j;
            }
        }
    }

    fclose(file);
}

void displayMap() {
    printf("Current Map:\n");
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
}

int canMove(int newRow, int newCol) {
    if (newRow < 0 || newRow >= MAX_ROWS || newCol < 0 || newCol >= MAX_COLS) {
        return 0;
    }
    return map[newRow][newCol] == ' ' || map[newRow][newCol] == 'E';
}

void makeMove(int newRow, int newCol) {
    map[playerRow][playerCol] = ' ';
    map[startRow][startCol] = 'S';
    map[newRow][newCol] = 'X';
    playerRow = newRow;
    playerCol = newCol;
}

int main() {
    char filePath[] = "map4.csv";
    initializeMap(filePath);

    char action;
    int newPlayerRow, newPlayerCol;

    while (1) {
        displayMap();

        printf("Enter move (w/a/s/d) or 'q' to quit: ");
        scanf(" %c", &action);

        if (action == 'q' || action == 'Q') {
            printf("Exiting the game. Goodbye!\n");
            break;
        }

        newPlayerRow = playerRow;
        newPlayerCol = playerCol;

        switch (action) {
            case 'w':
                newPlayerRow--;
                break;
            case 's':
                newPlayerRow++;
                break;
            case 'a':
                newPlayerCol--;
                break;
            case 'd':
                newPlayerCol++;
                break;
            default:
                printf("Invalid move. Use 'w', 'a', 's', or 'd'.\n");
                continue;
        }

        if (canMove(newPlayerRow, newPlayerCol)) {
            makeMove(newPlayerRow, newPlayerCol);
        } else {
            printf("Cannot move to the specified position.\n");
        }
    }

    return 0;
}

