#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480 

struct ShaderProgram {

    GLuint vertexShader = 0;

};

std::string Load_File(const std::string& filePath) {
    std::ifstream file(filePath);
    std::string fileContent;
    std::string line;

    if (!file.is_open()) {
        std::cerr << "The file could not be opened: " << filePath << std::endl;
        std::exit(EXIT_FAILURE);
    }

    while (std::getline(file, line)) {
        fileContent += line + "\n";
    }

    file.close();
    return fileContent;
}

GLuint LoadVertexShader(const std::string& filePath) {

    //Create a vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    //Use create function to read and the store
    std::string sShaderCode = Load_File(filePath);
    const char* cShaderSource = sShaderCode.c_str();

    //relate shader with the code
    glShaderSource(vertexShader, 1, &cShaderSource, nullptr);

    //Compile el vertex shader
    glCompileShader(vertexShader);

    //Check errors
    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    //If we have a success, return the vertex shader
    if (success) {

        return vertexShader;

    }
    else {

        //Log lenght
        GLint logLength;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength);

        //Obtain the log
        std::vector<GLchar> errorLog(logLength);
        glGetShaderInfoLog(vertexShader, logLength, nullptr, errorLog.data());

        //Show the log and finish the program
        std::cerr << "There is an error in the load of vertex shader: " << errorLog.data() << std::endl;
        std::exit(EXIT_FAILURE);


    }
}


void init() {

    glClearColor(1.0, 1.0, 1.0, 1.0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);


}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(0.0, 0.0, 0.0);

    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.5f, -0.5f);
    glVertex2f(0.0f, 0.5f);
    glEnd();

    glutSwapBuffers();
}


GLuint CreateProgram(const ShaderProgram& shaders) {

    GLuint program = glCreateProgram();
    if (shaders.vertexShader != 0) {

        glAttachShader(program, shaders.vertexShader);

    }

    glLinkProgram(program);

    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    //return program if everything is ok

    if (success) {

        //free resources
        if (shaders.vertexShader != 0) {
            glDetachShader(program, shaders.vertexShader);
        }

        return program;

    }
    else {

        GLint logLength;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);


        //store log
        std::vector<GLchar> errorLog(logLength);
        glGetProgramInfoLog(program, logLength, nullptr, errorLog.data());

        std::cerr << "Error to link the program:" << errorLog.data() << std::endl;
        std::exit(EXIT_FAILURE);

    }

}


int main(int argc, char** argv) {

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("GLUT Window");

    glewInit(); //HA DE SER DESPRÉS DE CREAR LA FINESTRA


    ShaderProgram myFirstProgram;
    myFirstProgram.vertexShader = LoadVertexShader("myShader.vert");

    //Compile program
    GLuint myFirstCompiledProgram;
    myFirstCompiledProgram = CreateProgram(myFirstProgram);

    //Indicate the GPU to use our program
    glUseProgram(myFirstCompiledProgram);


    init();
    glutDisplayFunc(Display);
    glutMainLoop();

    glUseProgram(0);
    glDeleteProgram(myFirstCompiledProgram);

    return 0;
}
