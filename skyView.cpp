#include <windows.h> // for MS Windows
#include <GL/glut.h>
#include <iostream>
#include<math.h>>
# define PI           3.14159265358979323846
using namespace std;

void renderBitmapString(float x, float y, float z, void *font, char *string)
{
    char *c;
    glRasterPos3f(x, y,z);
    for (c=string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}

void drawLine (float x, float y, float a, float b)
{
    //glLineWidth(2);
    glBegin (GL_LINES);
    glVertex2f (x, y);
    glVertex2f (a, b);
    glEnd();
}


void drawFiledEllipse(float cx, float cy, float rx, float ry, int num_segments)
{
    float theta = 2 * PI / float(num_segments);
    float c = cosf(theta);//precalculate the sine and cosine
    float s = sinf(theta);
    float t;

    float x = 1;//we start at angle = 0
    float y = 0;

    glBegin(GL_POLYGON);
    for(int ii = 0; ii < num_segments; ii++)
    {
        //apply radius and offset
        glVertex2f(x * rx + cx, y * ry + cy);//output vertex

        //apply the rotation matrix
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    glEnd();
}

void drawEmptyEllipse(float cx, float cy, float rx, float ry, int num_segments)
{
    float theta = 2 * PI / float(num_segments);
    float c = cosf(theta);//precalculate the sine and cosine
    float s = sinf(theta);
    float t;

    float x = 1;//we start at angle = 0
    float y = 0;

    glBegin(GL_LINE_LOOP);
    for(int ii = 0; ii < num_segments; ii++)
    {
        //apply radius and offset
        glVertex2f(x * rx + cx, y * ry + cy);//output vertex

        //apply the rotation matrix
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    glEnd();
}

void OmniRoute (float x, float y)
{
    glColor3ub(9, 18, 84);
    drawFiledEllipse(x, y, 0.2f, 0.18f, 1000);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawEmptyEllipse(x, y, 0.2f, 0.18f, 1000);
    glColor3ub(47, 58, 137);
    drawFiledEllipse(x, y, 0.18f, 0.17f, 1000);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawEmptyEllipse(x, y, 0.18f, 0.17f, 1000);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawLine (x, y+0.18f, x, y-0.18f);
    glColor3f(0.0f, 0.0f, 0.0f);
    drawLine (x+0.18f, y, x-0.18f, y);

    //BACK WINDOW:
    glColor3f(0.25f, 0.25f, 0.25f);
    glBegin (GL_POLYGON);
    glVertex2f (x-0.01f, y+0.01f);
    glVertex2f (x-0.01f, y+0.17f);
    glVertex2f (x-0.18f, y+0.01f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin (GL_LINES);
    glVertex2f (x-0.01f, y+0.01f);
    glVertex2f (x-0.01f, y+0.17f);
    glVertex2f (x-0.18f, y+0.01f);
    glEnd();

    //FRONT WINDOW:
    glColor3f(0.25f, 0.25f, 0.25f);
    glBegin (GL_POLYGON);
    glVertex2f (x+0.01f, y+0.01f);
    glVertex2f (x+0.01f, y+0.17f);
    glVertex2f (x+0.18f, y+0.01f);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin (GL_LINES);
    glVertex2f (x+0.01f, y+0.01f);
    glVertex2f (x+0.01f, y+0.17f);
    glVertex2f (x+0.18f, y+0.01f);
    glEnd();

    //pankha center
    glLineWidth (3);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin (GL_LINES);
    glVertex2f (x, y+0.18f);
    glVertex2f (x, y+0.21f);
    glEnd();

    //pankha right
    glLineWidth (3);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin (GL_LINES);
    //down
    glVertex2f (x, y+0.21f);
    glVertex2f (x+0.18f, y+0.17f);
    //up
    glVertex2f (x, y+0.21f);
    glVertex2f (x+0.16f, y+0.22f);
    glEnd();

    //pankha left
    glLineWidth (3);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin (GL_LINES);
    //down
    glVertex2f (x, y+0.21f);
    glVertex2f (x-0.18f, y+0.17f);
    //up
    glVertex2f (x, y+0.21f);
    glVertex2f (x-0.16f, y+0.22f);
    glEnd();
}

void gridLine (float x, float xL, float y, float yL, float is, float ie)
{
    //vertical
    drawLine (x, y, x, y+yL);
    //horizontal
    for (float i=is; i<=ie; i=i+0.05f)
    {
        drawLine (x-xL, y+i, x+xL, y+i);
    }
}

void windowBig ( float x, float y, float is, float ie)
{
    for (float i=is; i<ie; i=i+0.05f)
    {
        //Filled:
        glColor3f(0.9f, 0.9f, 0.9f);
        glBegin (GL_POLYGON);
        glVertex2f (x+0.01f, y+0.015f+i);
        glVertex2f (x+0.01f, y+0.035f+i);
        glVertex2f (x+0.04f, y+0.035f+i);
        glVertex2f (x+0.04f, y+0.015f+i);
        glEnd();

        glBegin (GL_POLYGON);
        glVertex2f (x-0.01f, y+0.015f+i);
        glVertex2f (x-0.01f, y+0.035f+i);
        glVertex2f (x-0.04f, y+0.035f+i);
        glVertex2f (x-0.04f, y+0.015f+i);
        glEnd();

        //Empty
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin (GL_LINE_LOOP);
        glVertex2f (x+0.01f, y+0.015f+i);
        glVertex2f (x+0.01f, y+0.035f+i);
        glVertex2f (x+0.04f, y+0.035f+i);
        glVertex2f (x+0.04f, y+0.015f+i);
        glEnd();

        glBegin (GL_LINE_LOOP);
        glVertex2f (x-0.01f, y+0.015f+i);
        glVertex2f (x-0.01f, y+0.035f+i);
        glVertex2f (x-0.04f, y+0.035f+i);
        glVertex2f (x-0.04f, y+0.015f+i);
        glEnd();
    }
}

void windowSmall ( float x, float y, float is, float ie)
{
    for (float i=is; i<ie; i=i+0.05f)
    {
        //Filled:
        glColor3f(0.9f, 0.9f, 0.9f);
        glBegin (GL_POLYGON);
        glVertex2f (x+0.005f, y+0.015f+i);
        glVertex2f (x+0.005f, y+0.035f+i);
        glVertex2f (x+0.02f, y+0.035f+i);
        glVertex2f (x+0.02f, y+0.015f+i);
        glEnd();

        glBegin (GL_POLYGON);
        glVertex2f (x-0.005f, y+0.015f+i);
        glVertex2f (x-0.005f, y+0.035f+i);
        glVertex2f (x-0.02f, y+0.035f+i);
        glVertex2f (x-0.02f, y+0.015f+i);
        glEnd();

        //Empty
        glColor3f(0.0f, 0.0f, 0.0f);
        glBegin (GL_LINE_LOOP);
        glVertex2f (x+0.005f, y+0.015f+i);
        glVertex2f (x+0.005f, y+0.035f+i);
        glVertex2f (x+0.02f, y+0.035f+i);
        glVertex2f (x+0.02f, y+0.015f+i);
        glEnd();

        glBegin (GL_LINE_LOOP);
        glVertex2f (x-0.005f, y+0.015f+i);
        glVertex2f (x-0.005f, y+0.035f+i);
        glVertex2f (x-0.02f, y+0.035f+i);
        glVertex2f (x-0.02f, y+0.015f+i);
        glEnd();
    }
}

void building1Block (float x, float y)
{
    //building block
    //glColor3ub(75, 40, 16);
    glBegin (GL_POLYGON);
    glVertex2f (x-0.05f, y);
    glVertex2f (x-0.05f, y+0.25f);
    glVertex2f (x+0.05f, y+0.25f);
    glVertex2f (x+0.05f, y);
    glEnd();

    glColor3ub(91, 88, 86);
    gridLine (x, 0.05f, y, 0.25f, 0.0f, 0.25f);
    windowBig (x, y, 0.0f, 0.25f);
}

void building2Block (float x, float y)
{
    //building block lower portion
    glBegin (GL_POLYGON);
    glVertex2f (x-0.05f, y);
    glVertex2f (x-0.05f, y+0.20f);
    glVertex2f (x+0.05f, y+0.20f);
    glVertex2f (x+0.05f, y);
    glEnd();

    glColor3ub(91, 88, 86);
    gridLine (x, 0.05f, y, 0.20f, 0.0f, 0.20f);
    windowBig (x, y, 0.0f, 0.20f);

    //building block upper portion
    //glColor3ub(91, 88, 86);
    glBegin (GL_POLYGON);
    glVertex2f (x-0.025f, y+0.20f);
    glVertex2f (x-0.025f, y+0.30f);
    glVertex2f (x+0.025f, y+0.30f);
    glVertex2f (x+0.025f, y+0.20f);
    glEnd();

    gridLine (x, 0.025f, y, 0.30f, 0.40f, 0.30f);
    windowSmall (x, y, 0.20f, 0.30f);
}

void buildingTall (float x, float y)
{
    //building block
    glBegin (GL_POLYGON);
    glVertex2f (x-0.05f, y);
    glVertex2f (x-0.05f, y+0.35f);
    glVertex2f (x+0.05f, y+0.35f);
    glVertex2f (x+0.05f, y);
    glEnd();

    glColor3ub(91, 88, 86);
    gridLine (x, 0.05f, y, 0.35f, 0.0f, 0.35f);
    windowBig (x, y, 0.0f, 0.35f);
}

void cloud (float x, float y)
{
    glColor3f(1.0f, 1.0f, 1.0f);
    drawFiledEllipse (x, y, 0.06f, 0.06f, 100);
    drawFiledEllipse (x+0.05f, y+0.05f, 0.05f, 0.06f, 100);
    drawFiledEllipse (x+0.05f, y-0.05f, 0.05f, 0.06f, 100);
    drawFiledEllipse (x+0.10f, y+0.04f, 0.05f, 0.08f, 100);
    drawFiledEllipse (x+0.10f, y-0.04f, 0.05f, 0.08f, 100);
    drawFiledEllipse (x+0.15f, y, 0.06f, 0.06f, 100);
}

void bird (float x, float y)
{
    //left wing
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin (GL_POLYGON);
    glVertex2f (x-0.03f, y+0.03f);
    glVertex2f (x-0.07f, y);
    glVertex2f (x-0.03f, y+0.02f);
    glEnd();
    glBegin (GL_POLYGON);
    glVertex2f (x, y);
    glVertex2f (x-0.03f, y+0.03f);
    glVertex2f (x-0.03f, y+0.02f);
    glEnd();

    //right wing
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin (GL_POLYGON);
    glVertex2f (x+0.03f, y+0.03f);
    glVertex2f (x+0.07f, y);
    glVertex2f (x+0.03f, y+0.02f);
    glEnd();
    glBegin (GL_POLYGON);
    glVertex2f (x, y);
    glVertex2f (x+0.03f, y+0.03f);
    glVertex2f (x+0.03f, y+0.02f);
    glEnd();

    //center
    drawFiledEllipse (x, y, 0.006f, 0.006f, 10);
}

void road ()
{
    glColor3f(0.25f, 0.25f, 0.25f);
    glBegin (GL_POLYGON);
    glVertex2f (-1.0f, -0.1f);
    glVertex2f (-1.0f, -0.25f);
    glVertex2f (1.0f, -0.75f);
    glVertex2f (1.0f, -0.55f);
    glEnd();

    glLineWidth (2);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin (GL_LINES);
    glVertex2f (1.0f, -0.55f);
    glVertex2f (-1.0f, -0.1f);
    glVertex2f (-1.0f, -0.25f);
    glVertex2f (1.0f, -0.75f);
    glVertex2f (-1.0f, -0.17f);
    glVertex2f (1.0f, -0.65f);
    glEnd();
}


/*
//sunny day
void sky ()
{
    glColor3ub(196, 231, 255);
    glBegin (GL_POLYGON);
    glVertex2f (-1.0f, 1.0f);
    glVertex2f (1.0f, 1.0f);
    glVertex2f (1.0f, -0.7f);
    glVertex2f (-1.0f, -0.70f);
    glEnd();

    glColor3ub(198, 235, 255);
    glBegin (GL_POLYGON);
    glVertex2f (-1.0f, -0.7f);
    glVertex2f (1.0f, -0.7f);
    glVertex2f (1.0f, -1.0f);
    glVertex2f (-1.0f, -1.0f);
    glEnd();
}
*/

//rainy day
void sky ()
{
    glBegin(GL_POLYGON);
    glColor3ub(198, 235, 255); // sky blue
    glVertex2f(0.0f, 1.0f);
    glColor3ub(5, 167, 247);
    glVertex2f(1.0f, 1.0f);
    glColor3ub(0, 0, 0); // black
    glVertex2f(1.0f, -1.0f);
    glColor3ub(20, 22, 61); // navy blue
    glVertex2f(-1.0f, -1.0f);
    glColor3ub(5, 167, 247);
    glVertex2f(-1.0f, 1.0f);
    glColor3ub(5, 167, 247); // sky blue
    glVertex2f(0.0f, 1.0f);
    glEnd();
}

void display()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer (background)

    sky ();

    //clouds
    cloud (0.5f, 0.5f);
    cloud (-0.5f, 0.5f);
    cloud (0.0f,0.2f);
    cloud (0.8f,0.2f);
    cloud (-0.8f,0.2f);
    cloud (-0.9f,0.8f);
    cloud (0.1f,0.7f);

    //birds
    bird(0.5f, 0.5f);
    bird(0.4f, 0.4f);
    bird(0.3f, 0.3f);
    bird(0.2f, 0.3f);
    bird(0.3f, 0.4f);
    bird(0.4f, 0.5f);
    bird(0.2f, 0.4f);
    bird(0.1f, 0.4f);
    bird(0.1f, 0.5f);
    bird(0.0f, 0.5f);


    bird(-0.5f, 0.5f);
    bird(-0.4f, 0.4f);
    bird(-0.3f, 0.3f);
    bird(-0.6f, 0.5f);
    bird(-0.7f, 0.4f);
    bird(-0.8f, 0.3f);


    // upper building layer
    glColor3ub(101, 165, 36); // grass green
    buildingTall (-1.0f, -0.2f);
    glColor3ub(172, 183, 33); // burnt yellow
    building2Block (-0.9f, -0.2f);
    glColor3ub(235,247,108); // light yellow
    buildingTall (-0.8f, -0.2f);
    glColor3ub(251,170,90); // orange
    buildingTall (-0.7f, -0.3f);
    glColor3ub(82, 85, 7); // ripe olive green
    building2Block (-0.6f, -0.2f);
    glColor3ub(37, 90, 115);// peacock blue
    buildingTall (-0.5f, -0.25f);
    glColor3ub(95, 237, 252); // sky blue
    buildingTall (-0.4f, -0.3f);
    glColor3ub(101, 165, 36); // grass green
    building2Block (-0.3f, -0.3f);
    glColor3ub(235,247,108); // light yellow
    buildingTall (-0.2f, -0.3f);
    glColor3ub(82, 85, 7); // ripe olive green
    building2Block (-0.1f, -0.35f);
    glColor3ub(37, 90, 115);// peacock blue
    buildingTall (0.0f, -0.35f);
    glColor3ub(210, 153, 25); // burnt orange
    buildingTall (0.1f, -0.45f);
    glColor3ub(95, 237, 252); // sky blue
    building2Block (0.2f, -0.45f);
    glColor3ub(82, 85, 7); // ripe olive green
    buildingTall (0.3f, -0.45f);
    glColor3ub(235,247,108); // light yellow
    buildingTall (0.4f, -0.55f);
    glColor3ub(37, 90, 115);// peacock blue
    building2Block (0.5f, -0.45f);
    glColor3ub(101, 165, 36); // grass green
    buildingTall (0.6f, -0.54f);
    glColor3ub(210, 153, 25); // burnt orange
    building2Block (0.7f, -0.5f);
    glColor3ub(95, 237, 252); // sky blue
    buildingTall (0.8f, -0.56f);
    glColor3ub(235,247,108); // light yellow
    buildingTall (0.9f, -0.60f);
    glColor3ub(101, 165, 36); // grass green
    building2Block (1.0f, -0.60f);

    road();


    OmniRoute (-0.3f, 0.3f);

    // Lower Building 1st layer
    glColor3ub(37, 90, 115);// peacock blue
    building1Block (-1.0f, -0.5f);
    glColor3ub(251,170,90); // orange
    buildingTall (-0.9f, -0.55f);
    glColor3ub(101, 165, 36); // grass green
    building2Block (-0.8f, -0.45f);
    glColor3ub(172, 183, 33); // burnt yellow
    building1Block (-0.7f, -0.5f);

    // Lower Building 2nd layer
    glColor3ub(210, 153, 25); // burnt orange
    building2Block (-1.02f, -0.6f);
    glColor3ub(101, 165, 36); // grass green
    building1Block (-0.92f, -0.6f);
    glColor3ub(20, 68, 125); //deep blue
    buildingTall (-0.82f, -0.6f);
    glColor3ub(241, 180, 45); // orange
    building2Block (-0.72f, -0.6f);
    glColor3ub(95, 237, 252); // sky blue
    buildingTall (-0.62f, -0.6f);
    glColor3ub(101, 165, 36); // grass green
    building2Block (-0.52f, -0.5f);
    glColor3ub(235,247,108); // light yellow
    buildingTall (-0.42f, -0.6f);
    glColor3ub(241, 180, 45); // orange
    building1Block (-0.32f, -0.6f);
    glColor3ub(20, 68, 125); //deep blue
    building2Block (-0.22f, -0.55f);
    glColor3ub(210, 153, 25); // burnt orange
    buildingTall (-0.12f, -0.6f);
    glColor3ub(95, 237, 252); // sky blue
    buildingTall (-0.02f, -0.7f);
    glColor3ub(101, 165, 36); // grass green
    building2Block (0.08f, -0.6f);
    glColor3ub(241, 180, 45); // orange
    building1Block (0.18f, -0.7f);
    glColor3ub(235,247,108); // light yellow
    building2Block (0.28f, -0.7f);


    // Lower Building 3rd layer
    glColor3ub(95, 237, 252); // sky blue
    buildingTall (-1.0f, -0.8f);
    glColor3ub(235,247,108); // light yellow
    building1Block (-0.9f, -0.8f);
    glColor3ub(82, 85, 7); // ripe olive green
    building2Block (-0.8f, -0.8f);
    glColor3ub(101, 165, 36); // grass green
    buildingTall (-0.7f, -0.8f);
    glColor3ub(241, 180, 45); // orange
    building1Block (-0.525f, -0.7f);
    glColor3ub(37, 90, 115);// peacock blue
    building1Block(-0.6f, -0.8f);
    glColor3ub(251,170,90); // orange
    buildingTall (-0.5f, -0.8f);
    glColor3ub(82, 85, 7); // ripe olive green
    building2Block (-0.4f, -0.8f);
    glColor3ub(95, 237, 252); // sky blue
    buildingTall (-0.3f, -0.8f);
    glColor3ub(101, 165, 36); // grass green
    building1Block(-0.2f, -0.8f);
    glColor3ub(235,247,108); // light yellow
    building1Block(-0.1f, -0.8f);
    glColor3ub(37, 90, 115);// peacock blue
    buildingTall(0.0f, -0.8f);
    glColor3ub(82, 85, 7); // ripe olive green
    building2Block (0.1f, -0.8f);
    glColor3ub(95, 237, 252); // sky blue
    building2Block (0.2f, -0.8f);
    glColor3ub(37, 90, 115);// peacock blue
    building1Block (0.3f, -0.8f);
    glColor3ub(101, 165, 36); // grass green
    buildingTall(0.4f, -0.8f);
    glColor3ub(210, 153, 25); // burnt orange
    building1Block (0.5f, -0.8f);
    glColor3ub(82, 85, 7); // ripe olive green
    building1Block (0.6f, -0.84f);
    glColor3ub(235,247,108); // light yellow
    building2Block (0.7f, -0.84f);
    glColor3ub(37, 90, 115);// peacock blue
    building1Block (0.8f, -0.85f);


    // Lower Building 4th layer
    glColor3ub(37, 90, 115);// peacock blue
    building2Block (-1.0f, -1.0f);
    glColor3ub(241, 180, 45); // orange
    building1Block (-0.9f, -1.0f);
    glColor3ub(95, 237, 252); // sky blue
    building1Block (-0.8f, -1.01f);
    glColor3ub(235,247,108); // light yellow
    buildingTall(-0.7f, -1.0f);
    glColor3ub(82, 85, 7); // ripe olive green
    building2Block (-0.6f, -1.0f);
    glColor3ub(101, 165, 36); // grass green
    buildingTall(-0.5f, -1.02f);
    glColor3ub(37, 90, 115);// peacock blue
    building1Block (-0.4f, -1.01f);
    glColor3ub(241, 180, 45); // orange
    building2Block (-0.3f, -1.0f);
    glColor3ub(82, 85, 7); // ripe olive green
    buildingTall(-0.2f, -1.03f);
    glColor3ub(95, 237, 252); // sky blue
    building2Block(-0.1f, -1.0f);
    glColor3ub(251,170,90); // orange
    buildingTall(0.0f, -1.0f);
    glColor3ub(235,247,108); // light yellow
    building1Block (0.1f, -1.01f);
    glColor3ub(101, 165, 36); // grass green
    buildingTall(0.2f, -1.04f);
    glColor3ub(82, 85, 7); // ripe olive green
    buildingTall(0.3f, -1.07f);
    glColor3ub(235,247,108); // light yellow
    building2Block(0.4f, -1.0f);
    glColor3ub(37, 90, 115);// peacock blue
    building1Block(0.5f, -1.0f);
    glColor3ub(95, 237, 252); // sky blue
    buildingTall(0.6f, -1.04f);
    glColor3ub(101, 165, 36); // grass green
    building1Block(0.7f, -1.0f);
    glColor3ub(82, 85, 7); // ripe olive green
    building1Block(0.8f, -1.02f);
    glColor3ub(251,170,90); // orange
    buildingTall(0.9f, -1.0f);
    glColor3ub(95, 237, 252); // sky blue
    buildingTall(1.0f, -1.02f);


    glFlush();
    // Render now
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(1400, 730);
    glutInitWindowPosition(30, 20);
    glutCreateWindow("OpenGL Setup Test");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}