#include "GL/freeglut.h"         //OpenGL��ͷ�ļ�Includ˳��ᵼ�³��ֱ������
#include"HandModel.h"
#include <tchar.h>
#include<ctime>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/kdtree/kdtree_flann.h>

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

clock_t  Begin, End;
double duration;

//�����ڴ����ض���
HANDLE hMapFile;
LPCTSTR pBuf;
#define BUF_SIZE 1024
TCHAR szName[] = TEXT("Global\\MyFileMappingObject");    //ָ��ͬһ�鹲���ڴ������
float *GetSharedMemeryPtr;
float *GetGloveData = new float[27];

pcl::PointCloud<pcl::PointXYZ>::Ptr Handmodel_visible_cloud(new pcl::PointCloud<pcl::PointXYZ>);
pcl::PointCloud<pcl::PointXYZ>::Ptr Kinect_visible_cloud(new pcl::PointCloud<pcl::PointXYZ>);
std::vector<int> cloud_correspond;
void load_handmodel_visible_cloud(pcl::PointCloud<pcl::PointXYZ>& cloud, HandModel &hm)
{
	cloud.points.clear();
	for (int i = 0; i < hm.Visible_vertices.size(); i++)
	{
		pcl::PointXYZ p;
		p.x = hm.Visible_vertices[i](0);
		p.y = hm.Visible_vertices[i](1);
		p.z = hm.Visible_vertices[i](2);
		cloud.points.push_back(p);
	}
}
void load_visible_cloud(pcl::PointCloud<pcl::PointXYZ>& cloud, HandModel &hm)
{
	cloud.points.clear();
	for (int i = 0; i < hm.Load_visible_vertices_NUM; i++)
	{
		pcl::PointXYZ p;
		p.x = hm.Load_visible_vertices(i,0);
		p.y = hm.Load_visible_vertices(i,1);
		p.z = hm.Load_visible_vertices(i,2);
		cloud.points.push_back(p);
	}
}
void find_correspondences(std::vector<int> & correspondences_out)
{
	correspondences_out.resize(Kinect_visible_cloud->points.size());

	pcl::KdTreeFLANN<pcl::PointXYZ> search_kdtree;
	search_kdtree.setInputCloud(Handmodel_visible_cloud);

	const int k = 1;
	std::vector<int> k_indices(k);
	std::vector<float> k_squared_distances(k);
	for (size_t i = 0; i < Kinect_visible_cloud->points.size(); ++i)
	{
		search_kdtree.nearestKSearch(*Kinect_visible_cloud, i, k, k_indices, k_squared_distances);
		correspondences_out[i] = k_indices[0];
	}
}
#pragma region OpenGL
/* executed when a regular key is pressed */
void keyboardDown(unsigned char key, int x, int y) {

	switch (key) {
	case  27:   // ESC
		exit(0);
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

/* executed when the mouse moves to position ('x', 'y') */
/* render the scene */
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



	///* render the scene here */
	//{
	//	glPointSize(2);
	//	glBegin(GL_POINTS);
	//	glColor3d(1.0, 0.0, 0.0);
	//	for (int i = 0; i < handmodel->NumofVertices; i++) {
	//		glVertex3d(handmodel->vertices_update_(i, 0), handmodel->vertices_update_(i, 1), handmodel->vertices_update_(i, 2));
	//	}
	//	glEnd();


	//	glPointSize(2);
	//	glBegin(GL_POINTS);
	//	glColor3d(0.0, 1.0, 0.0);
	//	for (int i = 0; i < handmodel->NumofVertices; i++) {
	//		glVertex3d(handmodel->Target_vertices(i, 0), handmodel->Target_vertices(i, 1), handmodel->Target_vertices(i, 2));
	//	}
	//	glEnd();


	//	for (int i = 0; i < handmodel->NumofVertices; i = i+10) {
	//		glVertex3d(handmodel->Target_vertices(i, 0), handmodel->Target_vertices(i, 1), handmodel->Target_vertices(i, 2));
	//		glLineWidth(1);
	//		glColor3f(1.0, 1.0, 1.0);
	//		glBegin(GL_LINES);
	//		glVertex3d(handmodel->Target_vertices(i, 0), handmodel->Target_vertices(i, 1), handmodel->Target_vertices(i, 2));
	//		glVertex3d(handmodel->vertices_update_(i, 0), handmodel->vertices_update_(i, 1), handmodel->vertices_update_(i, 2));
	//		glEnd();
	//	}
	//}


	//for (int i = 0; i < handmodel->NumofJoints; i++) {
	//	//���㿪ʼ 
	//	glColor3f(1.0, 0.0, 0.0);
	//	glPushMatrix();
	//	glTranslatef(handmodel->Joints[i].CorrespondingPosition(0), handmodel->Joints[i].CorrespondingPosition(1), handmodel->Joints[i].CorrespondingPosition(2));
	//	glutSolidSphere(5, 31, 10);
	//	glPopMatrix();

	//	//���������ʹ��push��popmatrix����Ϊ��֤ÿ���ؽڵ��ƫ�ƶ��������ȫ���������ĵ����ı任��

	//	int parent_joint_index = handmodel->Joints[i].parent_joint_index;
	//	//���߿�ʼ  //����wrist��arm��������
	//	if (parent_joint_index != -1) {
	//		glLineWidth(5);
	//		glColor3f(0.0, 1.0, 0);
	//		glBegin(GL_LINES);
	//		glVertex3f(handmodel->Joints[i].CorrespondingPosition(0), handmodel->Joints[i].CorrespondingPosition(1), handmodel->Joints[i].CorrespondingPosition(2));
	//		glVertex3f(handmodel->Joints[parent_joint_index].CorrespondingPosition(0), handmodel->Joints[parent_joint_index].CorrespondingPosition(1), handmodel->Joints[parent_joint_index].CorrespondingPosition(2));
	//		glEnd();
	//	}

	//	//glLineWidth(2);
	//	//glColor3f(1.0, 1.0, 1);
	//	//glBegin(GL_LINES);
	//	//glVertex3f(handmodel->Joints[i].CorrespondingPosition(0), handmodel->Joints[i].CorrespondingPosition(1), handmodel->Joints[i].CorrespondingPosition(2));
	//	//glVertex3f(handmodel->Target_joints(i, 0), handmodel->Target_joints(i, 1), handmodel->Target_joints(i, 2));
	//	//glEnd();

	//	//���߽���
	//}


	//for (int i = 0; i < handmodel->NumofJoints; i++) {
	//	//���㿪ʼ 
	//	glColor3f(0.0, 1.0, 0.0);
	//	glPushMatrix();
	//	glTranslatef(handmodel->Target_joints(i,0), handmodel->Target_joints(i,1), handmodel->Target_joints(i,2));
	//	glutSolidSphere(5, 31, 10);
	//	glPopMatrix();

	//	//���������ʹ��push��popmatrix����Ϊ��֤ÿ���ؽڵ��ƫ�ƶ��������ȫ���������ĵ����ı任��
	//}

	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3d(1.0, 0.0, 0.0);
	for (int i = 0; i < handmodel->Visible_vertices.size(); i++) {
		glVertex3d(handmodel->Visible_vertices[i](0), handmodel->Visible_vertices[i](1), handmodel->Visible_vertices[i](2));
	}
	glEnd();

	glPointSize(2);
	glBegin(GL_POINTS);
	glColor3d(1.0, 1.0, 0.0);
	for (int i = 0; i < handmodel->Load_visible_vertices.size(); i++) {
		glVertex3d(handmodel->Load_visible_vertices(i,0), handmodel->Load_visible_vertices(i,1), handmodel->Load_visible_vertices(i,2));
	}
	glEnd();


	glLineWidth(2);
	glColor3f(1.0, 1.0, 1);
	glBegin(GL_LINES);
	for (int i = 0; i < cloud_correspond.size(); i++)
	{
		glVertex3d(Kinect_visible_cloud->points[i].x, Kinect_visible_cloud->points[i].y, Kinect_visible_cloud->points[i].z);
		glVertex3f(Handmodel_visible_cloud->points[cloud_correspond[i]].x, Handmodel_visible_cloud->points[cloud_correspond[i]].y, Handmodel_visible_cloud->points[cloud_correspond[i]].z);
	}
	glEnd();

	glFlush();
	glutSwapBuffers();
}


void mouseMotion(int x, int y) {
	control.rotx = (x - control.x)*0.05f;
	control.roty = (y - control.y)*0.05f;

	//cout<< control.rotx <<" " << control.roty << endl;
	glutPostRedisplay();
}

/* executed when program is idle */
void idle() {

	Begin = clock();//��ʼ��ʱ
	for (int i = 0; i < 27; i++)
	{
		GetGloveData[i] = GetSharedMemeryPtr[i];
	}
	GetGloveData[16] = -GetGloveData[16];
	GetGloveData[17] = -GetGloveData[17];
	GetGloveData[18] = -GetGloveData[18];


	//GetGloveData[9] = 90;
	//GetGloveData[0] = 90;
	//GetGloveData[2] = 60;
	//GetGloveData[15] = 30;
	//GetGloveData[16] = -30;
	//GetGloveData[17] = -50;
	//GetGloveData[24] = 20;
	//GetGloveData[25] = 10;
	//GetGloveData[26] = -50;

	//handmodel->Updata(GetGloveData);


	End = clock();//������ʱ
	duration = double(End - Begin) / CLK_TCK;//duration�������к��������

	std::cout << "time is : " << duration*1000 << std::endl;

	//if (!handmodel->Solved)
	//{
	//	handmodel->MoveToVerticeTarget();

	//	for (int i = 0; i < handmodel->NumberofParams; i++)
	//	{
	//		std::cout << handmodel->Params[i] << "  ";
	//	}
	//	std::cout << std::endl << std::endl;
	//}
	glutPostRedisplay();
}

/* initialize OpenGL settings */
void initGL(int width, int height) {

	reshape(width, height);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClearDepth(1.0f);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}

#pragma endregion 

int main(int argc, char** argv)
{

	load_handmodel_visible_cloud(*Handmodel_visible_cloud, *handmodel);
	load_visible_cloud(*Kinect_visible_cloud, *handmodel);
	find_correspondences(cloud_correspond);

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