#include <GLFW/glfw3.h>
#include <iostream>
#include <config.h>

int main(int argc, char* argv[])
{
    std::cout << argv[0] << " Version "<< PROJECT_VERSION_MAJOR << " " << PROJECT_VERSION_MINOR << "\n";

	//init window 
    GLFWwindow* window;
    
    //Initialize the library 
    if (!glfwInit())
        return -1;

    //Create a windowed mode window and its OpenGL context 
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    //Make the window's context current 
    glfwMakeContextCurrent(window);

    //Loop until the user closes the window 
    while (!glfwWindowShouldClose(window))
    {
    // Render 

        glClear(GL_COLOR_BUFFER_BIT);
        
        //draw triangle
        glBegin(GL_TRIANGLES);
        glVertex2d(-0.5f,-0.5f);
        glVertex2d(0.0f,0.5f);
        glVertex2d(0.5f,-0.5f);
        glEnd();


        //Swap front and back buffers 
        glfwSwapBuffers(window);

        //Poll for and process events 
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}