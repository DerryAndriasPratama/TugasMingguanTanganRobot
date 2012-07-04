#include <GL\glut.h>
#include <GL\GL.H>
#include <MATH.H>

void kubus(float panjang,float lebar, float tinggi);
void rodaSemua(float jarakAntarSisi,float jarakSisiSama);
void roda(void);

int screen_width=800;
int screen_height=600;

double gerak=3;
double rotasiSemua=0,rotasiSemuaInc=0;
double rotasiLengan1=30,rotasiLengan1Inc=0;
double rotasiLengan2=30,rotasiLengan2Inc=0;
double gerakJepit=10,gerakJepitInc=0;
double rotasiJepit,rotasiJepitInc=0;
double maju=0,majuInc=0;
double muter=0,muterInc;
double zoom=-50,zoomInc=0;

GLfloat ambient_light[]={0.5,0.5,0.45,1.0};
GLfloat  source_light[]={0.8,0.8,0.8,1.0};
GLfloat     light_pos[]={7.0,0.0,0.1,1.0};

void init(void)
{
	glClearColor(1.0,1.0,1.0,0.0);  //putih
	//glClearColor(0.0,0.0,0.0,0.0); //back color
	glShadeModel(GL_SMOOTH);
	glViewport(0,0,screen_width,screen_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f,(GLfloat)screen_width/(GLfloat)screen_height,1.0f,1000.0f);

	glEnable		(GL_DEPTH_TEST);
	glPolygonMode   (GL_FRONT_AND_BACK,GL_FILL);
	glEnable		(GL_LIGHTING);
	glLightModelfv  (GL_LIGHT_MODEL_AMBIENT,ambient_light);
	glLightfv		(GL_LIGHT0,GL_DIFFUSE,source_light);
	glLightfv		(GL_LIGHT0,GL_POSITION,light_pos);
	glEnable		(GL_LIGHT0);
	glEnable		(GL_COLOR_MATERIAL);
	glColorMaterial	(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);
}

void resize(int width,int height)
{
	screen_width=width;
	screen_height=height;
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glViewport(0,0,screen_width,screen_height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f,(GLfloat)screen_width/(GLfloat)screen_height,1.0f,1000.0f);
	glutPostRedisplay();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	zoom+=zoomInc;
	glTranslatef(0.0,-10,zoom); // zoom kebelakang dan kebawah
 
	glRotatef(-90,1.0,0.0,0.0); // view thd smb x
	//glRotatef(10,0.0,1.0,0.0); // view terhadap smb y
	glRotatef(-45,0.0,0.0,1.0); // view thd smb z
	zoomInc=0;
	
	maju+=majuInc;
	glTranslatef(0.0,maju,0.0);   // bergerak ke kanan - kiri 
	majuInc=0;
	rotasiSemua+=rotasiSemuaInc; 
	glRotatef(rotasiSemua,0.0,0.0,1.0); //rotate semua objek
	rotasiSemuaInc=0;
	kubus(10,15,5); // kubus dasar
	rodaSemua(10,7); //4 roda

	//block lengan1
	glTranslatef(0.0,0.0,5); //menggeser lengan1 keatas
	rotasiLengan1+=rotasiLengan1Inc;
	glRotatef(rotasiLengan1,1.0,0.0,0.0);
	rotasiLengan1Inc=0; 
	kubus(4,4,10); //lengan1
	//akhir block lengan1

	//block lengan2	
	glTranslatef(0.0,0.0,10); //letakkan diujung lengan1
	rotasiLengan2+=rotasiLengan2Inc;
	glRotatef(rotasiLengan2,1.0,0.0,0.0);
	rotasiLengan2Inc=0;
	kubus(2.5,2.5,10);
	//akhir block lengan2

	//block jepit
	glTranslatef(0.0,0.0,10); //letakkan diujung lengan2
	rotasiJepit+=rotasiJepitInc;
	glRotatef(rotasiJepit,0.0,0.0,1.0);
	rotasiJepitInc=0;
	gerakJepit+=gerakJepitInc;
		//glPushMatrix();
			glRotatef(gerakJepit,0.0,1.0,0.0);
			kubus(0.3,0.5,3);
		//glPopMatrix();
		//	glPushMatrix();
			glRotatef(-gerakJepit,0.0,1.0,0.0);
			kubus(0.3,0.5,3);
		//glPopMatrix();
	gerakJepitInc=0;
	//glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void kubus(float panjang,float lebar, float tinggi)
{
	float pjg,lbr;
	pjg=panjang/2;
	lbr=lebar/2;
	glBegin(GL_QUADS);
			// Bawah
		  glColor3f(0.0,1.0,1.0); //cyan		  
		  glVertex3f(-pjg,-lbr,0.0);
	      glVertex3f(pjg,-lbr,0.0);
	      glVertex3f(pjg,lbr,0.0);
	      glVertex3f(-pjg,lbr,0.0);

          
		  glColor3f(1.0,0.0,0.0); //merah
		  glVertex3f(-pjg,-lbr,0.0);
	      glVertex3f(pjg,-lbr,0.0);
		  glVertex3f(pjg,-lbr,tinggi);
		  glVertex3f(-pjg,-lbr,tinggi);
	      
		  
		  glColor3f(1.0,0.0,1.0); //magenta
		  glVertex3f(pjg,-lbr,0.0);
	      glVertex3f(pjg,lbr,0.0);
		  glVertex3f(pjg,lbr,tinggi);
		  glVertex3f(pjg,-lbr,tinggi);
	      
		  glColor3f(0.0,1.0,0.0); // hijau
		  glVertex3f(pjg,lbr,0.0);
	      glVertex3f(-pjg,lbr,0.0);
		  glVertex3f(-pjg,lbr,tinggi);
		  glVertex3f(pjg,lbr,tinggi);
		       
		  glColor3f(0.0,0.0,1.0); //biru
		  glVertex3f(-pjg,lbr,0.0);
		  glVertex3f(-pjg,-lbr,0.0);
		  glVertex3f(-pjg,-lbr,tinggi);
	      glVertex3f(-pjg,lbr,tinggi);
		
		  //Atas		  
		  glColor3f(1.0,1.0,0.0); //kuning
		  glVertex3f(-pjg,-lbr,tinggi);
	      glVertex3f(pjg,-lbr,tinggi);
	      glVertex3f(pjg,lbr,tinggi);
	      glVertex3f(-pjg,lbr,tinggi);		
	glEnd();
}

void rodaSemua(float jarakAntarSisi,float jarakSisiSama)
{
	glPushMatrix();
	glRotatef(90,0.0,1.0,0.0); // rotasi agar sesuai dengan kubus
	glTranslatef(0.0,jarakSisiSama/2,0.0);
	glTranslatef(0.0,0.0,jarakAntarSisi/2);
	roda();
	glTranslatef(0.0,0.0,-jarakAntarSisi);
	roda();
	glTranslatef(0.0,-jarakSisiSama,0.0);
	roda();
	glTranslatef(0.0,0.0,jarakAntarSisi);
	roda();
	glPopMatrix();
}

void roda(void)
{
	glPushMatrix();
	glColor3f(0.2,0.3,0.1); //warna roda
	muter+=muterInc; 
	glRotatef(muter,0.0,0.0,1.0); //rotasi roda
	muterInc=0; 
	glutSolidTorus(1.0,1.5,12,12); //ukuran dan bentuk roda
	glPopMatrix();
}

void keyboard(int key,int x,int y)
{
	switch(key)
	{
	case GLUT_KEY_F1:
		if(gerakJepit <=50-gerak)    // max sudut gerakJepit 50 derajat
	    gerakJepitInc+=gerak;
		break;
    case GLUT_KEY_F2:
		if(gerakJepit >= gerak)	// min sudut gerakJepit 0 derajat
	    gerakJepitInc-=gerak;
		break;
	case GLUT_KEY_F3:
	    rotasiJepitInc+=gerak;
		break;
    case GLUT_KEY_F4:
	    rotasiJepitInc-=gerak;
		break;
	case GLUT_KEY_F5:	
		if(rotasiLengan2 >= -90+gerak)
		rotasiLengan2Inc-=gerak;
		break;
    case GLUT_KEY_F6:
		if(rotasiLengan2 <=90-gerak)
		rotasiLengan2Inc+=gerak;
		break;
	case GLUT_KEY_F7:
		if(rotasiLengan1 >= -90+gerak )
		rotasiLengan1Inc-=gerak;
		break;
	case GLUT_KEY_F8:
		if(rotasiLengan1 <=90-gerak)
		rotasiLengan1Inc+=gerak;
		break;
	case GLUT_KEY_LEFT:
		rotasiSemuaInc+=gerak;
		break;		
	case GLUT_KEY_RIGHT:
		rotasiSemuaInc-=gerak;
		break;		
   	case GLUT_KEY_UP:
		majuInc-=0.2;
		//muterInc+=1;
		break;		
	case GLUT_KEY_DOWN:	
		majuInc+=0.2;
		//muterInc-=1			;
		break;
	}
}

void mouse(int button, int state, int x, int y)
{
	if (state==0 && button==0)
		zoomInc+=gerak;
	if (state==0 && button==2)		
		zoomInc-=gerak;
}


int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(screen_width,screen_height);
	glutInitWindowPosition(0,0);
	glutCreateWindow("LENGAN ROBOT");
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutReshapeFunc(resize);
	glutSpecialFunc(keyboard);
	glutMouseFunc(mouse);
	init();
	glutMainLoop();
	return(0);
}
