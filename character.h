#include "obstacle.h"

#pragma once

class Character {
    public: 
        /*
         * Character constructor
         */
        Character() {
        }

        /*
         * Make character jump
         *
         * @param o: pointer to obstacle object
         * @param start: value of start time
         */
        void jump(Obstacle *o, double start) {
            //Loop through character y position to emulate jumping
            for (int i = -20; i <= 20; i++) {
                //Change character y position
                y += (int) (i*0.25);

                //Ensures obstacle is not overwritten & continues to move
                (*o).moveObstacle();
                drawCharacter(*o);

                //Redraw score, health & obstacle
                LCD.WriteAt("Score: ", 180, 10);
                LCD.WriteAt((int) (10*(TimeNow() - (start))), 255, 10);
                LCD.WriteAt("Health: ", 30, 10);
                LCD.WriteAt(health, 120, 10);

                //Check obstacle collision
                collision(o);

                //Delay for jump animation
                Sleep(0.01);
            }
        }

        /*
         * Checks for character collision with obstacle
         *
         * @param o: pointer to obstacle object
         */
        void collision(Obstacle *o) {
            //Determine if position of obstacle is within character boundaries
            if ((*o).getX() <= x + 25 && (*o).getX() >= x - 10) {
                if ((*o).getY() <= y + 25 && (*o).getY() >= y - 10) {
                    //Collision detected
                    health--;
                    (*o).resetPosition();
                    Sleep(0.5);
                    
                }
            }
        }

        /*
         * Get character health
         *
         * @return int: health value
         */
        int getHeath() {
            return health;
        }

        /*
         * Draws character
         *
         * @param o: Obstacle object
         */
        void drawCharacter(Obstacle o) {
            LCD.Clear( FEHLCD::Gray);
            LCD.DrawRectangle(x,y, SIZE, SIZE);
            o.drawObstacle();
            LCD.DrawLine(0, 200, 319, 200);
        }

        /*
         * Resets character variables
         */
        void reset() {
            x = 10;
            y = 180;
            health = 3;
        }

    private:
        //Character size
        const int SIZE = 20;
        //Character health
        int health = 3;
        //Character position
        int x = 10;
        int y = 180;
};