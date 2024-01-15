#ifndef SRC_VIEW_WIDGET_DRAWING_AREA_H_
#define SRC_VIEW_WIDGET_DRAWING_AREA_H_

#include <gtk/gtk.h>

#include "widget.h"
#include <epoxy/gl.h>

namespace s21 {
class DrawingArea: public Widget {
  public:
    DrawingArea() {
      InitArea(); 
	}

	~DrawingArea(){};

	void SetMother(s21::Widget* mother) {} //TODO
	void CatchSignal() {
     g_print("\ngo\n");
	 gtk_widget_queue_draw(area_);

	} //TODO
	void SendSignal() {} //TODO


	static void Realize(GtkWidget* area, s21::DrawingArea* self) {
	  gtk_gl_area_make_current(GTK_GL_AREA(self->area_));
	  self->context_ = gtk_gl_area_get_context(GTK_GL_AREA(self->area_));  
	  self->InitBuffer();
	  self->InitShader();
	}

	static void Render(GtkWidget* area, GdkGLContext* context, s21::DrawingArea* self) {
      gtk_gl_area_make_current(GTK_GL_AREA(self->area_));
	  glClearColor(0.0, 0.0, 0.5, 1.0); //TODO
	  glEnable(GL_DEPTH_TEST);
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	  self->DrawFigure();
	  glFlush();
	}

	static void Unrealize(GtkWidget* area, s21::DrawingArea* self) {
	  //self->RemoveBuffer();
	  //self->RemoveShader();
	}

  void ComputeMVP(float* mvp) {
    float tmp[9] = {1,0,0,  0,1,0, 0,0,1};
    float* array = affine_data_->GetData();
 
    Rotate(tmp, array[0], array[1], array[2]);
	for (size_t i = 0; i < 3; ++i) {
	  mvp[i] = tmp[i];
	  mvp[4+i] = tmp[3 + i];
	  mvp[8+i] = tmp[6 + i];
	}


	mvp[0] *=  array[6];
    mvp[5] *= array[7];
    mvp[10] *= array[8];

//	Rotate(mvp, array[0], array[1], array[2]);

	mvp[12] = array[3];
	mvp[13] = array[4];
	mvp[14] = array[5];

	
/*    Rotate(tmp, array[0], array[1], array[2]);
	for (size_t i = 0; i < 3; ++i) {
	  mvp[i] = tmp[i];
	  mvp[4+i] = tmp[3 + i];
	  mvp[8+i] = tmp[6 + i];
	}*/
  }

  void Rotate(float* mvp, float x_rad, float y_rad, float z_rad) {
    for (size_t i = 0; i < 9; i += 3) {
      float x_tmp = mvp[i + 0];
      float x_rot_1 = sin(x_rad) * mvp[i + 1] - cos(x_rad) * mvp[i + 2];
      float x_rot_2 = cos(x_rad) * mvp[i + 1] + sin(x_rad) * mvp[i + 2];
      float y_z_rot = cos(y_rad) * x_tmp;

      mvp[i + 0] = cos(z_rad) * (y_z_rot + sin(y_rad) * x_rot_1) + sin(z_rad) * x_rot_2;
      mvp[i + 1] = sin(z_rad) * (-y_z_rot - sin(y_rad) * x_rot_1)  + cos(z_rad) * x_rot_2;
      mvp[i + 2] = x_tmp * sin(y_rad) - x_rot_1 * cos(y_rad);
	  //g_print("\ni = %i\n", i);
	  //g_print("\nmvp is %f %f %f %f\n", mvp[i], mvp[i+1], mvp[i+2], mvp[i+3]);
    }
  }

	void DrawFigure() {
	  float mvp[16] = {1, 0, 0, 0,   0,1,0,0,  0,0,1,0, 0,0,0,1};

	  ComputeMVP(mvp);
	  glEnable(GL_CULL_FACE);
	  glFrontFace(GL_CW);

	  glUseProgram(program_);
	  glUniformMatrix4fv(mvp_, 1, GL_FALSE, &mvp[0]);
	  

	  glEnableVertexAttribArray(0);
	  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
	  glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);

	  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_);


      //glEnable(GL_POINT_SMOOTH);
	  //glEnable(GL_LINE_SMOOTH);
	  //glEnable(GL_POINTS);
	  //glEnable(GL_PROGRAM_POINT_SIZE);

	  glPointSize(20);
	  //glLineWidth(100.0);
	  //glEnable(GL_LINE_WIDTH);
	  glLineWidth(2);

	  GLfloat arr[10]{};
	  glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, arr);
	  g_print("\nglGet = %f, %f\n", arr[0], arr[1]);

      glDrawArrays(GL_POINTS, 0, 9);
      glDrawArrays(GL_LINE_LOOP, 0, 3);
	  glLineWidth(0.0000000001);
      glDrawArrays(GL_LINE_LOOP, 3, 3);
	  //glLineWidth(0.00001);
      glDrawArrays(GL_LINE_LOOP, 6, 3);

	  //TODO
	  glDisableVertexAttribArray(0);
	  glUseProgram(0);

	}

	void AttachAffineData(s21::AffineData* data) {
	  affine_data_ = data;
	}

  private:
    GtkWidget* area_ = nullptr;
	GdkGLContext* context_ = nullptr;
    
	GLuint vao_ = 0;
    GLuint vertex_buffer_ = 0;
    GLuint element_buffer_ = 0;
    GLuint program_ = 0;
    GLuint mvp_ = 0;

	s21::AffineData* affine_data_ = nullptr;


	void InitArea() {
	  area_ = gtk_gl_area_new();
	  gtk_widget_set_hexpand(area_, true);
	  gtk_widget_set_vexpand(area_, true);
	  gtk_frame_set_child(GTK_FRAME(GetFrame()), area_);
	  g_signal_connect(area_, "realize", G_CALLBACK(Realize), this);
	  g_signal_connect(area_, "render", G_CALLBACK(Render), this);
	  g_signal_connect(area_, "unrealize", G_CALLBACK(Unrealize), this);
	}

  void InitBuffer() {
    std::vector<float> v {-0.5, 0.0, 0.0,  0.0, 0.5, 0.0,  0.5, 0.0, 0.0,
                          -0.5, 0.0, 0.0,  0.5, -0.0, 0.0, 0.0, 0.0, 0.5,
                          -0.5, 0.0, 0.0,  0.0, 0.5, 0.0, 0.0, 0.0, 0.5};
    std::vector<int> f {1, 2, 3, 1, 4, 5};

    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    glGenBuffers(1, &vertex_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*v.size(), v.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenBuffers(1, &element_buffer_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_);
  }

  void InitShader() {
    GLuint vertex, fragment;
    int status; //??

    const char* file_name = "glarea/vs.glsl";
    vertex = CreateShader(GL_VERTEX_SHADER, LoadFile(file_name));

    if (vertex) {
      file_name = "glarea/fs.glsl";
      fragment = CreateShader(GL_FRAGMENT_SHADER, LoadFile(file_name));
    } else {
      g_print("\nvertex shader failed\n");
      return;
    }

    if (!fragment) {
      glDeleteShader(vertex);
      g_print("\nfragment shader failed\n");
      return;
    }

    program_ = glCreateProgram();
    glAttachShader(program_, vertex);
    glAttachShader(program_, fragment);
    glLinkProgram(program_);

    glGetProgramiv(program_, GL_LINK_STATUS, &status);
    if (status == GL_FALSE) {
      g_print("\nprogram link failed\n");
    } //TODO

    mvp_ = glGetUniformLocation(program_, "mvp");

    glDetachShader(program_, vertex);
    glDetachShader(program_, fragment);

    glDeleteShader(vertex);
    glDeleteShader(fragment);
  //g_print("\nprog = %i, <-> %i\n", program, *program_out);	
  }

  GLuint CreateShader(int type, const char* src) {
    GLuint shader;
    int status;

    shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE) {
      g_print("\nCreate shader error\n");
    } //TODO
	delete src;
    return shader;
  }

  char* LoadFile(const char* file_name) {
    int len = 1024; //TODO
    char* text = new char[len]();
    FILE* fp = fopen(file_name, "rb");
    if (fp) {
      fread(text, 1, len, fp);
      fclose(fp);
    } else {
      g_print("\nError Opening File\n");
    }
    return text;
  }

};
}


#endif
