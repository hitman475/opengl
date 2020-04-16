
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <math.h>
#include <iostream>
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Camera.h"


#include <vector>


#pragma region declare
const int SCR_WIDTH = 1600;
const int SCR_HEIGHT = 900;


void processInput(GLFWwindow* window);
void stb_load_image(unsigned int* texture, const char* filename);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
unsigned int loadCubemap(std::vector<std::string> faces);
#pragma endregion

#pragma region Model

float cubeVertices[] = {
	// positions          // Normal
	 -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

float planeVertices[] = {
	// positions          // texture Coords 
	 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
	-5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
	-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

	 5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
	-5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
	 5.0f, -0.5f, -5.0f,  2.0f, 2.0f
};

float skyboxVertices[] = {
	// positions          
	-10.0f,  10.0f, -10.0f,
	-10.0f, -10.0f, -10.0f,
	 10.0f, -10.0f, -10.0f,
	 10.0f, -10.0f, -10.0f,
	 10.0f,  10.0f, -10.0f,
	-10.0f,  10.0f, -10.0f,

	-10.0f, -10.0f,  10.0f,
	-10.0f, -10.0f, -10.0f,
	-10.0f,  10.0f, -10.0f,
	-10.0f,  10.0f, -10.0f,
	-10.0f,  10.0f,  10.0f,
	-10.0f, -10.0f,  10.0f,

	 10.0f, -10.0f, -10.0f,
	 10.0f, -10.0f,  10.0f,
	 10.0f,  10.0f,  10.0f,
	 10.0f,  10.0f,  10.0f,
	 10.0f,  10.0f, -10.0f,
	 10.0f, -10.0f, -10.0f,
	  
	-10.0f, -10.0f,  10.0f,
	-10.0f,  10.0f,  10.0f,
	 10.0f,  10.0f,  10.0f,
	 10.0f,  10.0f,  10.0f,
	 10.0f, -10.0f,  10.0f,
	-10.0f, -10.0f,  10.0f,
	 
	-10.0f,  10.0f, -10.0f,
	 10.0f,  10.0f, -10.0f,
	 10.0f,  10.0f,  10.0f,
	 10.0f,  10.0f,  10.0f,
	-10.0f,  10.0f,  10.0f,
	-10.0f,  10.0f, -10.0f,
	  
	-10.0f, -10.0f, -10.0f,
	-10.0f, -10.0f,  10.0f,
	 10.0f, -10.0f, -10.0f,
	 10.0f, -10.0f, -10.0f,
	-10.0f, -10.0f,  10.0f,
	 10.0f, -10.0f,  10.0f
};

#pragma endregion

#pragma region Camera Parameters

Camera camera(glm::vec3(0, 0, 5.0));
float lastX = SCR_WIDTH / 2, lastY = SCR_HEIGHT / 2;
bool firstMouse = true;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

#pragma endregion 

#pragma region skybox

std::vector<std::string> oceanFaces
{
	"skybox/sky1/right.jpg",
	"skybox/sky1/left.jpg",
	"skybox/sky1/top.jpg",
	"skybox/sky1/bottom.jpg",
	"skybox/sky1/front.jpg",
	"skybox/sky1/back.jpg"
};

std::vector<std::string> spaceFaces
{
	"skybox/sky2/bk_right.png",
	"skybox/sky2/bk_left.png",
	"skybox/sky2/bk_top.png",
	"skybox/sky2/bk_bottom.png",
	"skybox/sky2/bk_front.png",
	"skybox/sky2/bk_back.png"
};

std::vector<std::string> moutainFaces
{
	"skybox/sky3/mt_posx.jpg",
	"skybox/sky3/mt_negx.jpg",
	"skybox/sky3/mt_posy.jpg",
	"skybox/sky3/mt_negy.jpg",
	"skybox/sky3/mt_posz.jpg",
	"skybox/sky3/mt_negz.jpg"
};

std::vector<std::string> alienFaces
{
	"skybox/sky4/posx.tga",
	"skybox/sky4/negx.tga",
	"skybox/sky4/posy.tga",
	"skybox/sky4/negy.tga",
	"skybox/sky4/posz.tga",
	"skybox/sky4/negz.tga"
};

std::vector<std::string> faces
{
	"skybox/sky5/posx.JPG",
	"skybox/sky5/negx.JPG",
	"skybox/sky5/posy.JPG",
	"skybox/sky5/negy.JPG",
	"skybox/sky5/posz.JPG",
	"skybox/sky5/negz.JPG"
};



#pragma endregion

int main() {


#pragma region OpenWindow
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "my opengl", NULL, NULL);

	if (window == NULL) {
		printf("open window failed\n");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glewExperimental = true;
	if (glewInit() != GLEW_OK) {
		printf("init glew failed.");
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);
#pragma endregion

	Shader skyboxShader("skybox.vs", "skybox.fs");
	Shader shader("1.lamp.vs", "1.lamp.fs");

# pragma region  LoadTexture

	//cube
	


	//加载天空盒纹理
	unsigned int cubemapTexture = loadCubemap(oceanFaces);
	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

#pragma endregion

#pragma region init VAO VBO

	//cube
	unsigned int cubeVAO, cubeVBO;
	glGenVertexArrays(1, &cubeVAO);
	glGenBuffers(1, &cubeVBO);
	glBindVertexArray(cubeVAO);
	glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));


	//skybox
	unsigned int skyboxVAO, skyboxVBO; 
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	
#pragma endregion


#pragma region Init setttings

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);//设置鼠标不显示
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//线框模式
	glfwSetCursorPosCallback(window, mouse_callback);	//注册鼠标移动的回调函数
	glfwSetScrollCallback(window, scroll_callback);		//注册鼠标滚轮的回调函数
	glEnable(GL_DEPTH_TEST);


#pragma endregion


	//=========================================================
	while (!glfwWindowShouldClose(window)) {



		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window);

		glClearColor(0.0, 0.0, 0.0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//清理深度缓冲,如果不清除，移动的话物体会拖拽一个很长的残影，并且不会消失
		glEnable(GL_DEPTH_TEST);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 view = camera.GetViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

		
		//cube
		shader.use();
		shader.setMat4("model", model);
		shader.setMat4("view", view);
		shader.setMat4("projection", projection);
		shader.setVec3("cameraPos", camera.Position);


		glBindVertexArray(cubeVAO);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		//天空盒必须要在最后画 而且要关闭深度测试，这样天空盒就能在所有绘制的物体之后了
		glDepthFunc(GL_LEQUAL);	
		/*
			由于gl_Position = glPosition.xyww 导致天空盒的深度值为1.0f，即最大深度值，深度缓冲被1.0f填充
			所以需要设置为GL_LEQUAL（深度值小于等于能通过），让天空盒能够通过深度测试
		*/
		skyboxShader.use();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
		/*
			view矩阵这么写保证了天空盒相对于camera不做位移（实际上有位移），
			将view矩阵先转换为mat3，舍弃掉位移的部分再重新转换为mat4
		*/
		skyboxShader.setMat4("view", view);
		skyboxShader.setMat4("projection", projection);

		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS);
		

		glfwSwapBuffers(window);
		glfwPollEvents();//接收输入

	}
	glDeleteVertexArrays(1, &skyboxVAO);
	glDeleteBuffers(1, &skyboxVAO);


	glfwTerminate();
	return 0;
}

//加载纹理图像 
void stb_load_image(unsigned int* texture, const char* filename) {

	int width, height, nrChannels;
	glGenTextures(1, texture);	//para1:纹理的数量 para2:生成的纹理的索引
	glBindTexture(GL_TEXTURE_2D, *texture);
	//=========设置环绕方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//======================================

	unsigned char* data = stbi_load(filename, &width, &height, &nrChannels, 0);

	printf("%d\n", nrChannels);
	GLenum format;
	if (nrChannels == 1)
		format = GL_RED;
	else if (nrChannels == 3)
		format = GL_RGB;
	else if (nrChannels == 4)
		format = GL_RGBA;
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load texture" << std::endl;
	}
	//stbi_set_flip_vertically_on_load(true);	//反转纹理，如果纹理是正的就不要反转了 不然就变成倒的了
	stbi_image_free(data);
}


unsigned int loadCubemap(std::vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
	GLenum format;
	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		printf("%d\n", nrChannels);
		if (nrChannels == 1)
			format = GL_RED;
		else if (nrChannels == 3)
			format = GL_RGB;
		else if (nrChannels == 4)
			format = GL_RGBA;
		if (data) {
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		}
		else {
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

#pragma region Input Function
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	float cameraSpeed = 2.5f * deltaTime;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.ProcessKeyboard(FORWARD, deltaTime);
	}if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.ProcessKeyboard(BACKWARD, deltaTime);
	}if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.ProcessKeyboard(LEFT, deltaTime);
	}if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.ProcessKeyboard(RIGHT, deltaTime);
	}if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		camera.ProcessKeyboard(UP, deltaTime);
	}if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		camera.ProcessKeyboard(DOWN, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		camera.MovementSpeed = 10.0f;
	}
	else {
		camera.MovementSpeed = 2.5f;
	}
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

#pragma endregion 
