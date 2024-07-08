#include "opengl_model.h"
#include "figure.h"

void s21::Buffer::CreateBuffer(std::vector<float> &v_data,
                    std::vector<unsigned int> &e_data) {
  Clear();
  CreateVertexBuffer(v_data);
  CreateElementBuffer(e_data);
}

void s21::Buffer::Clear() {
  if (vertex_)
    glDeleteBuffers(1, &vertex_);
  if (element_)
    glDeleteBuffers(1, &element_);
}

void s21::Buffer::CreateVertexBuffer(std::vector<float> &data) {
    glGenBuffers(1, &vertex_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * data.size(), data.data(),
                 GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void s21::Buffer::CreateElementBuffer(std::vector<unsigned int> &data) {
      glGenBuffers(1, &element_);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                   sizeof(unsigned int) * data.size(), data.data(),
                   GL_STATIC_DRAW);
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }




void s21::Shader::LoadShader(const char* vertex_path, const char* fragment_path, const char* geometry_path) {
    InitShader(vertex_path, fragment_path, geometry_path);
}

void s21::Shader::InitShader(const char* vertex_path, const char* fragment_path, const char* geometry_path) {
  GLuint vertex, fragment, geometry;
  int status;

  vertex = CreateShader(GL_VERTEX_SHADER, LoadFile(vertex_path));

  if (vertex) {
    fragment = CreateShader(GL_FRAGMENT_SHADER, LoadFile(fragment_path));
    if (fragment && geometry_path) {
      geometry = CreateShader(GL_GEOMETRY_SHADER, LoadFile(geometry_path));
      if (!geometry) {
        g_print("\ngeometry shader failed\n");
      }
    }
  } else {
    g_print("\nvertex shader failed\n");
    return; // TODO
  }

  if (!fragment) {
    glDeleteShader(vertex);
    g_print("\nfragment shader failed\n");
    return;
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
    buffer = (char*)g_malloc(log_len + 1);
    glGetProgramInfoLog(program_, log_len, NULL, buffer);
    g_print("\nprogram link failed = %s\n", buffer);
  } // TODO

  glDetachShader(program_, vertex);
  glDetachShader(program_, fragment);
  glDetachShader(program_, geometry); //TODO

  glDeleteShader(vertex);
  glDeleteShader(fragment);
  glDeleteShader(geometry);
}

GLuint s21::Shader::CreateShader(int type, const char *src) {
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
      buffer = (char*)g_malloc(log_len + 1);
      glGetShaderInfoLog(shader, log_len, NULL, buffer);
      g_print("\ntype = %s\n", (type == GL_VERTEX_SHADER) ? "vertex" :
                                   ((type == GL_FRAGMENT_SHADER) ? "fragment" : "geometry"));
      g_print("\nprogram link failed = %s\n", buffer);

    } // TODO
    delete src;
    return shader;
  }

  char *s21::Shader::LoadFile(const char *file_name) {
    int len = 4096; // TODO
    char *text = new char[len]();
    FILE *fp = fopen(file_name, "rb");
    if (fp) {
      fread(text, 1, len, fp);
      fclose(fp);
    } else {
      g_print("\nError Opening File\n");
    }
    return text;
  } //TODO GetFileLength





void s21::Texture::Create(const std::string& file_name) {
    if (file_name != file_) {
      file_ = file_name;
      unsigned char* data = stbi_load(file_name.data(), &width_, &height_, &color_mod_, 0);
      if (color_mod_ < 3) {} //TODO
      glGenTextures(1, &id_);
      glBindTexture(GL_TEXTURE_2D, id_);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0,
                   ((color_mod_ == 3) ? GL_RGB : GL_RGBA), GL_UNSIGNED_BYTE, data);

      SamplerInit();
      glBindTexture(id_, 0);
      stbi_image_free(data);
    }
}

void s21::Texture::SamplerInit() {
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}







void s21::OpenGLModel::SetBuffer() {
    gtk_gl_area_make_current(GTK_GL_AREA(area_));
    InitBuffer();
    InitShaders();
}

void s21::OpenGLModel::LoadTexture(std::string& file) {
    texture_image_.Create(file);
}

void s21::OpenGLModel::Draw() {
  if (vertex_->GetVertexBuffer() != 0) {
    DrawFigure();
  }
}

  unsigned int* s21::OpenGLModel::Mirroring(size_t width, size_t height, unsigned int* data) {
    unsigned int arr[width*height];
    for (size_t i = 0; i < height; ++i) {
      unsigned int* row = data + width*i;
      unsigned int* arr_row = arr + width*(height - i - 1);
      for (size_t j = 0; j < width; ++j) {
        arr_row[j] = row[j];
      }
    }
    for (size_t i = 0; i < width*height; ++i) {
      data[i] = arr[i];
    }
    return data;
  }

  void s21::OpenGLModel::SavePicture(size_t m_width, size_t m_height, const char* file_name, const char* type) {
    size_t width = gtk_widget_get_width(GTK_WIDGET(area_));
    size_t height = gtk_widget_get_height(GTK_WIDGET(area_));
    size_t chanels = 4;

    unsigned int* data = new unsigned int[width * height]{0};
    Draw(); 
    glReadPixels(m_width - width, m_height - height, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
		data = Mirroring(width, height, data);
   
   stbi_write_png(file_name, width, height, chanels, data, chanels*width);
   stbi_write_jpg(file_name, width, height, chanels, data, 80);
   stbi_write_bmp(file_name, width, height, chanels, data);

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
    glClearColor(color.red, color.green, color.blue, color.alpha );
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  void s21::OpenGLModel::ConnectBuffers() {
    glBindBuffer(GL_ARRAY_BUFFER, vertex_->GetVertexBuffer());
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                          nullptr);
    glEnableVertexAttribArray(0);
  }

  void s21::OpenGLModel::DrawPoints(Matrix4f& mvp) {
    if (data_->GetPointType()) {
      mvp_location_ = glGetUniformLocation(point_shader.GetProgram(), "mvp");
      color_location_ = glGetUniformLocation(point_shader.GetProgram(), "color");
      glUseProgram(point_shader.GetProgram());
      glBindVertexArray(vao_);
      glUniformMatrix4fv(mvp_location_, 1, GL_TRUE, &mvp(0,0));
      glEnableVertexAttribArray(0);
				    
      GdkRGBA color = *(data_->GetPointColor());
      GLfloat point_color[4] {color.red, color.green, color.blue, color.alpha};
      glUniform4fv(color_location_, 1, point_color);
      glUniform1f(glGetUniformLocation(point_shader.GetProgram(), "size"), data_->GetPointSize());
      glUniform1i(glGetUniformLocation(point_shader.GetProgram(), "type"), data_->GetPointType());
      
			glDrawArrays(GL_POINTS, 0, s21::Figure::GetInstance()->GetVertexCount());
      glFlush();
    }
  }

  void s21::OpenGLModel::DrawLines(Matrix4f& mvp) {
    if (data_->GetLineType()) {
      mvp_location_ = glGetUniformLocation(line_shader.GetProgram(), "mvp");
      glUseProgram(line_shader.GetProgram());
      glBindVertexArray(vao_);
      glUniformMatrix4fv(mvp_location_, 1, GL_TRUE, &mvp(0,0));
      glEnableVertexAttribArray(0);

      GdkRGBA color = *(data_->GetLineColor());
      GLfloat line_color[4] {color.red, color.green, color.blue, color.alpha};
      glUniform4fv(glGetUniformLocation(line_shader.GetProgram(), "color"), 1, line_color);

      color = *(data_->GetAreaColor());
      GLfloat background_color[4] {color.red, color.green, color.blue, color.alpha};
      glUniform4fv(glGetUniformLocation(line_shader.GetProgram(), "background_color"), 1, background_color);


      glUniform1f(glGetUniformLocation(line_shader.GetProgram(), "size"), data_->GetLineWidth());
      glUniform1i(glGetUniformLocation(line_shader.GetProgram(), "type"), data_->GetLineType());
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertex_->GetElementBuffer());

      std::vector<unsigned int> offset = s21::Figure::GetInstance()->GetIndexOffset();

      size_t last_position = 0;
      glDrawElements(GL_LINE_LOOP, offset[0], GL_UNSIGNED_INT, (void *)(last_position));
      for (size_t i = 1; i < offset.size(); ++i) {
        last_position += offset[i-1] * sizeof(unsigned int);
        glDrawElements(GL_LINE_LOOP, offset[i], GL_UNSIGNED_INT, (void *)(last_position));
      }
      glFlush();
    }
  }

  void s21::OpenGLModel::InitShaders() {
    point_shader.LoadShader("glarea/point_vs.glsl", "glarea/point_fs.glsl", "glarea/point_gs.glsl");
    line_shader.LoadShader("glarea/line_vs.glsl", "glarea/line_fs.glsl", "glarea/line_gs.glsl");
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
    float *rotor = data_->GetRotation();
    mvp *= affine.GetRotation(rotor[0], rotor[1], rotor[2]);
  }

  void s21::OpenGLModel::Scaling(Matrix4f& mvp) {
    Affine3D affine;
    float *scale = data_->GetScaling();
    mvp *= affine.GetScaling(scale[0], scale[1], scale[2]);
  }

  void s21::OpenGLModel::Translation(Matrix4f& mvp) {
    Affine3D affine;
    float *trans = data_->GetTranslation();
    mvp *= affine.GetTranslation(trans[0], trans[1], 5 + trans[2]);
  }

  void s21::OpenGLModel::Projection(Matrix4f& mvp) {
    Affine3D affine;
   // mvp *= affine.GetTranslation(0,0,5);
    if(data_->GetProjection() == 0) { 
      mvp *= affine.GetParralelProjection();
    } else {
      mvp *= affine.GetCentralProjection();
    }
  }
