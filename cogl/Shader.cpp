//
// Created by ekin4 on 26/02/2017.
//

#include "Shader.h"

namespace cogl {
    Shader::Shader(const char *vertex_file_path, const char *fragment_file_path) {
        loadAndCompile(vertex_file_path, fragment_file_path);
    }

    Shader::Shader(const char *shader_file_path) {
        loadAndCompile(std::string(shader_file_path).append(".vs.glsl").c_str(),
                       std::string(shader_file_path).append(".fs.glsl").c_str());
    }

    Shader::Shader(std::string vertex_file_path, std::string fragment_file_path) {
        loadAndCompile(vertex_file_path.c_str(), fragment_file_path.c_str());
    }

    Shader::Shader(std::string shader_file_path) {
        loadAndCompile(std::string(shader_file_path).append(".vs.glsl").c_str(),
                       std::string(shader_file_path).append(".fs.glsl").c_str());
    }

    Shader::Shader(Shader &&other) {
        std::swap(this->Program, other.Program);
    }

    Shader &Shader::operator=(Shader &&other) {
        std::swap(this->Program, other.Program);
        return *this;
    }

    Shader::~Shader() {
        glUseProgram(0);
        if (glIsProgram(Program)) glDeleteProgram(Program);
    }

    void Shader::loadAndCompile(const char *vertex_file_path, const char *fragment_file_path) {
        // Create the shaders
        GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

        // Read the Vertex Shader code from the file
        std::string VertexShaderCode;
        std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
        if (VertexShaderStream.is_open()) {
            std::string Line = "";
            while (getline(VertexShaderStream, Line))
                VertexShaderCode += "\n" + Line;
            VertexShaderStream.close();
        } else {
            printf("Impossible to open %s. Are you in the right directory?\n", vertex_file_path);
            getchar();
        }

        // Read the Fragment Shader code from the file
        std::string FragmentShaderCode;
        std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
        if (FragmentShaderStream.is_open()) {
            std::string Line = "";
            while (getline(FragmentShaderStream, Line))
                FragmentShaderCode += "\n" + Line;
            FragmentShaderStream.close();
        }

        GLint Result = GL_FALSE;
        int InfoLogLength;

        // Compile Vertex Shader
        printf("Compiling shader : %s\n", vertex_file_path);
        char const *VertexSourcePointer = VertexShaderCode.c_str();
        glShaderSource(VertexShaderID, 1, &VertexSourcePointer, NULL);
        glCompileShader(VertexShaderID);

        // Check Vertex Shader
        glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if (InfoLogLength > 0) {
            std::vector<char> VertexShaderErrorMessage(InfoLogLength + 1);
            glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
            printf("%s\n", &VertexShaderErrorMessage[0]);
        }



        // Compile Fragment Shader
        printf("Compiling shader : %s\n", fragment_file_path);
        char const *FragmentSourcePointer = FragmentShaderCode.c_str();
        glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer, NULL);
        glCompileShader(FragmentShaderID);

        // Check Fragment Shader
        glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
        glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if (InfoLogLength > 0) {
            std::vector<char> FragmentShaderErrorMessage(InfoLogLength + 1);
            glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
            printf("%s\n", &FragmentShaderErrorMessage[0]);
        }

        // Link the program
        printf("Linking program\n");
        Program = (GLuint) glCreateProgram();
        glAttachShader(Program, VertexShaderID);
        glAttachShader(Program, FragmentShaderID);
        glLinkProgram(Program);

        // Check the program
        glGetProgramiv(Program, GL_LINK_STATUS, &Result);
        glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &InfoLogLength);
        if (InfoLogLength > 0) {
            std::vector<char> ProgramErrorMessage(InfoLogLength + 1);
            glGetProgramInfoLog(Program, InfoLogLength, NULL, &ProgramErrorMessage[0]);
            printf("%s\n", &ProgramErrorMessage[0]);
        }

        glValidateProgram(Program);
        check_gl_error();


        glDetachShader(Program, VertexShaderID);
        glDetachShader(Program, FragmentShaderID);
        glDeleteShader(VertexShaderID);
        glDeleteShader(FragmentShaderID);
    }

    void Shader::bind() const {
        glUseProgram(this->Program);
    }

    GLuint Shader::getUniformLoc(const char *uniformName) const {
        return (GLuint) glGetUniformLocation(Program, uniformName);
    }

    GLuint Shader::getAttribLoc(const char *attribName) const {
        return (GLuint) glGetAttribLocation(Program, attribName);
    }


}