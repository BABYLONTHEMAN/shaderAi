#include <iostream>
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
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

void mouse_callback(SDL_Event* event);
void scroll_callback(SDL_Event* event);
bool running = true;
bool isDragging = false;
int startX = 0, startY = 0;
float minFOV = 1.0f; float maxFOV = 200.0f;  float FOV = 45.0f;


static const char* vShader = "Shaders/shader.vert";
// Fragment Shader
static const char* fShader = "Shaders/shader.frag";

//class shaderAi.h
//I don't know yet but kind of doing all the shader/s stuff
class shaderAi
{
public:
    enum class JoryShader {VERTEX_SHADER,FRAGMENT_SHADER};

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

private:
    shaderAi();
    shaderAi(const shaderAi&);
    shaderAi& operator = (shaderAi&);
private:
    GLuint m_IdprogramyShaderaka;
    GLuint m_IdVertexyShader;
    GLuint m_IdFragmentyShader;

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
    m_IdVertexyShader =glCreateShader(GL_VERTEX_SHADER);

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
    return true;
}

bool shaderAi::koikarawaShader(const std::string& nawiFile, JoryShader joryShader) //koikarawaShader ---=====wata> compile...
{
    std::fstream file;
    std::string text;
    std::string sarchawayCode;
    GLuint idShader;

    idShader = (joryShader == JoryShader::VERTEX_SHADER)? m_IdVertexyShader : m_IdFragmentyShader;
    file.open(nawiFile);


    if (!file)
    {
        std::cout << "\n err xwendnaway filey shader (file.open(nawiFile) ... leraya err haya) : "<<nawiFile;
    }

    while (!file.eof()) 
    {
        std::getline(file,text);
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

        glGetShaderInfoLog(idShader,errSize,&errSize,errMsg);
        std::cout << "\n "<<errMsg<< "\n ";





    }
    return true;
}

void shaderAi::bilkenaShader() //bilkenaShader ---=====wata> Attach...
{
    glAttachShader(m_IdprogramyShaderaka, m_IdVertexyShader);
    glAttachShader(m_IdprogramyShaderaka, m_IdFragmentyShader);
}

bool shaderAi::bibastawaShader()
{
    glLinkProgram(m_IdprogramyShaderaka);

    glUseProgram(m_IdprogramyShaderaka);

    GLint halayCode;
    glGetProgramiv(m_IdprogramyShaderaka, GL_LINK_STATUS, &halayCode);
    if (halayCode == GL_TRUE)
    {
        std::cout << "\n bastnaway shader sarkawtw bw \n";
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
}

void shaderAi::lanawyBaraShader() //lanawyBaraShader ---=====wata> Delete...
{
    glDeleteShader(m_IdVertexyShader);
    glDeleteShader(m_IdFragmentyShader);

}

void shaderAi::lanawyBaraProgram()
{
    glDeleteProgram(m_IdprogramyShaderaka);
}

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
         void Shader::setBool(const std::string& name, bool value) const
         {
             glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
         }
         // ------------------------------------------------------------------------
         void Shader::setInt(const std::string& name, int value) const
         {
             glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
         }
         // ------------------------------------------------------------------------
         void Shader::setFloat(const std::string& name, float value) const
         {
             glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
         }
         // ------------------------------------------------------------------------
         void Shader::setVec2(const std::string& name, const glm::vec2& value) const
         {
             glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
         }
         void Shader::setVec2(const std::string& name, float x, float y) const
         {
             glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
         }
         // ------------------------------------------------------------------------
         void Shader::setVec3(const std::string& name, const glm::vec3& value) const
         {
             glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
         }
         void Shader::setVec3(const std::string& name, float x, float y, float z) const
         {
             glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
         }
         // ------------------------------------------------------------------------
         void Shader::setVec4(const std::string& name, const glm::vec4& value) const
         {
             glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
         }
         void Shader::setVec4(const std::string& name, float x, float y, float z, float w)
         {
             glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
         }
         // ------------------------------------------------------------------------
         void Shader::setMat2(const std::string& name, const glm::mat2& mat) const
         {
             glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
         }
         // ------------------------------------------------------------------------
         void Shader::setMat3(const std::string& name, const glm::mat3& mat) const
         {
             glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
         }
         // ------------------------------------------------------------------------
         void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
         {
             glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);

         }

         void Shader::checkCompileErrors(GLuint shader, std::string type)
         {

                 GLint success;
                         GLchar infoLog[1024];
                         if (type != "PROGRAM")
                         {
                             glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
                             if (!success)
                             { (infoLog);
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
    glm::vec3 Tangent;

    Vertex(const glm::vec3& pos, const glm::vec3& normal, const glm::vec2& tex, const glm::vec3& tangent)
        : Position(pos), Normal(normal), TexCoords(tex), Tangent(tangent) {}
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
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (void*)(sizeof(GLfloat) * 5));
    glEnableVertexAttribArray(2);

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


/////////////////Skybox.cpp////////////////
///////////////////////////////////
/////////////////////////////////////



/////////////////Skybox.cpp////////////////</>
///////////////////////////////////
/////////////////////////////////////
/////////////////SKYBOX//////////////</>

skyBox skybox;
void Shader::renderPass(glm::mat4 viewMatrix, glm::mat4 projectionMatrix)
{
    //glfwPollEvents();
     SDL_Event event;
    //glViewport(110, 10, 1366, 768);

    //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    skybox.DrawSkybox(viewMatrix, projectionMatrix);
    //meshterrain.wenayTerrainBkesha(viewMatrix, projectionMatrix);
    //meshterrain.wenayTerrainBkesha(viewMatrix, projectionMatrix);

    //glUseProgram(shader);

    glUseProgram(ID);
        //uniformModel = shaderList[0].GetModelLocation();
        //uniformModel2 = shaderList[0].GetModelLocation();// <|--------- this maybe works who knows?
    uniformProjection = shaderList[0].GetProjectionLocation();
    // you can use it without GetProjectionLocation like this >>>>>>>> uniformProjection = shaderList[0].uniformProjection;

    uniformView = shaderList[0].GetViewLocation();
    //uniformAmbientColour = shaderList[0].GetAmbientColourLocation();
    //uniformAmbientIntensity = shaderList[0].GetAmbientIntensityLocation();
    //uniformDirection = shaderList[0].GetDirectionLocation();
    //uniformDiffuseintensity = shaderList[0].GetDiffuseIntensityLocation();
           /* uniformEyePosition = shaderList[0].GetEyePositionLocation();
            uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
            uniformShininess = shaderList[0].GetShininessLocation();*/


    //glm::vec3 LowerLight = camera.getCameraPosition();
   // LowerLight.y -= 0.3f;
    //spotLights[0].SetFlash(LowerLight, camera.getCameraDirection()); //moving Torch 'Spotlight.cpp, .h

    //shaderList[0].SetDirectionalLight(&mainLight);
    //shaderList[0].SetPointLights(pointLights, pointLightCount);
   // shaderList[0].SetSpotLights(spotLights, spotLightCount);



    //glm 
    glm::mat4 model(1.0f);

    glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
   // glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
   // glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y,
     //   camera.getCameraPosition().z);


    //CreateObjects();
    //createShaders();

}
//</SHADER

/////////////////////////////////////
///////////////CAMERA///////////////
///////////////CAMERA///////////////
/////////////////////////////////////
// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW = -30.0f;
const float PITCH = 0.0f;
const float SPEED = 100.5f;
const float SENSITIVITY = 0.01f;
const float ZOOM = 2.0f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

    // constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up =
        glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : 
        Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }
    // constructor with scalar values
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :
        Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw/100.0f;
        Pitch = pitch/100.0f;
        updateCameraVectors();
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = MovementSpeed * deltaTime;
        if (direction == FORWARD)
            Position += Front * velocity; 
        if (direction == BACKWARD)
            Position -= Front * velocity;
        if (direction == LEFT)
            Position -= Right * velocity;
        if (direction == RIGHT)
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
        //if (FOV < minFOV) FOV = minFOV;
    }
    
    void zoomOut() {
        FOV += ZOOM; // Increase the field of view
        //if (FOV > maxFOV) FOV = maxFOV;
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
//////////////Mesh.h/////////////////


// ///////////Mesh.cpp////////////// </>
/////////////////////////////////////






////////////////INPUT////////////////
  
////////////////</INPUT>/////////////////



// settings
const unsigned int SCR_WIDTH = 1800;
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


int main(int argc, char* argv[])
{
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
    SDL_Window* window = SDL_CreateWindow("Flying Animals", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1800, 720, SDL_WINDOW_OPENGL);
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
    
        if (!gladLoaderLoadGL()){
        std::cerr << "Failed to initialize GLAD" << std::endl;
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

        GLint maxTessLevel;
        glGetIntegerv(GL_MAX_TESS_GEN_LEVEL, &maxTessLevel);
        std::cout << "Max available tess level: " << maxTessLevel << std::endl;

        // configure global opengl state
        // -----------------------------
        glEnable(GL_DEPTH_TEST);
        //ShaderAi part
        shaderAi::daspeka()->drwstkaProgram();
        shaderAi::daspeka()->drwstkaShader();
        shaderAi::daspeka()->koikarawaShader("Shaders/8.3.gpuheight.vert",shaderAi::JoryShader::VERTEX_SHADER);
        shaderAi::daspeka()->koikarawaShader("Shaders/8.3.gpuheight.frag", shaderAi::JoryShader::FRAGMENT_SHADER);
        shaderAi::daspeka()->bilkenaShader();
        shaderAi::daspeka()->bibastawaShader();


        //shaderAi::daspeka()->koikarawaShader("",);
        //shaderAi::daspeka()->();

        //ShaderAi part </

        // build and compile our shader program
        // ------------------------------------
        Shader tessHeightMapShader("Shaders/8.3.gpuheight.vert", "Shaders/8.3.gpuheight.frag", nullptr,            // if wishing to render as is
            "Shaders/8.3.gpuheightT.tesc", "Shaders/8.3.gpuheightT.tese");

        // load and create a texture
        // -------------------------
        unsigned int texture;
        glGenTextures(1, &texture);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        int width, height, nrChannels;
        // The FileSystem::getPath(...) is part of the GitHub repository so we can find files on any IDE/platform; replace it with your own image path.
        unsigned char* data = stbi_load("Textures/FRC.jpg", &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            tessHeightMapShader.setInt("heightMap", 0);
            std::cout << "Loaded heightmap of size " << height << " x " << width << std::endl;
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(data);

        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        std::vector<float> vertices;

        unsigned rez = 20;
        for (unsigned i = 0; i <= rez - 1; i++)
        {
            for (unsigned j = 0; j <= rez - 1; j++)
            {
                vertices.push_back(-width / 2.0f + width * i / (float)rez); // v.x
                vertices.push_back(0.0f); // v.y
                vertices.push_back(-height / 2.0f + height * j / (float)rez); // v.z
                vertices.push_back(i / (float)rez); // u
                vertices.push_back(j / (float)rez); // v

                vertices.push_back(-width / 2.0f + width * (i + 1) / (float)rez); // v.x
                vertices.push_back(0.0f); // v.y
                vertices.push_back(-height / 2.0f + height * j / (float)rez); // v.z
                vertices.push_back((i + 1) / (float)rez); // u
                vertices.push_back(j / (float)rez); // v

                vertices.push_back(-width / 2.0f + width * i / (float)rez); // v.x
                vertices.push_back(0.0f); // v.y
                vertices.push_back(-height / 2.0f + height * (j + 1) / (float)rez); // v.z
                vertices.push_back(i / (float)rez); // u
                vertices.push_back((j + 1) / (float)rez); // v

                vertices.push_back(-width / 2.0f + width * (i + 1) / (float)rez); // v.x
                vertices.push_back(0.0f); // v.y
                vertices.push_back(-height / 2.0f + height * (j + 1) / (float)rez); // v.z
                vertices.push_back((i + 1) / (float)rez); // u
                vertices.push_back((j + 1) / (float)rez); // v
            }
        }
        std::cout << "Loaded " << rez * rez << " patches of 4 control points each" << std::endl;
        std::cout << "Processing " << rez * rez * 4 << " vertices in vertex shader" << std::endl;

        // first, configure the cube's VAO (and terrainVBO)
        unsigned int terrainVAO, terrainVBO;
        glGenVertexArrays(1, &terrainVAO);
        glBindVertexArray(terrainVAO);

        glGenBuffers(1, &terrainVBO);
        glBindBuffer(GL_ARRAY_BUFFER, terrainVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texCoord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(sizeof(float) * 3));
        glEnableVertexAttribArray(1);

        glPatchParameteri(GL_PATCH_VERTICES, NUM_PATCH_PTS);

        
        //SHADER2 -----------
       
        //not implemented yet

        //SHADER2------------

        SDL_Event event;
        float deltaTime = 0.0f;
        float lastFrame = 0.0f;

                const int FPS = 60;
                const int frameDelay = 1000 / FPS;

        Uint32 frameStart;
        int frameTime;


        while (running) {
           // glViewport(0,0,800,800);
         
                                            //* (5.0f * (deltaTime * 0.001));
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            float currentFrame = SDL_GetTicks();

            //// Activate shader before drawing
            //ourShader.use();

            //// Set uniforms
            //ourShader.setFloat("someUniform", 0.5f);


                //// Set dynamic uniforms (like transformations)
                //glm::mat4 model = glm::mat4(1.0f);
                //glm::mat4 view = camera.GetViewMatrix();
                //glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
                //ourShader.setMat4("model", model);
                //ourShader.setMat4("view", view);
                //ourShader.setMat4("projection", projection);

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
                        camera.ProcessKeyboard(FORWARD, deltaTime); 
                        break;
                    case SDLK_s:
                        camera.ProcessKeyboard(BACKWARD, deltaTime);
                        break;
                    case SDLK_a:
                        camera.ProcessKeyboard(LEFT, deltaTime);
                        break;
                    case SDLK_d:
                        camera.ProcessKeyboard(RIGHT, deltaTime);
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
                        std::cout << "Dragging by: " << dx << ", " << dy << std::endl;

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
            
           

            // input
            // -----
            //processInput(window, running);

            // render
            // ------
          

            // be sure to activate shader when setting uniforms/drawing objects
            tessHeightMapShader.use();

            // view/projection transformations
            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
            glm::mat4 view = camera.GetViewMatrix();
            tessHeightMapShader.setMat4("projection", projection);
            tessHeightMapShader.setMat4("view", view);
            // world transformation
            glm::mat4 position;
            glm::mat4 model = glm::mat4(1.0f);
            tessHeightMapShader.setMat4("model", model);
            //glm::mat4 model = glm::mat4(1.0f);
           /* Transform model2;
            model2.SetScale(1.0f, 1.0f, 1.0f);
            model2.SetPosition(1.0f, 1.0f, 1.0f);
            model2.GetScale();*/


            // render the terrain
            glBindVertexArray(terrainVAO);
            glDrawArrays(GL_PATCHES, 0, NUM_PATCH_PTS * rez * rez);

            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            // -------------------------------------------------------------------------------
            //SDL_GL_SwapWindow(window);

     
            //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

            SDL_GL_SwapWindow(window);
        }
       // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        
        // optional: de-allocate all resources once they've outlived their purpose:
        // ------------------------------------------------------------------------
        glDeleteVertexArrays(1, &terrainVAO);
        glDeleteBuffers(1, &terrainVBO);

        // glfw: terminate, clearing all previously allocated GLFW resources.
        // ------------------------------------------------------------------
        //instead of glfwTerminate();
        // Quit SDL
        SDL_GL_DeleteContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();

        shaderAi::daspeka()->jyaikarawaShader();
        shaderAi::daspeka()->lanawyBaraShader();
        shaderAi::daspeka()->lanawyBaraProgram();



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



