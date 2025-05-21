#include <GL/glew.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480 

 GLuint VAO, VBO;
 std::vector<GLuint> myFirstCompiledProgram;
 

 struct GameObject{
    glm::vec3 position = glm::vec3(0.f);
    glm::vec3 forward = glm::vec3(1.f, 0.f, 0.f);
    float fVelocity = 0.1f;
 };

 GameObject cube;

struct ShaderProgram {

    GLuint vertexShader = 0;
    GLuint geometryShader = 0;
    GLuint fragmentShader = 0;

};

void Cleanup() {
    if (!myFirstCompiledProgram.empty()) {
        glDeleteProgram(myFirstCompiledProgram[0]);
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

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

GLuint LoadGeometryShader(const std::string& filePath) {

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
    if (shaders.geometryShader!=0){
        glAttachShader(program, shaders.geometryShader);
    }
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
        if (shaders.geometryShader !=0){
            glDetachShader(program, shaders.geometryShader);
        }
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


glm::mat4 GenerateTranslationMatrix(glm::vec3 translation){

    return glm::translate(glm::mat4(1.0f), translation);

}

void init() {

    glClearColor(0.0, 0.0, 0.0, 1.0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    

       float vertices[] = {
       -0.5f, 0.5f, -0.5f, //3
       0.5f, 0.5f , -0.5f,  //2
       -0.5f, 0.5f , -0.5f,  //6
       0.5f, -0.5f , -0.5f,   //7
        0.5f, -0.5f , 0.5f, //4
        0.5f, 0.5f , -0.5f, //2
        0.5f , 0.5f, 0.5f, //0
        -0.5f, 0.5f, -0.5f, //3
        -0.5f, 0.5f , 0.5f, //1
        -0.5f, 0.5f , -0.5f,  //6
        -0.5f , -0.5f, 0.5f, //5
        0.5f, -0.5f , 0.5f, //4
        -0.5f, 0.5f , 0.5f, //1
        0.5f , 0.5f, 0.5f //0
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

}

void Display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      
     //Indicate the GPU to use our program
    glUseProgram(myFirstCompiledProgram[0]);
    glBindVertexArray(VAO);

    // UPDATE CUBE POSITION
    cube.position += cube.forward * cube.fVelocity;
    if (cube.position.x >= 0.5f || cube.position.x <= -0.5f) {
        cube.forward *= -1.f;
    }

    // CREATE AND UPLOAD TRANSFORM MATRIX
    glm::mat4 cubeModel = GenerateTranslationMatrix(cube.position);
    GLuint transformLoc = glGetUniformLocation(myFirstCompiledProgram[0], "transform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(cubeModel));

    // DRAW WITH CORRECT VERTEX COUNT
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 14);



    glBindVertexArray(0);
    glUseProgram(0);

    glutSwapBuffers();
    glutPostRedisplay();
}



int main(int argc, char** argv) {

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("GLUT Window");

    glewInit(); 

    atexit(Cleanup);

    ShaderProgram myFirstProgram;
    myFirstProgram.vertexShader = LoadVertexShader("myShader.vert");
    //myFirstProgram.geometryShader = LoadGeometryShader("myShader.geom");
    myFirstProgram.fragmentShader = LoadFragmentShader("myShader.frag");

    //Compile program
    myFirstCompiledProgram.push_back(CreateProgram(myFirstProgram));

    

    init();
    glutDisplayFunc(Display);
    glutMainLoop();

    
    return 0;
}