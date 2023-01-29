#ifdef _WIN32
#include <GL/glut.h>
#elif defined(APPLE)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif*/
#include <iostream>
#include <math.h>
#include <stdlib.h> 
using namespace std;

#define X 0.525731112119133606 
#define Z 0.850650808352039932

static GLfloat ydata[12][3] = {
{-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z}, {0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X }, { 0.0, -Z, -X }, { Z, X, 0.0 }, { -Z, X, 0.0 }, { Z, -X, 0.0 }, { -Z, -X, 0.0 } };

static GLint tindices[20][3] = {
{1,4,0}, {4,9,0}, {4,9,5}, {8,5,4}, {1,8,4},
{1,10,8}, {10,3,8}, {8,3,5}, {3,2,5}, { 3,7,2 },
{3,10,7 }, { 10,6,7}, {6,11,7}, {6,0,11 }, { 6,1,0 },
{ 10,1,6 }, { 11,0,9 }, { 2,11,9 }, { 5,2,9 }, { 11,2,7 }
};

GLfloat color[20][3]; //6 colores R G B
GLfloat elevacion = 0;
GLfloat arco = 0;
GLfloat giro = 0;

GLdouble tx, ty, tz, ang;
GLfloat P0[3] = { 7,0,0 }, P1[3] = { 5,1,0 }, P2[3] = { 15,0,0 }, P3[3] = { 0,4,0 };
float d = 0;
float e = 1;

GLfloat d1[3], d2[3], n[3];
#pragma region Variables Iluminación
GLfloat light_ambient[] = { 0.3,0.3,0.3,1.0 };
GLfloat light_diffuse[] = { 0.3,0.3,0.3,1.0 };
GLfloat light_specular[] = { 0.2,0.2,0.2,1.0 };
GLfloat light_position[] = { -1.0,1.0,-1.0,1.0 };
GLfloat light_direction[] = { -1.0,1.0,-1.0,0.0 };

GLfloat ambient[] = { 0.2 , 0.2 , 0.2 , 1.0 };
GLfloat mat_d[] = { 0.4 , 0.4 , 0.4 , 1.0 };
GLfloat mat_s[] = { 0.2 , 0.2 , 0.4 , 1.0 };
GLfloat low_sh[] = { 5.0 };
GLfloat high_sh[] = { 10.0 };

GLfloat ambient2[] = { 0.2 , 0.2 , 0.2 , 1.0 };
GLfloat mat_d1[] = { 0.8 , -0.8 , 0.8 , 1.0 };
GLfloat mat_s1[] = { 0.4 , -0.4 , 0.8 , 1.0 };
GLfloat low_sh1[] = { 5.0 };
GLfloat high_sh1[] = { 10.0 };

GLfloat ambient3[] = { 0.2 , 0.2 , 0.2 , 1.0 };
GLfloat mat_d2[] = { -0.4 , -0.4 , -0.4 , 1.0 };
GLfloat mat_s2[] = { -0.2 , -0.2 , -0.4 , 1.0 };
GLfloat low_sh2[] = { 5.0 };
GLfloat high_sh2[] = { 10.0 };

//lampara
GLfloat lightPos[] = { 0.0f, 0.0f, 75.0f, 1.0f };
GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat ambient1[] = { 0.4f, 0.4f, 0.4f, 1.0f };
GLfloat spotDir[] = { 0.0f, -1.0f, -1.0f };
#pragma endregion

#pragma region Variable Camara
GLfloat cop_x = 5, cop_y = 5, cop_z = 5;
#pragma endregion

GLint depth = 0;
int op, op2, op3;

void init() {
	//Color de fondo
	glClearColor(0.0, 0.0, 0.0, 0.0);
	//Para que opengl sepa de los vertices
	//Inicializar();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT2, GL_POSITION, light_position);

	glLightfv(GL_LIGHT3, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT3, GL_POSITION, light_position);

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);// GL_FRONT_AND_BACK 
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_s);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_d);

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient2);// GL_FRONT_AND_BACK 
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_s1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_d2);

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient3);// GL_FRONT_AND_BACK 
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_s1);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_d2);
	//glMaterialfv ( GL_FRONT , GL_SHININESS , low_sh ); 
	glMaterialfv(GL_FRONT, GL_SHININESS, high_sh);
	glEnable(GL_COLOR_MATERIAL);

	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.5);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.2);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.1);

	//lampara
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, ambient1);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 60.0f);
	glEnable(GL_LIGHT1);

	switch (op3)
	{
	case 1:
		cout << "Suavizado" << endl;
		glShadeModel(GL_SMOOTH);
		break;
	case 2:
		cout << "Plano" << endl;
		glShadeModel(GL_FLAT);
		break;
	default:
		break;
	}

#pragma region Colores Objeto
	//Para cada cara 1 color
	//Cara # R			//Cara # G			//Cara # B
	color[0][0] = 1;	color[0][1] = 0;	color[0][2] = 0;
	color[1][0] = 0.5;	color[1][1] = 1;	color[1][2] = 1;
	color[2][0] = 1;	color[2][1] = 0;	color[2][2] = 1;
	color[3][0] = 1;	color[3][1] = 0;	color[3][2] = 0;
	color[4][0] = 0.5;	color[4][1] = 1;	color[4][2] = 1;
	color[5][0] = 1;	color[5][1] = 0;	color[5][2] = 1;
	color[6][0] = 1;	color[6][1] = 0;	color[6][2] = 0;
	color[7][0] = 0.5;	color[7][1] = 1;	color[7][2] = 1;
	color[8][0] = 1;	color[8][1] = 0;	color[8][2] = 1;
	color[9][0] = 1;	color[9][1] = 0;	color[9][2] = 0;
	color[10][0] = 0.5;	color[10][1] = 1;	color[10][2] = 1;
	color[11][0] = 1;	color[11][1] = 0;	color[11][2] = 1;
	color[12][0] = 1;	color[12][1] = 0;	color[12][2] = 0;
	color[13][0] = 0.5;	color[13][1] = 1;	color[13][2] = 1;
	color[14][0] = 1;	color[14][1] = 0;	color[14][2] = 1;
	color[15][0] = 1;	color[15][1] = 0;	color[15][2] = 0;
	color[16][0] = 0.5;	color[16][1] = 1;	color[16][2] = 1;
	color[17][0] = 1;	color[17][1] = 0;	color[17][2] = 1;
	color[18][0] = 1;	color[18][1] = 0;	color[18][2] = 0;
	color[19][0] = 0.5;	color[19][1] = 1;	color[19][2] = 1;
	//color[20][0] = 0.5;	color[20][1] = 0.5;	color[20][2] = 0.5;
#pragma endregion
}

void normalize(float y[3]) {
	GLfloat d = sqrt(y[0] * y[0] + y[1] * y[1] + y[2] * y[2]);
	y[0] /= d;
	y[1] /= d;
	y[2] /= d;
}

void normCrossProd(float u[3], float y[3], float out[3]) {
	out[0] = u[1] * y[2] - u[2] * y[1];
	out[1] = u[2] * y[0] - u[0] * y[2];
	out[2] = u[0] * y[1] - u[1] * y[0];
	normalize(out);
}

void timer(int id) {//Esta función va actualizando la pantalla
	if (d <= 1)
	{
		tx += 0.01;
		//Para y
		ty += 0.01;
		//Para z
		tz += 0.01;
		ang += 1;
		d += 0.005;
		glutPostRedisplay();
		glutTimerFunc(10, timer, 1);
		glFlush();
	}
}

void timer2(int id) {//Esta función va actualizando la pantalla
	if (d >= 0)
	{
		tx -= 0.01;
		//Para y
		ty -= 0.01;
		//Para z
		tz -= 0.01;
		ang -= 1;
		d -= 0.005;
		glutPostRedisplay();
		glutTimerFunc(20, timer2, 1);
		glFlush();
	}
}

void icoNormVec(int i) {
	for (int k = 0; k < 3; k++) {
		d1[k] = ydata[tindices[i][0]][k] - ydata[tindices[i][1]][k];
		d2[k] = ydata[tindices[i][1]][k] - ydata[tindices[i][2]][k];
	}
	normCrossProd(d1, d2, n);
	glNormal3fv(n);
}

/// //

void drawTriangle(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3]) {
	for (int i = 0; i < 20; i++) {
		glBegin(GL_TRIANGLES);
		//glColor3f(1, 0, 0);
		glColor3fv(&color[i][0]);
		icoNormVec(0);
		glVertex3fv(&ydata[tindices[i][0]][0]);
		glVertex3fv(&ydata[tindices[i][1]][0]);
		glVertex3fv(&ydata[tindices[i][2]][0]);
		glEnd();
	}
}

void subdivide(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3], int depth)
{
	GLfloat v12[3], v23[3], v31[3];
	int i;
	if (depth == 0) {
		drawTriangle(v1, v2, v3);
	}
	else {
		for (i = 0; i < 3; i++) {
			v12[i] = (v1[i] + v2[i]) / 2;
			v23[i] = (v2[i] + v3[i]) / 2;
			v31[i] = (v3[i] + v1[i]) / 2;
		}
		subdivide(v1, v12, v31, depth - 1);
		subdivide(v2, v23, v12, depth - 1);
		subdivide(v3, v31, v23, depth - 1);
		subdivide(v12, v23, v31, depth - 1);
		normalize(v12);
		normalize(v23);
		normalize(v31);
	}
}

void Rotacion(GLfloat distancia, GLfloat giro, GLfloat elevacion, GLfloat arco)
{
	glTranslated(0.0, 0.0, -distancia);
	glRotated(-giro, 0.0, 0.0, 1.0);
	glRotated(-elevacion, 1.0, 0.0, 0.0);
	glRotated(arco, 0.0, 0.0, 1.0);
}

void teclado(unsigned char op, int x, int y)
{
	switch (op) {
		//Mayusculas giro horario, x y z representan el eje de giro
	case 'X':
		elevacion = elevacion + 10.0f;
		glutPostRedisplay();
		break;
	case 'Y':
		arco = arco + 10.0f;
		glutPostRedisplay();
		break;
	case 'Z':
		giro = giro + 10.0f;
		glutPostRedisplay();
		break;
		//Minusculas giro anti-horario, x y z representan el eje de giro
	case 'x':
		elevacion = elevacion - 10.0f;
		glutPostRedisplay();
		break;
	case 'y':
		arco = arco - 10.0f;
		glutPostRedisplay();
		break;
	case 'z':
		giro = giro - 10.0f;
		glutPostRedisplay();
		break;
	}
}
//Funcion para rotar las cosas en pantalla
void iniciarRot()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW_MATRIX);
	glLoadIdentity();
	Rotacion(20, giro, elevacion, arco);
}

void reshape(int w, int h)// para matriz de visualisacion
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (float)w / (float)h, 1.0, 300.0);
	glFlush();
}

void display() {
	//gluLookAt(cop_x, cop_y, cop_z, 0.0, 0.0, 0.0, -10.0, 0.0, -5.0);
	glClearColor(0, 0, 0.2, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	iniciarRot();
	switch (op2) {
	case 1:
		for (int i = 0; i < 20; i++) {
			glBegin(GL_TRIANGLES);
			//glColor3f(1, 0, 0);
			glColor3fv(&color[i][0]);
			icoNormVec(i);
			glVertex3fv(&ydata[tindices[i][0]][0]);
			glVertex3fv(&ydata[tindices[i][1]][0]);
			glVertex3fv(&ydata[tindices[i][2]][0]);
			glEnd();
		}
		glFlush();
		break;
	case 2:
		for (int i = 0; i < 20; i++) {
			glBegin(GL_TRIANGLES);
			glColor3fv(&color[i][0]);
			glNormal3fv(&ydata[tindices[i][0]][0]);
			glVertex3fv(&ydata[tindices[i][0]][0]);

			glNormal3fv(&ydata[tindices[i][1]][0]);
			glVertex3fv(&ydata[tindices[i][1]][0]);

			glNormal3fv(&ydata[tindices[i][2]][0]);
			glVertex3fv(&ydata[tindices[i][2]][0]);
			glEnd();
		}
		glFlush();
		break;
	case 3:
		for (int i = 0; i < 20; i++) {
			subdivide(&ydata[tindices[i][0]][0], &ydata[tindices[i][1]][0], &ydata[tindices[i][2]][0], depth);
		}
		glFlush();
		break;
	case 4:
		glTranslatef(tx, ty, tz);
		glRotatef(ang, tx, ty, tz);
		glScaled(tx, ty, tz);
		for (int i = 0; i < 20; i++) {
			glBegin(GL_TRIANGLES);
			//glColor3f(1, 0, 0);
			glColor3fv(&color[i][0]);
			icoNormVec(i);
			glVertex3fv(&ydata[tindices[i][0]][0]);
			glVertex3fv(&ydata[tindices[i][1]][0]);
			glVertex3fv(&ydata[tindices[i][2]][0]);
			glEnd();
		}
		glFlush();
		break;
	}
}

int main(int argc, char** argv) {
	cout << "Elija una opcion" << endl;
	cout << "1. Ico sphere 1 version" << endl;
	cout << "2. Ico sphere 2 version" << endl;
	cout << "3. Sub Divisiones" << endl;
	cout << "4. Movimiento de la ico sphere" << endl;
	cin >> op;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(700, 700);
	glutInitWindowPosition(100, 100);
	glutCreateWindow(argv[0]);
	glutTimerFunc(1, timer, 1);
	glutTimerFunc(2, timer2, 1);
	init();
	switch (op) {
	case 1:
		cout << "Elija una opcion" << endl;
		cout << "1. Suavizado" << endl;
		cout << "2. Plano" << endl;
		cin >> op3;
		op2 = op;
		display();
		break;
	case 2:
		cout << "Elija una opcion" << endl;
		cout << "1. Suavizado" << endl;
		cout << "2. Plano" << endl;
		cin >> op3;
		op2 = op;
		display();
		break;
	case 3:
		cout << "Escriba un numero de 1 a 4" << endl;
		cin >> depth;
		op2 = op;
		display();
		break;
	case 4:
		op2 = op;
		display();
		break;
	default:
		break;
	}
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(teclado);
	glutMainLoop();
	return 0;
}