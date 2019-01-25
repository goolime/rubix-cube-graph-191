#pragma once   //maybe should be static class
#include "GLFW\glfw3.h"
#include "main.h"

static const int red1 = 3;
static const int red2 = 5;
static int rubix[27] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26 };
static double old_x, old_y,scrol_y;
static bool right_button=false;
static bool left_button = false;
static bool lock_keys = false;
static int key_lock;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if ((action == GLFW_PRESS) && (!lock_keys || (lock_keys && key == key_lock)) && (key == GLFW_KEY_R || key == GLFW_KEY_L || key == GLFW_KEY_U || key == GLFW_KEY_D || key == GLFW_KEY_F || key == GLFW_KEY_B)) {

		switch (key)
		{
		case GLFW_KEY_R:
			printf("right %d\n", rotate_dir);
			Key_R(rubix);
			break;
		case GLFW_KEY_L:
			printf("left %d\n", rotate_dir);
			Key_L(rubix);
			break;
		case GLFW_KEY_U:
			printf("up %d\n", rotate_dir);
			Key_U(rubix);
			break;
		case GLFW_KEY_D:
			printf("down %d\n", rotate_dir);
			Key_D(rubix);
			break;
		case GLFW_KEY_F:
			printf("forward %d\n", rotate_dir);
			Key_F(rubix);
			break;
		case GLFW_KEY_B:
			printf("backward %d\n", rotate_dir);
			Key_B(rubix);
			break;
		default:
			break;
		}
		turn_lock();

		while (has_turn()) {
			switch (key)
			{
			case GLFW_KEY_R:
				if (action == GLFW_PRESS) {
					int t1 = rubix[0];
					int t2 = rubix[3];
					int t3 = rubix[6];

					if (rotate_dir == -1) {

						rubix[0] = rubix[18];
						rubix[3] = rubix[9];
						rubix[9] = rubix[21];
						rubix[18] = rubix[24];
						rubix[21] = rubix[15];
						rubix[24] = t3;
						rubix[15] = t2;
						rubix[6] = t1;

					}
					else {
						rubix[3] = rubix[15];
						rubix[6] = rubix[24];
						rubix[15] = rubix[21];
						rubix[24] = rubix[18];
						rubix[21] = rubix[9];
						rubix[18] = t1;
						rubix[9] = t2;
						rubix[0] = t3;
					}
				}
				break;
			case GLFW_KEY_L:
				if (action == GLFW_PRESS) {
					int t1 = rubix[2];
					int t2 = rubix[5];
					int t3 = rubix[8];

					if (rotate_dir == -1) {
						rubix[5] = rubix[11];
						rubix[2] = rubix[20];
						rubix[11] = rubix[23];
						rubix[20] = rubix[26];
						rubix[23] = rubix[17];
						rubix[26] = t3;
						rubix[17] = t2;
						rubix[8] = t1;
					}
					else {
						rubix[5] = rubix[17];
						rubix[8] = rubix[26];
						rubix[17] = rubix[23];
						rubix[26] = rubix[20];
						rubix[23] = rubix[11];
						rubix[20] = t1;
						rubix[11] = t2;
						rubix[2] = t3;
					}
				}
				break;
			case GLFW_KEY_U:
				if (action == GLFW_PRESS) {
					int t1 = rubix[0];
					int t2 = rubix[1];
					int t3 = rubix[2];

					if (rotate_dir == 1) {
						rubix[1] = rubix[11];
						rubix[2] = rubix[20];
						rubix[11] = rubix[19];
						rubix[20] = rubix[18];
						rubix[19] = rubix[9];
						rubix[18] = t1;
						rubix[9] = t2;
						rubix[0] = t3;
					}
					else {
						rubix[1] = rubix[9];
						rubix[0] = rubix[18];
						rubix[9] = rubix[19];
						rubix[18] = rubix[20];
						rubix[19] = rubix[11];
						rubix[20] = t3;
						rubix[11] = t2;
						rubix[2] = t1;
					}
				}
				break;
			case GLFW_KEY_D:
				if (action == GLFW_PRESS) {
					int t1 = rubix[6];
					int t2 = rubix[7];
					int t3 = rubix[8];

					if (rotate_dir == 1) {
						rubix[6] = t3;
						rubix[7] = rubix[17];
						rubix[8] = rubix[26];
						rubix[17] = rubix[25];
						rubix[26] = rubix[24];
						rubix[25] = rubix[15];
						rubix[24] = t1;
						rubix[15] = t2;
					}
					else {
						rubix[8] = t1;
						rubix[7] = rubix[15];
						rubix[6] = rubix[24];
						rubix[15] = rubix[25];
						rubix[24] = rubix[26];
						rubix[25] = rubix[17];
						rubix[26] = t3;
						rubix[17] = t2;
					}
				}
				break;
			case GLFW_KEY_F:
				if (action == GLFW_PRESS) {
					int t1 = rubix[6];
					int t2 = rubix[7];
					int t3 = rubix[8];

					if (rotate_dir == -1) {
						rubix[7] = rubix[5];
						rubix[8] = rubix[2];
						rubix[5] = rubix[1];
						rubix[2] = rubix[0];
						rubix[1] = rubix[3];
						rubix[0] = t1;
						rubix[3] = t2;
						rubix[6] = t3;
					}
					else {
						rubix[7] = rubix[3];
						rubix[6] = rubix[0];
						rubix[3] = rubix[1];
						rubix[0] = rubix[2];
						rubix[1] = rubix[5];
						rubix[2] = t3;
						rubix[5] = t2;
						rubix[8] = t1;
					}
				}
				break;
			case GLFW_KEY_B:
				if (action == GLFW_PRESS) {
					int t1 = rubix[24];
					int t2 = rubix[25];
					int t3 = rubix[26];

					if (rotate_dir == -1) {
						rubix[25] = rubix[23];
						rubix[26] = rubix[20];
						rubix[23] = rubix[19];
						rubix[20] = rubix[18];
						rubix[19] = rubix[21];
						rubix[18] = t1;
						rubix[21] = t2;
						rubix[24] = t3;
					}
					else {
						rubix[25] = rubix[21];
						rubix[24] = rubix[18];
						rubix[21] = rubix[19];
						rubix[18] = rubix[20];
						rubix[19] = rubix[23];
						rubix[20] = t3;
						rubix[23] = t2;
						rubix[26] = t1;
					}
				}
				break;

			default:
				break;
			}
			roundturn_lock();
		}
		bool tmp = lock_keys;
		lock_keys = is_lock();
		if (lock_keys && !tmp)	key_lock = key;
	}

	switch (key) {
	case GLFW_KEY_ESCAPE:
		if (action == GLFW_PRESS) glfwSetWindowShouldClose(window, GLFW_TRUE);
		break;
	case GLFW_KEY_SPACE:
		if (action == GLFW_PRESS) flip();
		break;
	case GLFW_KEY_UP:
		Key_UP();
		break;
	case GLFW_KEY_DOWN:
		Key_DOWN();
		break;
	case GLFW_KEY_LEFT:
		Key_LEFT();
		break;
	case GLFW_KEY_RIGHT:
		Key_RIGHT();
		break;
	case GLFW_KEY_Z:
		if (action == GLFW_PRESS) div_angle();
		break;
	case GLFW_KEY_A:
		if (action == GLFW_PRESS) mul_angle();
		break;
	case GLFW_KEY_C:
		zeroize();
		break;
	case GLFW_KEY_X:
		if (action == GLFW_PRESS) {
			printf("restart\n");
			unlock();
			restart();
			{
				rubix[0] = 0;
				rubix[1] = 1;
				rubix[2] = 2;
				rubix[3] = 3;
				rubix[4] = 4;
				rubix[5] = 5;
				rubix[6] = 6;
				rubix[7] = 7;
				rubix[8] = 8;
				rubix[9] = 9;
				rubix[10] = 10;
				rubix[11] = 11;
				rubix[12] = 12;
				rubix[13] = 13;
				rubix[14] = 14;
				rubix[15] = 15;
				rubix[16] = 16;
				rubix[17] = 17;
				rubix[18] = 18;
				rubix[19] = 19;
				rubix[20] = 20;
				rubix[21] = 21;
				rubix[22] = 22;
				rubix[23] = 23;
				rubix[24] = 24;
				rubix[25] = 25;
				rubix[26] = 26;
			}
		}
		break;
	default:
		break;
	}

}

void mouse_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT) {
		if (action == GLFW_PRESS) {
			left_button = true;
		}
		if (action == GLFW_RELEASE) {
			left_button = false;
		}
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT) {
		if (action == GLFW_PRESS) {
			right_button = true;
		}
		if (action == GLFW_RELEASE) {
			right_button = false;
		}
	}
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (left_button) {
		if (xpos < old_x) {
			int tmp = int((old_x - xpos)/ red1);
			for (int i = 0; i < tmp; i++) {
				Key_LEFT();
			}
		}
		if (xpos > old_x) {
			int tmp = int((xpos - old_x)/ red1);
			for (int i = 0; i < tmp; i++) {
				Key_RIGHT();
			}
		}
		if (ypos < old_y) {
			int tmp = int((old_y - ypos)/ red1);
			for (int i = 0; i < tmp; i++) {
				Key_UP();
			}
		}
		if (ypos > old_y) {
			int tmp = int((ypos - old_y)/ red1);
			for (int i = 0; i < tmp; i++) {
				Key_DOWN();
			}
		}
	}

	if (right_button) {
		if(xpos < old_x) {
			int tmp = (old_x - xpos) / red2;
			for (int i = 0; i < tmp; i++) {
				mov_right();
			}
		}
		if (xpos > old_x) {
			int tmp = (xpos - old_x) / red2;
			for (int i = 0; i < tmp; i++) {
				mov_left();
			}
		}
		if (ypos < old_y) {
			int tmp = (old_y - ypos) / red2;
			for (int i = 0; i < tmp; i++) {
				mov_up();
			}
		}
		if (ypos > old_y) {
			int tmp = (ypos - old_y) / red2;
			for (int i = 0; i < tmp; i++) {
				mov_down();
			}
		}
	}

	old_x = xpos;
	old_y = ypos;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset){
	if (yoffset > 0) mov_in();
	if (yoffset < 0) mov_out();
}
