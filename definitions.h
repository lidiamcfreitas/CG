//
//  definitions.h
//

#ifndef definitions_h
#define definitions_h

#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <math.h>
#include <time.h>
#include <vector>
#include <memory>

#if defined(__APPLE__) || defined(MACOSX)
    #include <GLUT/glut.h>
    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#else
    #include <GL/glut.h>
    
#endif

// GAMEMANAGER
#define NUM_CHEERIOS            30
#define NUM_ORANGES             3
#define NUM_BUTTERS             5
#define ROAD_OUT_RADIUS         120
#define ROAD_WIDTH              40
#define TABLE_SIZE              250

// CAR
#define CAR_VEL_MAX             110
#define CAR_VEL_MIN             -40
#define CAR_VEL_STEP            10
#define CAR_ANGLE_STEP          180
#define CAR_ACCEL               50

// ORANGES
#define ORANGE_ACCEL            1
#define ORANGE_INI_VEL          10
#define ORANGE_PERIM            ORANGE_SIZE*2*M_PI
#define ORANGE_SIZE             5
#define ORANGE_VEL_STEP         5

// BUTTERS
#define BUTTER_DEACCEL          200

// CHEERIOS
#define CHEERIO_RADIUS_TUBE     1
#define CHEERIO_RADIUS          3
#define CHEERIO_DEACCEL         10*_vel
#define CHEERIO_REL_MASS        0.3

// CAMERAS
#define ORTHO_SIZE              130
#define FOV_Y                   45
#define PRESPCAM_POS            350 //distance from z=0 with a FOV_Y of 45
#define CAMERA_ORTHO            0
#define CAMERA_PERSP            1
#define CAMERA_CAR              2
#define DISTANCE_CAM_TO_CAR     75
#define HEIGHT_CAM_TO_CAR       100

// POINTLIGHTS
#define NUM_POINTLIGHTS         6
#define RADIUS_POINTLIGHTS      125

GLvoid main_wakeupOrange(int value);
#endif /* definitions_h */
