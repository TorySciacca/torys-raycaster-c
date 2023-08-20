#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#define PI 3.14159265359

float px,py,pdx,pdy,pa; //player position

void drawPlayer()
{
 glColor3f(1,1,0);   
 glPointSize(8);    
 glLineWidth(4);
 glBegin(GL_POINTS); 
 glVertex2i(px,py); 
 glEnd();
 
 glLineWidth(3);
 glBegin(GL_LINES);
 glVertex2i(px,py);
 glVertex2i(px+pdx*5, py+pdy*5);
 glEnd();
}

int mapX=8,mapY=8,mapS=64;
int map[]=
{
 1,1,1,1,1,1,1,1,
 1,0,1,0,0,0,0,1,
 1,0,1,0,0,0,0,1,
 1,0,1,0,0,0,0,1,
 1,0,0,0,0,0,0,1,
 1,0,0,0,0,1,0,1,
 1,0,0,0,0,0,0,1,
 1,1,1,1,1,1,1,1,	
};

void drawMap2D()
{
 int x,y,xo,yo;
 for (y=0;y<mapY;y++)
 {
 	for(x=0;x<mapX;x++)
    {
     if(map[y*mapX+x]==1){ glColor3f(1,1,1);} else{ glColor3f(0,0,0);}
     xo=x*mapS; yo=y*mapS;
     glBegin(GL_QUADS); 
     glVertex2i( 0   +xo+1, 0   +yo+1); 
     glVertex2i( 0   +xo+1, mapS+yo-1); 
     glVertex2i( mapS+xo-1, mapS+yo-1);  
     glVertex2i( mapS+xo-1, 0   +yo+1); 
     glEnd();
    }
 }
}

void drawRays3D()
{
 int r,mx,my,mp,dof; float rx,ry,ra,xo,yo;
 ra=pa;
 for(r=0;r<1;r++)
 {
 	//----Check Horizontal Lines---
 	dof=0;
 	float aTan=-1/tan(ra);
 	if(ra>PI){ ry((int)py>>6)>>6)-0.0001; rx=(py-ry)*aTan+px; yo=-64; xo=-yo*aTan;} //looking up (dividing by 64 via bit shifting)
 	if(ra>PI){ ry((int)py>>6)>>6)+64    ; rx=(py-ry)*aTan+px; yo=-64; xo=-yo*aTan;} 
 }
}

void display()
{
 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 drawMap2D();
 drawPlayer();
 glutSwapBuffers();
}

void buttons(unsigned char key, int x, int y)
{
	if(key=='a') { pa-=0.1; if(pa<   0){ pa+=2*PI;} pdx=cos(pa)*5; pdy=sin(pa)*5;}
	if(key=='d') { pa+=0.1; if(pa<2*PI){ pa-=2*PI;} pdx=cos(pa)*5; pdy=sin(pa)*5;} 
	if(key=='w') { px+=pdx; py+=pdy;}
	if(key=='s') { px-=pdx; py-=pdy;}
	glutPostRedisplay();				
}

void init ()
{
	glClearColor(0.3,0.3,0.3,0);
	gluOrtho2D(0,1024,512,0);
	px=300; py=300;
	pdx=cos(pa)*5; pdy=sin(pa)*5;
}

int main(int argc, char* argv[])
{  
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
 glutInitWindowSize(1024,512);
 glutCreateWindow("Tory's Raycaster");
 init();
 glutDisplayFunc(display);
 glutKeyboardFunc(buttons);
 glutMainLoop();
}
