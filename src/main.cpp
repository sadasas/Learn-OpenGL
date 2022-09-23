#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <config.h>

//creata macros
#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GlCheckError();\
x;\
ASSERT(GlCheckCall(#x,__FILE__,__LINE__)) 


static void GlCheckError()
{
    while (glGetError() != GL_NO_ERROR);

}

static bool GlCheckCall(const char* function, const char* file , int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << error << " " << function << " " << file << " " << line << std::endl;
        return false;
       
    }

    return true;
    
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
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
    {
        std::cout << "error";
    }

    //create triangle pos
    float positions[] ={
        -0.5f, -0.5f, //0
        0.5f, -0.5f, //1
        0.5f, 0.5f, //2
        -0.5f, 0.5f, //3
    };

    unsigned int indices[]= {
        0,1,2,
        2,3,0
    };

    //create vertex buffer
    unsigned int buffer;
    glGenBuffers(1,&buffer);
    glBindBuffer(GL_ARRAY_BUFFER,buffer);
    glBufferData(GL_ARRAY_BUFFER,6 * 2 * sizeof(float),positions,GL_STATIC_DRAW);
    
    //create vertex atribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(float)*2 ,0);

    //create indices buffer
    unsigned int ibo;
    glGenBuffers(1 ,&ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,6 * sizeof(unsigned int),indices,GL_STATIC_DRAW);

    //create shader
    std::string vertexShader = 
    "#version 330 core\n"
    "\n"
    "layout(location = 0) in vec4 position;"
    "\n"
    "void main()\n"
    "{\n"
    "gl_Position = position;\n"
    "}\n";

     std::string fragmentShader = 
    "#version 330 core\n"
    "\n"
    "layout(location = 0) out vec4 color;"
    "\n"
    "uniform vec4 u_Color;"
    "\n"
    "void main()\n"
    "{\n"
    "color = u_Color;\n"
    "}\n";

    unsigned int shader = CreateShader(vertexShader,fragmentShader);
    glUseProgram(shader);

    //search uniform registered and modified value
     GLCall(int location =  glGetUniformLocation(shader,"u_Color"));
     ASSERT(location!= -1);
     GLCall(glUniform4f(location,1.0f,0.0f,0.0f,1.0f));

    float r = 0.0f;
    float increment = 0.05f;
    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // Render

        glClear(GL_COLOR_BUFFER_BIT);

        // shaders
        GLCall(glUniform4f(location,r,0.3f,0.8f,1.0f));
        GLCall(glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,nullptr));

        if(r > 1.0f) increment = -0.05f;
        else if(r < 0.0f)increment = 0.05f;

        r+= increment;
        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Poll for and process events
        glfwPollEvents();
    }
    glDeleteProgram(shader);
    glfwTerminate();
    return 0;
}