//Includes header file
#include "header.h"

//Screen Manager file

//Constants for screen tracking
#define MENU 0
#define GAME 1
#define OTHER 2
#define GAME_OVER 3

//Struct for game tracking
struct game_state {
    int screen;
    int score[10] = {0};
};

/*
 * Draws menu screen
 *
 * @param menuIcon: array of icons to draw on screen
 */
void DrawMenu(FEHIcon::Icon menuIcon[5]) {
    //Set background color & text color
    LCD.Clear( FEHLCD::Scarlet);
    LCD.SetFontColor( FEHLCD::White );
    LCD.WriteAt("Buckeye Rush", 85, 10);
    
    //Button labels
    char labels[5][20] = {"Play", "Instructions", "High Scores", "Credits", "Exit"}; 

    //Draw the buttons
    FEHIcon::DrawIconArray(menuIcon, 5, 1, 50, 10, 75, 75, labels, WHITE, WHITE);
}

/*
 * Draws instructions screen
 */
void displayInstructions() {
    LCD.Clear( FEHLCD::Gray);

    //Write instructions
    LCD.WriteAt("Buckeye Rush", 90, 20);
    LCD.WriteAt("Click the screen to jump &", 5, 50);
    LCD.WriteAt("avoid obstacles!", 40, 70);
    LCD.WriteAt("Survive as long as you can", 5, 90);
    LCD.WriteAt("with 3 lives", 40, 110);
    LCD.WriteAt("The longer you go,", 5, 130);
    LCD.WriteAt("The higher your score!", 40, 150);
    
}

/*
 * Draws credits screen
 */
void displayCredits() {
    LCD.Clear( FEHLCD::Gray);
    LCD.WriteAt("Made by: Peter Sung", 30, 40);
    LCD.WriteAt("Using:", 15, 80);
    LCD.WriteAt("OSU Proteus Simulator", 30, 100);
}

/*
 * Draws game over screen
 *
 * @param score: final score to display
 */
void drawGameOver(int score) {
    LCD.Clear( FEHLCD::Black);
    LCD.WriteAt("Game Over", 105, 20);
    LCD.WriteAt("Final Score:", 55, 60);
    LCD.WriteAt(score, 215, 60);
}
/*
 * Loads scores from file
 *
 * @param state: game state struct
 */
void loadScore(game_state *state) {
    FILE *file;
    file = fopen("highscores.txt", "r");
    int score = 0;
    int index = 0;
    
    while (fscanf(file, "%d", &score) != EOF) {
        (*state).score[index] = score;
        index++;
    }
    fclose(file);
}

/*
 * Saves current scores to file
 *
 * @param state: game state struct
 */
void saveScores(game_state *state) {
    FILE *file;
    file = fopen("highscores.txt", "w");
    
    for (int scores : (*state).score) {
        fprintf(file, "%d\n", scores);
    }
    fclose(file);
}

/*
 * Update high score
 *
 * @param score: final score achieved
 * @param state: pointer to game state struct
 */
void updateHighScores(int score, game_state *state) {
    loadScore(state);
    //Check if score is high enough to be on high score list
    for (int i = 0; i < 10; i++) {
        if (score > (*state).score[i]) {
            //Shift all scores down
            for (int j = 9; j > i; j--) {
                (*state).score[j] = (*state).score[j-1];
            }
            //Insert new score
            (*state).score[i] = score;
            break;
        }
    }
    saveScores(state);
}


/* 
 * Draws high scores screen
 *
 * @param state: pointer to game state struct
 */
void displayHighScores(game_state *state) {
    LCD.Clear( FEHLCD::Gray);
    LCD.WriteAt("High Scores", 90, 10);
    LCD.DrawLine(0, 32, 319, 32);

    //Load scores
    loadScore(state);

    //Write high scores
    int y = 40;
    int counter = 1;
    char number[4];
    for (int score : (*state).score) {
        sprintf(number, "%d.", counter);
        LCD.WriteAt(number, 115, y);
        LCD.WriteAt(score, 175, y);
        y+=20;
        counter++;
    }
}