#ifndef SRC_VIEW_WIDGET_OPENGL_MODEL_H_
#define SRC_VIEW_WIDGET_OPENGL_MODEL_H_

#include <gtk/gtk.h>
#include <epoxy/gl.h>
#include <vector>

namespace s21 {
class Buffer {
  public:
    Buffer() {};
    ~Buffer() {
      glDeleteBuffers(1, &vertex_);
	  glDeleteBuffers(1, &element_);
	}

	void CreateBuffer(std::vector<float>& vertex, std::vector<int>& element) {
	  CreateVertexArrayObject();
	  CreateVertexBuffer(vertex);
	  CreateElementBuffer(element);
	}

    GLuint GetVAO() {return vao_;}
	GLuint GetVertexBuffer() {return vertex_;}
	GLuint GetElementBuffer() {return element_;}

  private:
    GLuint vao_ = 0; //TODO vbo
	GLuint vertex_ = 0;
	GLuint element_ = 0;

	void CreateVertexArrayObject() {
	  glGenVertexArrays(1, &vao_);
	  glBindVertexArray(vao_);
	}

	void CreateVertexBuffer(std::vector<float>& vertex) {
	  glGenBuffers(1, &vertex_);
	  glBindBuffer(GL_ARRAY_BUFFER, vertex_);
	  glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertex.size(), vertex.data(), GL_STATIC_DRAW);
	  glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void CreateElementBuffer(std::vector<int>& element) {
	  glGenBuffers(1, &element_);
	  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_);
	  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*element.size(), element.data(), GL_STATIC_DRAW);
	  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

};

class Shader {
  public:
    Shader() {}
	~Shader() {}

	void InitShader() {
	  GLuint vertex = CreateShader(GL_VERTEX_SHADER, GetVertexShaderSource());
      if (!vertex) throw std::runtime_error("Compilation vertex shader failed");

	  GLuint fragment = CreateShader(GL_FRAGMENT_SHADER, GetFragmentShaderSource());
      if (!fragment) throw std::runtime_error("Compilation fragment shader failed");
	
	  program_ = glCreateProgram();
	  glAttachShader(program_, vertex);
	  glAttachShader(program_, fragment);
	  glLinkProgram(program_);

	  int link_status = 0;
	  glGetProgramiv(program_, GL_LINK_STATUS, &link_status);
	  if (GL_FALSE == link_status) g_print("\nprogram link failed\n");

	  mvp_ = glGetUniformLocation(program_, "mvp");

	  glDetachShader(program_, vertex);
	  glDetachShader(program_, fragment);
	  glDeleteShader(vertex);
	  glDeleteShader(fragment);
	}

	GLuint GetProgram() {return program_;}
	GLuint GetMVP() {return mvp_;}

  private:
	GLuint program_ = 0;
	GLuint mvp_ = 0;

	GLuint CreateShader(int type, const char* src) {
	  GLuint shader = glCreateShader(type);
	  glShaderSource(shader, 1, &src, NULL);
	  glCompileShader(shader);

	  int compile_status = 0;
	  glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);
	  if(compile_status == GL_FALSE) {
        g_print("\nCreate Shader error! %i=%i\n", type, GL_FRAGMENT_SHADER);
	  }
	  return shader;
	}

    char* GetVertexShaderSource() {
	  std::string version = "#version 330\n";
	  std::string prefix = "layout(location=0) in vec4 position;\nuniform mat4 mvp;\n";
	  std::string main = "void main(){\ngl_Position=mvp*position;}\n\0";
	  static std::string res = version+prefix+main;
	  return res.data();
	}

    char* GetFragmentShaderSource() {
	  std::string version = "#version 330\n";
	  std::string prefix = "out vec4 outputColor;\n";
	  std::string main = "void main(){\noutputColor=vec4(1,0,0,1);}\n\0";
	  static std::string res = version+prefix+main;
	  return res.data();
	}

};

}

#endif
