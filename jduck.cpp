/**
 *
 *  @file jduck.cpp
 *
 *  @brief The class specify jurrassic duck model
 *
 *  @author Ren DING
 *  @date 05/08/12.
 *
 */

#include "glheaders.h"
#include "jdUtility.h"
#include "jdalgorithm.h"
#include "jduck.h"
#include "headers.h"

const float DUCK_STEERINGFORCE = 3.0;
const int PATROLLING = 0;
const int CHASING = 1;

/*
//These are only for testing AI algorithms
//cube vertex data
static GLfloat Vertices[8][3] = {
  { -1.0, -1.0,  1.0 }, // 0 left bottom front
  {  1.0, -1.0,  1.0 }, // 1 right bottom front
  {  1.0,  1.0,  1.0 }, // 2 right top front
  { -1.0,  1.0,  1.0 }, // 3 left top front
  { -1.0, -1.0, -1.0 }, // 4 left bottom rear
  {  1.0, -1.0, -1.0 }, // 5 right bottom rear
  {  1.0,  1.0, -1.0 }, // 6 right top rear
  { -1.0,  1.0, -1.0 }  // 7 left top rear
};

static GLfloat Normals[6][3] = {
    { 0, 0, 1 },    // front
    { 1, 0, 0 },    // right
    { 0, 0, -1},    // rear
    { -1, 0, 0},    // left
    { 0, 1, 0 },    // top
    { 0, -1, 0}     // bottom
};

//cube face vertex
static GLuint Faces[] = {
    0, 1, 2, 3, // front
    1, 5, 6, 2, // right
    5, 4, 7, 6, // rear
    4, 0, 3, 7, // left
    3, 2, 6, 7, // top
    4, 5, 1, 0  // bottom
};
void JDuck::drawJDuck()
{
    //update(0.025);
    glPushMatrix();
        glTranslatef(position[0], position[1], position[2]);
        glRotatef(-orientation,0.0,1.0,0.0);
        // Draw cube in traditional OpenGL style
        glBegin(GL_QUADS);
        glColor3fv(jdUtility::COLOR_RED);
        for (int i = 0; i < 1 * 4; i++)
        {
            glVertex3fv(Vertices[Faces[i]]);
            glNormal3fv(Normals[i / 4]);
        }
        glColor3fv(jdUtility::COLOR_GREEN);
        for (int i = 4; i < 6 * 4; i++)
        {
            glVertex3fv(Vertices[Faces[i]]);
            glNormal3fv(Normals[i / 4]);
        }
        glEnd();
    glPopMatrix();
}

*/

static int leftLeg_NVerts = 42 ;
static GLfloat leftLeg_Verts [] = {
    -0.3000, 0.0000, 0.0000,
    -0.4000, 0.0000, -0.1000,
    -0.2000, 0.0000, -0.1000,
    -0.4500, -0.2000, -0.1500,
    -0.3000, -0.2000, -0.3000,
    -0.1500, -0.2000, -0.1500,
    -0.3500, -0.3500, -0.1000,
    -0.2500, -0.3500, -0.1000,
    -0.3200, -0.8000, 0.1400,
    -0.2800, -0.8000, 0.1400,
    -0.3500, 0.0000, 0.1000,
    -0.2500, 0.0000, 0.1000,
    -0.4000, -0.2000, 0.0500,
    -0.2000, -0.2000, 0.0500,
    -0.3500, -0.3500, 0.0000,
    -0.2500, -0.3500, 0.0000,
    -0.3200, -0.8000, 0.1600,
    -0.2800, -0.8000, 0.1600,
    -0.3000, -0.8000, 0.1000,
    -0.2000, -0.8000, 0.2800,
    -0.4000, -0.8000, 0.2800,
    -0.3250, -0.8000, 0.3000,
    -0.2750, -0.8000, 0.3000,
    -0.3000, -0.8000, 0.3500,
    -0.3000, -0.8000, 0.1000,
    -0.4000, -0.8000, 0.2800,
    -0.3000, -0.7500, 0.2800,
    -0.3000, -0.8000, 0.1000,
    -0.3000, -0.7500, 0.2800,
    -0.2000, -0.8000, 0.2800,
    -0.3000, -0.7500, 0.2800,
    -0.4000, -0.8000, 0.2800,
    -0.3250, -0.8000, 0.3000,
    -0.3000, -0.7500, 0.2800,
    -0.2750, -0.8000, 0.3000,
    -0.2000, -0.8000, 0.2800,
    -0.3000, -0.7500, 0.2800,
    -0.3250, -0.8000, 0.3000,
    -0.3000, -0.8000, 0.3500,
    -0.3000, -0.7500, 0.2800,
    -0.3000, -0.8000, 0.3500,
    -0.2750, -0.8000, 0.3000,
};
static GLfloat leftLeg_Norms [] = {
    0.0000, 0.0000, 0.0000,
    -0.6932, 0.4705, -0.5460,
    0.6932, 0.4705, -0.5460,
    -0.9471, -0.1637, -0.2760,
    0.0000, -0.1677, -0.9858,
    0.9471, -0.1637, -0.2760,
    -0.5144, -0.6062, -0.6066,
    0.5952, -0.6076, -0.5259,
    -0.8815, -0.2666, -0.3898,
    0.6948, -0.3740, -0.6144,
    -0.6192, -0.0412, 0.7842,
    0.7959, 0.0481, 0.6035,
    -0.4682, -0.2704, 0.8412,
    0.4683, -0.2519, 0.8469,
    -0.7649, -0.1454, 0.6276,
    0.7435, -0.2713, 0.6113,
    -0.7135, 0.1920, 0.6738,
    0.4503, 0.2723, 0.8504,
    -0.0000, -1.0000, 0.0000,
    -0.0000, -1.0000, 0.0000,
    -0.0000, -1.0000, 0.0000,
    0.0000, -1.0000, 0.0000,
    0.0000, -1.0000, 0.0000,
    0.0000, -1.0000, 0.0000,
    -0.4340, 0.8680, -0.2411,
    -0.4340, 0.8680, -0.2411,
    -0.4340, 0.8680, -0.2411,
    0.4340, 0.8680, -0.2411,
    0.4340, 0.8680, -0.2411,
    0.4340, 0.8680, -0.2411,
    -0.2290, 0.4581, 0.8589,
    -0.2290, 0.4581, 0.8589,
    -0.2290, 0.4581, 0.8589,
    0.2290, 0.4581, 0.8589,
    0.2290, 0.4581, 0.8589,
    0.2290, 0.4581, 0.8589,
    -0.7581, 0.5307, 0.3790,
    -0.7581, 0.5307, 0.3790,
    -0.7581, 0.5307, 0.3790,
    0.7581, 0.5307, 0.3790,
    0.7581, 0.5307, 0.3790,
    0.7581, 0.5307, 0.3790,
};
static GLuint leftLeg_Idx [] = {
    2, 4, 1,
    4, 3, 1,
    5, 4, 2,
    6, 3, 4,
    7, 6, 4,
    5, 7, 4,
    9, 8, 6,
    7, 9, 6,
    10, 12, 13,
    10, 13, 11,
    12, 14, 15,
    12, 15, 13,
    14, 16, 17,
    14, 17, 15,
    3, 12, 10,
    1, 3, 10,
    4, 3, 1,
    3, 14, 12,
    6, 14, 3,
    4, 6, 3,
    8, 16, 14,
    6, 8, 14,
    11, 13, 5,
    11, 5, 2,
    2, 5, 4,
    13, 15, 5,
    5, 15, 7,
    5, 7, 4,
    15, 17, 9,
    15, 9, 7,
    18, 19, 20,
    21, 22, 23,
    24, 25, 26,
    27, 28, 29,
    30, 31, 32,
    33, 34, 35,
    36, 37, 38,
    39, 40, 41,
};

static int rightLeg_NVerts = 42 ;
static GLfloat rightLeg_Verts [] = {
    0.3000, 0.0000, 0.0000,
    0.2000, 0.0000, -0.1000,
    0.4000, 0.0000, -0.1000,
    0.1500, -0.2000, -0.1500,
    0.3000, -0.2000, -0.3000,
    0.4500, -0.2000, -0.1500,
    0.2500, -0.3500, -0.1000,
    0.3500, -0.3500, -0.1000,
    0.2800, -0.8000, 0.1400,
    0.3200, -0.8000, 0.1400,
    0.2500, 0.0000, 0.1000,
    0.3500, 0.0000, 0.1000,
    0.2000, -0.2000, 0.0500,
    0.4000, -0.2000, 0.0500,
    0.2500, -0.3500, 0.0000,
    0.3500, -0.3500, 0.0000,
    0.2800, -0.8000, 0.1600,
    0.3200, -0.8000, 0.1600,
    0.3000, -0.8000, 0.1000,
    0.4000, -0.8000, 0.2800,
    0.2000, -0.8000, 0.2800,
    0.2750, -0.8000, 0.3000,
    0.3250, -0.8000, 0.3000,
    0.3000, -0.8000, 0.3500,
    0.3000, -0.8000, 0.1000,
    0.2000, -0.8000, 0.2800,
    0.3000, -0.7500, 0.2800,
    0.3000, -0.8000, 0.1000,
    0.3000, -0.7500, 0.2800,
    0.4000, -0.8000, 0.2800,
    0.3000, -0.7500, 0.2800,
    0.2000, -0.8000, 0.2800,
    0.2750, -0.8000, 0.3000,
    0.3000, -0.7500, 0.2800,
    0.3250, -0.8000, 0.3000,
    0.4000, -0.8000, 0.2800,
    0.3000, -0.7500, 0.2800,
    0.2750, -0.8000, 0.3000,
    0.3000, -0.8000, 0.3500,
    0.3000, -0.7500, 0.2800,
    0.3000, -0.8000, 0.3500,
    0.3250, -0.8000, 0.3000,
};
static GLfloat rightLeg_Norms [] = {
    0.0000, 0.0000, 0.0000,
    -0.6932, 0.4705, -0.5460,
    0.6932, 0.4705, -0.5460,
    -0.9471, -0.1637, -0.2760,
    0.0000, -0.1677, -0.9858,
    0.9471, -0.1637, -0.2760,
    -0.5144, -0.6062, -0.6066,
    0.5952, -0.6076, -0.5259,
    -0.8815, -0.2666, -0.3898,
    0.6948, -0.3740, -0.6144,
    -0.6192, -0.0412, 0.7842,
    0.7959, 0.0481, 0.6035,
    -0.4682, -0.2704, 0.8412,
    0.4683, -0.2519, 0.8469,
    -0.7649, -0.1454, 0.6276,
    0.7435, -0.2713, 0.6113,
    -0.7135, 0.1920, 0.6738,
    0.4503, 0.2723, 0.8504,
    -0.0000, -1.0000, 0.0000,
    -0.0000, -1.0000, 0.0000,
    -0.0000, -1.0000, 0.0000,
    0.0000, -1.0000, 0.0000,
    0.0000, -1.0000, 0.0000,
    0.0000, -1.0000, 0.0000,
    -0.4340, 0.8680, -0.2411,
    -0.4340, 0.8680, -0.2411,
    -0.4340, 0.8680, -0.2411,
    0.4340, 0.8680, -0.2411,
    0.4340, 0.8680, -0.2411,
    0.4340, 0.8680, -0.2411,
    -0.2290, 0.4581, 0.8589,
    -0.2290, 0.4581, 0.8589,
    -0.2290, 0.4581, 0.8589,
    0.2290, 0.4581, 0.8589,
    0.2290, 0.4581, 0.8589,
    0.2290, 0.4581, 0.8589,
    -0.7581, 0.5307, 0.3790,
    -0.7581, 0.5307, 0.3790,
    -0.7581, 0.5307, 0.3790,
    0.7581, 0.5307, 0.3790,
    0.7581, 0.5307, 0.3790,
    0.7581, 0.5307, 0.3790,
};
static GLuint rightLeg_Idx [] = {
    2, 4, 1,
    4, 3, 1,
    5, 4, 2,
    6, 3, 4,
    7, 6, 4,
    5, 7, 4,
    9, 8, 6,
    7, 9, 6,
    10, 12, 13,
    10, 13, 11,
    12, 14, 15,
    12, 15, 13,
    14, 16, 17,
    14, 17, 15,
    3, 12, 10,
    1, 3, 10,
    4, 3, 1,
    3, 14, 12,
    6, 14, 3,
    4, 6, 3,
    8, 16, 14,
    6, 8, 14,
    11, 13, 5,
    11, 5, 2,
    2, 5, 4,
    13, 15, 5,
    5, 15, 7,
    5, 7, 4,
    15, 17, 9,
    15, 9, 7,
    18, 19, 20,
    21, 22, 23,
    24, 25, 26,
    27, 28, 29,
    30, 31, 32,
    33, 34, 35,
    36, 37, 38,
    39, 40, 41,
};

static int body_NVerts = 57 ;
static GLfloat body_Verts [] = {
    0.0000, 0.4000, 0.9000,
    0.0000, 0.4500, 0.6500,
    -0.1000, 0.4000, 0.6500,
    0.1000, 0.4000, 0.6500,
    0.0000, 0.3500, 0.9000,
    0.0000, 0.3000, 0.6500,
    -0.1000, 0.3500, 0.6500,
    0.1000, 0.3500, 0.6500,
    -0.1000, 0.3500, 0.5500,
    0.1000, 0.3500, 0.5500,
    -0.1000, 0.3500, 0.4500,
    0.1000, 0.3500, 0.4500,
    -0.2000, 0.1000, 0.4500,
    0.2000, 0.1000, 0.4500,
    -0.2000, 0.2000, 0.3500,
    0.2000, 0.2000, 0.3500,
    -0.3000, -0.0500, 0.3500,
    0.3000, -0.0500, 0.3500,
    -0.4000, 0.2500, 0.0000,
    0.4000, 0.2500, 0.0000,
    -0.5000, 0.0000, 0.0000,
    0.5000, 0.0000, 0.0000,
    -0.4000, -0.1000, 0.0000,
    0.4000, -0.1000, 0.0000,
    -0.4000, -0.0500, -0.3000,
    0.4000, -0.0500, -0.3000,
    -0.3000, 0.0500, -0.4500,
    0.3000, 0.0500, -0.4500,
    -0.2000, -0.0500, -0.6000,
    0.2000, -0.0500, -0.6000,
    0.0000, 0.1000, -0.9000,
    0.0000, 0.2500, 0.3500,
    0.0000, 0.3000, 0.0000,
    0.0000, 0.1500, -0.4000,
    -0.2000, 0.6000, 0.5000,
    0.2000, 0.6000, 0.5000,
    0.0000, 0.6500, 0.5500,
    0.0000, 0.6500, 0.3500,
    0.0000, 0.4500, 0.3500,
    0.0000, 0.4000, 0.9000,
    0.1000, 0.4000, 0.6500,
    0.0000, 0.4500, 0.6500,
    0.0000, 0.4500, 0.6500,
    -0.1000, 0.4000, 0.6500,
    0.0000, 0.4000, 0.9000,
    0.0000, 0.4000, 0.9000,
    -0.1000, 0.4000, 0.6500,
    0.1000, 0.4000, 0.6500,
    0.1000, 0.3500, 0.6500,
    -0.1000, 0.3500, 0.6500,
    0.0000, 0.3500, 0.9000,
    0.1000, 0.3500, 0.6500,
    0.0000, 0.3500, 0.9000,
    0.0000, 0.3000, 0.6500,
    0.0000, 0.3500, 0.9000,
    -0.1000, 0.3500, 0.6500,
    0.0000, 0.3000, 0.6500,
};
static GLfloat body_Norms [] = {
    0.0000, 0.0000, 0.0000,
    0.0000, 0.4816, 0.8764,
    -0.7353, 0.0546, 0.6756,
    0.5866, 0.0435, 0.8087,
    0.0000, 0.0000, 0.0000,
    0.0000, -0.9864, -0.1644,
    -0.5512, -0.3406, 0.7617,
    0.7333, -0.4532, 0.5067,
    -0.8537, -0.5039, 0.1311,
    0.7908, -0.5362, 0.2950,
    -0.7909, 0.1922, -0.5810,
    0.7909, 0.1922, -0.5810,
    -0.6183, -0.0532, 0.7841,
    0.6272, -0.0971, 0.7728,
    -0.7403, 0.6489, 0.1758,
    0.6424, 0.7489, 0.1626,
    -0.6297, -0.3570, 0.6899,
    0.6644, -0.4685, 0.5823,
    -0.6754, 0.7356, 0.0522,
    0.6780, 0.7335, -0.0474,
    -0.9687, -0.2254, 0.1044,
    0.9687, -0.2254, 0.1044,
    -0.3019, -0.9512, 0.0638,
    0.3027, -0.9531, -0.0032,
    -0.6908, -0.6283, -0.3579,
    0.6978, -0.6376, -0.3265,
    -0.6361, 0.6182, -0.4616,
    0.7199, 0.5117, -0.4690,
    -0.4517, -0.7857, -0.4226,
    0.5616, -0.6393, -0.5253,
    0.0000, 0.4983, -0.8670,
    -0.0227, 0.9425, -0.3335,
    -0.0005, 0.9939, -0.1104,
    0.0185, 0.9614, -0.2744,
    -0.9617, 0.2646, 0.0718,
    0.9617, 0.2646, 0.0718,
    0.0000, 0.8544, 0.5197,
    0.0000, 0.7715, -0.6362,
    0.0000, -0.2350, -0.9720,
    0.4402, 0.8805, 0.1761,
    0.4402, 0.8805, 0.1761,
    0.4402, 0.8805, 0.1761,
    -0.4402, 0.8805, 0.1761,
    -0.4402, 0.8805, 0.1761,
    -0.4402, 0.8805, 0.1761,
    0.0000, -1.0000, 0.0000,
    0.0000, -1.0000, 0.0000,
    0.0000, -1.0000, 0.0000,
    0.0000, 1.0000, 0.0000,
    0.0000, 1.0000, 0.0000,
    0.0000, 1.0000, 0.0000,
    0.4402, -0.8805, 0.1761,
    0.4402, -0.8805, 0.1761,
    0.4402, -0.8805, 0.1761,
    -0.4402, -0.8805, 0.1761,
    -0.4402, -0.8805, 0.1761,
    -0.4402, -0.8805, 0.1761,
};
static GLuint body_Idx [] = {
    8, 10, 12,
    10, 14, 12,
    14, 16, 12,
    14, 18, 16,
    18, 20, 16,
    20, 22, 16,
    18, 24, 20,
    20, 24, 22,
    18, 26, 24,
    26, 28, 24,
    26, 30, 28,
    9, 13, 11,
    11, 13, 15,
    15, 13, 17,
    15, 17, 19,
    19, 17, 21,
    21, 17, 23,
    19, 21, 25,
    21, 23, 25,
    19, 25, 27,
    27, 25, 29,
    27, 29, 30,
    10, 11, 31,
    14, 10, 31,
    31, 11, 15,
    14, 31, 18,
    18, 31, 32,
    31, 15, 32,
    32, 15, 19,
    18, 32, 26,
    26, 32, 33,
    32, 19, 33,
    33, 19, 27,
    26, 33, 30,
    27, 30, 33,
    8, 12, 9,
    9, 12, 13,
    12, 16, 13,
    13, 16, 17,
    16, 22, 17,
    17, 22, 23,
    22, 24, 23,
    23, 24, 25,
    24, 28, 25,
    25, 28, 29,
    28, 30, 29,
    10, 38, 11,
    8, 34, 10,
    11, 35, 9,
    10, 34, 38,
    11, 38, 35,
    38, 34, 37,
    37, 35, 38,
    37, 34, 36,
    36, 35, 37,
    9, 5, 8,
    5, 6, 8,
    9, 7, 5,
    6, 2, 8,
    3, 7, 9,
    3, 2, 6,
    3, 6, 7,
    8, 2, 34,
    3, 9, 35,
    34, 2, 1,
    35, 1, 3,
    36, 34, 1,
    35, 36, 1,
    39, 40, 41,
    42, 43, 44,
    45, 46, 47,
    48, 49, 50,
    51, 52, 53,
    54, 55, 56,
};

JDuck::JDuck(float x, float y, float z)
{
    this->position[0] = x;
    this->position[1] = y;
    this->position[2] = z;

    //set color
    this->color[0] = 0.0;
    this->color[1] = 1.0;
    this->color[2] = 0.0;
    this->color[3] = 1.0;

    //the duck is patrolling
    this->actionState = PATROLLING;

    this->maxPathStep = 200;

    //(-1,-1) indicates which element in the path array are not used
    for(int i = 0; i < maxPathStep;i++)
    {
        this->pathRow[i] = -1;
        this->pathCol[i] = -1;
    }

    this->currentPathStep = 0;
    this->firstTimeChasing = true;
    this->hasPatrolArray = false;

    // velocity vector in world coordinate
    this->orientation = JDAlgorithm::getRandomNumber(0,360,false);
    //orientation = 180;
    this->fSpeed = 3.0;

    this->velocity[0] = this->fSpeed * sin(JDAlgorithm::DegreesToRadians(360-orientation));
    this->velocity[1] = 0;
    this->velocity[2] = this->fSpeed * cos(JDAlgorithm::DegreesToRadians(360-orientation));

    this->velocityAngular[0] = 0.0;
    this->velocityAngular[1] = 0.0;
    this->velocityAngular[2] = 0.0;

    // initialize forces
    this->force[0] = 0.0;
    this->force[1] = 0.0;
    this->force[2] = 0.0;

    this->moment[0] = 0.0;
    this->moment[1] = 0.0;
    this->moment[2] = 0.0;

    this->otherForce[0] = 0.0;
    this->otherForce[1] = 0.0;
    this->otherForce[2] = 0.0;

    setThrusters(false,false,0.0);

    //acceleration factor
    this->fMass = 10.0;
    this->fInertia = 10.0;

    //legSwing
    this->legSwing = 0;
    this->step = 1;
}

JDuck::~JDuck()
{
    /*
    QMessageBox::information(NULL,"Testing",
                             "orientation: "+QString::number(orientation) + "\n" +
                             "force: " + QString::number(force[0]) + ","
                                       + QString::number(force[1]) + ","
                                       + QString::number(force[2]) + "\n" +
                             "velocity: " + QString::number(velocity[0]) + ","
                                          + QString::number(velocity[1]) + ","
                                          + QString::number(velocity[2]) + "\n");
    */
}

//
//  set/get position
//
void JDuck::setPos(float x, float y,float z)
{
    this->position[0] = x;
    this->position[1] = y;
    this->position[2] = z;
}

float JDuck::getPosX() const
{
    return this->position[0];
}

float JDuck::getPosY() const
{
    return this->position[1];
}

float JDuck::getPosZ() const
{
    return this->position[2];
}

Vec3 JDuck::getPos() const
{
    return this->position;
}

//set/get velocity

void JDuck::setVelocity(float x, float y,float z)
{
    this->velocity[0] = x;
    this->velocity[1] = y;
    this->velocity[2] = z;
}

Vec3 JDuck::getVelocity() const
{
    return this->velocity;
}

//get speed
float JDuck::getFSpeed()
{
    return this->fSpeed;
}

//set /get orientation

void JDuck::setOrientation(float orien)
{
    this->orientation = orien;
}

float JDuck::getOrientation() const
{
    return this->orientation;
}

//set/get force
void JDuck::setForce(float x, float y,float z)
{
    this->force[0] = x;
    this->force[1] = y;
    this->force[2] = z;
}

Vec3 JDuck::getForce() const
{
    return this->force;
}


//set/get otherforce
void JDuck::setOtherForce(float x, float y,float z)
{
    this->otherForce[0] = x;
    this->otherForce[1] = y;
    this->otherForce[2] = z;
}


void JDuck::setOtherForce(Vec3 oForce)
{
    this->otherForce[0] = oForce[0];
    this->otherForce[1] = oForce[1];
    this->otherForce[2] = oForce[2];
}


Vec3 JDuck::getOtherForce() const
{
    return this->otherForce;
}

//
//  change ducks action
//
void JDuck::patrol()
{
    this->actionState = PATROLLING;
}

void JDuck::chase()
{
    this->actionState = CHASING;
    //clear the patrolling array
    this->hasPatrolArray = false;
}

//get action state
int JDuck::getAction() const
{
    return this->actionState;
}

//get path array
int* JDuck::getPathRow()
{
    return this->pathRow;
}

int* JDuck::getPathCol()
{
    return this->pathCol;
}

//get maxPath Step
int JDuck::getMaxPathStep() const
{
    return this->maxPathStep;
}

//get/set current step
int JDuck::getCurrentPathStep()const
{
    return this->currentPathStep;
}

void JDuck::setCurrentPathStep(int curStep)
{
    this->currentPathStep = curStep;
}

void JDuck::increaseCurrentPathStep()
{
    if(this->currentPathStep == this->maxPathStep-1)
        return;
    this->currentPathStep++;
}

void JDuck::decreaseCurrentPathStep()
{
    if(this->currentPathStep == 0)
        return;
    this->currentPathStep--;
}

//set/get first time chasing
bool JDuck::getFirstTimeChasing()const
{
    return this->firstTimeChasing;
}

void JDuck::setFirstTimeChasing(bool isFirstTimeChasing)
{
    this->firstTimeChasing = isFirstTimeChasing;
}


//set/get hasPatrolArray
bool JDuck::getHasPatrolArray() const
{
    return this->hasPatrolArray;
}


void JDuck::setHasPatrolArray(bool hasbuiltPatrolArray)
{
    this->hasPatrolArray = hasbuiltPatrolArray;
}

//
//calculate the pattern movement pathArray
//
void JDuck::calculatePatternMovement()
{
    //if(!this->hasPatrolArray)
    JDAlgorithm::initializePath(this->pathRow, this->pathCol,this->maxPathStep);

    //pattern movement
    JDAlgorithm::buildPath(this->position[0], this->position[2], this->position[0]+10, this->position[2],
                           this->pathRow, this->pathCol,this->maxPathStep);

    JDAlgorithm::buildPath(this->position[0]+10, this->position[2], this->position[0]+10, this->position[2]-10,
                           this->pathRow, this->pathCol,this->maxPathStep);
    JDAlgorithm::buildPath(this->position[0]+10, this->position[2]-10, this->position[0], this->position[2]-10,
                           this->pathRow, this->pathCol,this->maxPathStep);
    JDAlgorithm::buildPath(this->position[0], this->position[2]-10, this->position[0], this->position[2],
                           this->pathRow, this->pathCol,this->maxPathStep);

    hasPatrolArray = true;
}

//
//calculate the ducks chasing path array
//
bool JDuck::calculateChasingPathArray(int playerRow, int playerPosCol)
{
    //calculate the ducks chasing path array
    return JDAlgorithm::lineOfSightTile(this->position[0], this->position[2],
                                        playerRow, playerPosCol,
                                        this->pathRow, this->pathCol,
                                        this->maxPathStep);
}

//update duck's position to the next position in path array
void JDuck::updateToNextPosition()
{

    int nextRow = this->pathRow[this->currentPathStep+1];
    int nextCol = this->pathCol[this->currentPathStep+1];
    if(nextRow == -1 && nextCol == -1)
    {//have finished iterating path array once, go back to the original position
        this->currentPathStep = 0;
    }
    else
    {
        this->setPos(nextRow,this->position[1],nextCol);
        this->increaseCurrentPathStep();
    }
}

//
//set thrust force
//
void JDuck::setThrusters(bool p, bool s, double f)
{
    this->pThrust[0] = 0;
    this->pThrust[1] = 0;
    this->pThrust[2] = 0;

    this->sThrust[0] = 0;
    this->sThrust[1] = 0;
    this->sThrust[2] = 0;

    if(p)//port side
        this->pThrust[0] = +DUCK_STEERINGFORCE * f;
    if(s)//starboard side
        this->sThrust[0] = -DUCK_STEERINGFORCE * f;

}


// Calculate forces and moments
void JDuck::calculateForcesMoments()
{
    Vec3 sumThrust; //stores the sum of forces
    Vec3 sumMoment; //stores the sum of moments
    Vec3 thrust;    //thrust force

    //reset forces and moments
    this->force[0] = 0.0;
    this->force[1] = 0.0;
    this->force[2] = 0.0;

    this->moment[0] = 0.0;
    this->moment[1] = 0.0;
    this->moment[2] = 0.0;

    sumThrust[0] = 0.0;
    sumThrust[1] = 0.0;
    sumThrust[2] = 0.0;

    sumMoment[0] = 0.0;
    sumMoment[1] = 0.0;
    sumMoment[2] = 0.0;

    //define the thrust force vector and its magnitude
    thrust[0] = 0.0;
    thrust[1] = 0.0;
    thrust[2] = 0.0;
    this->thrustForce = 10.0;
    thrust *= this->thrustForce; //combine the magnitude to the thrust force

    //calculate the Port and Starboard bow thruster forces:
    sumThrust += 3*this->pThrust;
    sumThrust += 3*this->sThrust;

    sumMoment += 0.5*this->pThrust;
    sumThrust += 0.5*this->sThrust;

    //add thrust forces to sum of thrust forces
    sumThrust += thrust;

    //add other forces to sum of thrust forces
    sumThrust += this->otherForce;

    //tanslate vector from local coordinate to global coordinate
    this->force = JDAlgorithm::vRotateCoord(this->orientation,sumThrust);

    this->moment += sumMoment;
}

//
//update position, velocity, orientation, force
//
void JDuck::update(double deltaTime)
{
    Vec3 acceleration;          //force(acceleration of velocity)
    Vec3 deltaVel;              //delta velocity
    Vec3 deltaDis;              //delta distance

    // Calculate forces and moments
    calculateForcesMoments();

    //Integrate linear equation of motion,
    acceleration = this->force / this->fMass;
    deltaVel = acceleration * deltaTime;
    this->velocity += deltaVel;
    deltaDis = this->velocity * deltaTime;
    this->position += deltaDis;

    this->fSpeed = this->velocity.magnitude();

    //calculate the orientation
    if(this->velocity[2] == 0)
    {
        if(this->velocity[0] > 0) this->orientation = 270;
        if(this->velocity[0] < 0) this->orientation = 90;
    }

    if(this->velocity[0] == 0)
    {
        if(this->velocity[2] > 0) this->orientation = 0;
        if(this->velocity[2] < 0) this->orientation = 180;
    }

    if(this->velocity[0] > 0 && this->velocity[2] > 0)
        this->orientation = 360 - JDAlgorithm::RadiansToDegrees(atan(this->velocity[0]/this->velocity[2]));
    if(this->velocity[0] > 0 && this->velocity[2] < 0)
            this->orientation = 180 - JDAlgorithm::RadiansToDegrees(atan(this->velocity[0]/this->velocity[2]));
    if(this->velocity[0] < 0 && this->velocity[2] > 0)
            this->orientation = - JDAlgorithm::RadiansToDegrees(atan(this->velocity[0]/this->velocity[2]));
    if(this->velocity[0] < 0 && this->velocity[2] < 0)
            this->orientation = 180 - JDAlgorithm::RadiansToDegrees(atan(this->velocity[0]/this->velocity[2]));

    if(this->orientation < 0) {
        this->orientation += 360;
    }

    legsUpdate(deltaTime);
}

//update legs based on deltaTime
void JDuck::legsUpdate(double deltaTime)
{
    if(this->legSwing > 30)
        this->step = -200*deltaTime;
    else if(this->legSwing < -30)
        this->step = 200*deltaTime;

    this->legSwing += this->step;
}

//
//detect if the duck run out of the map
//
bool JDuck::outOfMap()
{
    if( !(this->position[0] < 102 && this->position[0] > -102 &&
        this->position[2] < 102 && this->position[2] > -102)   )
    {
        this->orientation += 180;
        this->velocity[0] = -this->velocity[0];
        this->velocity[1] = -this->velocity[1];
        this->velocity[2] = -this->velocity[2];
        return true;
    }
    return false;
}

//
// draw duck
//
void JDuck::leftLeg_draw()
{
     glPushClientAttrib(GL_CLIENT_VERTEX_ARRAY_BIT);
     glEnableClientState(GL_VERTEX_ARRAY);
         glVertexPointer(3, GL_FLOAT, 0, leftLeg_Verts);
         glEnableClientState(GL_NORMAL_ARRAY);
         glNormalPointer(GL_FLOAT, 0, leftLeg_Norms);
         glDrawElements(GL_TRIANGLES, 114 , GL_UNSIGNED_INT, leftLeg_Idx);
     glPopClientAttrib();
}
void JDuck::rightLeg_draw()
{
     glPushClientAttrib(GL_CLIENT_VERTEX_ARRAY_BIT);
     glEnableClientState(GL_VERTEX_ARRAY);
         glVertexPointer(3, GL_FLOAT, 0, rightLeg_Verts);
         glEnableClientState(GL_NORMAL_ARRAY);
         glNormalPointer(GL_FLOAT, 0, rightLeg_Norms);
         glDrawElements(GL_TRIANGLES, 114 , GL_UNSIGNED_INT, rightLeg_Idx);
     glPopClientAttrib();
}
void JDuck::body_draw()
{
     glPushClientAttrib(GL_CLIENT_VERTEX_ARRAY_BIT);
     glEnableClientState(GL_VERTEX_ARRAY);
         glVertexPointer(3, GL_FLOAT, 0, body_Verts);
         glEnableClientState(GL_NORMAL_ARRAY);
         glNormalPointer(GL_FLOAT, 0, body_Norms);
         glDrawElements(GL_TRIANGLES, 222 , GL_UNSIGNED_INT, body_Idx);
     glPopClientAttrib();
}

void JDuck::drawJDuck()
{
    glPushMatrix();
        glTranslatef(this->position[0], this->position[1], this->position[2]);
        glRotatef(-this->orientation,0.0,1.0,0.0);
        glColor3fv(jdUtility::COLOR_GREEN);
        glPushMatrix();
            glRotatef(this->legSwing, 1, 0, 0);
            leftLeg_draw();
        glPopMatrix();

        glPushMatrix();
            glRotatef(- this->legSwing, 1, 0, 0);
            rightLeg_draw();
        glPopMatrix();
        body_draw();
    glPopMatrix();
}
