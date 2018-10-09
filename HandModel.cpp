#include"HandModel.h"
void HandModel::load_faces(char* filename)
{
	std::ifstream f;
	f.open(filename, std::ios::in);
	f >> NumofFaces;
	FaceIndex = Eigen::MatrixXi::Zero(NumofFaces, 3);
	for (int i = 0; i < NumofFaces; ++i) {
		f >> FaceIndex(i, 0) >> FaceIndex(i, 1) >> FaceIndex(i, 2);
	}
	f.close();
	printf("Load Faces succeed!!!\n");
	std::cout << "num of Face is: " << NumofFaces << std::endl;
}

void HandModel::load_vertices(char* filename)
{
	std::ifstream f;
	f.open(filename, std::ios::in);
	f >> NumofVertices;
	Vectices = Eigen::MatrixXf::Zero(NumofVertices, 3);
	Vertices_normal = Eigen::MatrixXf::Zero(NumofVertices, 3);
	for (int i = 0; i < NumofVertices; ++i) {
		f >> Vectices(i, 0) >> Vectices(i, 1) >> Vectices(i, 2);
	}
	f.close();
	printf("Load vertices succeed!!!\n");
	std::cout << "num of vertices is: " << NumofVertices << std::endl;
}

void HandModel::load_weight(char* filename)
{
	std::ifstream f;
	f.open(filename, std::ios::in);
	Weights = Eigen::MatrixXf::Zero(NumofVertices, NumofJoints);
	for (int i = 0; i < NumofVertices; ++i) {
		for (int j = 0; j < NumofJoints; ++j)
		{
			f >> Weights(i, j);
		}
	}
	f.close();
	printf("Load weights succeed!!!\n");
}

HandModel::HandModel()
{
	NumofJoints = 22;
	Joints = new Joint[22];
	//wrist
	{
		Joints[0].joint_name = "Wrist";
		Joints[0].joint_index = 0;
		Joints[0].GlobalInitPosition << 0, 0, 0, 1;
		Joints[0].ChildGlobalInitPosition << 4.74695f, 71.5019f, -12.1453f, 1;
		Joints[0].joint_dof[0] = true; Joints[0].joint_dof[1] = true; Joints[0].joint_dof[2] = true;
		Joints[0].parent_joint_index = -1;

		Joints[0].params_length = 6;
		Joints[0].params_index = new int[6]; Joints[0].params_type = new int[6];
		Joints[0].params_index[0] = 0; Joints[0].params_type[0] = dof_type(x_axis_trans);
		Joints[0].params_index[1] = 1; Joints[0].params_type[1] = dof_type(y_axis_trans);
		Joints[0].params_index[2] = 2; Joints[0].params_type[2] = dof_type(z_axis_trans);
		Joints[0].params_index[3] = 3; Joints[0].params_type[3] = dof_type(x_axis_rotate);
		Joints[0].params_index[4] = 4; Joints[0].params_type[4] = dof_type(y_axis_rotate);
		Joints[0].params_index[5] = 5; Joints[0].params_type[5] = dof_type(z_axis_rotate);
	}

	//handbone
	{
		Joints[1].joint_name = "Handbone";
		Joints[1].joint_index = 1;
		Joints[1].GlobalInitPosition << 4.74695f, 71.5019f, -12.1453f, 1;
		Joints[1].ChildGlobalInitPosition << 9.00001f, 101.267f, -3.93472f, 1;
		Joints[1].joint_dof[0] = false; Joints[1].joint_dof[1] = false; Joints[1].joint_dof[2] = false;
		Joints[1].parent_joint_index = 0;

		Joints[1].params_length = 0;
		Joints[1].params_index = NULL; Joints[1].params_type = NULL;
	}
	//index
	
	{
		{
			Joints[2].joint_name = "IndexLower";
			Joints[2].joint_index = 2;
			Joints[2].GlobalInitPosition << 29.2408f, 96.351f, -3.11671f, 1;
			Joints[2].ChildGlobalInitPosition << 35.6817f, 128.786f, -3.3307f, 1;
			Joints[2].joint_dof[0] = false; Joints[2].joint_dof[1] = true; Joints[2].joint_dof[2] = true;
			Joints[2].params_length = 2;
			Joints[2].params_index = new int[2]; Joints[2].params_type = new int[2];
			Joints[2].params_index[0] = 10; Joints[2].params_type[0] = dof_type(y_axis_rotate);
			Joints[2].params_index[1] = 11; Joints[2].params_type[1] = dof_type(z_axis_rotate);
			Joints[2].parent_joint_index = 1;
		}


		{
			Joints[3].joint_name = "IndexMiddle";
			Joints[3].joint_index = 3;
			Joints[3].GlobalInitPosition << 35.6817f, 128.786f, -3.3307f, 1;
			Joints[3].ChildGlobalInitPosition << 39.1804f, 159.882f, -3.93921f, 1;
			Joints[3].joint_dof[0] = false; Joints[3].joint_dof[1] = true; Joints[3].joint_dof[2] = false;
			Joints[3].params_length = 1;
			Joints[3].params_index = new int[1]; Joints[3].params_type = new int[1];
			Joints[3].params_index[0] = 12; Joints[3].params_type[0] = dof_type(y_axis_rotate);
			Joints[3].parent_joint_index = 2;
		}

		{
			Joints[4].joint_name = "IndexTop";
			Joints[4].joint_index = 4;
			Joints[4].GlobalInitPosition << 39.1804f, 159.882f, -3.93921f, 1;
			Joints[4].ChildGlobalInitPosition << 40.8995f, 178.091f, -5.84128f, 1;
			Joints[4].joint_dof[0] = false; Joints[4].joint_dof[1] = true; Joints[4].joint_dof[2] = false;
			Joints[4].params_length = 1;
			Joints[4].params_index = new int[1]; Joints[4].params_type = new int[1];
			Joints[4].params_index[0] = 13; Joints[4].params_type[0] = dof_type(y_axis_rotate);
			Joints[4].parent_joint_index = 3;
		}

		{
			Joints[5].joint_name = "IndexSite";
			Joints[5].joint_index = 5;
			Joints[5].GlobalInitPosition << 40.8995f, 178.091f, -5.84128f, 1;
			Joints[5].HasChild = false;
			Joints[5].joint_dof[0] = false; Joints[5].joint_dof[1] = false; Joints[5].joint_dof[2] = false;
			Joints[5].params_length = 0;
			Joints[5].params_index = NULL; Joints[5].params_type = NULL;
			Joints[5].parent_joint_index = 4;
		}
	}

	//middle
	{
		{
			Joints[6].joint_name = "MiddleLower";
			Joints[6].joint_index = 6;
			Joints[6].GlobalInitPosition << 9.00001f, 101.267f, -3.93472f, 1;
			Joints[6].ChildGlobalInitPosition << 8.19879f, 138.712f, -5.20814f, 1;
			Joints[6].joint_dof[0] = false; Joints[6].joint_dof[1] = true; Joints[6].joint_dof[2] = false;
			Joints[6].params_length = 2;
			Joints[6].params_index = new int[2]; Joints[6].params_type = new int[2];
			Joints[6].params_index[0] = 14;  Joints[6].params_type[0] = dof_type(y_axis_rotate);
			Joints[6].params_index[1] = 15; Joints[6].params_type[1] = dof_type(z_axis_rotate);
			Joints[6].parent_joint_index = 1;
		}
		{
			Joints[7].joint_name = "MiddleMiddle";
			Joints[7].joint_index = 7;
			Joints[7].GlobalInitPosition << 8.19879f, 138.712f, -5.20814f, 1;
			Joints[7].ChildGlobalInitPosition << 7.12465f, 168.352f, -4.7175f, 1;
			Joints[7].joint_dof[0] = false; Joints[7].joint_dof[1] = true; Joints[7].joint_dof[2] = false;
			Joints[7].params_length = 1;
			Joints[7].params_index = new int[1]; Joints[7].params_type = new int[1];
			Joints[7].params_index[0] = 16; Joints[7].params_type[0] = dof_type(y_axis_rotate);
			Joints[7].parent_joint_index = 6;
		}

		{
			Joints[8].joint_name = "MiddleTop";
			Joints[8].joint_index = 8;
			Joints[8].GlobalInitPosition << 7.12465f, 168.352f, -4.7175f, 1;
			Joints[8].ChildGlobalInitPosition << 6.95019f, 185.733f, -7.207f, 1;
			Joints[8].joint_dof[0] = false; Joints[8].joint_dof[1] = true; Joints[8].joint_dof[2] = false;
			Joints[8].params_length = 1;
			Joints[8].params_index = new int[1]; Joints[8].params_type = new int[1];
			Joints[8].params_index[0] = 17; Joints[8].params_type[0] = dof_type(y_axis_rotate);
			Joints[8].parent_joint_index = 7;
		}

		{
			Joints[9].joint_name = "MiddleSite";
			Joints[9].joint_index = 9;
			Joints[9].GlobalInitPosition << 6.95019f, 185.733f, -7.207f, 1;
			Joints[9].HasChild = false;
			Joints[9].joint_dof[0] = false; Joints[9].joint_dof[1] = false; Joints[9].joint_dof[2] = false;
			Joints[9].params_length = 0;
			Joints[9].params_index = NULL; Joints[9].params_type = NULL;
			Joints[9].parent_joint_index = 8;
		}
	}
	//Pinkey
	{
		{
			Joints[10].joint_name = "PinkeyLower";
			Joints[10].joint_index = 10;
			Joints[10].GlobalInitPosition << -28.85f, 86.4131f, -0.163318f, 1;
			Joints[10].ChildGlobalInitPosition << -40.1235f, 115.175f, 0.380951f, 1;
			Joints[10].joint_dof[0] = false; Joints[10].joint_dof[1] = true; Joints[10].joint_dof[2] = true;
			Joints[10].params_length = 2;
			Joints[10].params_index = new int[2]; Joints[10].params_type = new int[2];
			Joints[10].params_index[0] = 22; Joints[10].params_type[0] = dof_type(y_axis_rotate);
			Joints[10].params_index[1] = 23; Joints[10].params_type[1] = dof_type(z_axis_rotate);
			Joints[10].parent_joint_index = 1;
		}
		{
			Joints[11].joint_name = "PinkeyMiddle";
			Joints[11].joint_index = 11;
			Joints[11].GlobalInitPosition << -40.1235f, 115.175f, 0.380951f, 1;
			Joints[11].ChildGlobalInitPosition << -49.0937f, 136.986f, -0.0051192f, 1;
			Joints[11].joint_dof[0] = false; Joints[11].joint_dof[1] = true; Joints[11].joint_dof[2] = false;
			Joints[11].params_length = 1;
			Joints[11].params_index = new int[1]; Joints[11].params_type = new int[1];
			Joints[11].params_index[0] = 24; Joints[11].params_type[0] = dof_type(y_axis_rotate);
			Joints[11].parent_joint_index = 10;
		}

		{
			Joints[12].joint_name = "PinkeyTop";
			Joints[12].joint_index = 12;
			Joints[12].GlobalInitPosition << -49.0937f, 136.986f, -0.0051192f, 1;
			Joints[12].ChildGlobalInitPosition << -55.3593f, 151.231f, -0.197348f, 1;
			Joints[12].joint_dof[0] = false; Joints[12].joint_dof[1] = true; Joints[12].joint_dof[2] = false;
			Joints[12].params_length = 1;
			Joints[12].params_index = new int[1]; Joints[12].params_type = new int[1];
			Joints[12].params_index[0] = 25; Joints[12].params_type[0] = dof_type(y_axis_rotate);
			Joints[12].parent_joint_index = 11;
		}

		{
			Joints[13].joint_name = "PinkeySite";
			Joints[13].joint_index = 13;
			Joints[13].GlobalInitPosition << -55.3593f, 151.231f, -0.197348f, 1;
			Joints[13].HasChild = false;
			Joints[13].joint_dof[0] = false; Joints[13].joint_dof[1] = false; Joints[13].joint_dof[2] = false;
			Joints[13].params_length = 0;
			Joints[13].params_index = NULL; Joints[13].params_type = NULL;
			Joints[13].parent_joint_index = 12;
		}
	}

	//ring
	{
		{
			Joints[14].joint_name = "RingLower";
			Joints[14].joint_index = 14;
			Joints[14].GlobalInitPosition << -11.2335f, 96.4782f, -3.66419f, 1;
			Joints[14].ChildGlobalInitPosition << -16.3215f, 130.53f, -7.34456f, 1;
			Joints[14].joint_dof[0] = false; Joints[14].joint_dof[1] = true; Joints[14].joint_dof[2] = true;
			Joints[14].params_length = 2;
			Joints[14].params_index = new int[2]; Joints[14].params_type = new int[2];
			Joints[14].params_index[0] = 18; Joints[14].params_type[0] = dof_type(y_axis_rotate);
			Joints[14].params_index[1] = 19; Joints[14].params_type[1] = dof_type(z_axis_rotate);
			Joints[14].parent_joint_index = 1;
		}

		{
			Joints[15].joint_name = "RingMiddle";
			Joints[15].joint_index = 15;
			Joints[15].GlobalInitPosition << -16.3215f, 130.53f, -7.34456f, 1;
			Joints[15].ChildGlobalInitPosition << -21.4588f, 160.548f, -8.54878f, 1;
			Joints[15].joint_dof[0] = false; Joints[15].joint_dof[1] = true; Joints[15].joint_dof[2] = false;
			Joints[15].params_length = 1;
			Joints[15].params_index = new int[1]; Joints[15].params_type = new int[0];
			Joints[15].params_index[0] = 20;  Joints[15].params_type[0] = dof_type(y_axis_rotate);
			Joints[15].parent_joint_index = 14;
		}

		{
			Joints[16].joint_name = "RingTop";
			Joints[16].joint_index = 16;
			Joints[16].GlobalInitPosition << -21.4588f, 160.548f, -8.54878f, 1;
			Joints[16].ChildGlobalInitPosition << -23.8667f, 178.005f, -9.97166f, 1;
			Joints[16].joint_dof[0] = false; Joints[16].joint_dof[1] = true; Joints[16].joint_dof[2] = false;
			Joints[16].params_length = 1;
			Joints[16].params_index = new int[1]; Joints[16].params_type = new int[1];
			Joints[16].params_index[0] = 21; Joints[16].params_type[0] = dof_type(y_axis_rotate);
			Joints[16].parent_joint_index = 15;
		}

		{
			Joints[17].joint_name = "RingSite";
			Joints[17].joint_index = 17;
			Joints[17].GlobalInitPosition << -23.8667f, 178.005f, -9.97166f, 1;
			Joints[17].HasChild = false;
			Joints[17].joint_dof[0] = false; Joints[17].joint_dof[1] = false; Joints[17].joint_dof[2] = false;
			Joints[17].params_length = 0;
			Joints[17].params_index = NULL; Joints[17].params_type = NULL;
			Joints[17].parent_joint_index = 16;
		}
	}

	//thumb

	{
		{
			Joints[18].joint_name = "ThumbLower";
			Joints[18].joint_index = 18;
			Joints[18].GlobalInitPosition << 42.7179f, 28.8392f, -1.60427f, 1;
			Joints[18].ChildGlobalInitPosition << 59.2979f, 56.6487f, 1.57589f, 1;
			Joints[18].joint_dof[0] = true; Joints[18].joint_dof[1] = true; Joints[18].joint_dof[2] = true;
			Joints[18].params_length = 2;
			Joints[18].params_index = new int[2];  Joints[18].params_type = new int[2];
			Joints[18].params_index[0] = 6; Joints[18].params_type[0] = dof_type(y_axis_rotate);
			Joints[18].params_index[1] = 7; Joints[18].params_type[1] = dof_type(z_axis_rotate);
			Joints[18].parent_joint_index = 1;
		}
		{
			Joints[19].joint_name = "ThumbMiddle";
			Joints[19].joint_index = 19;
			Joints[19].GlobalInitPosition << 59.2979f, 56.6487f, 1.57589f, 1;
			Joints[19].ChildGlobalInitPosition << 81.6844f,  85.0783f,  3.81609f, 1;
			Joints[19].joint_dof[0] = false; Joints[19].joint_dof[1] = true; Joints[19].joint_dof[2] = false;
			Joints[19].params_length = 1;
			Joints[19].params_index = new int[1]; Joints[19].params_type = new int[1];
			Joints[19].params_index[0] = 8; Joints[19].params_type[0] = dof_type(z_axis_rotate);
			Joints[19].parent_joint_index = 18;
		}

		{
			Joints[20].joint_name = "ThumbTop";
			Joints[20].joint_index = 20;
			Joints[20].GlobalInitPosition << 81.6844f, 85.0783f, 3.81609f, 1;
			Joints[20].ChildGlobalInitPosition << 95.188f,  99.7447f,  8.79695f, 1;
			Joints[20].joint_dof[0] = false; Joints[20].joint_dof[1] = true; Joints[20].joint_dof[2] = false;
			Joints[20].params_length = 1;
			Joints[20].params_index = new int[1]; Joints[20].params_type = new int[1];
			Joints[20].params_index[0] = 9; Joints[20].params_type[0] = dof_type(z_axis_rotate);
			Joints[20].parent_joint_index = 19;
		}

		{
			Joints[21].joint_name = "ThumbSite";
			Joints[21].joint_index = 21;
			Joints[21].GlobalInitPosition << 95.188f, 99.7447f, 8.79695f, 1;
			Joints[21].HasChild = false;
			Joints[21].joint_dof[0] = false; Joints[21].joint_dof[1] = false; Joints[21].joint_dof[2] = false;
			Joints[21].params_length = 0;
			Joints[21].params_index = NULL; Joints[21].params_type = NULL;
			Joints[21].parent_joint_index = 20;
		}
	}

	GlobalPosition << 0, 0, 0, 0;

	load_vertices(".\\model\\new_new_vertes.txt");
	load_faces(".\\model\\newFaces.txt");
	load_weight(".\\model\\newWeights.txt");

	//Params对应关系
	//       0       ------>    wrist_T_x    //全局平移
	//       1       ------>    wrist_T_y    //全局平移
	//       2       ------>    wrist_T_z    //全局平移
	//       3       ------>    wrist_R_x
	//       4       ------>    wrist_R_y
	//       5       ------>    wrist_R_z
	//       6       ------>    Thumb_Low_R_y
	//       7       ------>    Thumb_Low_R_z
	//       8       ------>    Thumb_mid_R_z    //这里注意了，是z不是y了
	//       9       ------>    Thumb_top_R_z    //这里注意了，是z不是y了
	//       10      ------>    Index_Low_R_y
	//       11      ------>    Index_Low_R_z
	//       12      ------>    Index_mid_R_y
	//       13      ------>    Index_top_R_y
	//       14      ------>    Middle_Low_R_y
	//       15      ------>    Middle_Low_R_z
	//       16      ------>    Middle_mid_R_y
	//       17      ------>    Middle_top_R_y
	//       18      ------>    Ring_Low_R_y
	//       19      ------>    Ring_Low_R_z
	//       20      ------>    Ring_mid_R_y
	//       21      ------>    Ring_top_R_y
	//       22      ------>    Pinkey_Low_R_y
	//       23      ------>    Pinkey_Low_R_z
	//       24      ------>    Pinkey_mid_R_y
	//       25      ------>    Pinkey_top_R_y
	NumberofParams = 26;
	Params = new float[26]();
	ParamsUpperBound = new int[26]();
	ParamsLowerBound = new int[26]();


	//Scale对应关系
	//       0      ------>    整体变长
	//       1      ------>    整体变宽
	//       2      ------>    整体变厚
	Hand_scale << 1, 1, 1;

	//Jacobain related 
	Joints_jacobian = Eigen::MatrixXf::Zero(NumofJoints * 3, NumberofParams);
	Solved = false;


	compute_local_coordinate();
	compute_parent_child_transform();
	Updata(Params);
}

void HandModel::set_one_rotation(const Pose& pose, int index)
{
	Eigen::MatrixXf x = Eigen::MatrixXf::Identity(4, 4);
	Eigen::MatrixXf y = Eigen::MatrixXf::Identity(4, 4);
	Eigen::MatrixXf z = Eigen::MatrixXf::Identity(4, 4);

	float cx = cos(pose.x / 180 * PI);
	float sx = sin(pose.x / 180 * PI);

	float cy = cos(pose.y / 180 * PI);
	float sy = sin(pose.y / 180 * PI);

	float cz = cos(pose.z / 180 * PI);
	float sz = sin(pose.z / 180 * PI);

	x(1, 1) = cx; x(2, 2) = cx;
	x(1, 2) = -sx; x(2, 1) = sx;

	y(0, 0) = cy; y(0, 2) = sy;
	y(2, 0) = -sy; y(2, 2) = cy;

	z(0, 0) = cz; z(1, 1) = cz;
	z(0, 1) = -sz; z(1, 0) = sz;

	if (index == 0)
	{
		Joints[index].rotation = y*x*z;
	}
	else
	{
		if (index == 18)
		{
			Joints[index].rotation = x*z*y;
		}
		else
		{
			Joints[index].rotation = x*y*z;
		}
	}

}

void HandModel::compute_local_coordinate() {

	float axisx[3] = { 0.0f,0.0f,0.0f };
	float axisy[3] = { 0.0f,0.0f,0.0f };
	float axisz[3] = { 0.0f,0.0f,1.0f };

	for (int i = 0; i < NumofJoints; ++i)
	{
		if (Joints[i].HasChild)
		{

			axisz[0] = 0.0f; axisz[1] = 0.0f; axisz[2] = 1.0f;

			float position[3] = { Joints[i].GlobalInitPosition(0) ,Joints[i].GlobalInitPosition(1) ,Joints[i].GlobalInitPosition(2) };

			axisx[0] = Joints[i].ChildGlobalInitPosition(0) - Joints[i].GlobalInitPosition(0);
			axisx[1] = Joints[i].ChildGlobalInitPosition(1) - Joints[i].GlobalInitPosition(1);
			axisx[2] = Joints[i].ChildGlobalInitPosition(2) - Joints[i].GlobalInitPosition(2);

			normalize(axisx);
			cross_product(axisx, axisz, axisy);
			normalize(axisy);
			cross_product(axisx, axisy, axisz);
			normalize(axisz);

			Joints[i].local = Eigen::MatrixXf::Zero(4, 4);

			Joints[i].local(0, 0) = axisx[0]; Joints[i].local(1, 0) = axisx[1]; Joints[i].local(2, 0) = axisx[2];
			Joints[i].local(0, 1) = axisy[0]; Joints[i].local(1, 1) = axisy[1]; Joints[i].local(2, 1) = axisy[2];
			Joints[i].local(0, 2) = axisz[0]; Joints[i].local(1, 2) = axisz[1]; Joints[i].local(2, 2) = axisz[2];
			Joints[i].local(0, 3) = position[0]; Joints[i].local(1, 3) = position[1]; Joints[i].local(2, 3) = position[2];
			Joints[i].local(3, 3) = 1.0;
		}
		else
		{
			float position[3] = { Joints[i].GlobalInitPosition(0) ,Joints[i].GlobalInitPosition(1) ,Joints[i].GlobalInitPosition(2) };
			int parent_index = Joints[i].parent_joint_index;
			Joints[i].local = Joints[parent_index].local;
			Joints[i].local(0, 3) = position[0]; Joints[i].local(1, 3) = position[1]; Joints[i].local(2, 3) = position[2];
		}
	}
}

void HandModel::compute_parent_child_transform()
{
	for (int i = 0; i < NumofJoints; ++i)
	{
		int parent_joint_index = Joints[i].parent_joint_index;
		if (parent_joint_index != -1)
		{
			Joints[i].trans = Joints[parent_joint_index].local.inverse()*Joints[i].local;
		}
		else
		{
			Joints[i].trans = Joints[i].local;
		}
	}
}

void HandModel::compute_rotation_matrix(float* params)
{

	//Params对应关系
	//       0       ------>    wrist_T_x    //全局平移
	//       1       ------>    wrist_T_y    //全局平移
	//       2       ------>    wrist_T_z    //全局平移
	//       3       ------>    wrist_R_x
	//       4       ------>    wrist_R_y
	//       5       ------>    wrist_R_z
	//       6       ------>    Thumb_Low_R_y
	//       7       ------>    Thumb_Low_R_z
	//       8       ------>    Thumb_mid_R_y    //这里注意了，是z不是y了
	//       9       ------>    Thumb_top_R_y    //这里注意了，是z不是y了
	//       10      ------>    Index_Low_R_y
	//       11      ------>    Index_Low_R_z
	//       12      ------>    Index_mid_R_y
	//       13      ------>    Index_top_R_y
	//       14      ------>    Middle_Low_R_y
	//       15      ------>    Middle_Low_R_z
	//       16      ------>    Middle_mid_R_y
	//       17      ------>    Middle_top_R_y
	//       18      ------>    Ring_Low_R_y
	//       19      ------>    Ring_Low_R_z
	//       20      ------>    Ring_mid_R_y
	//       21      ------>    Ring_top_R_y
	//       22      ------>    Pinkey_Low_R_y
	//       23      ------>    Pinkey_Low_R_z
	//       24      ------>    Pinkey_mid_R_y
	//       25      ------>    Pinkey_top_R_y

	GlobalPosition(0) = params[0];
	GlobalPosition(1) = params[1];
	GlobalPosition(2) = params[2];
	GlobalPosition(3) = 1;

	Pose p_wrist(params[3], params[4], params[5]);
	set_one_rotation(p_wrist, 0);

	//thumb
	Pose p_thumb_lower(0, params[6], params[7]);
	Pose p_thumb_middle(0, 0, params[8]);    //这里注意了，是z不是y了
	Pose p_thumb_top(0, 0, params[9]);      //这里注意了，是z不是y了
	set_one_rotation(p_thumb_lower, 18);
	set_one_rotation(p_thumb_middle, 19);
	set_one_rotation(p_thumb_top, 20);

	//index
	Pose p_pinkey_lower(0, params[10], params[11]);
	Pose p_pinkey_middle(0, params[12], 0);
	Pose p_pinkey_top(0, params[13], 0);
	set_one_rotation(p_pinkey_lower, 2);
	set_one_rotation(p_pinkey_middle, 3);
	set_one_rotation(p_pinkey_top, 4);

	//middle
	Pose p_ring_lower(0, params[14], params[15]);
	Pose p_ring_middle(0, params[16], 0);
	Pose p_ring_top(0, params[17], 0);
	set_one_rotation(p_ring_lower, 6);
	set_one_rotation(p_ring_middle, 7);
	set_one_rotation(p_ring_top, 8);

	//ring
	Pose p_middle_lower(0, params[18], params[19]);
	Pose p_middle_middle(0, params[20], 0);
	Pose p_middle_top(0, params[21], 0);
	set_one_rotation(p_middle_lower, 14);
	set_one_rotation(p_middle_middle, 15);
	set_one_rotation(p_middle_top, 16);

	//pinkey
	Pose p_index_lower(0, params[22], params[23]);
	Pose p_index_middle(0, params[24], 0);
	Pose p_index_top(0, params[25], 0);
	set_one_rotation(p_index_lower, 10);
	set_one_rotation(p_index_middle, 11);
	set_one_rotation(p_index_top, 12);
}

void HandModel::compute_global_matrix()
{
	//这里的Scaling是在Wrist局部坐标系下进行缩放，然后再将缩放后的坐标转换到世界坐标系下，然后在世界坐标系中进行Params[0~2]的平移
	Eigen::Matrix<float, 4, 4> Scaling = Eigen::MatrixXf::Zero(4, 4);
	Scaling(0, 0) = Hand_scale(0);
	Scaling(1, 1) = Hand_scale(1);
	Scaling(2, 2) = Hand_scale(2);
	Scaling(3, 3) = 1;

	Joints[0].global = Joints[0].local*Scaling*Joints[0].rotation;

	for (int i = 0; i < NumofJoints; ++i)
	{
		int parent_joint_index = Joints[i].parent_joint_index;
		if (parent_joint_index != -1)
		{
			Joints[i].global = Joints[parent_joint_index].global*Joints[i].trans*Joints[i].rotation;
		}
	}
}

void HandModel::Updata_Joints()
{
	//updata joints
	for (int i = 0; i < NumofJoints; ++i)
	{
		Joints[i].CorrespondingPosition << Joints[i].global*Joints[i].local.inverse()*Joints[i].GlobalInitPosition + GlobalPosition;
	}
}

void HandModel::Updata_axis()
{
	//updata axis  这里的axis指的是绕的哪个轴旋转的axis的更新，对于不饶旋转的轴，可以不更新，比如: joint[1、5、9、13、17]这五根手指的low 
	//
	for (int i = 0; i < NumofJoints; ++i)
	{
		if (i != 0 && i != 2 && i != 6 && i != 10 && i != 14&&i!=18)
		{
			Joints[i].CorrespondingAxis[0] << Joints[i].global*Joints[i].dof_axis[0] + GlobalPosition;
			Joints[i].CorrespondingAxis[1] << Joints[i].global*Joints[i].dof_axis[1] + GlobalPosition;
			Joints[i].CorrespondingAxis[2] << Joints[i].global*Joints[i].dof_axis[2] + GlobalPosition;
		}
		else
		{
			if (i == 0)
			{
				//y*x*z;         ==> y轴不变，x轴左乘y轴旋转，z轴完全旋转
				Pose pose(Params[3], Params[4], Params[5]);
				Eigen::MatrixXf x = Eigen::MatrixXf::Identity(4, 4);
				Eigen::MatrixXf y = Eigen::MatrixXf::Identity(4, 4);
				Eigen::MatrixXf z = Eigen::MatrixXf::Identity(4, 4);

				float cx = cos(pose.x / 180 * PI);
				float sx = sin(pose.x / 180 * PI);

				float cy = cos(pose.y / 180 * PI);
				float sy = sin(pose.y / 180 * PI);

				float cz = cos(pose.z / 180 * PI);
				float sz = sin(pose.z / 180 * PI);

				x(1, 1) = cx; x(2, 2) = cx;
				x(1, 2) = -sx; x(2, 1) = sx;

				y(0, 0) = cy; y(0, 2) = sy;
				y(2, 0) = -sy; y(2, 2) = cy;

				z(0, 0) = cz; z(1, 1) = cz;
				z(0, 1) = -sz; z(1, 0) = sz;


				Joints[i].CorrespondingAxis[0] << Joints[i].local*y*Joints[i].dof_axis[0] + GlobalPosition;
				Joints[i].CorrespondingAxis[1] << Joints[i].local*Joints[i].dof_axis[1] + GlobalPosition;
				Joints[i].CorrespondingAxis[2] << Joints[i].local*y*x*Joints[i].dof_axis[2] + GlobalPosition;
			}
			else
			{
				if (i == 18)
				{
					//x*z*y;   ==>x轴用不到，因此不更新，z本应该左乘x的旋转，但是x的旋转为单位阵，则z不变，y轴则遵循完全旋转
					int parent_joint_index = Joints[i].parent_joint_index;

					Joints[i].CorrespondingAxis[1] << Joints[i].global*Joints[i].dof_axis[1] + GlobalPosition;
					Joints[i].CorrespondingAxis[2] << Joints[parent_joint_index].global*Joints[i].trans*Joints[i].dof_axis[2] + GlobalPosition;
				}
				else
				{
					//x*y*z;    ==>x轴不变，但是x轴用不到，因此不更新，y轴左乘x轴旋转，但是x轴不旋转，因此绕x旋转是单位矩阵，因此y轴也不变，z轴完全旋转
					int parent_joint_index = Joints[i].parent_joint_index;

					Joints[i].CorrespondingAxis[1] << Joints[parent_joint_index].global*Joints[i].trans*Joints[i].dof_axis[1] + GlobalPosition;
					Joints[i].CorrespondingAxis[2] << Joints[i].global*Joints[i].dof_axis[2] + GlobalPosition;
				}
			}
		}

	}
}

void HandModel::Updata_Vertics()
{
	Eigen::MatrixXf t = Eigen::MatrixXf::Zero(4, NumofVertices);
	Eigen::MatrixXf x = Eigen::MatrixXf::Ones(4, NumofVertices);
	x.block(0, 0, 3, NumofVertices) = Vectices.block(0, 0, NumofVertices, 3).transpose();

	Eigen::MatrixXf y;
	Eigen::MatrixXf y0;
	Eigen::MatrixXf z;

	for (int i = 0; i < NumofJoints; ++i) {
		y = Weights.block(0, i, NumofVertices, 1);// 在所有顶点 对于 该关节点的weight
		y0 = y.replicate(1, 4);    //分别是行重复1遍，列重复4遍，结果为（num_vertices_，4）这么大小的矩阵
		z = Joints[i].global * Joints[i].local.inverse() * x;
		t = t + z.cwiseProduct(y0.transpose());
	}
	vertices_update_ = t.transpose();

	for (int i = 0; i < vertices_update_.rows(); ++i) {
		vertices_update_(i, 0) += GlobalPosition(0);
		vertices_update_(i, 1) += GlobalPosition(1);
		vertices_update_(i, 2) += GlobalPosition(2);
	}
}

void HandModel::Updata(float* params)
{
	load_target_joints();

	compute_rotation_matrix(params);
	compute_global_matrix();
	Updata_Joints();
	Updata_axis();

	Updata_Vertics();        //经过测试最耗时 ： 共需要8ms左右

	Compute_normal_And_visibel_vertices();    //耗时需要1ms左右

	Joint_matrix = Eigen::MatrixXf::Zero(NumofJoints, 3);
	for (int i = 0; i < NumofJoints; ++i)
	{
		Joint_matrix(i, 0) = Joints[i].CorrespondingPosition(0);
		Joint_matrix(i, 1) = Joints[i].CorrespondingPosition(1);
		Joint_matrix(i, 2) = Joints[i].CorrespondingPosition(2);
	}

}

void HandModel::Compute_normal_And_visibel_vertices()
{
	Visible_vertices.clear();
	Visible_vertices_index.clear();
	Face_normal.clear();
	Vertices_normal.setZero();
	Vector3f A, B, C, BA, BC;
	for (int i = 0; i < NumofFaces; ++i)
	{
		//这里我假设，如果假设错了，那么叉乘时候，就BC*BA变成BA*BC
		//            A
		//          /  \
				//         B — C
		A << vertices_update_(FaceIndex(i, 0), 0), vertices_update_(FaceIndex(i, 0), 1), vertices_update_(FaceIndex(i, 0), 2);
		B << vertices_update_(FaceIndex(i, 1), 0), vertices_update_(FaceIndex(i, 1), 1), vertices_update_(FaceIndex(i, 1), 2);
		C << vertices_update_(FaceIndex(i, 2), 0), vertices_update_(FaceIndex(i, 2), 1), vertices_update_(FaceIndex(i, 2), 2);

		BC << C - B;
		BA << A - B;

		Vector3f nom(BC.cross(BA));

		nom.normalize();
		Face_normal.push_back(nom);

		Vertices_normal(FaceIndex(i, 0), 0) += nom(0);
		Vertices_normal(FaceIndex(i, 1), 0) += nom(0);
		Vertices_normal(FaceIndex(i, 2), 0) += nom(0);

		Vertices_normal(FaceIndex(i, 0), 1) += nom(1);
		Vertices_normal(FaceIndex(i, 1), 1) += nom(1);
		Vertices_normal(FaceIndex(i, 2), 1) += nom(1);

		Vertices_normal(FaceIndex(i, 0), 2) += nom(2);
		Vertices_normal(FaceIndex(i, 1), 2) += nom(2);
		Vertices_normal(FaceIndex(i, 2), 2) += nom(2);

	}

	for (int i = 0; i < Vertices_normal.rows(); ++i)
	{
		Vertices_normal.row(i).normalize();

		if (-(Vertices_normal(i, 2)) >= 0)
		{
			Vector3f visible_v(vertices_update_(i, 0), vertices_update_(i, 1), vertices_update_(i, 2));
			Visible_vertices.push_back(visible_v);
			Visible_vertices_index.push_back(i);
		}
	}

	//cout << "visible vertices find done!" << endl;
}


//=================Jacobain    related    function==============================
void HandModel::Updata_joints_Jacobian()
{
	Joints_jacobian.setZero();

	for (int i = 0; i < NumofJoints; ++i)
	{
		Joints_jacobian.block(i * 3, 0, 3, NumberofParams) = Compute_one_Joint_Jacobian(i);
	}
}

Eigen::MatrixXf HandModel::Compute_one_Joint_Jacobian(int index)
{
	float omiga = 3.141592f / 180.0f;
	Eigen::MatrixXf Jacobain_ = Eigen::MatrixXf::Zero(3, NumberofParams);

	int current_indx = index;
	Eigen::Vector3f current_joint_position(Joints[index].CorrespondingPosition(0), Joints[index].CorrespondingPosition(1), Joints[index].CorrespondingPosition(2));

	//计算时候会用到的变量
	Eigen::Vector3f axis_base_position;
	Eigen::Vector3f x_axis_position;
	Eigen::Vector3f y_axis_position;
	Eigen::Vector3f z_axis_position;

	Eigen::Vector3f w_x, w_y, w_z;
	Eigen::Vector3f S;
	Eigen::Vector3f result;

	while (current_indx >= 0)
	{
		axis_base_position << Joints[current_indx].CorrespondingPosition(0), Joints[current_indx].CorrespondingPosition(1), Joints[current_indx].CorrespondingPosition(2);

		x_axis_position << Joints[current_indx].CorrespondingAxis[0](0), Joints[current_indx].CorrespondingAxis[0](1), Joints[current_indx].CorrespondingAxis[0](2);
		y_axis_position << Joints[current_indx].CorrespondingAxis[1](0), Joints[current_indx].CorrespondingAxis[1](1), Joints[current_indx].CorrespondingAxis[1](2);
		z_axis_position << Joints[current_indx].CorrespondingAxis[2](0), Joints[current_indx].CorrespondingAxis[2](1), Joints[current_indx].CorrespondingAxis[2](2);


		w_x << (x_axis_position - axis_base_position);
		w_y << (y_axis_position - axis_base_position);
		w_z << (z_axis_position - axis_base_position);

		w_x.normalize();
		w_y.normalize();
		w_z.normalize();

		S << (current_joint_position - axis_base_position);

		int params_len = Joints[current_indx].params_length;
		for (int idx = 0; idx < params_len; idx++)
		{
			int params_idx = Joints[current_indx].params_index[idx];

			switch (Joints[current_indx].params_type[idx])
			{
			case dof_type(x_axis_rotate): {
				result << omiga*w_x.cross(S);
				Jacobain_(0, params_idx) += result(0);
				Jacobain_(1, params_idx) += result(1);
				Jacobain_(2, params_idx) += result(2);
				break;
			}
			case dof_type(y_axis_rotate): {
				result << omiga*w_y.cross(S);
				Jacobain_(0, params_idx) += result(0);
				Jacobain_(1, params_idx) += result(1);
				Jacobain_(2, params_idx) += result(2);
				break;
			}
			case dof_type(z_axis_rotate): {
				result << omiga*w_z.cross(S);
				Jacobain_(0, params_idx) += result(0);
				Jacobain_(1, params_idx) += result(1);
				Jacobain_(2, params_idx) += result(2);
				break;
			}
			case dof_type(x_axis_trans): {
				result << 1, 0, 0;
				Jacobain_(0, params_idx) += result(0);
				Jacobain_(1, params_idx) += result(1);
				Jacobain_(2, params_idx) += result(2);
				break;
			}
			case dof_type(y_axis_trans): {
				result << 0, 1, 0;
				Jacobain_(0, params_idx) += result(0);
				Jacobain_(1, params_idx) += result(1);
				Jacobain_(2, params_idx) += result(2);
				break;
			}
			case dof_type(z_axis_trans): {
				result << 0, 0, 1;
				Jacobain_(0, params_idx) += result(0);
				Jacobain_(1, params_idx) += result(1);
				Jacobain_(2, params_idx) += result(2);
				break;
			}
			}

		}

		current_indx = Joints[current_indx].parent_joint_index;
	}

	return Jacobain_;
}

void HandModel::MoveToJointTarget()
{
	Eigen::VectorXf e = Eigen::VectorXf::Zero(3 * NumofJoints, 1);
	for (int i = 0; i < NumofJoints; i++)
	{
		e(i * 3 + 0) = -Joint_matrix(i, 0) + Target_joints(i, 0);
		e(i * 3 + 1) = -Joint_matrix(i, 1) + Target_joints(i, 1);
		e(i * 3 + 2) = -Joint_matrix(i, 2) + Target_joints(i, 2);
	}


	Updata_joints_Jacobian();
	Eigen::MatrixXf J = Joints_jacobian;
	Eigen::MatrixXf Jt = Joints_jacobian.transpose();

	Eigen::Matrix<float, 26, 26> D = Eigen::Matrix<float, 26, 26>::Identity(26, 26);

	int omiga = 20;

	Eigen::VectorXf dAngles = Eigen::VectorXf::Zero(NumberofParams, 1);

	MatrixXf JtJ = Jt*J + omiga*D;
	VectorXf JTe = Jt*e;

	dAngles = JtJ.colPivHouseholderQr().solve(JTe);

	for (int i = 0; i < NumberofParams; i++)
		Params[i] += dAngles(i);

	Updata(Params);

	Eigen::VectorXf e_updata = Eigen::VectorXf::Zero(3 * NumofJoints, 1);
	for (int i = 0; i < NumofJoints; i++)
	{
		e_updata(i * 3 + 0) = -Joint_matrix(i, 0) + Target_joints(i, 0);
		e_updata(i * 3 + 1) = -Joint_matrix(i, 1) + Target_joints(i, 1);
		e_updata(i * 3 + 2) = -Joint_matrix(i, 2) + Target_joints(i, 2);
	}

	if (e_updata.norm() < 1)
	{
		Solved = true;
	}
	else
	{
		Solved = false;
	}
}

void HandModel::save_target_joints()
{
	std::ofstream f;
	f.open(".\\test\\target_joints.txt", std::ios::out);
	for (int i = 0; i < NumofJoints; i++) {
		f << Joints[i].CorrespondingPosition(0) << "  " << Joints[i].CorrespondingPosition(1) << "  " << Joints[i].CorrespondingPosition(2) << endl;
	}
	f.close();
	printf("Save Target Joints succeed!!!\n");
}

void HandModel::load_target_joints()
{
	std::ifstream f;
	f.open(".\\test\\target_joints.txt", std::ios::in);
	Target_joints = Eigen::MatrixXf::Zero(NumofJoints, 3);
	for (int i = 0; i < NumofJoints; i++) {
		f >> Target_joints(i, 0) >> Target_joints(i, 1) >> Target_joints(i, 2);
	}
	f.close();
	//printf("Load Target Joints succeed!!!\n");
}