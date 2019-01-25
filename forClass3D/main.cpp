#include <Windows.h>
#include <iostream>
#include <string>
#include "display.h"
#include "mesh.h"
#include "shader.h"
#include "inputManager.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

using namespace glm;

static const int DISPLAY_WIDTH = 1000;
static const int DISPLAY_HEIGHT = 1000;

static mat4 M;
static mat4 antiM;
static vec3 positions[27];
static mat4 rotation[27];
//static int rubix[27] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26};
static float angle = 90.0;
static vec3 pos = vec3(0, 0, -5);
static vec3 forward = glm::vec3(0.0f, 0.0f, 1.0f);
static vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
static vec3 mov = glm::vec3(0.0f, 0.0f, 0.0f);
static const double mov_t = 0.1;
static float lock = 0;

int main(int argc, char** argv)
{
	Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, "HW3 | rubix qube | Gal Meir - 305382137");
	
	Vertex vertices[] =
	{
		Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 0), glm::vec3(0, 0, -1),glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 0, -1),glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 0, -1),glm::vec3(0, 0, 1)),
		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(0, 0, -1),glm::vec3(0, 0, 1)),

		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(0, 0, 1),glm::vec3(0, 1, 1)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(0, 0, 1),glm::vec3(0, 1, 1)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 1), glm::vec3(0, 0, 1),glm::vec3(0, 1, 1)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 1), glm::vec3(0, 0, 1),glm::vec3(0, 1, 1)),

		Vertex(glm::vec3(-1, -1, -1), glm::vec2(0, 1), glm::vec3(0, -1, 0),glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 1), glm::vec3(0, -1, 0),glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(0, -1, 0),glm::vec3(0, 1, 0)),
		Vertex(glm::vec3(1, -1, -1), glm::vec2(0, 0), glm::vec3(0, -1, 0),glm::vec3(0, 1, 0)),

		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(0, 1, 0),glm::vec3(1, 1, 0)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(1, 1), glm::vec3(0, 1, 0),glm::vec3(1, 1, 0)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(1, 0), glm::vec3(0, 1, 0),glm::vec3(1, 1, 0)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 0), glm::vec3(0, 1, 0),glm::vec3(1, 1, 0)),

		Vertex(glm::vec3(-1, -1, -1), glm::vec2(1, 1), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(-1, -1, 1), glm::vec2(1, 0), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(-1, 1, 1), glm::vec2(0, 0), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),
		Vertex(glm::vec3(-1, 1, -1), glm::vec2(0, 1), glm::vec3(-1, 0, 0),glm::vec3(1, 0, 0)),

		Vertex(glm::vec3(1, -1, -1), glm::vec2(1, 1), glm::vec3(1, 0, 0),glm::vec3(1, 0, 1)),
		Vertex(glm::vec3(1, -1, 1), glm::vec2(1, 0), glm::vec3(1, 0, 0),glm::vec3(1, 0, 1)),
		Vertex(glm::vec3(1, 1, 1), glm::vec2(0, 0), glm::vec3(1, 0, 0),glm::vec3(1, 0, 1)),
		Vertex(glm::vec3(1, 1, -1), glm::vec2(0, 1), glm::vec3(1, 0, 0),glm::vec3(1, 0, 1))
	};

	unsigned int indices[] = {0, 1, 2,
							  0, 2, 3,

							  6, 5, 4,
							  7, 6, 4,

							  10, 9, 8,
							  11, 10, 8,

							  12, 13, 14,
							  12, 14, 15,

							  16, 17, 18,
							  16, 18, 19,

							  22, 21, 20,
							  23, 22, 20
	                          };
	
	// mesh declerations
	
	Mesh qube(vertices, sizeof(vertices) / sizeof(vertices[0]), indices, sizeof(indices) / sizeof(indices[0]));
	
	//Mesh monkey("./res/meshes/monkeyNoUV.obj");
	Shader shader("./res/shaders/basicShader");
	
	// starting positions declerations
	{
		positions[0] = glm::vec3(-2.f, 2.f, -2.f);
		positions[1] = glm::vec3(0.f, 2.f, -2.f);
		positions[2] = glm::vec3(2.f, 2.f, -2.f);
		positions[3] = glm::vec3(-2.f, 0.f, -2.f);
		positions[4] = glm::vec3(0.f, 0.f, -2.f);
		positions[5] = glm::vec3(2.f, 0.f, -2.f);
		positions[6] = glm::vec3(-2.f, -2.f, -2.f);
		positions[7] = glm::vec3(0.f, -2.f, -2.f);
		positions[8] = glm::vec3(2.f, -2.f, -2.f);
		positions[9] = glm::vec3(-2.f, 2.f, 0.f);
		positions[10] = glm::vec3(0.f, 2.f, 0.f);
		positions[11] = glm::vec3(2.f, 2.f, 0.f);
		positions[12] = glm::vec3(-2.f, 0.f, 0.f);
		positions[13] = glm::vec3(0.f, 0.f, 0.f);
		positions[14] = glm::vec3(2.f, 0.f, 0.f);
		positions[15] = glm::vec3(-2.f, -2.f, 0.f);
		positions[16] = glm::vec3(0.f, -2.f, 0.f);
		positions[17] = glm::vec3(2.f, -2.f, 0.f);
		positions[18] = glm::vec3(-2.f, 2.f, 2.f);
		positions[19] = glm::vec3(0.f, 2.f, 2.f);
		positions[20] = glm::vec3(2.f, 2.f, 2.f);
		positions[21] = glm::vec3(-2.f, 0.f, 2.f);
		positions[22] = glm::vec3(0.f, 0.f, 2.f);
		positions[23] = glm::vec3(2.f, 0.f, 2.f);
		positions[24] = glm::vec3(-2.f, -2.f, 2.f);
		positions[25] = glm::vec3(0.f, -2.f, 2.f);
		positions[26] = glm::vec3(2.f, -2.f, 2.f);
	}

	//intiation to 1 diagonal matrix
	restart();

	mat4 P = glm::perspective(60.0f, (float)DISPLAY_WIDTH/(float)DISPLAY_HEIGHT, 0.1f, 100.0f);
	M = glm::mat4(1.f); //glm::rotate(45.0f,vec3(1,1,1));//glm::mat4(1);
	antiM = glm::mat4(1.f);
	//mat4 Yp= glm::rotate(90.0f, vec3(0, 1, 0));
	mat4 s = glm::scale(glm::vec3(0.3f));
	P = P * glm::lookAt(pos, pos + forward, up);
	mat4 MVP = P*M;
	mat4 T;
	glfwSetKeyCallback(display.m_window,key_callback);
	glfwSetMouseButtonCallback(display.m_window,mouse_callback);
	glfwSetCursorPosCallback(display.m_window, cursor_position_callback);
	glfwSetScrollCallback(display.m_window, scroll_callback);
	/*
	rotation[0] = glm::rotate(90.0f, vec3(0, 1, 0));
	rotation[0] = rotation[0] * glm::rotate(90.0f, vec3(0, 0, 1));
	*/
	while(!glfwWindowShouldClose(display.m_window))
	{
		Sleep(3);
		//M = glm::rotate(M,0.1f,up);
		//MVP = P * s * M;
		display.Clear(1.0f, 1.0f, 1.0f, 1.0f);

		shader.Bind();
		shader.Update(MVP,M);
		mat4 Tmov = glm::translate(glm::mat4(1.f), mov);
		
		for (int i = 0; i < 27; i++) {
			T = glm::translate(glm::mat4(1.f), positions[i]);
			MVP = P * s  * Tmov * M * rotation[i] * T;
			shader.Bind();
			shader.Update(MVP, M*rotation[i]);
			qube.Draw();
		}
		
		display.SwapBuffers();

		glfwPollEvents();
	}

	return 0;
}

mat4 my_rotate(mat4 old_rotate, vec3 axis) {
	mat4 tmp = glm::rotate(rotate_dir*angle, axis);
	return tmp * old_rotate;
}

mat4 my_rotate_g(mat4 old_rotate, vec3 axis , int dir) {
	return  glm::rotate(dir*1.f, axis) * old_rotate;
}

void Key_UP()
{
	M = my_rotate_g(M, glm::vec3(1.f,0.f,0.f),1);
}

void Key_DOWN()
{
	M = my_rotate_g(M, glm::vec3(1.f, 0.f, 0.f), -1);
}

void Key_RIGHT()
{
	M = my_rotate_g(M, glm::vec3(0.f, 1.f, 0.f), 1);
}

void Key_LEFT()
{
	M = my_rotate_g(M, glm::vec3(0.f, 1.f, 0.f), -1);
}

void Key_R(int rubix[])
{
	vec3 axis = glm::vec3(1.f, 0.f, 0.f);
	rotation[rubix[0]] = my_rotate(rotation[rubix[0]], axis);
	rotation[rubix[3]] = my_rotate(rotation[rubix[3]], axis);
	rotation[rubix[6]] = my_rotate(rotation[rubix[6]], axis);
	rotation[rubix[9]] = my_rotate(rotation[rubix[9]], axis);
	rotation[rubix[12]] = my_rotate(rotation[rubix[12]], axis);
	rotation[rubix[15]] = my_rotate(rotation[rubix[15]], axis);
	rotation[rubix[18]] = my_rotate(rotation[rubix[18]], axis);
	rotation[rubix[21]] = my_rotate(rotation[rubix[21]], axis);
	rotation[rubix[24]] = my_rotate(rotation[rubix[24]], axis);
}

void Key_L(int rubix[])
{
	vec3 axis = glm::vec3(1.f, 0.f, 0.f);
	rotation[rubix[2]] = my_rotate(rotation[rubix[2]], axis);
	rotation[rubix[5]] = my_rotate(rotation[rubix[5]], axis);
	rotation[rubix[8]] = my_rotate(rotation[rubix[8]], axis);
	rotation[rubix[11]] = my_rotate(rotation[rubix[11]], axis);
	rotation[rubix[14]] = my_rotate(rotation[rubix[14]], axis);
	rotation[rubix[17]] = my_rotate(rotation[rubix[17]], axis);
	rotation[rubix[20]] = my_rotate(rotation[rubix[20]], axis);
	rotation[rubix[23]] = my_rotate(rotation[rubix[23]], axis);
	rotation[rubix[26]] = my_rotate(rotation[rubix[26]], axis);
}

void Key_U(int rubix[])
{
	vec3 axis = glm::vec3(0.f, 1.f, 0.f);
	rotation[rubix[0]] = my_rotate(rotation[rubix[0]],axis);
	rotation[rubix[1]] = my_rotate(rotation[rubix[1]], axis);
	rotation[rubix[2]] = my_rotate(rotation[rubix[2]], axis);
	rotation[rubix[9]] = my_rotate(rotation[rubix[9]], axis);
	rotation[rubix[10]] = my_rotate(rotation[rubix[10]], axis);
	rotation[rubix[11]] = my_rotate(rotation[rubix[11]], axis);
	rotation[rubix[18]] = my_rotate(rotation[rubix[18]], axis);
	rotation[rubix[19]] = my_rotate(rotation[rubix[19]], axis);
	rotation[rubix[20]] = my_rotate(rotation[rubix[20]], axis);
}

void Key_D(int rubix[])
{
	vec3 axis = glm::vec3(0.f, 1.f, 0.f);
	rotation[rubix[6]] = my_rotate(rotation[rubix[6]], axis);
	rotation[rubix[7]] = my_rotate(rotation[rubix[7]], axis);
	rotation[rubix[8]] = my_rotate(rotation[rubix[8]], axis);
	rotation[rubix[15]] = my_rotate(rotation[rubix[15]], axis);
	rotation[rubix[16]] = my_rotate(rotation[rubix[16]], axis);
	rotation[rubix[17]] = my_rotate(rotation[rubix[17]], axis);
	rotation[rubix[24]] = my_rotate(rotation[rubix[24]], axis);
	rotation[rubix[25]] = my_rotate(rotation[rubix[25]], axis);
	rotation[rubix[26]] = my_rotate(rotation[rubix[26]], axis);

}

void Key_F(int rubix[]) {
	vec3 axis = glm::vec3(0.f, 0.f, 1.f);
	rotation[rubix[0]] = my_rotate(rotation[rubix[0]], axis);
	rotation[rubix[1]] = my_rotate(rotation[rubix[1]], axis);
	rotation[rubix[2]] = my_rotate(rotation[rubix[2]], axis);
	rotation[rubix[3]] = my_rotate(rotation[rubix[3]], axis);
	rotation[rubix[4]] = my_rotate(rotation[rubix[4]], axis);
	rotation[rubix[5]] = my_rotate(rotation[rubix[5]], axis);
	rotation[rubix[6]] = my_rotate(rotation[rubix[6]], axis);
	rotation[rubix[7]] = my_rotate(rotation[rubix[7]], axis);
	rotation[rubix[8]] = my_rotate(rotation[rubix[8]], axis);
}

void Key_B(int rubix[]) {
	vec3 axis = glm::vec3(0.f, 0.f, 1.f);
	rotation[rubix[18]] = my_rotate(rotation[rubix[18]], axis);
	rotation[rubix[19]] = my_rotate(rotation[rubix[19]], axis);
	rotation[rubix[20]] = my_rotate(rotation[rubix[20]], axis);
	rotation[rubix[21]] = my_rotate(rotation[rubix[21]], axis);
	rotation[rubix[22]] = my_rotate(rotation[rubix[22]], axis);
	rotation[rubix[23]] = my_rotate(rotation[rubix[23]], axis);
	rotation[rubix[24]] = my_rotate(rotation[rubix[24]], axis);
	rotation[rubix[25]] = my_rotate(rotation[rubix[25]], axis);
	rotation[rubix[26]] = my_rotate(rotation[rubix[26]], axis);
}

void flip()
{
	rotate_dir = rotate_dir * -1;
}

void zeroize()
{
	M= glm::mat4(1.f);
	mov = glm::vec3(0.f, 0.f, 0.f);
}

void restart()
{
	rotation[0] = glm::mat4(1.f);
	rotation[1] = glm::mat4(1.f);
	rotation[2] = glm::mat4(1.f);
	rotation[3] = glm::mat4(1.f);
	rotation[4] = glm::mat4(1.f);
	rotation[5] = glm::mat4(1.f);
	rotation[6] = glm::mat4(1.f);
	rotation[7] = glm::mat4(1.f);
	rotation[8] = glm::mat4(1.f);
	rotation[9] = glm::mat4(1.f);
	rotation[10] = glm::mat4(1.f);
	rotation[11] = glm::mat4(1.f);
	rotation[12] = glm::mat4(1.f);
	rotation[13] = glm::mat4(1.f);
	rotation[14] = glm::mat4(1.f);
	rotation[15] = glm::mat4(1.f);
	rotation[16] = glm::mat4(1.f);
	rotation[17] = glm::mat4(1.f);
	rotation[18] = glm::mat4(1.f);
	rotation[19] = glm::mat4(1.f);
	rotation[20] = glm::mat4(1.f);
	rotation[21] = glm::mat4(1.f);
	rotation[22] = glm::mat4(1.f);
	rotation[23] = glm::mat4(1.f);
	rotation[24] = glm::mat4(1.f);
	rotation[25] = glm::mat4(1.f);
	rotation[26] = glm::mat4(1.f);
	angle = 90.0;
}

void mov_up()
{
	mov = mov + glm::vec3(0.f, mov_t, 0.f);
}

void mov_down()
{
	mov = mov + glm::vec3(0.f, -1*mov_t, 0.f);
}

void mov_right()
{
	mov = mov + glm::vec3(mov_t, 0.f, 0.f);
}

void mov_left()
{
	mov = mov + glm::vec3(-1*mov_t, 0.f, 0.f);
}

void mov_in()
{
	mov = mov + glm::vec3(0.f, 0.f,  - 1 * mov_t);
}

void mov_out()
{
	mov = mov + glm::vec3(0.f, 0.f, mov_t);
}

void div_angle()
{
	angle = angle / 2;
}

void mul_angle()
{
	if (angle<180) angle = angle * 2;
}

bool is_lock()
{
	if (lock != 0) {
		return true;
	}
	else {
		return false;
	}
}

void turn_lock() {
	lock = lock + ((angle * rotate_dir) / 90);
}

bool has_turn()
{
	return (1 <= abs(lock));
}

void roundturn_lock() {
	lock = lock + (rotate_dir * -1);
}

void unlock()
{
	lock = 0;
}

