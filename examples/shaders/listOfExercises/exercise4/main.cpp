#include <GL/glew.h>
#include <GL/glut.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480 

GLuint myFirstCompiledProgram;
GLuint VAO, VBO;

struct ShaderProgram {

    GLuint vertexShader = 0;
    //GLuint geometryShader = 0;
    GLuint fragmentShader = 0;

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

GLuint LoadGeomtryShader(const std::string& filePath) {

    //Create a vertex shader
    GLuint geometryShader = glCreateShader(GL_GEOMETRY_SHADER);

    //Use create function to read and the store
    std::string sShaderCode = Load_File(filePath);
    const char* cShaderSource = sShaderCode.c_str();

    //relate shader with the code
    glShaderSource(geometryShader, 1, &cShaderSource, nullptr);

    //Compile el vertex shader
    glCompileShader(geometryShader);

    //Check errors
    GLint success;
    glGetShaderiv(geometryShader, GL_COMPILE_STATUS, &success);

    //If we have a success, return the vertex shader
    if (success) {

        return geometryShader;

    }
    else {

        //Log lenght
        GLint logLength;
        glGetShaderiv(geometryShader, GL_INFO_LOG_LENGTH, &logLength);

        //Obtain the log
        std::vector<GLchar> errorLog(logLength);
        glGetShaderInfoLog(geometryShader, logLength, nullptr, errorLog.data());

        //Show the log and finish the program
        std::cerr << "There is an error in the load of vertex shader: " << errorLog.data() << std::endl;
        std::exit(EXIT_FAILURE);


    }
}

GLuint LoadFragmentShader(const std::string& filePath) {

    //Create a vertex shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    //Use create function to read and the store
    std::string sShaderCode = Load_File(filePath);
    const char* cShaderSource = sShaderCode.c_str();

    //relate shader with the code
    glShaderSource(fragmentShader, 1, &cShaderSource, nullptr);

    //Compile el vertex shader
    glCompileShader(fragmentShader);

    //Check errors
    GLint success;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    //If we have a success, return the vertex shader
    if (success) {

        return fragmentShader;

    }
    else {

        //Log lenght
        GLint logLength;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength);

        //Obtain the log
        std::vector<GLchar> errorLog(logLength);
        glGetShaderInfoLog(fragmentShader, logLength, nullptr, errorLog.data());

        //Show the log and finish the program
        std::cerr << "There is an error in the load of fragment shader: " << errorLog.data() << std::endl;
        std::exit(EXIT_FAILURE);


    }
}


GLuint CreateProgram(const ShaderProgram& shaders) {

    GLuint program = glCreateProgram();
    if (shaders.vertexShader != 0) {

        glAttachShader(program, shaders.vertexShader);

    }
    /*
    if (shaders.geometryShader!=0){
        glAttachShader(program, shaders.geometryShader);
    }*/
    if (shaders.fragmentShader!=0){
        glAttachShader(program, shaders.fragmentShader);
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
        /*
        if (shaders.geometryShader !=0){
            glDetachShader(program, shaders.geometryShader);
        }*/
        if (shaders.fragmentShader != 0){
            glDetachShader(program, shaders.fragmentShader);
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

void init() {

    glClearColor(0.0, 0.0, 0.0, 1.0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

     float vertices[] = {
        // position   // color
        -0.5f, -0.5f, 1.0f ,0.0f , 0.0f,   // vertex 1
        0.5f , -0.5f, 0.0f , 1.0f , 0.0f,
        0.0f , 0.5f , 0.0f , 0.0f , 1.0f
    };
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    //color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float),(void*)(2*sizeof(float)) );
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);

}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0);

     //Indicate the GPU to use our program
    glUseProgram(myFirstCompiledProgram);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glBindVertexArray(0);
    glUseProgram(0);

    glutSwapBuffers();
}



int main(int argc, char** argv) {

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("GLUT Window");

    glewInit(); //HA DE SER DESPR�S DE CREAR LA FINESTRA


    ShaderProgram myFirstProgram;
    myFirstProgram.vertexShader = LoadVertexShader("myShader.vert");
    //myFirstProgram.geometryShader = LoadGeomtryShader("myShader.geom");
    myFirstProgram.fragmentShader = LoadFragmentShader("myShader.frag");

    //Compile program
    myFirstCompiledProgram = CreateProgram(myFirstProgram);


    init();
    glutDisplayFunc(Display);
    glutMainLoop();

    glUseProgram(0);
    glDeleteProgram(myFirstCompiledProgram);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    return 0;
}