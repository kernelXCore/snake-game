#include <GL/glut.h>
#include <vector>
#include <ctime>
#include <iostream>

using namespace std;

const int GRID_SIZE = 20;     
const int GRID_WIDTH = 30;    
const int GRID_HEIGHT = 30;     


struct Point { int x, y; };
vector<Point> snake;
int dirX = 1, dirY = 0; 
bool gameOver = false;


Point apple;


int score = 0;


void spawnApple()
{
    apple.x = rand() % GRID_WIDTH;
    apple.y = rand() % GRID_HEIGHT;
}


void resetGame()
{
    snake.clear();
    snake.push_back({ GRID_WIDTH / 2, GRID_HEIGHT / 2 });
    dirX = 1; dirY = 0;
    gameOver = false;
    score = 0;
    spawnApple();
}


void drawSquare(int x, int y, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_QUADS); // square
    glVertex2f(x * GRID_SIZE, y * GRID_SIZE);
    glVertex2f((x + 1) * GRID_SIZE, y * GRID_SIZE);
    glVertex2f((x + 1) * GRID_SIZE, (y + 1) * GRID_SIZE);
    glVertex2f(x * GRID_SIZE, (y + 1) * GRID_SIZE);
    glEnd();
}


void update(int value)
{
    if (!gameOver)
    {
        
        Point newHead = { snake[0].x + dirX, snake[0].y + dirY };

        
        if (newHead.x < 0 || newHead.x >= GRID_WIDTH || newHead.y < 0 || newHead.y >= GRID_HEIGHT)
        {
            gameOver = true;
        }
        

        
        for (size_t i = 0; i < snake.size(); i++)
        {
            if (snake[i].x == newHead.x && snake[i].y == newHead.y)
            {
                gameOver = true;
                break;
            }
        }

        
        snake.insert(snake.begin(), newHead);

        
        if (newHead.x == apple.x && newHead.y == apple.y)
        {
            score++;
            spawnApple();
            snake.push_back(snake.back());
            snake.push_back(snake.back());
            snake.push_back(snake.back());


     
        }
        else
        {
            snake.pop_back();
        }
    }

    glutPostRedisplay();
    glutTimerFunc(100, update, 0); 
}


void render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

  
    for (size_t i = 0; i < snake.size(); i++)
    {
        drawSquare(snake[i].x, snake[i].y, 0.0f, 1.0f, 0.0f); 
    }

    drawSquare(apple.x, apple.y, 1.0f, 0.0f, 0.0f); // أحمر

    if (gameOver)
    {
        glRasterPos2f(GRID_WIDTH * GRID_SIZE / 4, GRID_HEIGHT * GRID_SIZE / 2);
        const char* msg = "GAME OVER! Press R to Restart";
        while (*msg)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *msg++);
        }
    }

    glutSwapBuffers();
}

void specialKeys(int key, int x, int y)
{
    if (gameOver) return;

    switch (key)
    {
    case GLUT_KEY_UP:    if (dirY == 0) { dirX = 0; dirY = 1; };  break;
    case GLUT_KEY_DOWN:  if (dirY == 0) { dirX = 0; dirY = -1; }  break;
    case GLUT_KEY_LEFT:  if (dirX == 0) { dirX = -1; dirY = 0; }  break;
    case GLUT_KEY_RIGHT: if (dirX == 0) { dirX = 1; dirY = 0; } break;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 'r' || key == 'R')
        resetGame();
}

int main(int argc, char** argv)
{
    srand(time(0));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(GRID_WIDTH * GRID_SIZE, GRID_HEIGHT * GRID_SIZE);
    glutCreateWindow("Snake Game - OpenGL");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, GRID_WIDTH * GRID_SIZE, 0, GRID_HEIGHT * GRID_SIZE);
    glMatrixMode(GL_MODELVIEW);

    resetGame();

    glutDisplayFunc(render);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(10, update, 0);

    glutMainLoop();
    return 0;
}














