#include<GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>
#include "BmpLoader.h"

const double PI = 3.14159265389;


GLboolean bRotate = false,uRotate=false, ambRun=1;
int f=0,f1=0;
GLfloat alpha = 0.0, theta = 0.0, axis_x=0.0, axis_y=0.0,beta=0.0,gamma=0.0,angle=0.0,fai=0.0,scan_tray=0.0,scan=0.0,xray1=3.5,rotat=0.0,xray2=0.0, angle_P = 270.0, angle_Y = 270.0, angle_R = 90.0;
double eye[]={50,7,200};
double centre[]={50,4,80};
double upy=1,upx=0,upz=0,xx=1,yy=1,zz=1;
unsigned int ID[100];
double x=0,y=0,z=0,a1=.3,a2=.3,a3=.3,s1=1,s2=1,s3=1,d1=1,d2=1,d3=1,p1=0,p2=50,p3=-15,s_l=1;;
double windowHeight=1100, windowWidth=1000;
bool spot_light_switch1=false,spot_light_switch2=false, spot_light_switch3 = false, lightswitch=true;
double limit = 360;
double roll_value = 1;
double ambX = -28;
double value = 0.5;

GLfloat angleYaw = 90.0, anglePitch = 90.0, angleRoll = 90.0;
GLfloat angleYawLimit1 = 180.0, anglePitchLimit1 = 360.0;
GLfloat angleYawLimit2 = 0.0, anglePitchLimit2 = 180.0,angleRollLimit1=0,angleRollLimit2=180;


static GLfloat cube[8][4] =
{
    {0.0, 0.0, 0.0},
    {1.0, 0.0, 0.0},
    {1.0, 0.0, 1.0},
    {0.0, 0.0, 1.0},
    {0.0, 1.0, 0.0},
    {1.0, 1.0, 0.0},
    {1.0, 1.0, 1.0},
    {0.0, 1.0, 1.0},

};

static GLubyte p_Indices[6][4] =
{
    {0, 1, 2, 3},
    {4, 5, 6, 7},
    {4, 0, 3, 7},
    {5, 1, 2, 6},
    {4, 0, 1, 5},
    {3, 2, 6, 7},


};
static void getNormal3p
(GLfloat x1, GLfloat y1,GLfloat z1, GLfloat x2, GLfloat y2,GLfloat z2, GLfloat x3, GLfloat y3,GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2-x1;
    Uy = y2-y1;
    Uz = z2-z1;

    Vx = x3-x1;
    Vy = y3-y1;
    Vz = z3-z1;

    Nx = Uy*Vz - Uz*Vy;
    Ny = Uz*Vx - Ux*Vz;
    Nz = Ux*Vy - Uy*Vx;

    glNormal3f(Nx,Ny,Nz);
}

static GLfloat v[8][3] =
{
    {0,2,2},
    {2,2,2},
    {0,0,2},
    {2,0,2},
    {0,0,0},
    {2,0,0},
    {0,2,0},
    {2,2,0}

};
static GLubyte quadIndices[2][8] =
{
    {0,1,2,3,4,5,6,7},
    {3,5,1,7,0,6,2,4}
};
void drawcone(GLfloat a,GLfloat b,GLfloat c,GLfloat d)
{
    GLfloat mat_ambient[] = { a*0.5,b*0.5, c*0.5, 1.0 };
    GLfloat mat_diffuse[] = { a, b, c, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glBegin(GL_QUAD_STRIP);
    GLUquadricObj *obj = gluNewQuadric();
    gluQuadricTexture(obj,TRUE);
    glColor3f(1,0,0);
    gluCylinder(obj, 3.0, d, 7, 20, 30);
    gluDeleteQuadric(obj);
    glEnd();
}
void drawcubee(GLfloat a,GLfloat b,GLfloat c)
{
    glBegin(GL_QUAD_STRIP);
    for (GLint i = 0; i <2; i++)
    {

        glVertex3fv(&v[quadIndices[i][0]][0]);
        glTexCoord2f(0,0);
        ////glColor3f(0.0, 1.0, 0.0);
        glVertex3fv(&v[quadIndices[i][1]][0]);
        glTexCoord2f(1,0);

        ////glColor3f(0.0, 1.0, 0.0);
        glVertex3fv(&v[quadIndices[i][2]][0]);
        glTexCoord2f(1,1);

        glVertex3fv(&v[quadIndices[i][3]][0]);
        glTexCoord2f(0,1);

        ////glColor3f(colors[i+1][0],colors[i+1][1],colors[i+1][2]);
        glVertex3fv(&v[quadIndices[i][4]][0]);
        glTexCoord2f(0,0);

        ////glColor3f(0.8, 0.0, 1.0);
        glVertex3fv(&v[quadIndices[i][5]][0]);
        glTexCoord2f(1,0);

        ////glColor3f(0.5, 0.0, 0.2);
        glVertex3fv(&v[quadIndices[i][6]][0]);
        glTexCoord2f(1,1);

        ////glColor3f(0.5, 0.0, 0.2);
        glVertex3fv(&v[quadIndices[i][7]][0]);
        glTexCoord2f(0,1);

    }
    glEnd();
}

void drawcylinder(GLfloat a,GLfloat b,GLfloat c,GLfloat d)
{
    GLfloat mat_ambient[] = { a*0.5,b*0.5, c*0.5, 1.0 };
    GLfloat mat_diffuse[] = { a, b, c, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    glPushMatrix();
    glRotatef(90,1,0,0);
    glBegin(GL_QUAD_STRIP);
    GLUquadricObj *obj = gluNewQuadric();
    gluQuadricTexture(obj,TRUE);
    gluCylinder(obj, 3.0, 3, 7, 20, 30);
    gluDeleteQuadric(obj);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glRotatef(90,1,0,0);
    glBegin(GL_QUAD_STRIP);
    GLUquadricObj *obj1 = gluNewQuadric();
    gluQuadricTexture(obj1,TRUE);
    gluDisk(obj1, d, 3, 20, 30);
    gluDeleteQuadric(obj1);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-6.7,0);
    glRotatef(90,1,0,0);
    glPushMatrix();
    glBegin(GL_QUAD_STRIP);
    GLUquadricObj *obj2 = gluNewQuadric();
    //gluQuadricTexture(obj2,TRUE);
    gluDisk(obj2, d, 3, 20, 30);
    gluDeleteQuadric(obj2);
    glEnd();
    glPopMatrix();

}
void drawsphere(GLfloat a,GLfloat b,GLfloat c,GLfloat r)
{
    GLfloat mat_ambient[] = { a*0.5,b*0.5, c*0.5, 1.0 };
    GLfloat mat_diffuse[] = { a, b, c, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);

    GLUquadricObj *obj=gluNewQuadric();
    gluQuadricTexture(obj,GL_TRUE);
    gluSphere(obj,r,50,20);
    gluDeleteQuadric(obj);

}
void drawcube(GLfloat a,GLfloat b,GLfloat c)
{

    GLfloat mat_ambient[] = { a*0.5,b*0.5, c*0.5, 1.0 };
    GLfloat mat_diffuse[] = { a, b, c, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = {60};

    glMaterialfv( GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv( GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv( GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv( GL_FRONT, GL_SHININESS, mat_shininess);


    glBegin(GL_QUADS);
    for (GLint i = 0; i <8; i++)
    {
        getNormal3p(cube[p_Indices[i][0]][0], cube[p_Indices[i][0]][1], cube[p_Indices[i][0]][2],
                    cube[p_Indices[i][1]][0], cube[p_Indices[i][1]][1], cube[p_Indices[i][1]][2],
                    cube[p_Indices[i][2]][0], cube[p_Indices[i][2]][1], cube[p_Indices[i][2]][2]);


        glVertex3fv(&cube[p_Indices[i][0]][0]);
        glTexCoord2f(1,1);
        glVertex3fv(&cube[p_Indices[i][1]][0]);
        glTexCoord2f(1,0);
        glVertex3fv(&cube[p_Indices[i][2]][0]);
        glTexCoord2f(0,0);
        glVertex3fv(&cube[p_Indices[i][3]][0]);
        glTexCoord2f(0,1);


    }
    glEnd();

}

void LoadTexture(const char*filename,int a)
{
    glGenTextures(1, &ID[a]);
    glBindTexture(GL_TEXTURE_2D, ID[a]);
    //printf("%d",ID[a]);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID[a]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}
void light()
{
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {a1,a2,a3, 1.0};
    GLfloat light_diffuse[]  = { d1,d2,d3, 1.0 };
    GLfloat light_specular[] = { s1,s2,s3, 1.0 };
    GLfloat light_position[] = { p1,p2,p3, 1.0 };

    //glEnable( GL_LIGHT0);
    //fv=floot vector
    //GL_LIGHT0=0th light
    glLightfv( GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT0, GL_POSITION, light_position);

    /*  GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };
      glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
      glLightf( GL_LIGHT0, GL_SPOT_CUTOFF, 10.0); */
}


void ground()
{
    glBindTexture(GL_TEXTURE_2D, ID[1]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();//ground
    glTranslatef(-220,-2.2,-120);
    glScalef(500,.2,270);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void road()
{

    glBindTexture(GL_TEXTURE_2D, ID[6]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-80,-2,68);
    glScalef(20,.02,30);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, ID[6]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-80,-2,28);
    glScalef(20,.02,30);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, ID[6]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(40,-2,68);
    glScalef(20,.02,30);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, ID[6]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(40,-2,28);
    glScalef(20,.02,30);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, ID[6]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(170,-2,68);
    glScalef(20,.02,30);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, ID[6]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(170,-2,28);
    glScalef(20,.02,30);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);



    glBindTexture(GL_TEXTURE_2D, ID[7]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-220,-2,100);
    glScalef(480,.02,30);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, ID[7]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-90,-2,100);
    glScalef(100,.02,18);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


}
void ultra()
{
    glBindTexture(GL_TEXTURE_2D, ID[2]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();// base
    glTranslatef(1.3,-12.25,35);
    glScalef(2,.2,2);
    drawcube(.7,.7,.7);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, ID[2]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();//usg lomba
    glTranslatef(1.7,-12.05,35.4);
    glScalef(1,1.5,1);
    drawcube(.7,.7,.7);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, ID[2]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();//usg lomba 2
    glTranslatef(2,-10.55,35.7);
    glScalef(.5,1,.5);
    drawcube(.7,.7,.7);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, ID[16]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();//usg board
    glTranslatef(1.7,-8.55,35.0);
    glRotatef(-30,0,0,1);
    glScalef(1.5,.1,2);
    drawcube(.7,.7,.7);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, ID[3]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();//button tex
    glTranslatef(1.7,-8.42,37.0);
    glRotatef(-30,0,0,1);
    glScalef(1.5,.0001,2);
    glRotatef(90,0,1,0);
    drawcube(.7,.7,.7);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, ID[16]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();//usg lomba 3
    glTranslatef(1.3,-9.65,35.9);
    glScalef(.7,.2,.2);
    drawcube(.7,.7,.7);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, ID[16]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();//usg lomba 4
    glTranslatef(1.1,-9.65,35.9);
    glScalef(.2,1.9,.2);
    drawcube(.7,.7,.7);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, ID[16]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();//usg screen
    glTranslatef(1.8,-8.05,35.0);
    glScalef(.1,1.5,2);
    drawcube(.7,.7,.7);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, ID[4]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();//usg screen texture
    glTranslatef(1.91,-8.05,35.0);
    glScalef(.0001,1.5,2);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

}

void xray()
{
    glPushMatrix();//xray_base
    glTranslatef(2.5,-12.25,50.8);
    glScalef(1.3,.2,1.4);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();//xray_1_LOMBA
    glTranslatef(2.7,-12.25,51);
    glScalef(.7,7,1);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();//xray_11_LOMBA
    glTranslatef(3.4,-12.25,51.1);
    glScalef(.3,7,.7);
    drawcube(.7,.7,.7);
    glPopMatrix();

    glPushMatrix();//xray_majher char kona
    glTranslatef(0,xray1,0);
    glTranslatef(3.4,-11.85,50.6);
    glScalef(.31,1.7,1.7);
    drawcube(.7,.7,.7);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, ID[5]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();//xray_majher char kona
    glTranslatef(0,xray1,0);
    glTranslatef(3.72,-11.85,50.6);
    glScalef(.001,1.7,1.7);
    drawcube(.7,.7,.7);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();//xray_2_LOMBA
    glTranslatef(7,-12.25,49);
    glScalef(1,7,.7);
    drawcube(1,1,1);
    glPopMatrix();


    glPushMatrix();//xray_21_LOMBA
    glTranslatef(7.1,-7.25,49.7);
    glScalef(.8,.5,1.5);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();//xray_22_LOMBA
    glTranslatef(7,-7,51.3);
    glScalef(.15,.08,.08);
    glRotatef(90,0,0,1);
    drawcylinder(.7,.7,.7,.0001);
    glPopMatrix();

    glPushMatrix();//xray
    glTranslatef(7.5,-7,51.3);
    glScalef(.15,.08,.08);
    glRotatef(xray2,0,0,1);
    glRotatef(90,1,0,0);
    glBegin(GL_QUAD_STRIP);
    GLUquadricObj *obj = gluNewQuadric();
    gluQuadricTexture(obj,TRUE);
    gluCylinder(obj, 0.0001, 3.5, 7, 20, 30);
    gluDeleteQuadric(obj);
    glEnd();
    glPopMatrix();


    glPushMatrix();//xray_tray
    glTranslatef(5,-10.25,50.5);
    glScalef(5,.1,1.8);
    drawcube(0.000, 0.000, 0.545);
    glPopMatrix();


    glPushMatrix();//xray_tray base
    glTranslatef(6.75,-12.25,50.9);
    glScalef(2,2,1);
    drawcube(1,1,1);
    glPopMatrix();

}


void firstf()
{
    glBindTexture(GL_TEXTURE_2D, ID[9]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();//ground
    glTranslatef(-25,-2,-100);
    glScalef(150,.2,120);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glBindTexture(GL_TEXTURE_2D, ID[10]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();//ground
    glTranslatef(-25,-1.95,-100);
    glScalef(150,.2,120);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void groudf()
{
    glBindTexture(GL_TEXTURE_2D, ID[11]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();//ground
    glTranslatef(-180,-2,-100);
    glScalef(440,.2,120);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void ceiling()
{
    glBindTexture(GL_TEXTURE_2D, ID[10]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();//ground
    glTranslatef(-180,60,-100);
    glScalef(440,.2,120);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}
void wall()
{
    ///Back
    glPushMatrix();
    glTranslatef(-180,-2,-100);
    glScalef(480,62,2);
    drawcube(1,1,1);
    glPopMatrix();


    ///Left
    //glBindTexture(GL_TEXTURE_2D, ID[20]);
    //glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(-25,-2,-100);
    glScalef(2,62,120);
    drawcube(1,1,1);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

    //glBindTexture(GL_TEXTURE_2D, ID[20]);
    //glEnable(GL_TEXTURE_2D);
    ///Left left
    glPushMatrix();
    glTranslatef(-180,-2,-100);
    glScalef(2,62,120);
    drawcube(1,1,1);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

    ///Right
    //glBindTexture(GL_TEXTURE_2D, ID[20]);
    //glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(120,-2,-100);
    glScalef(2,62,120);
    drawcube(1,1,1);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

    ///Right Right

    //glBindTexture(GL_TEXTURE_2D, ID[20]);
    //glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(260,-2,-100);
    glScalef(2,62,120);
    drawcube(1,1,1);
    glPopMatrix();
    //glDisable(GL_TEXTURE_2D);

}
void amb()
{
    glPushMatrix();     ///Headlight 1
    glTranslatef(0,2.8,1.3);
    glScalef(.1,.10,.1);
    drawcylinder(1,0,0,.0001);
    glPopMatrix();

    glPushMatrix();     ///Headlight 2
    glTranslatef(0,2.8,4.3);
    glScalef(.1,.10,.1);
    drawcylinder(1,0,0,.0001);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, ID[15]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();     ///base
    glTranslatef(0,1.8,0);
    glScalef(8,1.7,5);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();     ///second base
    glTranslatef(1.5,3.5,0);
    glScalef(1.5,2,5);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();     ///angle
    glTranslatef(.95,3.5,0);
    glRotatef(-20,0,0,1);
    glScalef(.6,2.15,5);
    drawcube(1,1,1);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, ID[12]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();     ///BASE 3
    glTranslatef(3,3.5,0);
    glScalef(5,2,5);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, ID[13]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();     ///angletex
    glTranslatef(.85,3.5,0);
    glRotatef(-20,0,0,1);
    glScalef(.0001,2.15,5);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, ID[13]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();     ///second base tex
    glTranslatef(1.5,3.5,5.01);
    glScalef(1.5,1.9,.0001);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, ID[13]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();     ///second base pichon
    glTranslatef(1.5,3.5,-.1);
    glScalef(1.5,1.9,.0001);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, ID[14]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();     ///chaka samne right
    glTranslatef(1,1.5,1);
    glRotatef(90,1,0,0);
    glScalef(.3,.07,.3);
    drawcylinder(1,1,1,.75);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glBindTexture(GL_TEXTURE_2D, ID[14]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();     ///chaka samne left
    glTranslatef(1,1.5,4.6);
    glRotatef(90,1,0,0);
    glScalef(.3,.07,.3);
    drawcylinder(1,1,1,.75);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glBindTexture(GL_TEXTURE_2D, ID[14]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();     ///chaka pichon right
    glTranslatef(7,1.5,1);
    glRotatef(90,1,0,0);
    glScalef(.3,.07,.3);
    drawcylinder(1,1,1,.75);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glBindTexture(GL_TEXTURE_2D, ID[14]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();     ///chaka pichon left
    glTranslatef(7,1.5,4.6);
    glRotatef(90,1,0,0);
    glScalef(.3,.07,.3);
    drawcylinder(1,1,1,.75);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


    glPushMatrix();     ///AMB LIGHT
    glTranslatef(3,6.2,2.3);
    glScalef(.12,.10,.35);
    drawcylinder(1,0,0,.0001);
    glPopMatrix();

}

void ambulance()
{

    glPushMatrix();
    glScalef(5,5,5);
    glTranslatef(-22,-1,5);
    glRotatef(180,0,1,0);
    amb();
    glPopMatrix();

    glPushMatrix();
    glScalef(5,5,5);
    glTranslatef(-22,-1,-8);
    glRotatef(180,0,1,0);
    amb();
    glPopMatrix();

    glPushMatrix();
    glScalef(5,5,5);
    glTranslatef(-14,-1,0);
    amb();
    glPopMatrix();

    glPushMatrix();
    glScalef(5,5,5);
    glTranslatef(-14,-1,-8);
    amb();
    glPopMatrix();


}

void chairdisplay(void)
{
    //light_call(1,1,1,1,1,1);

    glPushMatrix();//seat
    glScalef(4,.2,6);
    drawcube(1,1,1);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();
    glScalef(.2,-1.5,.2);//pichon1
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glScalef(.2,-1.5,.2);//pichon2
    glTranslatef(18,0,0);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glScalef(.2,-1.5,.2);//samne1
    glTranslatef(0,0,28);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glScalef(.2,-1.5,.2);//samne2
    glTranslatef(18,0,28);
    drawcube(1,1,1);
    glPopMatrix();

}

void chair1()
{
    glPushMatrix();//seat
    glScalef(4,.4,6);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();//upor
    glScalef(.2,1,6);
    glTranslatef(0,3,0);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();//pichon1u
    glScalef(.2,3,.2);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glScalef(.2,-3,.2);//pichon1
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glScalef(.2,-3,.2);//pichon2
    glTranslatef(18,0,0);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glScalef(.2,3,.2);//pichon2u
    glTranslatef(0,0,28);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glScalef(.2,-3,.2);//samne1
    glTranslatef(0,0,28);
    drawcube(1,1,1);
    glPopMatrix();

    glPushMatrix();
    glScalef(.2,-3,.2);//samne2
    glTranslatef(18,0,28);
    drawcube(1,1,1);
    glPopMatrix();
}

void bed()
{

    ///base
    glPushMatrix();
    glScalef(5, .7, 4.8);
    drawcube(1,1,1);
    glPopMatrix();

    ///Balish
    glBindTexture(GL_TEXTURE_2D, ID[17]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(2.5, 1, 1.7);
    glTranslated(0.5,0,0);
    drawcube(0.96,0.96,0.96);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // dandi1
    glPushMatrix();
    glScalef(.2,5,.2);
    drawcube(0.69,0.70,0.72);
    glPopMatrix();

    glPushMatrix();
    glScalef(4.8,0.2,.2);
    glTranslatef(0,24,0);
    drawcube(0.69,0.70,0.72);
    glPopMatrix();

    glPushMatrix();
    glScalef(.2,-1.5,.2);///pichon1
    drawcube(0.69,0.70,0.72);
    glPopMatrix();


    // dandi2
    glPushMatrix();
    glScalef(.2,5,.2);
    glTranslatef(23,0,0);
    drawcube(0.69,0.70,0.72);
    glPopMatrix();

    glPushMatrix();
    glScalef(.2,-1.5,.2);///pichon2
    glTranslatef(23,0,0);
    drawcube(0.69,0.70,0.72);
    glPopMatrix();

    glPushMatrix();
    glScalef(.2,-1.5,.2);///samne1
    glTranslatef(0,0,23);
    drawcube(0.69,0.70,0.72);
    glPopMatrix();

    glPushMatrix();
    glScalef(.2,-1.5,.2);///samne2
    glTranslatef(23,0,23);
    drawcube(0.69,0.70,0.72);
    glPopMatrix();
}


void fan()
{

    glScalef(.5,.5,.5);
    glTranslatef(0,8.4,0);
    glPushMatrix();

    glTranslatef(-3,0,0);

    //base
    glPushMatrix();
    glScalef(2.5,.8,2.5);
    //glTranslatef(-2,5.8,0);
    //glRotatef( theta, axis_x, axis_y, 0.0 );
    drawsphere(.37,.37,.37,1);
    glPopMatrix();

    //base_line
    glPushMatrix();
    glScalef(.5,1.5,.5);
    glTranslatef(0,.5,0);
    //glRotatef( theta, axis_x, axis_y, 0.0 );
    drawcube(.37,.37,.37);
    glPopMatrix();

    glRotatef( alpha, axis_x, axis_y, 0.0 );
    glRotatef( theta, axis_x, axis_y, 0.0 );

    //line
    glPushMatrix();
    glScalef(3,.2,.2);
    //glTranslatef(-2,5.8,0);
    //glRotatef( theta, axis_x, axis_y, 0.0 );
    drawcube(.37,.37,.37);
    glPopMatrix();

    //line
    glPushMatrix();
    glScalef(.2,.2,3);
    //glTranslatef(-2,5.8,0);
    //glRotatef( theta, axis_x, axis_y, 0.0 );
    drawcube(.37,.37,.37);
    glPopMatrix();

    //pakha1
    glPushMatrix();
    glScalef(3.5,.2,1);
    glTranslatef(.85,0,0);
    //glRotatef( theta, axis_x, axis_y, 0.0 );
    drawcube(.37,.37,.37);
    glPopMatrix();

    //pakha2
    glPushMatrix();
    glScalef(7.5,.2,1);
    glTranslatef(-.85,0,0);
    //glRotatef( theta, axis_x, axis_y, 0.0 );
    drawcube(.37,.37,.37);
    glPopMatrix();

    //pakha3
    glPushMatrix();
    glScalef(1,.2,3.5);
    glTranslatef(0,0,.85);
    //glRotatef( theta, axis_x, axis_y, 0.0 );
    drawcube(.37,.37,.37);
    glPopMatrix();

    //pakha4
    glPushMatrix();
    glScalef(1,.2,7.5);
    glTranslatef(0,0,-.85);
    //glRotatef( theta, axis_x, axis_y, 0.0 );
    drawcube(.37,.37,.37);
    glPopMatrix();
    glPopMatrix();
}


void spot_boby(float x,float y,float z)
{
    glPushMatrix();
    glTranslatef(x,y,z);
    drawsphere(1,1,1,2);
    glPopMatrix();

    glPushMatrix();
    glScalef(1,30,1);
    glTranslatef(x,30-y,z);
    drawcube(0,0,0);
    glPopMatrix();

}

void bulb(float x,float y,float z)
{
    glPushMatrix();
    glTranslatef(x,y,z);
    drawsphere(1,1,1,2);
    glPopMatrix();

}

void spot_light_function(float x, float y, float z, float c)
{
    // Light Specification
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.9, 0.9, 0, 1.0};
    GLfloat light_diffuse[]  = { 1, 1, 0, 1.0 };
    GLfloat light_specular[] = { 0.9, 0.9, 0, 1.0 };
    GLfloat light_position[] = { x,y,z, 1.0 };

    glLightfv( GL_LIGHT2, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT2, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT2, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT2, GL_POSITION, light_position);
    GLfloat direction[]= {0,-1,0};
    GLfloat cut_off=c;
    glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION,direction);
    glLightf(GL_LIGHT2,GL_SPOT_CUTOFF,cut_off);

}

void spot_light_function2(float x, float y, float z, float c)
{
    // Light Specification
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.9, 0.9, 0, 1.0};
    GLfloat light_diffuse[]  = { 1, 1, 0, 1.0 };
    GLfloat light_specular[] = { 0.9, 0.9, 0, 1.0 };
    GLfloat light_position[] = { x,y,z, 1.0 };

    glLightfv( GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv( GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv( GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv( GL_LIGHT1, GL_POSITION, light_position);
    GLfloat direction[]= {0,-1,0};
    GLfloat cut_off=c;
    glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION,direction);
    glLightf(GL_LIGHT1,GL_SPOT_CUTOFF,cut_off);
}

GLfloat light_diffuse3[][4]  = {
    { 0.9, 0.9, 0.9, 1.0 },
    { 0.9, 0.0, 0.0, 1.0 },
    { 0.0, 0.9, 0.3, 1.0 },
    { 0.0, 0.1, 0.9, 1.0 }
};

int light3_i = 0;

void spot_light_function3(float x, float y, float z, float c)
{
    // Light Specification
    GLfloat no_light[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light_ambient[]  = {0.9, 0.9, 0.9, 1.0};
    GLfloat light_diffuse[]  = { 1, 1, 1, 1.0 };
    GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1.0 };
    GLfloat light_position[] = { x,y,z, 1.0 };

    glLightfv( GL_LIGHT4, GL_AMBIENT, light_diffuse3[light3_i]);
    glLightfv( GL_LIGHT4, GL_DIFFUSE, light_diffuse3[light3_i]);
    glLightfv( GL_LIGHT4, GL_SPECULAR, light_diffuse3[light3_i]);
    glLightfv( GL_LIGHT4, GL_POSITION, light_position);
    GLfloat direction[]= {0,-1,0};
    GLfloat cut_off=c;
    glLightfv(GL_LIGHT4,GL_SPOT_DIRECTION,direction);
    glLightf(GL_LIGHT4,GL_SPOT_CUTOFF,cut_off);
}


void Yaw() // x axis , p o
{
    centre[0] = eye[0]+30.0*(cos(angle_Y*3.1416/180.0));
    centre[2] = eye[2]+30.0*(sin(angle_Y*3.1416/180.0));
}

void Pitch() // y axis , y t
{

    centre[1] = eye[1]+30.0*(cos(angle_P*3.1416/180.0));
    centre[2] = eye[2]+30.0*(sin(angle_P*3.1416/180.0));

}

void Roll() // z axis ,r e
{
    upx = 100.0*(cos(angle_R*3.1416/180.0));
    upy = 100.0*(sin(angle_R*3.1416/180.0));

}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glClearColor (0,0,0,1);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glFrustum(-3,3,-3,3, 3,300);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    gluLookAt(eye[0],eye[1],eye[2], centre[0],centre[1],centre[2], upx,upy,upz);
    glViewport(0, 0, windowHeight, windowWidth);
    glScalef(xx,yy,zz);

    ///table
    glPushMatrix();
    glScalef(6,6,6);
    glTranslatef(6,1.3,-5);
    chairdisplay();
    glPopMatrix();

    ///chair
    glBindTexture(GL_TEXTURE_2D, ID[8]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(3,3,3);
    glTranslatef(30,1.6,5);
    glRotatef(180,0,1,0);
    chair1();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///chair
    glBindTexture(GL_TEXTURE_2D, ID[8]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glScalef(1.4,3,1.8);
    glTranslatef(-7,1.6,5);
    glRotatef(90,0,1,0);
    chair1();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///Bed 1
    glPushMatrix();
    glScalef(5,6,6);
    glTranslatef(26,1.3,-5);
    bed();
    glPopMatrix();

    ///Bed 2
    glPushMatrix();
    glScalef(5,6,6);
    glTranslatef(26,1.3,-13);
    bed();
    glPopMatrix();

    ///Bed 3
    glPushMatrix();
    glScalef(5,6,6);
    glTranslatef(44,1.3,-5);
    bed();
    glPopMatrix();

    ///Bed 4
    glPushMatrix();
    glScalef(5,6,6);
    glTranslatef(44,1.3,-13);
    bed();
    glPopMatrix();

    ///Bed 5
    glPushMatrix();
    glScalef(5,6,6);
    glTranslatef(35,1.3,-5);
    bed();
    glPopMatrix();

    ///Bed 6
    glPushMatrix();
    glScalef(5,6,6);
    glTranslatef(35,1.3,-13);
    bed();
    glPopMatrix();


    ///spot
    spot_boby(-80,30,95);
    glPushMatrix();
    spot_light_function(-85,60,80,50);
    glPopMatrix();
    spot_boby(120,30,95);
    glPushMatrix();
    spot_light_function2(115,60,80,50);
    glPopMatrix();

    spot_light_function3(47,80,-10, 50);

    ///Bulb
    glPushMatrix();
    glScalef(2, 1.3, 2);
    bulb(25,45,-10);
    glPopMatrix();


    ///ambulance
    //glPushMatrix();
    ambulance();
    //glPopMatrix();


    ///ceil
    glPushMatrix();
    ceiling();
    glPopMatrix();



    ///wall
    glBindTexture(GL_TEXTURE_2D, ID[20]);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    wall();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    ///1st
    glPushMatrix();
    firstf();
    glPopMatrix();
    ///garage
    glPushMatrix();
    groudf();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(250,60,-30);
    glScalef(5,5,2);
    glRotatef(-90,0,1,0);
    xray();
    glPopMatrix();

    ///ultra-xray
    glPushMatrix();
    glTranslatef(250,60,-10);
    glScalef(5,5,2);
    glRotatef(-90,0,1,0);

    ultra();
    // xray();
    glPopMatrix();
    ///ground
    glPushMatrix();
    ground();
    glPopMatrix();

    ///road
    glPushMatrix();
    road();
    glPopMatrix();

    ///Ambulance
    glPushMatrix();
    glScalef(5,5,5);
    glTranslatef(ambX,-1,26);
    glRotatef(180,0,1,0);
    amb();
    glPopMatrix();

    ///Fan
    glPushMatrix();
    glScalef(5,5,5);
    glTranslatef(38,6.3,0);
    fan();
    glPopMatrix();


    glFlush();
    glutSwapBuffers();
}

void setCameraEye_Yaw() // y axis , y u
{

    centre[1] = 100.0*(cos(angleYaw*3.1416/180.0));

}

void setCameraEye_Roll() // z axis ,i o
{

    upx = 100.0*(cos(angleRoll*3.1416/180.0));
    upy = 100.0*(sin(angleRoll*3.1416/180.0));

}

void setCameraEye_Pitch() // x axis , r t
{
    centre[0] = 100.0*(cos(anglePitch*3.1416/180.0));
}

int a=0;
void myKeyboardFunc( unsigned char key, int x, int y )
{

    switch ( key )
    {

    case 'f':
        bRotate = !bRotate;
        uRotate = false;
        axis_x=0.0;
        axis_y=1.0;
        break;

    case 'w': // move eye point upwards along Y axis
        eye[1]+=1.0;
        break;
    case 's': // move eye point downwards along Y axis
        eye[1]-=1.0;
        break;
    case 'a': // move eye point left along X axis
        eye[0]-=1.0;
        break;
    case 'd': // move eye point right along X axis
        eye[0]+=1.0;
        break;

    case 'u':
        eye[1]+=1.0;
        centre[1]+=1.0;
        break;
    case 'U':
        eye[1]-=1.0;
        centre[1]-=1.0;
        break;


    case 'b':
        eye[0]+=1.0;
        centre[0]+=1.0;
        break;
    case 'B':
        eye[0]-=1.0;
        centre[0]-=1.0;
        break;
    case 'z':
        xx+=0.05;
        yy+=0.05;
        zz+=0.05;
        glutPostRedisplay();

        break;
    case 'Z':
        xx-=0.05;
        yy-=0.05;
        zz-=0.05;
        glutPostRedisplay();
        break;

    case '+':
        eye[2]-=1;
        centre[2]-=1;
        break;
    case '-':
        eye[2]+=1;
        centre[2]+=1;
        break;


    case 'y':
        angle_Y +=  value;
        //if(angle_Y>=90 || angle_Y<=-90) refZ=-refZ;
        Yaw();
        break;
    case 'Y':
        angle_Y -=  value;
        //if(angle_Y>=90 || angle_Y<=-90) refZ=-refZ;
        Yaw();
        break;
    case 'R':
        angle_R +=  value;
        //if(angle_Y>=90 || angle_Y<=-90) refZ=-refZ;
        Roll();
        break;
    case 'r':
        angle_R -=  value;
        //if(angle_Y>=90 || angle_Y<=-90) refZ=-refZ;
        Roll();
        break;
    case 'p':
        angle_P +=  value;
        //if(angle_Y>=90 || angle_Y<=-90) refZ=-refZ;
        Pitch();
        break;
    case 'P':
        angle_P -=  value;
        //if(angle_Y>=90 || angle_Y<=-90) refZ=-refZ;
        Pitch();
        break;

    case 'c':
        ambRun = !ambRun;
        break;

    case 'v':
        ambRun = 2;
        break;


    case '1':
        if(lightswitch==true)
        {
            lightswitch=false,glDisable(GL_LIGHT0);
            break;
        }
        else if(lightswitch==false)
        {
            lightswitch=true,glEnable(GL_LIGHT0);
            break;
        }
    case '2':
        if(a1==1 && a2==1 && a3==1)
        {
            a1=.3,a2=.3, a3=.3;
            light();
            break;
        }
        else
        {
            a1=1,a2=1, a3=1;
            light();
            break;
        }
    case '3':
        if(s1==1)
        {
            s1=0,s2=0, s3=0;
            light();
            break;
        }
        else
        {
            s1=1,s2=1, s3=1;
            light();
            break;
        }
    case '4':
        if(d1==1 && d2==1 && d3==1)
        {
            d1=0,d2=0, d3=0;
            light();
            break;
        }
        else
        {
            d1=1,d2=1, d3=1;
            light();
            break;
        }

    case '6':

        if(!spot_light_switch2)
        {
            spot_light_switch2=!spot_light_switch2;
            break;
        }
        else
        {
            spot_light_switch2=!spot_light_switch2;
            break;
        }

    case '5':

        if(!spot_light_switch1)
        {
            spot_light_switch1=!spot_light_switch1;
            break;
        }
        else
        {
            spot_light_switch1=!spot_light_switch1;
            break;
        }
    case '7':
        spot_light_switch3 = !spot_light_switch3;
        break;

    case '8':
        light3_i = (light3_i + 1) % 4;

    }
    glutPostRedisplay();



}


void animate()
{
    if (spot_light_switch1)
    {
        glEnable( GL_LIGHT1);
    }
    else if(!spot_light_switch1)
    {
        glDisable( GL_LIGHT1);
    }

    if (spot_light_switch3)
    {
        glEnable( GL_LIGHT4);
    }
    else if(!spot_light_switch3)
    {
        glDisable( GL_LIGHT4);
    }

    if (spot_light_switch2)
    {
        glEnable( GL_LIGHT2);
    }
    else if(!spot_light_switch2)
    {
        glDisable( GL_LIGHT2);
    }

    if (bRotate == true)
    {
        theta += 2;
        if(theta > 360.0)
            theta -= 360.0*floor(theta/360.0);
    }

    if (uRotate == true)
    {
        alpha += 0.2;
        if(alpha > 360.0)
            alpha -= 360.0*floor(alpha/360.0);
    }

    if (ambRun == 1) {
        ambX += 0.05;
    }
    else if (ambRun == 2){
        ambX -= 0.05;
    }

    if (ambX > 52.0)
        ambX = -32;

    glutPostRedisplay();

}


void texture_info()
{

    LoadTexture("D:\\3D- Medical Center\\Image\\grass.bmp",1);//grass
    LoadTexture("D:\\3D- Medical Center\\Image\\scan_body.bmp",2);//scanbody
    LoadTexture("D:\\3D- Medical Center\\Image\\scan_button1.bmp",3);//scanbutton1
    LoadTexture("D:\\3D- Medical Center\\Image\\usg.bmp",4);//usg screen
    LoadTexture("D:\\3D- Medical Center\\Image\\xrayfilm.bmp",5);//xrayfilm
    LoadTexture("D:\\3D- Medical Center\\Image\\inroad1.bmp",6);//road
    LoadTexture("D:\\3D- Medical Center\\Image\\road1.bmp",7);//
    LoadTexture("D:\\3D- Medical Center\\Image\\chair.bmp",8);//
    LoadTexture("D:\\3D- Medical Center\\Image\\floor.bmp",9);
    LoadTexture("D:\\3D- Medical Center\\Image\\wall.bmp",10);
    LoadTexture("D:\\3D- Medical Center\\Image\\garage.bmp",11);
    LoadTexture("D:\\3D- Medical Center\\Image\\blue.bmp",12);
    LoadTexture("D:\\3D- Medical Center\\Image\\glass3.bmp",13);
    LoadTexture("D:\\3D- Medical Center\\Image\\wheel.bmp",14);
    LoadTexture("D:\\3D- Medical Center\\Image\\car4.bmp",15);
    LoadTexture("D:\\3D- Medical Center\\Image\\wood.bmp",16);
    LoadTexture("D:\\3D- Medical Center\\Image\\Balish.bmp",17);
    LoadTexture("D:\\3D- Medical Center\\Image\\wall2.bmp",20);
}
int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(150,150);
    glutInitWindowSize(windowHeight, windowWidth);
    glutCreateWindow("Medical centre");

    glShadeModel( GL_SMOOTH );
    glEnable( GL_DEPTH_TEST );
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    /* GLfloat globalAmbient[] = {0.0, 0.0, 0.0, 1.0};
     glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);*/

    light();
    texture_info();

    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutIdleFunc(animate);
    glutMainLoop();

    return 0;
}
