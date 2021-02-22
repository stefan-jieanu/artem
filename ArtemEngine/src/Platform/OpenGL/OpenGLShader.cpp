#include "aepch.h"
#include "OpenGLShader.h"

#include <fstream>

namespace ArtemEngine {

    OpenGLShader::OpenGLShader(const std::string& filepath)
        : shaderID_(0)
    {
        // Get the the of the shader from the filepath
        auto lastSlash = filepath.find_last_of("/\\");
        lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
        auto lastDot = filepath.rfind(".");

        auto count = lastDot == std::string::npos ? filepath.size() - lastSlash : lastDot - lastSlash;
        name_ = filepath.substr(lastSlash, count);

        // Get the source code for each shader program
        ShaderProgramSource source = ParseShader(filepath);

        // Create a shader using the source code previously loaded
        shaderID_ = CreateShader(source.vertexSource, source.fragmentSource);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(shaderID_);
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(shaderID_);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }

    void OpenGLShader::SetUniformFloat(const std::string& name, float value) const
    {
        glUniform1f(GetUniformLocation(name), value);
    }

    void OpenGLShader::SetUniformFloat2(const std::string& name, const Math::Vector2& value) const
    {
        glUniform2f(GetUniformLocation(name), value.x, value.y);
    }

    void OpenGLShader::SetUniformFloat2(const std::string& name, float v1, float v2) const
    {
        glUniform2f(GetUniformLocation(name), v1, v2);
    }

    void OpenGLShader::SetUniformFloat3(const std::string& name, const Math::Vector3& value) const
    {
        glUniform3f(GetUniformLocation(name), value.x, value.y, value.z);
    }

    void OpenGLShader::SetUniformFloat3(const std::string& name, float v1, float v2, float v3) const
    {
        glUniform3f(GetUniformLocation(name), v1, v2, v3);
    }

    void OpenGLShader::SetUniformFloat4(const std::string& name, const Math::Vector4& value) const
    {
        glUniform4f(GetUniformLocation(name), value.x, value.y, value.z, value.w);
    }

    void OpenGLShader::SetUniformFloat4(const std::string& name, float v1, float v2, float v3, float v4) const
    {
        glUniform4f(GetUniformLocation(name), v1, v2, v3, v4);
    }

    void OpenGLShader::SetUniformMat3() const
    {
        LOG_CORE_ASSERT(false, "SetUniformMat3() not implemented!");
    }

    void OpenGLShader::SetUniformMat4(const std::string& name, const Math::Matrix4& value) const
    {
        glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, Math::GetValuePointer(value));
    }

    void OpenGLShader::SetUnifomInt(const std::string& name, int value) const
    {
        glUniform1i(GetUniformLocation(name), value);
    }

    void OpenGLShader::SetUnifomInt2(const std::string& name, const Math::Vector2& value) const
    {
        glUniform2i(GetUniformLocation(name), (int)value.x, (int)value.y);
    }

    void OpenGLShader::SetUnifomInt2(const std::string& name, int v1, int v2) const
    {
        glUniform2i(GetUniformLocation(name), v1, v2);
    }

    void OpenGLShader::SetUnifomInt3(const std::string& name, const Math::Vector3& value) const
    {
        glUniform3i(GetUniformLocation(name), (int)value.x, (int)value.y, (int)value.z);
    }

    void OpenGLShader::SetUnifomInt3(const std::string& name, int v1, int v2, int v3) const
    {
        glUniform3i(GetUniformLocation(name), v1, v2, v3);
    }

    void OpenGLShader::SetUnifomInt4(const std::string& name, const Math::Vector4& value) const
    {
        glUniform4i(GetUniformLocation(name), (int)value.x, (int)value.y, (int)value.z, (int)value.w);
    }

    void OpenGLShader::SetUnifomInt4(const std::string& name, int v1, int v2, int v3, int v4) const
    {
        glUniform4i(GetUniformLocation(name), v1, v2, v3, v4);
    }

    void OpenGLShader::SetUniformIntArray(const std::string& name, int* values, uint32_t count) const
    {
        glUniform1iv(GetUniformLocation(name), count, values);
    }

    void OpenGLShader::SetUniformBoll(const std::string& name, bool value) const
    {
        LOG_CORE_ASSERT(false, "SetUniformBool() not implemented!");
    }

    ShaderProgramSource OpenGLShader::ParseShader(const std::string& filepath)
    {
        std::ifstream stream(filepath);
        if (!stream.good())
            LOG_CORE_ERROR("Shader source file not found: {}", filepath);

        std::string line;

        enum class ShaderType
        {
            NONE = -1, VERTEX = 0, FRAGMENT = 1
        };

        std::stringstream ss[2];
        ShaderType type = ShaderType::NONE;

        while (std::getline(stream, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                    type = ShaderType::VERTEX;
                else if (line.find("fragment") != std::string::npos)
                    type = ShaderType::FRAGMENT;
            }
            else
            {
                ss[(int)type] << line << "\n";
            }
        }

        return { ss[0].str(), ss[1].str() };
    }

    uint32_t OpenGLShader::CompileShader(unsigned int type, const std::string& source)
    {
        uint32_t id = glCreateShader(type);
        const char* src = source.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        // Error handling
        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE)
        {
            int lenght;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
            char* message = (char*)alloca(lenght * sizeof(char));
            glGetShaderInfoLog(id, lenght, &lenght, message);
            LOG_CORE_ERROR("Failed to compile {} shader", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"));
            LOG_CORE_ERROR("{}", message);
            glDeleteShader(id);
            return 0;
        }

        return id;
    }

    uint32_t OpenGLShader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
    {
        // The shader program containing fragment and vertex
        unsigned int program = glCreateProgram();

        // The vertex shader by itself
        unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);

        // The fragment shader by itself
        unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

        // Linking vertex and fragment into a single shader program
        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);

        // Deleting the now unused vertex and fragment shader because they are now stored 
        // in a unified(linked) shader program
        glDetachShader(program, vs);
        glDetachShader(program, fs);
        glDeleteShader(vs);
        glDeleteShader(fs);

        return program;
    }

    int32_t OpenGLShader::GetUniformLocation(const std::string& name) const
    {
        int location = glGetUniformLocation(shaderID_, name.c_str());
        if (location == -1)
            LOG_CORE_WARN("Uniform \"{}\" doesn't exist", name);
        return location;
    }
}