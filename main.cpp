
#if defined(__APPLE__) || defined(MACOSX)
    #include <GLUT/glut.h>
#else
    #include <stdlib.h>
    #include <GL/glut.h>
    #define _USE_MATH_DEFINES
#endif

#include "gamemanager.h"
#include <stdarg.h>
#include <cmath>
#define GL_GLEXT_PROTOTYPES



GLboolean solidOrwire = true;
GLboolean paused = false;
GLdouble lastUpTime = 0.0;

GameManager gamemanager = GameManager();

GLvoid specialKeys( int key, int x, int y ) {
    
    if (key == GLUT_KEY_RIGHT)
        gamemanager.setKeyRight(true);
    else if (key == GLUT_KEY_LEFT)
        gamemanager.setKeyLeft(true);
    else if (key == GLUT_KEY_UP)
        gamemanager.setKeyUp(true);
    else if (key == GLUT_KEY_DOWN)
        gamemanager.setKeyDown(true);

}

GLvoid specialKeysUp( int key, int x, int y ) {
    
    if (key == GLUT_KEY_RIGHT)
        gamemanager.setKeyRight(false);
    else if (key == GLUT_KEY_LEFT)
        gamemanager.setKeyLeft(false);
    else if (key == GLUT_KEY_UP)
        gamemanager.setKeyUp(false);
    else if (key == GLUT_KEY_DOWN)
        gamemanager.setKeyDown(false);
}
GLvoid GameControl(unsigned char key, int x, int y){
	switch (key){
	case 'r':
		gamemanager = GameManager();
		gamemanager.init();
		break;
	case 's':
		paused = !paused;
		break;
	}
	if (!paused){
		gamemanager.keyPressed(key);
	}
}

GLvoid display()
{
    gamemanager.display(solidOrwire); 
}

GLvoid reshape(int w, int h)
{
    gamemanager.reshape(w, h);
}

GLvoid timer(int value)
{
    GLdouble currentTime = glutGet(GLUT_ELAPSED_TIME);
    GLdouble diff = currentTime - lastUpTime;
    lastUpTime = currentTime;
    
    if (!paused) {
        gamemanager.update(diff);
        if (gamemanager.itsOver()){
            gamemanager = GameManager();
            gamemanager.init();
        }
    }
    
	glutPostRedisplay();
    
    glutTimerFunc(10, timer, 0);

}

GLvoid main_wakeupOrange(int value){
    gamemanager.wakeupOrange(value);
}

GLvoid main_levelUp(int value){
    gamemanager.levelUp();
    glutTimerFunc(10000, main_levelUp, 0);
}

int main(int argc, char **argv)
{

    glutInit(&argc, argv);
	glutInitWindowSize(900, 600);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Micro Machines");
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    
    gamemanager.init();
    
	glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glutSpecialUpFunc(specialKeysUp);
    glutKeyboardFunc(GameControl);
    
	glutReshapeFunc(reshape);
    //glClearColor( 1., 1., 1., 0.);
    glClearColor( 65./255, 105./255, 1., 0.);
	glutTimerFunc(10, timer, 0);
    glutTimerFunc(10000, main_levelUp, 0);
    
	glutMainLoop();
	return 0;
}
