#include <iostream>
#include <raylib.h>

int main(int argno, char** args){
    const int sWidth = 750;
    const int sHieght = 750;

    int ball_x = 100;
    int ball_y = 100;
    int ball_speed_x = 5;
    int ball_speed_y = 5;

    int ball_radius = 30;

    std::cout<<"Hello world"<<std::endl;

    InitWindow(sWidth, sHieght, "Snake");
    SetTargetFPS(60);

    while (WindowShouldClose() == false){
        BeginDrawing();
        ClearBackground(BLACK);
        ball_x += ball_speed_x;
        ball_y += ball_speed_y;

        if(ball_x + ball_radius >= sWidth  || ball_x - ball_radius <= 0)
        {
            ball_speed_x *= -1;
        }

        if(ball_y + ball_radius >= sHieght  || ball_y - ball_radius <= 0)
        {
            ball_speed_y *= -1;
        }

        DrawRectangle(ball_x, ball_y, ball_radius, ball_radius, RED);
        // DrawCircle(ball_x,ball_y,ball_radius, WHITE);
        EndDrawing();
    }

    CloseWindow();
    return 0;

}
