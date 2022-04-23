/*********

I displayed a fishing boat and a hook.
You can right click on middle of the fish (purple part) and catch them,
the program displays how many fish you've caught so far.
*********/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>

#define WINDOW_WIDTH  1150
#define WINDOW_HEIGHT 700

#define TIMER_PERIOD  5 // Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer

#define D2R 0.0174532

/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height
int xMove, yMove, counter = 0, objx, objy;
int arr[10][2], timecnt = 0;
bool activeTimer = false, hook = false;
int xConverted, yConverted, shapeNo, hookx, hooky, fishcnt = 0;
//
// to draw circle, center at (x,y)
// radius r
//
void circle(int x, int y, int r)
{
#define PI 3.1415
    float angle;
    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void circle_wire(int x, int y, int r)
{
#define PI 3.1415
    float angle;

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 100; i++)
    {
        angle = 2 * PI * i / 100;
        glVertex2f(x + r * cos(angle), y + r * sin(angle));
    }
    glEnd();
}

void print(int x, int y, const char* string, void* font)
{
    int len, i;

    glRasterPos2f(x, y);
    len = (int)strlen(string);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, string[i]);
    }
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void* font, const char* string, ...)
{
    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);

    int len, i;
    glRasterPos2f(x, y);
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutBitmapCharacter(font, str[i]);
    }
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, const char* string, ...) {

    va_list ap;
    va_start(ap, string);
    char str[1024];
    vsprintf_s(str, string, ap);
    va_end(ap);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(size, size, 1);

    int len, i;
    len = (int)strlen(str);
    for (i = 0; i < len; i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
    }
    glPopMatrix();
}

// To display onto window using OpenGL commands

void onMove(int x, int y) {
    // GLUT to OpenGL coordinate conversion:
 //   x2 = x1 - winWidth / 2
 //   y2 = winHeight / 2 - y1
    xMove = x - winWidth / 2;
    yMove = winHeight / 2 - y;
    // to refresh the window it calls display() function

}

void drawComplex()
{
    //drawing the fish
    glColor3f(0.292, 0.56, 0.552);
    glBegin(GL_QUADS);
    glVertex2f(objx - 65, objy + 0);
    glVertex2f(objx + 0, objy + 25);
    glColor3f(0.592, 0.86, 0.852);
    glVertex2f(objx + 65, objy + 0);
    glVertex2f(objx + 0, objy - 25);
    glEnd();
    glColor3f(0.292, 0.56, 0.552);
    glBegin(GL_TRIANGLES);
    glVertex2f(objx - 60, objy + 0);
    glColor3f(0.492, 0.76, 0.752);
    glVertex2f(objx - 80, objy + 25);
    glVertex2f(objx - 80, objy - 25);
    glEnd();
    glColor3f(0.292, 0.56, 0.552);
    glBegin(GL_TRIANGLES);
    glVertex2f(objx + 1, objy + 25);
    glVertex2f(objx - 11, objy + 19);
    glColor3f(0.392, 0.66, 0.652);
    glVertex2f(objx - 17, objy + 33);
    glEnd();
    glColor3f(0.292, 0.56, 0.552);
    glBegin(GL_TRIANGLES);
    glVertex2f(objx - 1, objy - 25);
    glVertex2f(objx - 15, objy - 19);
    glColor3f(0.392, 0.66, 0.652);
    glVertex2f(objx - 20, objy - 31);
    glEnd();
    glColor3f(1, 1, 1);
    circle(objx + 34, objy + 8, 3.5);
    glColor3f(0, 0, 0);
    circle(objx + 34, objy + 8, 2.5);

    glBegin(GL_LINES);
    glVertex2f(objx + 52, objy + 6);
    glVertex2f(objx + 45, objy + 2);
    glEnd();
    //first row 
    glColor3f(0.53, 0.25, 0.67);

    circle(objx + 16, objy + 9, 4);
    circle(objx + 16, objy + 3, 4);
    circle(objx + 16, objy - 3, 4);
    circle(objx + 16, objy - 9, 4);

    //second row
    glColor3f(0.58, 0.3, 0.72);
    circle(objx + 10, objy + 15, 4);
    circle(objx + 10, objy + 9, 4);
    circle(objx + 10, objy + 3, 4);
    circle(objx + 10, objy - 3, 4);
    circle(objx + 10, objy - 9, 4);
    circle(objx + 10, objy - 15, 4);
    //third row
    glColor3f(0.68, 0.4, 0.82);
    circle(objx + 4, objy + 15, 4);
    circle(objx + 4, objy + 9, 4);
    circle(objx + 4, objy + 3, 4);
    circle(objx + 4, objy - 3, 4);
    circle(objx + 4, objy - 9, 4);
    circle(objx + 4, objy - 15, 4);
    //fourth row
    glColor3f(0.58, 0.3, 0.72);

    circle(objx - 2, objy + 9, 4);
    circle(objx - 2, objy + 3, 4);
    circle(objx - 2, objy - 3, 4);
    circle(objx - 2, objy - 9, 4);
    glColor3f(0.58, 0.3, 0.72);
    circle(objx - 8, objy + 3, 4);
    circle(objx - 8, objy - 3, 4);
    glColor3f(0.58, 0.3, 0.72);
    circle(objx - 14, objy + 0, 4);
    glColor3f(0, 0, 0);
    //writing numbers on each shape
    vprint(objx, objy, GLUT_BITMAP_TIMES_ROMAN_10, "%d", shapeNo);


}
void drawBubbles()
{
    glColor3f(1, 1, 1);
    circle_wire(objx + 67, objy + 8, 3);
    circle_wire(objx + 67, objy + 16, 5);
    circle_wire(objx + 67, objy + 28, 7);
}
void throwHook()
{
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2f(0, 368);
    glVertex2f(hookx, hooky);
    glEnd();
    vprint2(hookx, hooky - 15, 0.2, "U");
    glBegin(GL_TRIANGLES);
    glVertex2f(hookx + 10, hooky);
    glVertex2f(hookx + 15, hooky + 10);
    glVertex2f(hookx + 20, hooky);
    glEnd();
}
void drawFishingboat()
{
    glColor3f(1, 0, 0);
    glBegin(GL_QUADS);
    glVertex2f(-140, 300);
    glVertex2f(-160, 368);
    glVertex2f(160, 368);
    glVertex2f(140, 300);
    glEnd();

}
void display() {
    // clear window to black
    glClearColor(0.26, 0.36, 0.476, 0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.052, 0.108, 0.168);
    glRectf(-500, 360, -370, 290);
    glColor3f(0.996, 0.9, 0.984);
    vprint2(-490, 335, 0.1, "Niyousha Mojoudi");
    vprint2(-490, 320, 0.1, "  22001297");
    vprint2(-490, 315, 0.1, "___________");
    vprint2(500, -330, 0.1, "(%d,%d)", xMove, yMove);
    //displaying ten objects on the screen
    for (int i = 0; i < counter; i++) {
        if (arr[i][0] <= 700)
            arr[i][0] += timecnt;
        else
            arr[i][0] = -700;
        objx = arr[i][0];
        objy = arr[i][1];
        shapeNo = i + 1;
        drawComplex();
        
        drawBubbles();

    }
    //if right click is activated, throw the hook
    if (hook)
        throwHook();
    drawFishingboat();
    //display the count of caught fish
    glColor3f(0.052, 0.108, 0.168);
    glRectf(270, 345, 550, 300);
    glColor3f(0.996, 0.9, 0.984);
    vprint2(-500, 300, 0.1, "You caught %d fish!", fishcnt);
    vprint2(280, 335, 0.1, "Left click on the screen to display fish.");
    vprint2(280, 325, 0.1, "Press F1 button to animate fish.");
    vprint2(280, 315, 0.1, "Right click on the screen to catch fish.");
    vprint2(280, 305, 0.1, "Press esc button to exit.");
  
    glutSwapBuffers();

}

//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

void onKeyUp(unsigned char key, int x, int y)
{
    // exit when ESC is pressed.
    if (key == 27)
        exit(0);

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown(int key, int x, int y)
{
    if (key == GLUT_KEY_F1) {
        activeTimer = !activeTimer;
        if (activeTimer == 1) {
            printf("Timer is activated.");
        }
        else if (activeTimer == 0) {
            printf("Timer is deactivated.");
            timecnt = 0;
        }
    }

    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP: up = true; break;
    case GLUT_KEY_DOWN: down = true; break;
    case GLUT_KEY_LEFT: left = true; break;
    case GLUT_KEY_RIGHT: right = true; break;
    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp(int key, int x, int y)
{

    // Write your codes here.
    switch (key) {
    case GLUT_KEY_UP: up = false; break;
    case GLUT_KEY_DOWN: down = false; break;
    case GLUT_KEY_LEFT: left = false; break;
    case GLUT_KEY_RIGHT: right = false; break;
    }

    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
void onClick(int button, int stat, int x, int y) {
    xConverted = x - winWidth / 2;
    yConverted = winHeight / 2 - y;
    if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN && counter < 10 && yConverted < 270) {
        int flag = 0;
        //not letting objects overlap eachother, first get the first coordinates, then check each new cordinate with  all the previous ones
        if (counter == 0) {
            arr[counter][0] = xConverted;
            arr[counter][1] = yConverted;
            counter++;
        }
        else {

            for (int i = 0; i < counter; i++) {
                if (((xConverted <= arr[i][0] + 130) && (xConverted >= arr[i][0] - 130)) && ((yConverted <= arr[i][1] + 40) && (yConverted >= arr[i][1] - 40))) {
                    flag = 1;
                }


            }
            if (flag != 1) {
                arr[counter][0] = x - winWidth / 2;
                arr[counter][1] = winHeight / 2 - y;
                counter++;
            }
        }


    }
    if (button == GLUT_RIGHT_BUTTON && stat == GLUT_DOWN)
    {
        hook = true;
        hookx = xConverted;
        hooky = yConverted;
        //check if the hook is clicked in the purple are
        for (int i = 0; i < counter; i++) {
            if (hookx >= arr[i][0] - 15 && hookx <= arr[i][0] + 15 && hooky >= arr[i][1] - 15 && hooky <= arr[i][1] + 15) {
                fishcnt++;
            }
        }
    }
    glutPostRedisplay();


    // Write your codes here.
    vprint2(540, -335, 0.1, "(%d,%d)", x, y);
    // to refresh the window it calls display() function
    glutPostRedisplay();
}

//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize(int w, int h)
{
    winWidth = w;
    winHeight = h;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-w / 2, w / 2, -h / 2, h / 2, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    display(); // refresh window.
}

void onMoveDown(int x, int y) {
    // Write your codes here.



    // to refresh the window it calls display() function   
    glutPostRedisplay();
}

// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1



void onTimer(int v) {
    glutTimerFunc(TIMER_PERIOD, onTimer, 0);



    if (activeTimer == 1)
    {
        //set time to one, it functions like the speed of the fish
        timecnt = 1;

    }
    // to refresh the window it calls display() function
    glutPostRedisplay(); // display()

}


void Init() {

    // Smoothing shapes
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    //glutInitWindowPosition(100, 100);
    glutCreateWindow("Deep in the Ocean");

    glutDisplayFunc(display);
    glutReshapeFunc(onResize);

    //
    // keyboard registration
    //
    glutKeyboardFunc(onKeyDown);
    glutSpecialFunc(onSpecialKeyDown);

    glutKeyboardUpFunc(onKeyUp);
    glutSpecialUpFunc(onSpecialKeyUp);

    //
    // mouse registration
    //
    glutMouseFunc(onClick);
    glutMotionFunc(onMoveDown);
    glutPassiveMotionFunc(onMove);


    glutTimerFunc(TIMER_PERIOD, onTimer, 0);
    Init();

    glutMainLoop();
}