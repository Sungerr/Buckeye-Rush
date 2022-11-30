//Includes FEHLCD.h & FEHUtility.h
#include "header.h"

//Constants for screen tracking
#define MENU 0
#define GAME 1
#define OTHER 2
#define GAME_OVER 3

//Struct for game tracking
struct game_state {
    int screen;
    int score[20];
    char scoreNames[20][20];
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
 * Draws game screen
 *
 * @param state: pointer to game state struct
 */
void playGame(game_state *state) {
    LCD.Clear( FEHLCD::Gray);
    LCD.WriteAt("Play Game Here", 5, 20);
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
 * Draws high scores screen
 *
 * @param state: pointer to game state struct
 */
void displayHighScores(game_state *state) {
    LCD.Clear( FEHLCD::Gray);
    LCD.WriteAt("Name", 30, 20);
    LCD.WriteAt("Score", 220, 20);
    LCD.DrawLine(0, 40, 319, 40);
    LCD.DrawLine(160, 0, 160, 319);

    //Write names
    char name[20];
    strcpy(name, (*state).scoreNames[0]);
    LCD.WriteAt(name, 30, 50);

    //Write high scores
    char score[2];
    LCD.WriteAt(score, 230, 50);
}

/*
 * Draws credits screen
 */
void displayCredits() {
    LCD.Clear( FEHLCD::Gray);
    LCD.WriteAt("Made by: Peter Sung", 5, 20);
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