#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <config.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;

};

static ShaderProgramSource ParseShader(const std::string& filePath)
{
    std::ifstream stream(filePath);
    enum class ShaderType
    {
        NONE =-1,VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while (getline(stream,line))
    {
        std::cout << "12" << std::endl;
        
        if(line.find("#shader")!= std::string::npos)
        {
            if(line.find("vertex") != std::string::npos)
                type = ShaderType::VERTEX;
            else if(line.find("fragment") != std::string::npos)
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line <<'\n';
        }

    }
    
    return { ss[0].str(),ss[1].str()};
}

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id,1,&src,nullptr);
    glCompileShader(id);
    return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER,vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER,fragmentShader);

    glAttachShader(program,vs);
    glAttachShader(program,fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

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

    //create shader
    ShaderProgramSource source = ParseShader("res/shaders/Basic.shader");
    std::cout << source.VertexSource << std::endl;
    std::cout << source.FragmentSource << std::endl;
    std::cout << "saa" << std::endl;


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