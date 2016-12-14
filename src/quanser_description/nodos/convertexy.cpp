#include "ros/ros.h"
#include"math.h"
//#include "std_msgs/String.h"
//#include <sstream>

void manipuladados(float manipulados[])
{
	// maximos das variaves
	float max_x =	1000;
	float max_y = 1000;

	// tamanhos dos links
	l1 = 0.343;
	l2 = 0.267;

	// declarando thetas
	float theta1 = 0;
	float theta2 = 0;


	// normalizando as coordenadas do tablet para a extensao maxima
	manipulados[0] = manipulados[0]*(l1+l2)/max_x;
	manipulados[1] = manipulados[0]*(l1+l2)/max_y;


	theta2 = modelo_inverso_2(manipulados);

	theta1 = modelo_inverso_1(manipulados);

	ros::NodeHandle p;
	ros::Publisher mani_pub = p.advertise<theta1>("/quanser/joint_bloco_link1_velocity_controller/command", 1000);
	ros::Publisher mani_pub = p.advertise<theta2>("/quanser/joint_link1_link2_velocity_controller/command", 1000);

}

float modelo_inverso_1(float coordenadas[],float theta2){

	float theta1;
	float l1 = 0.343;
	float l2 = 0.267;

	theta1 = atan(coordenadas[1]/coordenadas[0]) - atan((l2*sin(theta2))/(l1+l2*cos(theta2)));

	return theta1
}

float modelo_inverso_2(float coordenadas[]){

	float theta2;
	float l1 = 0.343;
	float l2 = 0.267;

	theta2 = acos((coordenadas[0]^2+coordenadas[1]^2-l1^2-l2^2)/(2*l1*l2));

	return theta2
}



int main(int argc, char **argv)
{
	ros::init(argc, argv, "convertexy");
	ros::NodeHandle s;
	ros::Rate loop_rate(10);


	while (ros::ok())
	{
		ros::Subscriber sub = s.subscribe("xypressure", 1000, manipuladados);

		ros::spinOnce();

		loop_rate.sleep();

	}
	return 0;
}
