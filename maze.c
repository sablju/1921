#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

constexpr int MAX_ROWS = 100;
constexpr int MAX_COLS = 100;
constexpr int MIN_ROWS = 5;
constexpr int MIN_COLS = 5;

typedef struct {
    char map[MAX_ROWS][MAX_COLS];
    int playerRow;
    int playerCol;
    int startRow;
    int startCol;
} GameMap;

void initializeMap(GameMap *game, const char *filePath)
 {
    FILE *file = fopen(filePath, "r");
   
    if (file == NULL) 
    {
        printf("Error opening file: %s\n", filePath);
        exit(EXIT_FAILURE);
    }
    std::string name = filePath;

    int map_rows = (name[name.size()-7]-'0');//行
    int map_cols = (name[name.size()-5]-'0');//列
   

    std::ifstream in(filePath);
    std::string lines;

    std::vector<int>Cols;
    while (getline(in, lines)) 
    {
        {
            Cols.push_back(lines.size());
        }
    }

if(Cols.size()<5)
{
    std::cout<<"ERROR:Rows less than 5 !!!"<<std::endl;
    
}
else if (Cols.size() >100)
{
    std::cout<<"ERROR:Rows greater than 100 !!!"<<std::endl;
    
}

if(Cols.size()!=map_rows)
{
    std::cout << "ERROR:Wrong number of rows !!!" << std::endl;
    
}
for (size_t i = 0; i < Cols.size()-1; i++)
{
    if(Cols[i]<5)
    {
        std::cout<<"ERROR:The number of columns is less than 5 !!!"<<std::endl;
        
    }
    else if (Cols[i] >100)
    {
        std::cout<<"ERROR:The number of columns greater than 100 !!!"<<std::endl;
       
    }
    if (Cols[i]!=map_cols)
    {
        std::cout << "ERROR:Wrong number of cols !!!" << std::endl;
        
    }
}
    char line[MAX_COLS + 2]; // Additional space for '\n' and '\0'
    int row = 0;

    while (fgets(line, sizeof(line), file) && row < MAX_ROWS) {
        int j = 0; // Initialize j here

        for (; line[j] != '\0' && j < MAX_COLS; j++) {
            game->map[row][j] = line[j];

            if (line[j] == 'S') {
                game->startRow = row;
                game->startCol = j;
            }
        }

        // Fill remaining columns with null characters
        for (; j < MAX_COLS; j++) {
            game->map[row][j] = '\0';
        }

        row++;
    }

    game->playerRow = game->startRow;
    game->playerCol = game->startCol;
    game->map[game->playerRow][game->playerCol] = 'X';


    fclose(file); 
}

void displayMap(GameMap *game) {
    std::cout<<"Current Map:"<<std::endl;
    for (int i = 0; i < MAX_ROWS && game->map[i][0] != '\0'; i++) {
        printf("%s", game->map[i]);
    }
    printf("\n"); 
}

int canMove(GameMap *game, int newRow, int newCol) {
    if (newRow < 0 || newRow >= MAX_ROWS || newCol < 0 || newCol >= MAX_COLS) {
        return 0;
    }
    return game->map[newRow][newCol] == ' ' || game->map[newRow][newCol] == 'E';
}

void makeMove(GameMap *game, int newRow, int newCol) {
    if (newRow >= 0 && newRow < MAX_ROWS && newCol >= 0 && newCol < MAX_COLS) {
        if (canMove(game, newRow, newCol)) {
            game->map[game->playerRow][game->playerCol] = ' ';
            game->map[game->startRow][game->startCol] = 'S';
            game->map[newRow][newCol] = 'X';
            game->playerRow = newRow;
            game->playerCol = newCol;
        } else {
            printf("Cannot move to the specified position.\n");
        }
    } else {
        printf("Invalid move. Out of bounds.\n");
    }
}

int main(int argc, char* argv[]) {
     if (argc != 2) {
        printf("Usage: %s <map_file>\n", argv[0]);
        return EXIT_FAILURE;
    }

    GameMap game;
    initializeMap(&game, argv[1]);

    
    int newPlayerRow, newPlayerCol;

    while (1) {
        char action;
        printf("Enter move (w/a/s/d) or 'M' to view the map, 'Q' to quit: ");
        scanf(" %c", &action);

        if (action == 'q' || action == 'Q') {
            printf("Exiting the game. Goodbye!!!\n");
            break;
        }

        if (action == 'm' || action == 'M') {
            displayMap(&game);
            continue;
        }

        newPlayerRow = game.playerRow;
        newPlayerCol = game.playerCol;

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

        makeMove(&game, newPlayerRow, newPlayerCol);

        if (game.map[game.playerRow][game.playerCol] == 'E') {
            printf("Congratulations! You win!\n");
            break;
        }
    }

    return EXIT_SUCCESS;
}
