#include "GL/freeglut.h"         //OpenGL��ͷ�ļ�Includ˳��ᵼ�³��ֱ������
#include"HandModel.h"
#include <tchar.h>
#include<ctime>

struct Control {
	int x;
	int y;
	bool mouse_click;
	GLfloat rotx;
	GLfloat roty;
	double gx;
	double gy;
	double gz;

	Control() :x(0), y(0), rotx(0.0), roty(0.0), mouse_click(false),
		gx(0), gy(0), gz(0) {

	}
};
Control control;
HandModel *handmodel = new HandModel();
bool show_mesh = true;
clock_t  Begin, End;
double duration;

//�����ڴ����ض���
HANDLE hMapFile;
LPCTSTR pBuf;
#define BUF_SIZE 1024
TCHAR szName[] = TEXT("Global\\MyFileMappingObject");    //ָ��ͬһ�鹲���ڴ������
float *GetSharedMemeryPtr;
float *GetGloveData = new float[26];

bool move_to_target = false;

#pragma region OpenGL
void light() {
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	// ����̫����Դ������һ�ְ�ɫ�Ĺ�Դ  
	GLfloat sun_light_position[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat sun_light_ambient[] = { 0.25f, 0.25f, 0.15f, 1.0f };
	GLfloat sun_light_diffuse[] = { 0.7f, 0.7f, 0.55f, 1.0f };
	GLfloat sun_light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, sun_light_position); //ָ����0�Ź�Դ��λ��   
	glLightfv(GL_LIGHT0, GL_AMBIENT, sun_light_ambient); //GL_AMBIENT��ʾ���ֹ������䵽�ò����ϣ�  
														 //�����ܶ�η�������������ڻ����еĹ���ǿ�ȣ���ɫ��  
	glLightfv(GL_LIGHT0, GL_DIFFUSE, sun_light_diffuse); //�������~~  
	glLightfv(GL_LIGHT0, GL_SPECULAR, sun_light_specular);//���淴���~~~  

	glEnable(GL_LIGHT0); //ʹ�õ�0�Ź���   
}
/* executed when a regular key is pressed */
void keyboardDown(unsigned char key, int x, int y) {

	switch (key) {
	case  27:   // ESC
		exit(0);
	case 'm':
		show_mesh = !show_mesh;
		break;
	case 's':
		handmodel->save_target_joints();
		break;
	case 'b':
		move_to_target = !move_to_target;
		break;
	}
}

/* reshaped window */
void reshape(int width, int height) {

	GLfloat fieldOfView = 90.0f;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fieldOfView, (GLfloat)width / (GLfloat)height, 0.1, 500.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/* executed when button 'button' is put into state 'state' at screen position ('x', 'y') */
void mouseClick(int button, int state, int x, int y) {
	control.mouse_click = 1;
	control.x = x;
	control.y = y;
}

void mouseMotion(int x, int y) {
	control.rotx = (x - control.x)*0.05f;
	control.roty = (y - control.y)*0.05f;

	//cout<< control.rotx <<" " << control.roty << endl;
	glutPostRedisplay();
}

/* render the scene */

void draw_mesh()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	{
		glColor3f(0.4f, 0.8f, 0.3f);
		glBegin(GL_TRIANGLES);
		for (int i = 0; i < handmodel->NumofFaces; ++i)
		{

			glNormal3f(handmodel->Face_normal[i](0), handmodel->Face_normal[i](1), handmodel->Face_normal[i](2));

			glVertex3f(handmodel->vertices_update_(handmodel->FaceIndex(i, 0), 0), handmodel->vertices_update_(handmodel->FaceIndex(i, 0), 1), handmodel->vertices_update_(handmodel->FaceIndex(i, 0), 2));
			glVertex3f(handmodel->vertices_update_(handmodel->FaceIndex(i, 1), 0), handmodel->vertices_update_(handmodel->FaceIndex(i, 1), 1), handmodel->vertices_update_(handmodel->FaceIndex(i, 1), 2));
			glVertex3f(handmodel->vertices_update_(handmodel->FaceIndex(i, 2), 0), handmodel->vertices_update_(handmodel->FaceIndex(i, 2), 1), handmodel->vertices_update_(handmodel->FaceIndex(i, 2), 2));
		}
		glEnd();
	}
}

void draw_WireHand()
{
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	for (int i = 0; i < handmodel->NumofFaces; ++i)
	{
		glLineWidth(1);
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex3f(handmodel->vertices_update_(handmodel->FaceIndex(i, 0), 0), handmodel->vertices_update_(handmodel->FaceIndex(i, 0), 1), handmodel->vertices_update_(handmodel->FaceIndex(i, 0), 2));
		glVertex3f(handmodel->vertices_update_(handmodel->FaceIndex(i, 1), 0), handmodel->vertices_update_(handmodel->FaceIndex(i, 1), 1), handmodel->vertices_update_(handmodel->FaceIndex(i, 1), 2));
		glEnd();

		glLineWidth(1);
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex3f(handmodel->vertices_update_(handmodel->FaceIndex(i, 0), 0), handmodel->vertices_update_(handmodel->FaceIndex(i, 0), 1), handmodel->vertices_update_(handmodel->FaceIndex(i, 0), 2));
		glVertex3f(handmodel->vertices_update_(handmodel->FaceIndex(i, 2), 0), handmodel->vertices_update_(handmodel->FaceIndex(i, 2), 1), handmodel->vertices_update_(handmodel->FaceIndex(i, 2), 2));
		glEnd();

		glLineWidth(1);
		glColor3f(1.0, 0.0, 0.0);
		glBegin(GL_LINES);
		glVertex3f(handmodel->vertices_update_(handmodel->FaceIndex(i, 1), 0), handmodel->vertices_update_(handmodel->FaceIndex(i, 1), 1), handmodel->vertices_update_(handmodel->FaceIndex(i, 1), 2));
		glVertex3f(handmodel->vertices_update_(handmodel->FaceIndex(i, 2), 0), handmodel->vertices_update_(handmodel->FaceIndex(i, 2), 1), handmodel->vertices_update_(handmodel->FaceIndex(i, 2), 2));
		glEnd();
	}
}

void draw_vertex()
{
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3d(1.0, 1.0, 0.0);
	for (int i = 0; i < handmodel->NumofVertices; ++i) {
		glVertex3d(handmodel->vertices_update_(i, 0), handmodel->vertices_update_(i, 1), handmodel->vertices_update_(i, 2));
	}
	glEnd();
}

void draw_skeleton()
{
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	for (int i = 0; i < handmodel->NumofJoints; ++i) {
		//���㿪ʼ 
		glColor3f(1.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(handmodel->Joints[i].CorrespondingPosition(0), handmodel->Joints[i].CorrespondingPosition(1), handmodel->Joints[i].CorrespondingPosition(2));
		glutSolidSphere(3, 31, 10);
		glPopMatrix();
		//���������ʹ��push��popmatrix����Ϊ��֤ÿ���ؽڵ��ƫ�ƶ��������ȫ���������ĵ����ı任��
		int parent_joint_index = handmodel->Joints[i].parent_joint_index;
		//���߿�ʼ  //����wrist��arm��������
		if (parent_joint_index != -1) {
			glLineWidth(5);
			glColor3f(0.0, 1.0, 0);
			glBegin(GL_LINES);
			glVertex3f(handmodel->Joints[i].CorrespondingPosition(0), handmodel->Joints[i].CorrespondingPosition(1), handmodel->Joints[i].CorrespondingPosition(2));
			glVertex3f(handmodel->Joints[parent_joint_index].CorrespondingPosition(0), handmodel->Joints[parent_joint_index].CorrespondingPosition(1), handmodel->Joints[parent_joint_index].CorrespondingPosition(2));
			glEnd();
		}
	}
}

void draw_Coordinate()
{
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	//x
	glLineWidth(5);
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(100, 0, 0);
	glEnd();

	//y
	glLineWidth(5);
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 100, 0);
	glEnd();

	//z
	glLineWidth(5);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 100);
	glEnd();
}

void draw_joint_local_coordinate(int index)
{
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	int scale = 30;

	Vector4 x = handmodel->Joints[index].CorrespondingAxis[0] - handmodel->Joints[index].CorrespondingPosition;
	glLineWidth(2);
	glColor3f(1.0, 0.0, 0);
	glBegin(GL_LINES);
	glVertex3f(handmodel->Joints[index].CorrespondingPosition(0), handmodel->Joints[index].CorrespondingPosition(1), handmodel->Joints[index].CorrespondingPosition(2));
	glVertex3f(handmodel->Joints[index].CorrespondingPosition(0) + scale*x(0), handmodel->Joints[index].CorrespondingPosition(1) + scale * x(1), handmodel->Joints[index].CorrespondingPosition(2) + scale * x(2));
	glEnd();


	Vector4 y = handmodel->Joints[index].CorrespondingAxis[1] - handmodel->Joints[index].CorrespondingPosition;
	glLineWidth(2);
	glColor3f(0.0, 1.0, 0);
	glBegin(GL_LINES);
	glVertex3f(handmodel->Joints[index].CorrespondingPosition(0), handmodel->Joints[index].CorrespondingPosition(1), handmodel->Joints[index].CorrespondingPosition(2));
	glVertex3f(handmodel->Joints[index].CorrespondingPosition(0) + scale * y(0), handmodel->Joints[index].CorrespondingPosition(1) + scale * y(1), handmodel->Joints[index].CorrespondingPosition(2) + scale * y(2));
	glEnd();

	Vector4 z = handmodel->Joints[index].CorrespondingAxis[2] - handmodel->Joints[index].CorrespondingPosition;
	glLineWidth(2);
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINES);
	glVertex3f(handmodel->Joints[index].CorrespondingPosition(0), handmodel->Joints[index].CorrespondingPosition(1), handmodel->Joints[index].CorrespondingPosition(2));
	glVertex3f(handmodel->Joints[index].CorrespondingPosition(0) + scale * z(0), handmodel->Joints[index].CorrespondingPosition(1) + scale * z(1), handmodel->Joints[index].CorrespondingPosition(2) + scale * z(2));
	glEnd();
}

void draw_ALL_joint_coordinate()
{
	for (int i = 0; i<21; ++i)  	draw_joint_local_coordinate(i);
}

void draw_Hand_visible_vertex()
{
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3d(1.0, 0.0, 0.0);
	for (int i = 0; i < handmodel->Visible_vertices.size(); i++) {
		glVertex3d(handmodel->Visible_vertices[i](0), handmodel->Visible_vertices[i](1), handmodel->Visible_vertices[i](2));
	}
	glEnd();
}

void draw_target_difference()
{
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	for (int i = 0; i < handmodel->NumofJoints; ++i) {
		//���㿪ʼ 
		glColor3f(0.0, 1.0, 0.0);
		glPushMatrix();
		glTranslatef(handmodel->Target_joints(i, 0), handmodel->Target_joints(i, 1), handmodel->Target_joints(i, 2));
		glutSolidSphere(3, 31, 10);
		glPopMatrix();
		//���������ʹ��push��popmatrix����Ϊ��֤ÿ���ؽڵ��ƫ�ƶ��������ȫ���������ĵ����ı任��

		//���߿�ʼ  //����wrist��arm��������

		glLineWidth(5);
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);
		glVertex3f(handmodel->Joints[i].CorrespondingPosition(0), handmodel->Joints[i].CorrespondingPosition(1), handmodel->Joints[i].CorrespondingPosition(2));
		glVertex3f(handmodel->Target_joints(i, 0), handmodel->Target_joints(i, 1), handmodel->Target_joints(i, 2));
		glEnd();

	}
}

void draw_Collision()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	for (int i = 0; i < handmodel->Collision_sphere.size(); i++)
	{
		glColor3f(1.0, 0.0, 0.0);
		glPushMatrix();
		glTranslatef(handmodel->Collision_sphere[i].updata_Position(0), handmodel->Collision_sphere[i].updata_Position(1), handmodel->Collision_sphere[i].updata_Position(2));
		glutSolidSphere(handmodel->Collision_sphere[i].updata_radius, 10, 10);
		glPopMatrix();
	}
}

void show_Collision()
{
	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHTING);
	int NUMofCollision = handmodel->Collision_sphere.size();
	for (int i = 0; i < NUMofCollision; ++i)
	{
		for (int j = 0; j < NUMofCollision; ++j)
		{
			if (handmodel->Collision_Judge_Matrix(i, j) == 1)
			{
				glColor3f(1.0, 1.0, 0.0);
				glPushMatrix();
				glTranslatef(handmodel->Collision_sphere[i].updata_Position(0), handmodel->Collision_sphere[i].updata_Position(1), handmodel->Collision_sphere[i].updata_Position(2));
				glutSolidSphere(handmodel->Collision_sphere[i].updata_radius, 10, 10);
				glPopMatrix();

				glColor3f(1.0, 1.0, 0.0);
				glPushMatrix();
				glTranslatef(handmodel->Collision_sphere[j].updata_Position(0), handmodel->Collision_sphere[j].updata_Position(1), handmodel->Collision_sphere[j].updata_Position(2));
				glutSolidSphere(handmodel->Collision_sphere[j].updata_radius, 10, 10);
				glPopMatrix();
			}
		}
	}
}

void draw() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	gluPerspective(180, 1.5, -1000, 1000);
	glLoadIdentity();
	control.gx = handmodel->GlobalPosition(0);
	control.gy = handmodel->GlobalPosition(1);
	control.gz = handmodel->GlobalPosition(2);
	double r = 200;
	double x = r*sin(control.roty)*cos(control.rotx);
	double y = r*sin(control.roty)*sin(control.rotx);
	double z = r*cos(control.roty);
	//cout<< x <<" "<< y <<" " << z<<endl;
	gluLookAt(x + control.gx, y + control.gy, z + control.gz, control.gx, control.gy, control.gz, 0.0, 1.0, 0.0);//��������ʼ�ǿ���-z�ģ�֮��ĽǶ�����global�����ϵ��ӵģ�����Ҫ��

	if (show_mesh)  draw_mesh();
	else draw_WireHand();

	//draw_vertex();
	draw_skeleton();
	draw_Coordinate();
	//draw_ALL_joint_coordinate();
	draw_Collision();
	show_Collision();
	//draw_target_difference();
	//draw_Hand_visible_vertex();

	glFlush();
	glutSwapBuffers();
}

/* executed when program is idle */
void idle() {

	Begin = clock();//��ʼ��ʱ

	if (!move_to_target)
	{
		for (int i = 0; i < 26; ++i)
		{
			GetGloveData[i] = GetSharedMemeryPtr[i];
		}

		handmodel->Updata(GetGloveData);
	}
	else
	{
		handmodel->MoveToJointTarget();
	}
	
	End = clock();//������ʱ
	duration = double(End - Begin) / CLK_TCK;//duration�������к��������

	std::cout << "time is : " << duration * 1000 << std::endl;

	glutPostRedisplay();
}

/* initialize OpenGL settings */
void initGL(int width, int height) {

	reshape(width, height);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	light();
}

#pragma endregion 

int main(int argc, char** argv)
{


#pragma region SharedMemery
	hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,    // use paging file
		NULL,                    // default security
		PAGE_READWRITE,          // read/write access
		0,                       // maximum object size (high-order DWORD)
		BUF_SIZE,                // maximum object size (low-order DWORD)
		szName);                 // name of mapping object

	if (hMapFile == NULL)
	{
		_tprintf(TEXT("Could not create file mapping object (%d).\n"),
			GetLastError());
		return 1;
	}
	pBuf = (LPTSTR)MapViewOfFile(hMapFile,   // handle to map object
		FILE_MAP_ALL_ACCESS, // read/write permission
		0,
		0,
		BUF_SIZE);

	if (pBuf == NULL)
	{
		_tprintf(TEXT("Could not map view of file (%d).\n"),
			GetLastError());

		CloseHandle(hMapFile);

		return 1;
	}

	GetSharedMemeryPtr = (float*)pBuf;
#pragma endregion SharedMemery


#pragma region OpenGL
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Interactron");

	// register glut call backs
	glutKeyboardFunc(keyboardDown);
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMotion);
	glutReshapeFunc(reshape);
	glutDisplayFunc(draw);
	glutIdleFunc(idle);
	glutIgnoreKeyRepeat(true); // ignore keys held down
	initGL(800, 600);

	glutMainLoop();

#pragma endregion

	return 0;
}