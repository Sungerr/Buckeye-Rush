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
                (*o).resetPosition(collision((*o).getX(), (*o).getY()));

                //Delay for jump animation
                Sleep(0.01);
            }
        }

        /*
         * Checks for character collision with obstacle
         *
         * @param obstacleX: obstacle x position
         * @param obstacleY: obstacle y position
         * @return bool: true if collision occurs
         */
        bool collision(int obstacleX, int obstacleY) {
            bool hit = false;
            //Determine if position of obstacle is within character boundaries
            if (obstacleX <= x + 25 && obstacleX >= x - 10) {
                if (obstacleY <= y + 10 && obstacleY >= y - 25) {
                    //Collision detected
                    hit = true;

                    //Decrease health
                    health--;
                    
                    printf("Health: %d\n", health);
                    printf("Hit: %d\n", hit);
                }
            }
            return hit;
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