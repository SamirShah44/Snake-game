#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>

using namespace std;
const int height = 20;
const int width = 40;

class Food
{
public:
    int foodX;
    int foodY;

    void foodPos()
    {
        foodX = rand() % width + 1;
        foodY = rand() % height + 1;
        if(foodX==1||foodX==width){
        foodX = rand() % width + 1;
            
        }
        if(foodY==0||foodY==height){
        foodY = rand() % height + 1;

        }
    }
    Food()
    {
        foodPos();
    }
};
Food food;
class Snake
{
public:
    int len;
    int vel;
    char direction;
    int tailX[100], tailY[100], ntail = 1;
    int y = height / 2, x = width / 2;
    bool gameover = false;
    Snake()
    {
        vel = 1;
        direction = 'O';
        vel = 1;
        len = 0;
    }

    void change_dir(char dir)
    {
        direction = dir;
    }
    void tail()
    {
        int prevX = tailX[0];
        int prevY = tailY[0];
        int prev2X, prev2Y;
        tailX[0] = x;
        tailY[0] = y;
        for (int i = 1; i < ntail; i++)
        {
            prev2X = tailX[i];
            prev2Y = tailY[i];
            tailX[i] = prevX;
            tailY[i] = prevY;
            prevX = prev2X;
            prevY = prev2Y;
        }
    }

    void move()
    {
        switch (direction)
        {
        case 'w':
            y -= vel;
            break;
        case 'a':
            x -= vel;
            break;
        case 's':
            y += vel;
            break;
        case 'd':
            x += vel;
            break;
        case 'x':
            gameover = true;
            break;
        }
        if (x == food.foodX && y == food.foodY)
        {
            ntail++;
            len++;
            food.foodPos();
        }
        tail();
        if (x >= width)
            x = 0;
        else if (x < 0)
            x = width - 1;
        if (y >= height)
            y = 0;
        else if (y < 0)
            y = height - 1;
        for (int i = 1; i < ntail; i++)
        {
            if (tailX[i] == x && tailY[i] == y)
            {
                gameover = true;
            }
        }
    }
};

Snake snake;

void draw()
{

    for (int i = 0; i < height; i++)
    {

        cout << "#";
        for (int j = 0; j < width; j++)
        {
            if (i == 0 || i == height - 1)
            {
                cout << "#";
            }
            else if (i == snake.y && j == snake.x)
            {
                cout << "0";
            }
            else if (i == food.foodY && j == food.foodX)
            {
                cout << "@";
            }
            else
            {
                bool print = false;
                for (int k = 0; k < snake.ntail; k++)
                {
                    if (snake.tailX[k] == j && snake.tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                {
                    cout << " ";
                }
            }
        }
        cout << "#" << endl;
    }
    cout << endl;
    cout << "Score:" << snake.len << endl;
}

int main()
{
    srand(time(NULL));
    while (!snake.gameover)
    {

        draw();
        if (_kbhit())
        {
            switch (_getch())
            {
            case 'w':
                snake.change_dir('w');
                break;
            case 'a':
                snake.change_dir('a');
                break;
            case 's':
                snake.change_dir('s');
                break;
            case 'd':
                snake.change_dir('d');
                break;
            default:
                break;
            }
        }
        snake.move();

        Sleep(10);
        system("cls");
    }
    if (snake.gameover)
    {
        cout << "Gameover\nYour score : " << snake.len;
    }

    return 0;
}