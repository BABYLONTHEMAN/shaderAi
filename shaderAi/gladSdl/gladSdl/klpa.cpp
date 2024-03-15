#include <iostream>
#include <thread>
#include <SDL.h>
#include "glad/gl.h"
#include <glm.hpp>
//#include "Shader.h"
//#include "Texture.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "Transform.h"
#include <../glm/gtc/matrix_transform.hpp>
#include<../glm/glm.hpp>
#include<../glm/gtc/type_ptr.hpp>
//#include <GL/glew.h>

#include <random>
#include <math.h>


#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


bool swranawa = false;
unsigned int loadTexture(const char* path);
void mouse_callback(SDL_Event* event);
void scroll_callback(SDL_Event* event);
bool running = true;
bool isDragging = false;
int startX = 0, startY = 0;
float minFOV = 1.0f; float maxFOV = 200.0f;  float FOV = 45.0f;

//unsigned int loadTexture(const char* path);
static const char* vShader = "Shaders/shader.vert";
// Fragment Shader
static const char* fShader = "Shaders/shader.frag";

//class shaderAi.h
//I don't know yet but kind of doing all the shader/s stuff
class shaderAi
{
public:
    enum class JoryShader { VERTEX_SHADER, FRAGMENT_SHADER, TESS_CONTROL_SHADER, TESS_EVALUATION_SHADER };

public:
    static shaderAi* daspeka();

public:
    bool drwstkaProgram();
    bool drwstkaShader();

    bool koikarawaShader(const std::string& nawiFile, JoryShader joryShader);
    void bilkenaShader();
    bool bibastawaShader();

    void jyaikarawaShader();
    void lanawyBaraShader();
    void lanawyBaraProgram();
    GLuint getShaderId(JoryShader shaderType);
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec2(const std::string& name, const glm::vec2& value) const;
    void setVec2(const std::string& name, float x, float y) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
    void setVec4(const std::string& name, const glm::vec4& value) const;
    void setVec4(const std::string& name, float x, float y, float z, float w);
    void setMat2(const std::string& name, const glm::mat2& mat) const;
    void setMat3(const std::string& name, const glm::mat3& mat) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;

    void bakaryBena();
    void set(const std::string& name, bool value) const;
    void set(const std::string& name, int value) const;
    void set(const std::string& name, float value) const;
    void set(const std::string& name, glm::mat4 value) const;
    void set(const std::string& name, float r, float g, float b) const;
    void set(const std::string& name, glm::vec3 value) const;


    //GLuint m_IdprogramyShaderaka;

private:
    shaderAi();
    shaderAi(const shaderAi&);
    shaderAi& operator = (shaderAi&);
private:
    GLuint m_IdprogramyShaderaka;
    GLuint m_IdVertexyShader;
    GLuint m_IdFragmentyShader;
    GLuint m_IdTessellEvaShader;
    GLuint m_IdTessCtrlShader;


};


// <shaderAi.cpp>
shaderAi* shaderAi::daspeka()
{
    static shaderAi* shaderAiObj = new shaderAi();
    return shaderAiObj;
}

shaderAi::shaderAi()
{
    m_IdprogramyShaderaka = 0;
    m_IdVertexyShader = 0;
    m_IdFragmentyShader = 0;
    m_IdTessellEvaShader = 0;
    m_IdTessCtrlShader = 0;


}

bool shaderAi::drwstkaProgram()
{
    m_IdprogramyShaderaka = glCreateProgram();
    if (m_IdprogramyShaderaka == 0)
    {
        std::cout << "\n err drwstkaProgram \n";
        return false;
    }

    return true;
}

bool shaderAi::drwstkaShader()
{
    m_IdVertexyShader = glCreateShader(GL_VERTEX_SHADER);

    if (m_IdVertexyShader == 0)
    {
        std::cout << "\n err (m_IdVertexyShader)y drwstkaShader \n";
        return false;
    }
    m_IdFragmentyShader = glCreateShader(GL_FRAGMENT_SHADER);

    if (m_IdFragmentyShader == 0)
    {
        std::cout << "\n err (m_IdFragmentyShader)y drwstkaShader \n";
        return false;
    }
    m_IdTessellEvaShader = glCreateShader(GL_TESS_EVALUATION_SHADER);
    if (m_IdTessellEvaShader == 0)
    {
        std::cout << "\n err (m_IdTessellEvaShader)y drwstkaShader \n";
        return false;
    }
    m_IdTessCtrlShader = glCreateShader(GL_TESS_CONTROL_SHADER);

    if (m_IdTessCtrlShader == 0)
    {
        std::cout << "\n err (m_IdTessCtrlShader)y drwstkaShader \n";
        return false;
    }
    return true;
}

bool shaderAi::koikarawaShader(const std::string& nawiFile, JoryShader joryShader) //koikarawaShader ---=====wata> compile...
{
    std::fstream file;
    std::string text;
    std::string sarchawayCode;
    GLuint idShader;

    //idShader = (joryShader == JoryShader::VERTEX_SHADER)? m_IdVertexyShader : m_IdFragmentyShader;

    switch (joryShader) {
    case JoryShader::VERTEX_SHADER:
        idShader = m_IdVertexyShader;
        //"\033[1;31mDway Away\033[0m"
        std::cout << "\033[1;36m";
        std::cout << "\n  idShader = m_IdVertexyShader; \n";
        break;
    case JoryShader::FRAGMENT_SHADER:
        idShader = m_IdFragmentyShader;
        std::cout << "\n  idShader = m_IdFragmentyShader;\n";
        break;
    case JoryShader::TESS_CONTROL_SHADER:
        idShader = m_IdTessCtrlShader;
        std::cout << "\n  idShader = m_IdTessCtrlShader;\n";
        break;
    case JoryShader::TESS_EVALUATION_SHADER:
        idShader = m_IdTessellEvaShader;
        std::cout << "\n idShader = m_IdTessellEvaShader;\n";
        break;
    default:
        std::cout << "\n Invalid shader type \n";
        return false; // Return false for error case
        //return 0; // Return 0 or handle error case
        std::cout << "\033[0m";
    }

   /* file.open(nawiFile);


    if (!file)
    {
        std::cout << "\033[33m\n err xwendnaway filey shader (file.open(nawiFile) ...\033[0m"<<"\033[1;32mAm file'a chakka \033[0m" << "\033[1;33m" <<">>"<< " \033[0m" << "\033[1;35m" << nawiFile << "\033[0m";
    }

    while (!file.eof())
    {
        std::getline(file, text);
        sarchawayCode += text + "\n";
    }

    file.close();*/

    file.open(nawiFile);
    if (!file.is_open())
    {
        std::cout << "\033[33m\n err xwendnaway filey shader (file.open(nawiFile) ...\033[0m" << "\033[1;32mAm file'a chakka \033[0m" << "\033[1;33m" << ">>" << " \033[0m" << "\033[1;35m" << nawiFile << "\033[0m";
        return false; // Return false to indicate failure
    }

    while (std::getline(file, text))
    {
        sarchawayCode += text + "\n";
    }

    file.close();

    //kota sarchawaycode
    const GLchar* kotasarchawayCode = reinterpret_cast<const GLchar*> (sarchawayCode.c_str());
    glShaderSource(idShader, 1, &kotasarchawayCode, nullptr);
    glCompileShader(idShader);
    GLint halayCode;
    glGetShaderiv(idShader, GL_COMPILE_STATUS, &halayCode);
    if (halayCode == GL_TRUE)
    {
        std::cout << "\n kokrdnaway shader sarkawtw bw \n";
    }
    else
    {
        GLchar errMsg[1000];
        GLsizei errSize = 1000;

        glGetShaderInfoLog(idShader, errSize, &errSize, errMsg);
        std::cout << "\n " << errMsg << "\n ";
    }
    return true;
}

void shaderAi::bilkenaShader() //bilkenaShader ---=====wata> Attach...
{
    glAttachShader(m_IdprogramyShaderaka, m_IdVertexyShader);
    glAttachShader(m_IdprogramyShaderaka, m_IdFragmentyShader);
    glAttachShader(m_IdprogramyShaderaka, m_IdTessCtrlShader);
    glAttachShader(m_IdprogramyShaderaka, m_IdTessellEvaShader);
}

bool shaderAi::bibastawaShader()
{
    glLinkProgram(m_IdprogramyShaderaka);

    glUseProgram(m_IdprogramyShaderaka);

    GLint halayCode;
    glGetProgramiv(m_IdprogramyShaderaka, GL_LINK_STATUS, &halayCode);
    if (halayCode == GL_TRUE)
    {
        std::cout << "\033[1;36m" << "\n bastnaway shader sarkawtw bw\n\n";
    }
    else
    {
        GLchar errMsg[1000];
        GLsizei errSize = 1000;

        glGetProgramInfoLog(m_IdprogramyShaderaka, errSize, &errSize, errMsg);
        std::cout << "\n " << errMsg << "\n ";

    }

    return true;
}

void shaderAi::jyaikarawaShader() //jyaikarawaShader ---=====wata> Detach...
{
    glDetachShader(m_IdprogramyShaderaka, m_IdVertexyShader);
    glDetachShader(m_IdprogramyShaderaka, m_IdFragmentyShader);
    glDetachShader(m_IdprogramyShaderaka, m_IdTessCtrlShader);
    glDetachShader(m_IdprogramyShaderaka, m_IdTessellEvaShader);
    std::cout << "\033[1;33m" << "\n jyakrdnaway Shader Sarkawtw bw" << " \033[0m" << std::endl;
}

void shaderAi::lanawyBaraShader() //lanawyBaraShader ---=====wata> Delete...
{
    glDeleteShader(m_IdVertexyShader);
    glDeleteShader(m_IdFragmentyShader);
    glDeleteShader(m_IdTessCtrlShader);
    glDeleteShader(m_IdTessellEvaShader);


}

void shaderAi::lanawyBaraProgram()
{
    glDeleteProgram(m_IdprogramyShaderaka);
}


//set w met 
void shaderAi::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_IdprogramyShaderaka, name.c_str()), (int)value);
}
// ------------------------------------------------------------------------
void shaderAi::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(m_IdprogramyShaderaka, name.c_str()), value);
}
// ------------------------------------------------------------------------
void shaderAi::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(m_IdprogramyShaderaka, name.c_str()), value);
}
// ------------------------------------------------------------------------
void shaderAi::setVec2(const std::string& name, const glm::vec2& value) const
{
    glUniform2fv(glGetUniformLocation(m_IdprogramyShaderaka, name.c_str()), 1, &value[0]);
}
void shaderAi::setVec2(const std::string& name, float x, float y) const
{
    glUniform2f(glGetUniformLocation(m_IdprogramyShaderaka, name.c_str()), x, y);
}
// ------------------------------------------------------------------------
void shaderAi::setVec3(const std::string& name, const glm::vec3& value) const
{
    glUniform3fv(glGetUniformLocation(m_IdprogramyShaderaka, name.c_str()), 1, &value[0]);
}
void shaderAi::setVec3(const std::string& name, float x, float y, float z) const
{
    glUniform3f(glGetUniformLocation(m_IdprogramyShaderaka, name.c_str()), x, y, z);
}
// ------------------------------------------------------------------------
void shaderAi::setVec4(const std::string& name, const glm::vec4& value) const
{
    glUniform4fv(glGetUniformLocation(m_IdprogramyShaderaka, name.c_str()), 1, &value[0]);
}
void shaderAi::setVec4(const std::string& name, float x, float y, float z, float w)
{
    glUniform4f(glGetUniformLocation(m_IdprogramyShaderaka, name.c_str()), x, y, z, w);
}
// ------------------------------------------------------------------------
void shaderAi::setMat2(const std::string& name, const glm::mat2& mat) const
{
    glUniformMatrix2fv(glGetUniformLocation(m_IdprogramyShaderaka, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void shaderAi::setMat3(const std::string& name, const glm::mat3& mat) const
{
    glUniformMatrix3fv(glGetUniformLocation(m_IdprogramyShaderaka, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}
// ------------------------------------------------------------------------
void shaderAi::setMat4(const std::string& name, const glm::mat4& mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_IdprogramyShaderaka, name.c_str()), 1, GL_FALSE, &mat[0][0]);

}


//set stuff /*https://github.com/Khasehemwy/LearnOpenGL/blob/master/OpenGL/Shader.h */
void shaderAi::bakaryBena()
{
    glUseProgram(m_IdprogramyShaderaka);
}


void shaderAi::set(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_IdprogramyShaderaka, name.c_str()), (int)value);
}
void shaderAi::set(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(m_IdprogramyShaderaka, name.c_str()), value);
}
void shaderAi::set(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(m_IdprogramyShaderaka, name.c_str()), value);
}

void shaderAi::set(const std::string& name, glm::mat4 value) const
{
    glUniformMatrix4fv(glGetUniformLocation(m_IdprogramyShaderaka, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void shaderAi::set(const std::string& name, float r, float g, float b) const
{
    glUniform3f(glGetUniformLocation(m_IdprogramyShaderaka, name.c_str()), r, g, b);
}
void shaderAi::set(const std::string& name, glm::vec3 value) const
{
    glUniform3fv(glGetUniformLocation(m_IdprogramyShaderaka, name.c_str()), 1, &value[0]);
}


//set w met </>
//</shaderAi.cpp>




////SHADER
//std::vector<Shader>shaderList;

//()_()_()_()_()_()_()_()_()_shader.h()_()_()_()_()_()_()_()_()_()_()
class Shader {
public:
    GLuint uniformProjection, uniformView;

    unsigned int ID;

    Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr,
        const char* tessControlPath = nullptr, const char* tessEvalPath = nullptr);

    void renderPass(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

    std::string ReadFile(const char* fileLoc);
    GLuint GetProjectionLocation();
    GLuint GetModelLocation();
    GLuint GetViewLocation();

    inline void compileShader(const char* vertexCode, const char* fragmentCode);
    void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);

    void use();

    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec2(const std::string& name, const glm::vec2& value) const;
    void setVec2(const std::string& name, float x, float y) const;
    void setVec3(const std::string& name, const glm::vec3& value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;
    void setVec4(const std::string& name, const glm::vec4& value) const;
    void setVec4(const std::string& name, float x, float y, float z, float w);
    void setMat2(const std::string& name, const glm::mat2& mat) const;
    void setMat3(const std::string& name, const glm::mat3& mat) const;
    void setMat4(const std::string& name, const glm::mat4& mat) const;

    inline void createFromFiles(const char* vertexLocation, const char* fragmentLocation);
    inline void createFromString(const char* vertexCode, const char* fragmentCode);

public:
    void checkCompileErrors(GLuint shader, std::string type);
};

std::vector<Shader> shaderList;
//()_()_()_()_()_()_()_()_()_</shader.h>_()_()_()_()_()_()_()_()_()_()

//()_()_()_()_()_()_()_()_()_()_()_shader.cpp()_()_()_()_()_()_()_()_()

 //()()()()()()()()()()()()()()()()(
void Shader::use()
{
    glUseProgram(ID);
}
// utility uniform functions
// ------------------------------------------------------------------------


void Shader::checkCompileErrors(GLuint shader, std::string type)
{

    GLint success;
    GLchar infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            (infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
        uniformProjection = glGetUniformLocation(ID, "projection"); //idy projection axata naw variably uniformProjection

    }
}
/*                            void Shader::createFromString(const char* vertexCode, const char* fragmentCode)

                            {
                                compileShader(vertexCode, fragmentCode);
                            }*/

void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
    GLuint theShader = glCreateShader(shaderType);
    const GLchar* theCode[1];
    theCode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);///////////////////////////

    GLint result = 0;
    GLchar eLog[1024] = { 0 };
    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);

    if (!result)
    {
        glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
        printf("Error compiling %d shader: '%s'\n", shaderType, eLog);
        return;
    }
    glAttachShader(theProgram, theShader);
}

//()()()()()()()()()()()()()()()(
Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath,
    const char* tessControlPath, const char* tessEvalPath) {
    // Implementation of the constructor...
        {
            // 1. retrieve the vertex/fragment source code from filePath
            std::string vertexCode;
            std::string fragmentCode;
            std::string geometryCode;
            std::string tessControlCode;
            std::string tessEvalCode;
            std::ifstream vShaderFile;
            std::ifstream fShaderFile;
            std::ifstream gShaderFile;
            std::ifstream tcShaderFile;
            std::ifstream teShaderFile;
            // ensure ifstream objects can throw exceptions:
            vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            tcShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            teShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            try
            {
                uniformProjection = 0;

                // open files
                vShaderFile.open(vertexPath);
                fShaderFile.open(fragmentPath);
                std::stringstream vShaderStream, fShaderStream;
                // read file's buffer contents into streams
                vShaderStream << vShaderFile.rdbuf();
                fShaderStream << fShaderFile.rdbuf();
                // close file handlers
                vShaderFile.close();
                fShaderFile.close();
                // convert stream into string
                vertexCode = vShaderStream.str();
                fragmentCode = fShaderStream.str();
                // if geometry shader path is present, also load a geometry shader
                if (geometryPath != nullptr)
                {
                    gShaderFile.open(geometryPath);
                    std::stringstream gShaderStream;
                    gShaderStream << gShaderFile.rdbuf();
                    gShaderFile.close();
                    geometryCode = gShaderStream.str();
                }
                if (tessControlPath != nullptr) {
                    tcShaderFile.open(tessControlPath);
                    std::stringstream tcShaderStream;
                    tcShaderStream << tcShaderFile.rdbuf();
                    tcShaderFile.close();
                    tessControlCode = tcShaderStream.str();
                }
                if (tessEvalPath != nullptr) {
                    teShaderFile.open(tessEvalPath);
                    std::stringstream teShaderStream;
                    teShaderStream << teShaderFile.rdbuf();
                    teShaderFile.close();
                    tessEvalCode = teShaderStream.str();
                }
            }
            catch (std::ifstream::failure& e)
            {
                std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: "
                    << e.what() << std::endl;
            }
            const char* vShaderCode = vertexCode.c_str();
            const char* fShaderCode = fragmentCode.c_str();
            // 2. compile shaders
            unsigned int vertex, fragment;
            // vertex shader
            vertex = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex, 1, &vShaderCode, NULL);
            glCompileShader(vertex);
            checkCompileErrors(vertex, "VERTEX");
            // fragment Shader
            fragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment, 1, &fShaderCode, NULL);
            glCompileShader(fragment);
            checkCompileErrors(fragment, "FRAGMENT");
            // if geometry shader is given, compile geometry shader
            unsigned int geometry;
            if (geometryPath != nullptr)
            {
                const char* gShaderCode = geometryCode.c_str();
                geometry = glCreateShader(GL_GEOMETRY_SHADER);
                glShaderSource(geometry, 1, &gShaderCode, NULL);
                glCompileShader(geometry);
                checkCompileErrors(geometry, "GEOMETRY");
            }
            // if tessellation shader is given, compile tessellation shader
            unsigned int tessControl;
            if (tessControlPath != nullptr)
            {
                const char* tcShaderCode = tessControlCode.c_str();
                tessControl = glCreateShader(GL_TESS_CONTROL_SHADER);
                glShaderSource(tessControl, 1, &tcShaderCode, NULL);
                glCompileShader(tessControl);
                checkCompileErrors(tessControl, "TESS_CONTROL");
            }
            unsigned int tessEval;
            if (tessEvalPath != nullptr)
            {
                const char* teShaderCode = tessEvalCode.c_str();
                tessEval = glCreateShader(GL_TESS_EVALUATION_SHADER);
                glShaderSource(tessEval, 1, &teShaderCode, NULL);
                glCompileShader(tessEval);
                checkCompileErrors(tessEval, "TESS_EVALUATION");
            }
            // shader Program
            ID = glCreateProgram();
            glAttachShader(ID, vertex);
            glAttachShader(ID, fragment);
            if (geometryPath != nullptr)
                glAttachShader(ID, geometry);
            if (tessControlPath != nullptr)
                glAttachShader(ID, tessControl);
            if (tessEvalPath != nullptr)
                glAttachShader(ID, tessEval);
            glLinkProgram(ID);
            checkCompileErrors(ID, "PROGRAM");
            // delete the shaders as they're linked into our program now and no longer necessary
            glDeleteShader(vertex);
            glDeleteShader(fragment);
            if (geometryPath != nullptr)
                glDeleteShader(geometry);

        }
}

//void Shader::renderPass(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {
//    // Implementation of renderPass function...
//}
inline void Shader::createFromFiles(const char* vertexLocation, const char* fragmentLocation)
{
    std::string vertexString = ReadFile(vertexLocation);
    std::string fragmentString = ReadFile(fragmentLocation);
    const char* vertexCode = vertexString.c_str();
    const char* fragmentCode = fragmentString.c_str();

    compileShader(vertexCode, fragmentCode);
}
//()()()()()( compile shader 
void Shader::compileShader(const char* vertexCode, const char* fragmentCode)

{

    ID = glCreateProgram();
    if (!ID) {
        printf("error fragment creating ...");

        return;

    }


    AddShader(ID, vertexCode, GL_VERTEX_SHADER);
    AddShader(ID, fragmentCode, GL_FRAGMENT_SHADER);


    //chunk of code 27:30 

    GLint result = 0;
    GLchar eLog[1024] = { 0 };

    glLinkProgram(ID);
    glGetProgramiv(ID, GL_LINK_STATUS, &result);

    if (!result)
    {
        glGetProgramInfoLog(ID, sizeof(eLog), NULL, eLog);
        printf("Error Linking Program  %d shader: '%s ", eLog);
        return;

    }
    glValidateProgram(ID);
    glGetProgramiv(ID, GL_VALIDATE_STATUS, &result);

    if (!result)
    {
        glGetProgramInfoLog(ID, sizeof(eLog), NULL, eLog);
        printf("Error Validating Program  %d shader: '%s ", eLog);
        return;

    }
    //uniformModel = glGetUniformLocation(shader, "xMove");
    //vertexInStuff = glGetAttribLocation(shaderID, "heightmapTexture"); /*Ama bo terrain la bri 1518 chwnka natwanm accessy shaderId bkam laweya boya lerawa aykam*/ 

}


void Shader::createFromString(const char* vertexCode, const char* fragmentCode)

{
    compileShader(vertexCode, fragmentCode);
}


GLuint Shader::GetProjectionLocation()
{
    return uniformProjection;
}
// ... (Implementation of other member functions)

//()_()_()_()_()_()_()_()_()_()_()_</shader.cpp>()_()_()_()_()_()_()_()_()






void createShaders() {
    Shader* shader1 =
        new Shader("Shaders/skyBox.vert", "Shaders/skyBox.frag");
    shader1->createFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);
}

GLuint Shader::GetViewLocation()
{
    return uniformView;

}


std::string Shader::ReadFile(const char* fileloc)
{
    std::string content;
    std::ifstream fileStream(fileloc, std::ios::in);

    if (!fileStream.is_open()) {


        printf("Failed to read %s| File doesn not exist.", fileloc);
        return "";
    }
    std::string line = "";
    while (!fileStream.eof())
    {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }
    fileStream.close();
    return content;
}
/////////////////////////////////////
///////////////SKYBOX///////////////
///////////////Skybox.h///////////////

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 TexCoord; //for skybox, it's vec2? why? I don't know myself dammit
    glm::vec3 Tangent;

    Vertex(const glm::vec3& pos, const glm::vec3& normal, const glm::vec2& tex, glm::vec3& texx, const glm::vec3& tangent)
        : Position(pos), Normal(normal), TexCoords(tex), TexCoord(texx), Tangent(tangent) {}
};


class Mesh
{
public:
    Mesh();

    void createMesh(const GLfloat* vertices, const unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices);
    void RenderMesh();
    void clearMesh();

    // New method to get the vertices.
    const std::vector<glm::vec3>& getVertices() const { return storedVertices; }
    // Method to set the texture for the mesh.


    void setTexture(unsigned int textureID) { //code0
        this->textureID = textureID;
    }


    ~Mesh();


private:
    GLuint VAO, VBO, IBO;
    GLsizei indexCount;
    GLenum error;

    unsigned int textureID;	//code0


    // New member to store the vertex data.
    std::vector<glm::vec3> storedVertices;
};

// ///////////Mesh.h////////////// </>
/////////////////////////////////////


/////////////////////////////////////
///////////////Mesh.cpp////////////// 
Mesh::Mesh()
{
    VAO = 0;
    VBO = 0;
    IBO = 0;
    indexCount = 0;

}
//redefititiony makarawa
//struct Vertex {
//	glm::vec3 Position;
//	glm::vec3 Normal;
//	glm::vec2 TexCoords;
//	glm::vec3 Tangent;
//	// No virtual functions or other complex features.
//};
    // Create mesh using given vertex and index data
void Mesh::createMesh(const GLfloat* vertices, const unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices) {
    // Save the number of indices for rendering later
    indexCount = numOfIndices;

    // Generate and bind vertex array object (VAO)
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate and bind index buffer object (IBO)
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * numOfIndices, indices, GL_STATIC_DRAW);

    // Generate and bind vertex buffer object (VBO)
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    /*glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * numOfVertices * 8, vertices, GL_STATIC_DRAW); */
    if (vertices != nullptr) {
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);
    }
    else {
        // handle null pointer case
        // for example, print an error message and return
        std::cerr << "Error: vertices pointer is null" << std::endl;
        return;
    }

    //VBO for terrainFlat
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, numOfVertices * sizeof(Vertex), vertices, GL_STATIC_DRAW);

    //</VBO for terrainFlat


    // Set vertex attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)(sizeof(GLfloat) * 3));
    glEnableVertexAttribArray(1);
    
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoord));
    //attribpointer for terrainFlat
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
    glEnableVertexAttribArray(3);
    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    //UNBIND

    while ((error = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << error << std::endl;
    }

    storedVertices.clear();
    for (unsigned int i = 0; i < numOfVertices; i += 8) {  // Assuming 8 GLfloats per vertex 
        storedVertices.emplace_back(vertices[i], vertices[i + 1], vertices[i + 2]);
    }
}



void Mesh::RenderMesh()   //called glDrawElements 
{

    // Bind the texture before drawing the mesh
    glBindTexture(GL_TEXTURE_2D, this->textureID); //code0 

    glBindVertexArray(VAO);// bakary aheninawa Bindy akain hamw jare ka bakary ahenin
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO); //some times doesn't need to bind this IBO, this for some graphic card buggs
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);// wena akeshin 
    //When glDrawElements is called,it uses count sequential elements from an enabled array, starting at indices to construct a sequence of geometric primitives.

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); //unbind IBO ka eshman penama
    glBindVertexArray(0); //unbind VAO ka eshman penama 

    glBindTexture(GL_TEXTURE_2D, 0); //code0 // Unbind the texture when done (optional, but good practice)

}


void Mesh::clearMesh()
{
    if (IBO != 0)
    {
        glDeleteBuffers(1, &IBO);
        IBO = 0;
    }

    if (VBO != 0)
    {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }

    if (VAO != 0)
    {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;

    }
    indexCount = 0;
}


Mesh::~Mesh()
{

    clearMesh();
}



Mesh* skyMesh;
class skyBox
{

public:
    skyBox();

    skyBox(std::vector<std::string> faceLocations);
    void DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix);

    ~skyBox();

public:
    //Mesh* veticeModelyYak;
    //Mesh* veticeModelyDw;


    Shader* skyShader; //we use this for createFromFiles 


    GLuint uniformProjection, uniformView;
private:
    GLuint textureID;

};
/////////////////Skybox.h////////////////</>
///////////////////////////////////</>
/////////////////////////////////////

skyBox::skyBox()
{
}
skyBox::skyBox(std::vector<std::string> faceLocations)
{
    //shader setup for skybox
    //skyShader = new Shader();
    //stbi_set_flip_vertically_on_load(true);
    stbi_set_flip_vertically_on_load(false);
    //stbi_set_flip_vertically_on_load(false);

    skyShader->createFromFiles("Shaders/skyBox.vert", "Shaders/skyBox.frag");

    uniformProjection = skyShader->GetProjectionLocation();
    uniformView = skyShader->GetViewLocation();
    //Texture setup for skybox
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    //stbi_set_flip_vertically_on_load(true);
    int width, height, bitdepth;
    for (size_t i = 0; i < 6; i++)
    {
        unsigned char* texData = stbi_load(faceLocations[i].c_str(), &width, &height, &bitdepth, 0);
        if (!texData)
        {
            printf(" failed ...to do stuff find: %s\n", faceLocations[i].c_str());
            return;
        }
        //glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA,
        //width, height, 0, GL_RGBA,GL_UNSIGNED_BYTE, texData); //sometimes skybox throw error use this RGBA

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, texData); //<--- Alpha stuff RGBA error
        stbi_image_free(texData);
        //stbi_set_flip_vertically_on_load(true);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //stbi_set_flip_vertically_on_load(true);

    //Mesh Setup for SkyBox
    unsigned int skyBoxindices[] = {
        //front
        0,1,2,
        2,1,3,
        //right
        2,3,5,
        5,3,7,
        //back
        5,7,4,
        4,7,6,
        //left
        4,6,0,
        0,6,1,
        //top
        4,0,5,
        5,0,2,
        //bottom
        1,6,3,
        3,6,7
    };

    float skyBoxVertices[] = {
        -1.0f,1.0f,-1.0f,      0.0f, 0.0f,   0.0f,0.0f,0.0f,
        -1.0f,-1.0f,-1.0f,     0.0f, 0.0f,   0.0f,0.0f,0.0f,
        1.0f,1.0f,-1.0f,       0.0f, 0.0f,   0.0f,0.0f,0.0f,
        1.0f,-1.0f,-1.0f,      0.0f, 0.0f,   0.0f,0.0f,0.0f,


        -1.0f,1.0f,1.0f,      0.0f, 0.0f,   0.0f,0.0f,0.0f,
        1.0f,1.0f,1.0f,       0.0f, 0.0f,   0.0f,0.0f,0.0f,
        -1.0f,-1.0f,1.0f,     0.0f, 0.0f,   0.0f,0.0f,0.0f,
        1.0f,-1.0f,1.0f,      0.0f, 0.0f,   0.0f,0.0f,0.0f
    };
    skyMesh = new Mesh();
    skyMesh->createMesh(skyBoxVertices, skyBoxindices, 64, 36);

}

void skyBox::DrawSkybox(glm::mat4 viewMatrix, glm::mat4 projectionMatrix) {

    viewMatrix = glm::mat4(glm::mat3(viewMatrix));
    glDepthMask(GL_FALSE);

    //stbi_set_flip_vertically_on_load(false);

    skyShader->use();
    //uniformModel = glGetUniformLocation(shaderID, "model");
    glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    skyMesh->RenderMesh();

    glDepthMask(GL_TRUE);
}

skyBox::~skyBox() {}

skyBox skybox;
void Shader::renderPass(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
    //glfwPollEvents();
    SDL_Event event;
    skybox.DrawSkybox(viewMatrix, projectionMatrix);
    glUseProgram(ID);
    uniformProjection = shaderList[0].GetProjectionLocation();
    uniformView = shaderList[0].GetViewLocation();
    glm::mat4 model(1.0f);
    glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
}
//</SHADER

/////////////////////////////////////
///////////////CAMERA///////////////
///////////////CAMERA///////////////
/////////////////////////////////////
// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods




// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
//class Camera
//{
//public:
//    // camera Attributes
//    glm::vec3 Position;
//    glm::vec3 Front;
//    glm::vec3 Up;
//    glm::vec3 Right;
//    glm::vec3 WorldUp;
//    glm::vec3 centerOfRotation;
//    // euler Angles
//    float Yaw;
//    float Pitch;
//    // camera options
//    float MovementSpeed;
//    float MouseSensitivity;
//    float Zoom;
//    glm::mat4 calculateViewMatrix();
//    // constructor with vectors
//    Camera(glm::vec3 position = glm::vec3(10.0f, 10.0f, 10.0f), glm::vec3 up =
//        glm::vec3(10.0f, 1.0f, 100.0f), float yaw = YAW, float pitch = PITCH) :
//        Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
//    {
//        Position = position;
//        WorldUp = up;
//        Yaw = yaw;
//        Pitch = pitch;
//        updateCameraVectors();
//    }
//    // constructor with scalar values
//    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :
//        Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
//    {
//        Position = glm::vec3(posX, posY, posZ);
//        WorldUp = glm::vec3(upX, upY, upZ);
//        Yaw = yaw / 100.0f;
//        Pitch = pitch / 100.0f;
//        updateCameraVectors();
//    }
//
//    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
//    glm::mat4 GetViewMatrix()
//    {
//        return glm::lookAt(Position, Position + Front, Up);
//    }
//
//    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
//    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
//    {
//        float velocity = MovementSpeed * deltaTime;
//        if (direction == FORWARD)
//            Position += Front * velocity;
//        if (direction == BACKWARD)
//            Position -= Front * velocity;
//        if (direction == LEFT)
//            Position -= Right * velocity;
//        if (direction == RIGHT)
//            Position += Right * velocity;
//    }
//
//    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
//    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
//    {
//        xoffset *= MouseSensitivity;
//        yoffset *= MouseSensitivity;
//
//        Yaw += xoffset;
//        Pitch += yoffset;
//
//        // make sure that when pitch is out of bounds, screen doesn't get flipped
//        if (constrainPitch)
//        {
//            if (Pitch > 89.0f)
//                Pitch = 89.0f;
//            if (Pitch < -89.0f)
//                Pitch = 89.0f;
//        }
//
//        // update Front, Right and Up Vectors using the updated Euler angles
//        updateCameraVectors();
//    }
//    void zoomIn() {
//        FOV -= ZOOM; // Decrease the field of view
//        //if (FOV < minFOV) FOV = minFOV;
//    }
//
//    void zoomOut() {
//        FOV += ZOOM; // Increase the field of view
//        //if (FOV > maxFOV) FOV = maxFOV;
//    }
//    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
//    void ProcessMouseScroll(float yoffset)
//    {
//        Zoom -= (float)yoffset;
//        if (Zoom < 1.0f)
//            Zoom = 1.0f;
//        if (Zoom > 45.0f)
//            Zoom = 45.0f;
//    }
//    void zoom(int amount) {
//        // Move the camera along the front vector
//        Position += Front * static_cast<float>(amount);
//    }
//
//    //to drag terrain with mouse 
//    void Pan(float xoffset, float yoffset) {
//        glm::vec3 right = glm::normalize(glm::cross(Front, WorldUp));
//        glm::vec3 up = glm::normalize(glm::cross(right, Front));
//
//        Position += right * xoffset * MouseSensitivity;
//        Position += up * yoffset * MouseSensitivity;
//    }
//private:
//    // calculates the front vector from the Camera's (updated) Euler Angles
//    void updateCameraVectors()
//    {
//        // calculate the new Front vector
//        glm::vec3 front;
//        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
//        front.y = sin(glm::radians(Pitch));
//        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
//        Front = glm::normalize(front);
//        // also re-calculate the Right and Up vector
//        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
//        Up = glm::normalize(glm::cross(Right, Front));
//    }
//
//
//
//};

//glm::mat4 Camera::camera::cameracalculateViewMatrix()
//{
//
//    if (swranawa)
//
//        return glm::lookAt(Position, centerOfRotation, Up);
//    else
//        return glm::lookAt(Position, Position + Front, Up); //lookAt functioneka wata bnwara :)
//}
/////////////////////////////////////
///////////////CAMERA///////////////</>
// Define camera movements
enum class Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera {
public:
    // Camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    glm::vec3 centerOfRotation;
    // Euler Angles
    float Yaw;
    float Pitch;
    // Camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    float FOV;
    // Constructor with vectors
    Camera(glm::vec3 position = glm::vec3(10.0f, 10.0f, 10.0f), glm::vec3 up =
        glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) :
        Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM), FOV(45.0f)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix() const {
        return glm::lookAt(Position, Position + Front, Up);
    }
    glm::mat4 calculateViewMatrix();
    // Processes input received from any keyboard-like input system
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);

    // Processes input received from a mouse input system
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

    // Processes input received from a mouse scroll-wheel event
    void ProcessMouseScroll(float yoffset);

    // Zooms the camera in
    void zoomIn();

    // Zooms the camera out
    void zoomOut();

    // Zooms the camera with a specified amount
    void zoom(int amount);

    // Pans the camera with a specified offset
    void Pan(float xoffset, float yoffset);

    // Sets the rotation center of the camera
    void SetRotationCenter(glm::vec3 newCenter);

private:
    // Calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
};
//cpp
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
    float velocity = MovementSpeed * deltaTime;
    if (direction == Camera_Movement::FORWARD)
        Position += Front * velocity;
    if (direction == Camera_Movement::BACKWARD)
        Position -= Front * velocity;
    if (direction == Camera_Movement::LEFT)
        Position -= Right * velocity;
    if (direction == Camera_Movement::RIGHT)
        Position += Right * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // Make sure that when pitch is out of bounds, the screen doesn't get flipped
    if (constrainPitch) {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // Update Front, Right, and Up vectors using the updated Euler angles
    updateCameraVectors();
}

void Camera::ProcessMouseScroll(float yoffset) {
    Zoom -= yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}

void Camera::zoomIn() {
    Zoom -= ZOOM; // Decrease the field of view
}

void Camera::zoomOut() {
    Zoom += ZOOM; // Increase the field of view
}

void Camera::zoom(int amount) {
    // Move the camera along the front vector
    Position += Front * static_cast<float>(amount);
}

void Camera::Pan(float xoffset, float yoffset) {
    glm::vec3 right = glm::normalize(glm::cross(Front, WorldUp));
    glm::vec3 up = glm::normalize(glm::cross(right, Front));

    Position += right * xoffset * MouseSensitivity;
    Position += up * yoffset * MouseSensitivity;
}

void Camera::SetRotationCenter(glm::vec3 newCenter) {
    centerOfRotation = newCenter;
}

void Camera::updateCameraVectors() {
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}


glm::mat4 Camera::calculateViewMatrix()
{

    if (swranawa)
    {
        glm::mat4 viewMatrix = glm::lookAt(Position, centerOfRotation, Up);

        // Print out the first column vector
        glm::vec3 column1 = glm::vec3(viewMatrix[0][0], viewMatrix[1][0], viewMatrix[2][0]);
        std::cout << "Column 1: (" << column1.x << ", " << column1.y << ", " << column1.z << ")" << std::endl;

        // Print out the second column vector
        glm::vec3 column2 = glm::vec3(viewMatrix[0][1], viewMatrix[1][1], viewMatrix[2][1]);
        std::cout << "Column 2: (" << column2.x << ", " << column2.y << ", " << column2.z << ")" << std::endl;

        // Print out the third column vector
        glm::vec3 column3 = glm::vec3(viewMatrix[0][2], viewMatrix[1][2], viewMatrix[2][2]);
        std::cout << "Column 3: (" << column3.x << ", " << column3.y << ", " << column3.z << ")" << std::endl;

        // Print out the fourth column vector (usually translation vector)
        glm::vec3 column4 = glm::vec3(viewMatrix[0][3], viewMatrix[1][3], viewMatrix[2][3]);
        std::cout << "Column 4: (" << column4.x << ", " << column4.y << ", " << column4.z << ")" << std::endl;
        return glm::lookAt(Position, centerOfRotation, Up);
    }
    else {
        return glm::lookAt(Position, Position + Front, Up); //lookAt functioneka wata bnwara :)
    }
    }
///////////////CAMERA///////////////</>
/////////////////////////////////////
//////////////Mesh.h/////////////////


// ///////////Mesh.cpp////////////// </>
/////////////////////////////////////





////////////////INPUT////////////////

////////////////</INPUT>/////////////////
   //cubemap 


// 
//definey textureId
GLuint loadCubemap0(std::vector<std::string> faces) {
    unsigned int skybox;
    glGenTextures(1, &skybox);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skybox);
    //glBindTexture(GL_TEXTURE_2D, skybox);
    // Bind the texture object

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        //data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return skybox;

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        // Print or log the error message
        std::cerr << "OpenGL error: " << error << std::endl;
    }
}


//GLuint textureID;
GLuint loadCubemap(std::vector<std::string> faces, const std::string& defaultFace) {
    GLuint skybox;
    glGenTextures(1, &skybox);
    //glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skybox);
    //glBindTexture(GL_TEXTURE_2D, skybox);
    // Bind the texture object

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++) {
        unsigned char* data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        //data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return skybox;

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        // Print or log the error message
        std::cerr << "OpenGL error: " << error << std::endl;
    }
}



// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 720;
const unsigned int NUM_PATCH_PTS = 4;

// camera - give pretty starting point
Camera camera(glm::vec3(10.0f, 10.0f, 10.0f),
    glm::vec3(-1.0f, -1.0f, -1.0f),
    -128.1f, -42.4f);
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;
////////////////////////////////////
////////////////////////////////////

bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}


//CAMERA2
class Camera2
{
public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    glm::vec3 centerOfRotation;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // constructor with vectors
    Camera2(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    // constructor with scalar values
    Camera2(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw / 100.0f;
        Pitch = pitch / 100.0f;
        updateCameraVectors();
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
        //return glm::lookAt(Position, centerOfRotation, Up);
    }
   
    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == Camera_Movement::FORWARD)
            Position += Front * velocity;
        if (direction == Camera_Movement::FORWARD)
            Position -= Front * velocity;
        if (direction == Camera_Movement::LEFT)
            Position -= Right * velocity;
        if (direction == Camera_Movement::RIGHT)
            Position += Right * velocity;
    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }
    void zoomIn() {
        FOV -= ZOOM; // Decrease the field of view
        if (FOV < minFOV) FOV = minFOV;
    }

    void zoomOut() {
        FOV += ZOOM; // Increase the field of view
        if (FOV > maxFOV) FOV = maxFOV;
    }
    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }
    void zoom(int amount) {
        // Move the camera along the front vector
        Position += Front * static_cast<float>(amount);
    }

    //to drag terrain with mouse 
    void Pan(float xoffset, float yoffset) {
        glm::vec3 right = glm::normalize(glm::cross(Front, WorldUp));
        glm::vec3 up = glm::normalize(glm::cross(right, Front));

        Position += right * xoffset * MouseSensitivity;
        Position += up * yoffset * MouseSensitivity;
    }
private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up = glm::normalize(glm::cross(Right, Front));
    }
};


/////////////////////////////////////
///////////////CAMERA///////////////</>
///////////////CAMERA///////////////</>
/////////////////////////////////////





// camera - give pretty starting point
Camera2 camera2(glm::vec3(1.0f, 1.0f, 10.0f),
    glm::vec3(0.0f, 1.0f, 0.0f),
    -128.1f, -42.4f);
// CAMERA2</>
unsigned int loadTexture(char const* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
float randomFloat(float min, float max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);
    return dis(gen);
}


void updateRandomCamera(Camera& camera) {
    // Randomly adjust the camera's position
    float offsetX = randomFloat(-1.5f, 10.5f);
    float offsetY = randomFloat(-1.5f, 10.5f);
    float offsetZ = randomFloat(-1.5f, 10.5f);
   
    camera.Position += glm::vec3(offsetX, offsetY, offsetZ);
    if (offsetX > 10.0f || offsetX < -10.0f) {
        offsetX = offsetX > 0 ? 0.5f : -0.5f;
    }

    if (offsetY > 10.0f || offsetY < -10.0f) {
        offsetY = offsetY > 0 ? 0.5f : -0.5f;
    }

    if (offsetZ > 10.0f || offsetZ < -10.0f) {
        offsetZ = offsetZ > 0 ? 0.5f : -0.5f;
    }
    // Randomly adjust the camera's orientation
    float pitch = randomFloat(-10.0f, 10.0f);
    float yaw = randomFloat(-10.0f, 10.0f);

    camera.ProcessMouseMovement(yaw, pitch);
}
//MAIN
int main(int argc, char* argv[])
{

    // Vertices for rendering a cube
    float skyboxVertices[] = {
        // positions
        -1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,

        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,

        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,

        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };


    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        return -1;
    }
    std::cout << "Camera Pos: " << camera.Position.x << ", " << camera.Position.y << ", " << camera.Position.z << std::endl;
    std::cout << "Camera Front: " << camera.Front.x << ", " << camera.Front.y << ", " << camera.Front.z << std::endl;


    // Set OpenGL attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Flying Animals", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL);
    if (!window) {
        std::cerr << "Failed to create window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return -1;
    }

    // Create an OpenGL context
    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (!context) {
        std::cerr << "Failed to create OpenGL context: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }
    

    // Initialize GLAD

    if (!gladLoaderLoadGL()) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

   
    const std::string defaultFace = "Textures/skybox/muspelheim.png";
    // load textures
    // -------------
    std::vector<std::string> faces{
    "Textures/skybox/xpos.png",
    "Textures/skybox/xneg.png",
    "Textures/skybox/ypos.png",
    "Textures/skybox/yneg.png",
    "Textures/skybox/zpos.png",
    "Textures/skybox/xneg.png"
    };
    for (std::string& face : faces) {
        if (!fileExists(face)) {
            std::cerr << "\033[1;31mAm Fila Nadozrawatawa: " << face << "\033[0m" << std::endl; // Print in red
            std::cerr << "\033[1;32mBoya aigorin bam " << "\033[1;33m" << "'Textures/skybox/muspelheim.png'" << " \033[0m" << "\033[1;32mdefaulta \033[0m\n";
            std::cerr << "\033[1;36mPesh Away \033[0m" << "\033[1;31m(\033[0m" << "\033[33m'face = defaultFace;\033[0m'" << "\033[1;31m)\033[0m" << "\033[1;34m'face'\033[0m"
                << "\033[1;31m britya la '\033[0m" << face << "'\033[0m" << std::endl; // Print in green
            face = defaultFace;
            std::cerr << "\033[1;31mDway Away\033[0m" << "\033[1;31m (\033[0m" << "\033[33m'face = defaultFace;\033[0m'" << "\033[1;31m)\033[0m" << "\033[1;34m'face'\033[0m" << "\033[1;35m britya la '\033[0m"
                << "\033[1;33m" << face << " \033[0m" << std::endl; // Print in green
        }
        else
        {
            std::cerr << "\033[1;32mBro xoty shamal: \033[0m" << "\033[36m ...... \033[0m" << "\033[35m" << face << "\033[0m" << "\033[33m ...... \033[0m" << std::endl;

        }
    }

    //</cube map>

    std::cerr << "\033[1;32m......\033[0m" << "\033[36m ...... \033[0m" << "\033[30m" << "\033[0m" << "\033[33m ...... \033[0m" <<
        "\033[1;32m...... \033[0m" << "\033[36m ...... \033[0m" << "\033[30m" << "\033[0m" << "\033[33m ...... \033[0m\n";



    


    //shaderAi::daspeka()->bakaryBena();

    shaderAi::daspeka()->drwstkaProgram();
    shaderAi::daspeka()->drwstkaShader(); 
    // skybox VAO
    GLuint skyboxVBO, skyboxVAO;
    

    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    
 
    shaderAi::daspeka()->drwstkaProgram();
   shaderAi::daspeka()->drwstkaShader();
    //shaderAi::daspeka()->bakaryBena();
    shaderAi::daspeka()->bibastawaShader();

   shaderAi::daspeka()->koikarawaShader("Shaders/skyBox.vert", shaderAi::JoryShader::VERTEX_SHADER);
   shaderAi::daspeka()->koikarawaShader("Shaders/skyBox.frag", shaderAi::JoryShader::FRAGMENT_SHADER);

   

   shaderAi::daspeka()->set("cubeMap", 0);
   shaderAi::daspeka()->set("skybox", 0);

   GLuint cubemapTexture = loadCubemap(faces, defaultFace);
   //GLuint cubemapTexture0 = loadCubemap0(faces);
    //system("color A");

   
    //cube map
        
  
    //SHADER2 -----------

    //not implemented yet

    //SHADER2------------
   //terrain moved here//
    //here terrain moved to//
   GLint maxTessLevel;
   glGetIntegerv(GL_MAX_TESS_GEN_LEVEL, &maxTessLevel);
   std::cout << "\033[35mMax available tess level: \033[0m" << "\033[33m" << maxTessLevel << "\033[0m" << std::endl;



   // shader configuration
   // --------------------
   //shaderAi::daspeka()->setInt("skybox", 0);

   // configure global opengl state
   // -----------------------------

   //glEnable(GL_DEPTH_TEST);
   //ShaderAi part


  /* shaderAi::daspeka()->bilkenaShader();
   shaderAi::daspeka()->bibastawaShader();

   shaderAi::daspeka()->jyaikarawaShader();
   shaderAi::daspeka()->lanawyBaraShader();
   shaderAi::daspeka()->lanawyBaraProgram();*/

   //shaderAi::daspeka()->drwstkaProgram();
   //shaderAi::daspeka()->drwstkaShader();
  /* shaderAi::daspeka()->koikarawaShader("Shaders/skyBox.vert", shaderAi::JoryShader::VERTEX_SHADER);
   shaderAi::daspeka()->koikarawaShader("Shaders/skyBox.frag", shaderAi::JoryShader::FRAGMENT_SHADER);*/


   //shaderAi::daspeka()->koikarawaShader("Shaders/shader.vert", shaderAi::JoryShader::VERTEX_SHADER);
   //shaderAi::daspeka()->koikarawaShader("Shaders/shader.frag", shaderAi::JoryShader::FRAGMENT_SHADER);

   //ShaderAi part </
   // build and compile our shader program
   // ------------------------------------
   // load and create a texture
   // -------------------------
   //unsigned int texture;
  // glGenTextures(1, &texture);
  // glActiveTexture(GL_TEXTURE0);
   //glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
   // set the texture wrapping parameters
   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   //// set texture filtering parameters
  // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   //load image, create texture and generate mipmaps
   int width, height, nrChannels;
   // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
   //unsigned char* dataTess = stbi_load("Textures/Fog.png", &width, &height, &nrChannels, 0);
   unsigned char* dataTess = stbi_load("Textures/FRC.jpg", &width, &height, &nrChannels, 0);

  

   // set up vertex data (and buffer(s)) and configure vertex attributes
   // ------------------------------------------------------------------
   std::vector<float> Tvertices;

   unsigned rez = 20;
   for (unsigned i = 0; i <= rez - 1; i++)
   {
       for (unsigned j = 0; j <= rez - 1; j++)
       {
           Tvertices.push_back(-width / 2.0f + width * i / (float)rez); // v.x
           Tvertices.push_back(0.0f); // v.y
           Tvertices.push_back(-height / 2.0f + height * j / (float)rez); // v.z
           Tvertices.push_back(i / (float)rez); // u
           Tvertices.push_back(j / (float)rez); // v

           Tvertices.push_back(-width / 2.0f + width * (i + 1) / (float)rez); // v.x
           Tvertices.push_back(0.0f); // v.y
           Tvertices.push_back(-height / 2.0f + height * j / (float)rez); // v.z
           Tvertices.push_back((i + 1) / (float)rez); // u
           Tvertices.push_back(j / (float)rez); // v

           Tvertices.push_back(-width / 2.0f + width * i / (float)rez); // v.x
           Tvertices.push_back(0.0f); // v.y
           Tvertices.push_back(-height / 2.0f + height * (j + 1) / (float)rez); // v.z
           Tvertices.push_back(i / (float)rez); // u
           Tvertices.push_back((j + 1) / (float)rez); // v

           Tvertices.push_back(-width / 2.0f + width * (i + 1) / (float)rez); // v.x
           Tvertices.push_back(0.0f); // v.y
           Tvertices.push_back(-height / 2.0f + height * (j + 1) / (float)rez); // v.z
           Tvertices.push_back((i + 1) / (float)rez); // u
           Tvertices.push_back((j + 1) / (float)rez); // v
       }
   }
   std::cout << "Loaded " << rez * rez << " patches of 4 control points each" << std::endl;
   std::cout << "Processing " << rez * rez * 4 << " vertices in vertex shader" << std::endl;
   //GLuint textureID;
   // first, configure the cube's VAO (and terrainVBO)
   unsigned int terrainVAO, terrainVBO; // skyboxVAO, skyboxVBO;
   glGenVertexArrays(1, &terrainVAO);
   glBindVertexArray(terrainVAO);

   //glBindBuffer(GL_ARRAY_BUFFER, 0);

   glGenBuffers(1, &terrainVBO);
   glBindBuffer(GL_ARRAY_BUFFER, terrainVBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(float) * Tvertices.size(), &Tvertices[0], GL_STATIC_DRAW);

   // position attribute
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
   glEnableVertexAttribArray(0);
   // texCoord attribute
   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(sizeof(float) * 3));
   glEnableVertexAttribArray(1);

   glPatchParameteri(GL_PATCH_VERTICES, NUM_PATCH_PTS);

   // Set texture parameters
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

   // Load texture data and upload to GPU
   if (dataTess)
   {
       glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
           GL_UNSIGNED_BYTE, dataTess);
       glGenerateMipmap(GL_TEXTURE_2D);
       shaderAi::daspeka()->setInt("heightMap", 0);
       //shaderAi::daspeka()->setInt("skycube", 0); //????
       //shaderAi::daspeka()->setInt("cubemap", 0);//??????
       std::cout << "\033[1;32m Loady heightmapy dataTess ba qabaray :\033[0m" <<
           "\033[1;32m" << height << " x " << width << "\033[0m" << std::endl;
       //glGenerateMipmap(GL_TEXTURE_2D);
   }
   else
   {
       std::cout << "datatess bwny nia" << std::endl;
   }




   //shaderAi::daspeka()->koikarawaShader("Shaders/skyBox.vert", shaderAi::JoryShader::VERTEX_SHADER);
   //shaderAi::daspeka()->koikarawaShader("Shaders/skyBox.frag", shaderAi::JoryShader::FRAGMENT_SHADER);  
   shaderAi::daspeka()->koikarawaShader("Shaders/8.3.gpuheight.vert", shaderAi::JoryShader::VERTEX_SHADER);
   shaderAi::daspeka()->koikarawaShader("Shaders/8.3.gpuheight.frag", shaderAi::JoryShader::FRAGMENT_SHADER);
   shaderAi::daspeka()->koikarawaShader("Shaders/8.3.gpuheightT.tesc", shaderAi::JoryShader::TESS_CONTROL_SHADER);
   shaderAi::daspeka()->koikarawaShader("Shaders/8.3.gpuheightT.tese", shaderAi::JoryShader::TESS_EVALUATION_SHADER);
   shaderAi::daspeka()->bilkenaShader(); //Attach (idprog,idShaderaka) 
   shaderAi::daspeka()->bibastawaShader(); //glLinkProgram(idprog) glUseProgram(idprog) 



  // shaderAi::daspeka()->jyaikarawaShader();
   //</here terrain moved to
   //</terrain moved here//
    SDL_Event event;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    const int FPS = 60;
    const int frameDelay = 1000/ FPS;

    Uint32 frameStart;
    int frameTime;

    while (running) {
        //glViewport(0,0,800,800); 
        glClearColor(0.2f, 0.1f, 0.1f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        static int framesUntilNextRandomUpdate = 10; // Adjust as needed
        if (framesUntilNextRandomUpdate <= 0) {
            updateRandomCamera(camera);
            framesUntilNextRandomUpdate = 5; // Reset the counter
        }

        framesUntilNextRandomUpdate--;
        float currentFrame = SDL_GetTicks();
        scroll_callback(&event);
        while (SDL_PollEvent(&event)) {
           
            switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    running = false;
                    break;
                case SDLK_w:
                    camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
                    break;
                case SDLK_s:
                    camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
                    break;
                case SDLK_a:
                    camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
                    break;
                case SDLK_d:
                    camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
                    break;
                    // Add more key bindings as needed
                case SDLK_r:
                    //wireframe
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                    break;
                case SDLK_f:
                    //fill frame
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                    break;
                case SDLK_t:
                    //wireframe
                    swranawa = false;

                    break;
                case SDLK_g:
                    //fill frame
                    swranawa = true;

                    break;
                   
                }
                
            case SDL_MOUSEMOTION:
                mouse_callback(&event);

                // Add other event types as needed
                if (isDragging) {
                    // Calculate the distance dragged
                    int x = event.motion.x;
                    int y = event.motion.y;
                    int dx = x - startX;
                    int dy = y - startY;
                    std::cout <<"\033[0;36m" << 
                        "Rakeshany Arasta: \033[0m" <<
                        "\033[0;33m" << dx << 
                        "\033[0m" << "\033[0;34m" 
                        << ", " << " \033[0m" <<
                        "\033[0;33m" << dy <<
                        "\033[0m" << std::endl;

                    // Optionally: Update the start position for smoother dragging
                    camera.Pan(static_cast<float>(-dx), static_cast<float>(dy));

                    startX = x;
                    startY = y;

                }
                break;

            case SDL_MOUSEWHEEL:
                scroll_callback(&event);

                if (event.wheel.y != 0) { // scroll up
                    // Zoom in
                    int zoomAmount = event.wheel.y > 0 ? -1 : 1; // Determine direction
                    camera.zoom(zoomAmount);
                }
                else if (event.wheel.y < 0) { // scroll down
                    // Zoom out
                    camera.zoomOut();
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {  // If the left button was pressed
                    isDragging = true;
                    startX = event.button.x;
                    startY = event.button.y;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT) {  // If the left button was released
                    isDragging = false;
                }

            }
        }
        deltaTime = (currentFrame - lastFrame) / 1000.0f; // Convert milliseconds to seconds
        lastFrame = currentFrame;

        frameStart = SDL_GetTicks();
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDelay > frameTime) {
            SDL_Delay(frameDelay - frameTime);
        }


        //shaderAi::daspeka()->bakaryBena();
        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians(45.0f),
            (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.01f, 10000.0f);
        glm::mat4 view = camera.GetViewMatrix();
        glm::mat4 viewSky = camera2.GetViewMatrix();

        /*glm::mat4 view = camera2.GetViewMatrix();*/

        
        
        // world transformation
        glm::mat4 position;
        glm::mat4 model = glm::mat4(1.0f);
        shaderAi::daspeka()->setMat4("model", model);
        shaderAi::daspeka()->setVec3("cameraPos", camera.Position);
        shaderAi::daspeka()->set("view", view);
        shaderAi::daspeka()->set("projection", projection);
        shaderAi::daspeka()->set("heightMap", 0);
        
        
        
        // Draw skybox
       
        //glIsEnabled(GL_DEPTH_TEST));
        //glDisable(GL_DEPTH_TEST);

        

        //view = camera.GetViewMatrix();
       // projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT,
           // 0.1f, 100000.0f);

        

        // <Skytexture>
        

        //cubemapTexture = loadCubemap(faces, defaultFace);

       
        // </Skytexture//
      
        //glDepthMask(GL_FALSE);

        glBindVertexArray(terrainVAO);
        glDrawArrays(GL_PATCHES, 0, NUM_PATCH_PTS* rez* rez);
        glBindVertexArray(0);

        //drawSkybox
        glDepthFunc(GL_LEQUAL);
        /*
        1-Turn on the depth mask glDepthMask( GL_TRUE )
        2-Draw all opaque objects, in any order
        3-Turn off the depth mask glDepthMask( GL_FALSE )
        4-Turn on a BLEND_MODE --:|> glDisable( GL_BLEND ); 
        5-Draw translucent objects sorted from furthest away to nearest
        */
        glm::mat4 modelSky = glm::mat4(1.0f);
        shaderAi::daspeka()->set("model", modelSky);
        glGenVertexArrays(1, &skyboxVAO);
        glBindVertexArray(skyboxVAO);
        GLenum error = glGetError();

        error = glGetError();
        if (error != GL_NO_ERROR) {
            // Handle or log the error
            std::cerr << "Error binding VAO: " << error << std::endl;
        }

        glGenBuffers(1, &skyboxVBO);

       
        // Bind the VBO for the skybox vertices
        glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
        error = glGetError();
        if (error != GL_NO_ERROR) {
            // Handle or log the error
            std::cerr << "Error binding VBO: " << error << std::endl;
        }
        // Set up vertex attribute pointers
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        error = glGetError();
        if (error != GL_NO_ERROR) {
            // Handle or log the error
            std::cerr << "Error ama glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);: " << error << std::endl;
        }
        
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        viewSky = camera.GetViewMatrix();

        // Bind the VAO for the skybox
        //shaderAi::daspeka()->bakaryBena();
        shaderAi::daspeka()->set("projectionSky", projection);
        shaderAi::daspeka()->set("viewSky", viewSky);
        shaderAi::daspeka()->set("skybox", 0);

        //shaderAi::daspeka()->bakaryBena();
          //glActiveTexture(GL_TEXTURE0);
          //glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        if (error != GL_NO_ERROR) {
            // Handle or log the error
            std::cerr << "Error bakaryBena Line 2274" << error << std::endl;
        }
   
        // Set up vertex attribute pointers OR Set the cubemap texture, same thing 
        glActiveTexture(GL_TEXTURE0);
        
        error = glGetError();
        if (error != GL_NO_ERROR) {
            // Handle or log the error
            std::cerr << "Error GL_TEXTURE0: " << error << std::endl;
        }
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        error = glGetError();
        if (error != GL_NO_ERROR) {
            // Handle or log the error
            std::cerr << "Error binding texture: " << error << std::endl;
        }

        // Disable writing to the depth buffer
        //glDepthMask(GL_FALSE);
        glDepthMask(GL_TRUE);
        error = glGetError();
        if (error != GL_NO_ERROR) {
            // Handle or log the error
            std::cerr << "Error disabling depth mask: " << error << std::endl;
        }
        // Render the skybox
        glDrawArrays(GL_TRIANGLES, 0, 36); // 36 vertices for a cube

        error = glGetError();
        if (error != GL_NO_ERROR) {
            // Handle or log the error
            std::cerr << "Error drawing skybox: " << error << std::endl;
        }
       //glDepthMask(GL_TRUE);
        glDepthFunc(GL_LESS);
        // render the terrain
        glDepthMask(GL_FALSE);
        glDisable(GL_BLEND);
        SDL_GL_SwapWindow(window);
    }
 
    glDeleteVertexArrays(1, &terrainVAO);
    glDeleteVertexArrays(1, &skyboxVAO);
    glDeleteBuffers(1, &terrainVBO);
    glDeleteBuffers(1, &skyboxVBO);

    shaderAi::daspeka()->jyaikarawaShader();
    shaderAi::daspeka()->lanawyBaraShader();
    shaderAi::daspeka()->lanawyBaraProgram();
    
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

////




void checkForWindowResize() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED) {
            int width = event.window.data1;
            int height = event.window.data2;
            glViewport(0, 0, width, height);
        }
    }
}

void handleMouseMovement() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_MOUSEMOTION) {
            float xoffset = event.motion.xrel;
            float yoffset = event.motion.yrel; // reversed since y-coordinates go from bottom to top

            camera.ProcessMouseMovement(xoffset, yoffset);
        }
    }
}

void handleMouseScroll() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_MOUSEWHEEL) {
            camera.ProcessMouseScroll(event.wheel.y);
        }
    }
}


void mouse_callback(SDL_Event* event) {
    if (firstMouse) {
        lastX = event->motion.x;
        lastY = event->motion.y;
        firstMouse = false;
    }

    float xoffset = event->motion.x - lastX;
    float yoffset = lastY - event->motion.y; // reversed since y-coordinates go from bottom to top

    lastX = event->motion.x;
    lastY = event->motion.y;

    camera.ProcessMouseMovement(xoffset, yoffset);
}


void scroll_callback(SDL_Event* event) {
    // SDL mouse wheel events report the amount scrolled in event->wheel.y
    float yoffset = static_cast<float>(event->wheel.y);
    camera.ProcessMouseScroll(yoffset);
    //SDL_Event event;

}


