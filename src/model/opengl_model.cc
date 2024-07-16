
#include <stdexcept>

#include "opengl_model.h"
#include "figure.h"



void s21::Buffer::CreateBuffer(std::vector<float>& v_data,
                               std::vector<unsigned int>& e_data) {
  Clear();
  CreateVertexBuffer(v_data);
  CreateElementBuffer(e_data);
}

void s21::Buffer::Clear() {
  if (vertex_) glDeleteBuffers(1, &vertex_);
  if (element_) glDeleteBuffers(1, &element_);
}

void s21::Buffer::CreateVertexBuffer(std::vector<float>& data) {
  glGenBuffers(1, &vertex_);
  glBindBuffer(GL_ARRAY_BUFFER, vertex_);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(),
               GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void s21::Buffer::CreateElementBuffer(std::vector<unsigned int>& data) {
  glGenBuffers(1, &element_);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * data.size(),
               data.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}



void s21::Shader::LoadShader(const char* vertex_path, const char* fragment_path,
                             const char* geometry_path) {
  InitShader(vertex_path, fragment_path, geometry_path);
}

void s21::Shader::InitShader(const char* vertex_path, const char* fragment_path,
                             const char* geometry_path) {
  GLuint vertex, fragment, geometry;
  int status;
  vertex = CreateShader(GL_VERTEX_SHADER, LoadFile(vertex_path));

  if (vertex) {
    fragment = CreateShader(GL_FRAGMENT_SHADER, LoadFile(fragment_path));
    if (fragment && geometry_path) {
      geometry = CreateShader(GL_GEOMETRY_SHADER, LoadFile(geometry_path));
      if (!geometry) {
				throw std::invalid_argument("Geometry shader failed");
      } 	
    }
  } else {
    throw std::invalid_argument("Vertex shader failed");
  }

  if (!fragment) {
    glDeleteShader(vertex);
    throw std::invalid_argument("fragment shader failed");
  }

  program_ = glCreateProgram();
  glAttachShader(program_, vertex);
  glAttachShader(program_, fragment);
  if (geometry_path) {
    glAttachShader(program_, geometry);
  }
  glLinkProgram(program_);

  glGetProgramiv(program_, GL_LINK_STATUS, &status);
  if (status == GL_FALSE) {
    int log_len;
    char* buffer;
    glGetProgramiv(program_, GL_INFO_LOG_LENGTH, &log_len);
    buffer = new char[log_len + 1]();
    glGetProgramInfoLog(program_, log_len, 0, buffer);
		std::string error_message = "Program link failed: \n";
		error_message += buffer;
		throw std::invalid_argument(error_message);
  } 

  glDetachShader(program_, vertex);
  glDetachShader(program_, fragment);
  glDetachShader(program_, geometry);

  glDeleteShader(vertex);
  glDeleteShader(fragment);
  glDeleteShader(geometry);
}



GLuint s21::Shader::CreateShader(int type, const char* src) {
  GLuint shader;
  int status;
  shader = glCreateShader(type);
  glShaderSource(shader, 1, &src, NULL);
  glCompileShader(shader);

  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) {
    int log_len;
    char* buffer;	
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_len);
    buffer = new char[log_len + 1];
    glGetShaderInfoLog(shader, log_len, NULL, buffer);
		std::string error_type = ((type == GL_VERTEX_SHADER) ? "vertex" :
		                         ((type == GL_FRAGMENT_SHADER) ? "fragment" : "geometry"));

    std::string error_message = "Program link failed on ";
		error_message += error_type;
		error_message += " shader. \n";
		error_message += "Program text is:\n";
		error_message += src;
		error_message += '\0';
		throw std::invalid_argument(error_message);
  } 
  delete src;
  return shader;
}

size_t s21::Shader::GetFileLength(const char* file_name) {
  size_t length = 0;
	FILE* fp = fopen(file_name, "rb");
	if (fp) {
	  fseek(fp, 0, SEEK_END);
		length = ftell(fp);
		fclose(fp);
	}
	return length;
}

char* s21::Shader::LoadFile(const char* file_name) {
  size_t length = GetFileLength(file_name);
  char* text = new char[length + 1]();
  FILE* fp = fopen(file_name, "rb");
  if (fp) {
    fread(text, 1, length, fp);
		text[length] = 0;
    fclose(fp);
  } else {
		std::string error_message = "s21::Shader::LoadFile : error opening shader file \"";
		error_message += file_name;
		error_message += "\"";
    throw std::invalid_argument(error_message.data());
  }
  return text;
}




void s21::OpenGLModel::SetBuffer() {
  gtk_gl_area_make_current(GTK_GL_AREA(area_));
  InitBuffer();
  InitShaders();
}


void s21::OpenGLModel::Draw() {
  if (vertex_->GetVertexBuffer() != 0) {
    DrawFigure();
  }
}


void s21::OpenGLModel::DrawFigure() {
  Matrix4f mvp;
  ComputeMVP(mvp);
  ResetField();

  ConnectBuffers();

  DrawLines(mvp);
  DrawPoints(mvp);

  glDisableVertexAttribArray(0);
  glUseProgram(0);
}

void s21::OpenGLModel::ResetField() {
  GdkRGBA color = *(data_->GetAreaColor());
  glClearColor(color.red, color.green, color.blue, color.alpha);
  glEnable(GL_DEPTH_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void s21::OpenGLModel::ConnectBuffers() {
  glBindBuffer(GL_ARRAY_BUFFER, vertex_->GetVertexBuffer());
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), nullptr);
  glEnableVertexAttribArray(0);
}

void s21::OpenGLModel::DrawPoints(Matrix4f& mvp) {
  if (data_->GetPointType()) {
    mvp_location_ = glGetUniformLocation(point_shader.GetProgram(), "mvp");
    color_location_ = glGetUniformLocation(point_shader.GetProgram(), "color");
    glUseProgram(point_shader.GetProgram());
    glBindVertexArray(vao_);
    glUniformMatrix4fv(mvp_location_, 1, GL_TRUE, &mvp(0, 0));
    glEnableVertexAttribArray(0);

    GdkRGBA color = *(data_->GetPointColor());
    GLfloat point_color[4]{color.red, color.green, color.blue, color.alpha};
    glUniform4fv(color_location_, 1, point_color);
    glUniform1f(glGetUniformLocation(point_shader.GetProgram(), "size"),
                data_->GetPointSize());
    glUniform1i(glGetUniformLocation(point_shader.GetProgram(), "type"),
                data_->GetPointType());

    glDrawArrays(GL_POINTS, 0, s21::Figure::GetInstance()->GetVertexCount());
    glFlush();
  }
}

void s21::OpenGLModel::DrawLines(Matrix4f& mvp) {
  if (data_->GetLineType()) {
    mvp_location_ = glGetUniformLocation(line_shader.GetProgram(), "mvp");
    glUseProgram(line_shader.GetProgram());
    glBindVertexArray(vao_);
    glUniformMatrix4fv(mvp_location_, 1, GL_TRUE, &mvp(0, 0));
    glEnableVertexAttribArray(0);

    GdkRGBA color = *(data_->GetLineColor());
    GLfloat line_color[4]{color.red, color.green, color.blue, color.alpha};
    glUniform4fv(glGetUniformLocation(line_shader.GetProgram(), "color"), 1,
                 line_color);

    color = *(data_->GetAreaColor());
    GLfloat background_color[4]{color.red, color.green, color.blue,
                                color.alpha};
    glUniform4fv(
        glGetUniformLocation(line_shader.GetProgram(), "background_color"), 1,
        background_color);

    glUniform1f(glGetUniformLocation(line_shader.GetProgram(), "size"),
                data_->GetLineWidth());
    glUniform1i(glGetUniformLocation(line_shader.GetProgram(), "type"),
                data_->GetLineType());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertex_->GetElementBuffer());

    std::vector<unsigned int> offset =
        s21::Figure::GetInstance()->GetIndexOffset();

    size_t last_position = 0;
    glDrawElements(GL_LINE_LOOP, offset[0], GL_UNSIGNED_INT,
                   (void*)(last_position));
    for (size_t i = 1; i < offset.size(); ++i) {
      last_position += offset[i - 1] * sizeof(unsigned int);
      glDrawElements(GL_LINE_LOOP, offset[i], GL_UNSIGNED_INT,
                     (void*)(last_position));
    }
    glFlush();
  }
}

void s21::OpenGLModel::InitShaders() {
  point_shader.LoadShader("glarea/point_vs.glsl", "glarea/point_fs.glsl",
                          "glarea/point_gs.glsl");
  line_shader.LoadShader("glarea/line_vs.glsl", "glarea/line_fs.glsl",
                         "glarea/line_gs.glsl");
}

void s21::OpenGLModel::InitBuffer() {
  glGenVertexArrays(1, &vao_);
  glBindVertexArray(vao_);
  std::vector<float> v = s21::Figure::GetInstance()->GetVertex();
  std::vector<unsigned int> e = s21::Figure::GetInstance()->GetVSurface();
  vertex_->CreateBuffer(v, e);
}

void s21::OpenGLModel::ComputeMVP(Matrix4f& mvp) {
  Projection(mvp);
  Translation(mvp);
  Rotation(mvp);
  Scaling(mvp);
}

void s21::OpenGLModel::Rotation(Matrix4f& mvp) {
  Affine3D affine;
  float* rotor = data_->GetRotation();
  mvp *= affine.GetRotation(rotor[0], rotor[1], rotor[2]);
}

void s21::OpenGLModel::Scaling(Matrix4f& mvp) {
  Affine3D affine;
  float* scale = data_->GetScaling();
  mvp *= affine.GetScaling(scale[0], scale[1], scale[2]);
}

void s21::OpenGLModel::Translation(Matrix4f& mvp) {
  Affine3D affine;
  float* trans = data_->GetTranslation();
  mvp *= affine.GetTranslation(trans[0], trans[1], 5 + trans[2]);
}

void s21::OpenGLModel::Projection(Matrix4f& mvp) {
  Affine3D affine;
  // mvp *= affine.GetTranslation(0,0,5);
  if (data_->GetProjection() == 0) {
    mvp *= affine.GetParralelProjection();
  } else {
    mvp *= affine.GetCentralProjection();
  }
}
