#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <config.h>

int main(int argc, char *argv[])
{
    std::cout << argv[0] << " Version " << PROJECT_VERSION_MAJOR << " " << PROJECT_VERSION_MINOR << "\n";

    // init window
    GLFWwindow *window;

    // Initialize the library
    if (!glfwInit())
        return -1;

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "error";
    }

    //create triangle pos
    float positions[6] ={
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f,
    };
    //create vertex buffer
    unsigned int buffer;
    glGenBuffers(1,&buffer);
    glBindBuffer(GL_ARRAY_BUFFER,buffer);
    glBufferData(GL_ARRAY_BUFFER,6 * sizeof(float),positions,GL_STATIC_DRAW);
    
    //create vertex atribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(float)*2 ,0);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // Render

        glClear(GL_COLOR_BUFFER_BIT);

        // shaders
        glDrawArrays(GL_TRIANGLES,0,3);
    

        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}