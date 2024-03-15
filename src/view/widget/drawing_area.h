#ifndef SRC_VIEW_WIDGET_DRAWING_AREA_H_
#define SRC_VIEW_WIDGET_DRAWING_AREA_H_

#include <gtk/gtk.h>

#include "widget.h"
#include "data/data.h"
#include "../../controller/controller.h"
#include <epoxy/gl.h>

namespace s21 {
class DrawingArea: public Widget {
  public:
    DrawingArea(s21::Data* data, s21::Controller* controller):data_(data), controller_(controller) {
      InitArea(); 
	}

	~DrawingArea(){};

	void SetMother(s21::Widget* mother) override {
      mother_ = mother;
	}

	void CatchSignal() override {
	 gtk_widget_queue_draw(area_);

	} //TODO

	void SendSignal() override {
      if(mother_) mother_->CatchSignal();
	} //TODO


  void SetBuffer() {
	  gtk_gl_area_make_current(GTK_GL_AREA(area_));
	  context_ = gtk_gl_area_get_context(GTK_GL_AREA(area_));  
    InitBuffer();//TODO
    InitShader();
  }

	static void Realize(GtkWidget* area, s21::DrawingArea* self) { //TODO private
	  gtk_gl_area_make_current(GTK_GL_AREA(self->area_));
	  self->context_ = gtk_gl_area_get_context(GTK_GL_AREA(self->area_));  
	  //self->InitBuffer();
	 // self->InitShader(); //TODO
	}

	static void Render(GtkWidget* area, GdkGLContext* context, s21::DrawingArea* self) { //TODO private
      gtk_gl_area_make_current(GTK_GL_AREA(self->area_));
      self->SetAreaColor();
	  self->DrawFigure();
	  glFlush();
	}

	static void Unrealize(GtkWidget* area, s21::DrawingArea* self) { //TODO private
	  //self->RemoveBuffer();
	  //self->RemoveShader();
	}

	void DrawFigure() { //TODO private
	  float mvp[16] = {1, 0, 0, 0,   0,1,0,0,  0,0,1,0, 0,0,0,1};

	  ComputeMVP(mvp);

    //g_print("\nmvp[0] = %f\n", mvp_[0]);
	  glEnable(GL_CULL_FACE);
	  glFrontFace(GL_CW);

	  glUseProgram(program_);
	  glUniformMatrix4fv(mvp_location_, 1, GL_FALSE, &mvp[0]);
	  

	  glEnableVertexAttribArray(0);
	  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
	  glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);

   // for(size_t i = 0; i < element_buffer_.size(); ++i) {
	 //   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_[i]);
   // }


      //glEnable(GL_POINT_SMOOTH);
	  //glEnable(GL_LINE_SMOOTH);
	  //glEnable(GL_POINTS);
	  //glEnable(GL_PROGRAM_POINT_SIZE);

	  glPointSize(3);
	  //glLineWidth(100.0);
	  //glEnable(GL_LINE_WIDTH);
	  //glLineWidth(2);

	  glEnable(GL_LINE_STIPPLE);
	  glLineStipple(0, 0);
	  //GLfloat arr[10]{};
	  //glGetFloatv(GL_ALIASED_LINE_WIDTH_RANGE, arr);
	  //g_print("\nglGet = %f, %f\n", arr[0], arr[1]);

    size_t element_length = controller_->GetSurfacesCount();
		//g_print("\nsdgstghftyf %li\n", element_length);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_);
		int offset = 0;
    for(size_t i = 0; i < element_length; ++i) {
      //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_);

	  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
	  glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);
    glDrawArrays(GL_POINTS, 0, controller_->GetVertexCount());
      //glDrawArrays(GL_LINE_LOOP, 0, 3);
	//  glLineWidth(0.0000000001);
     // glDrawArrays(GL_LINE_LOOP, 3, 3);
	  //glLineWidth(0.00001);
      //glDrawArrays(GL_LINE_LOOP, 6, 3);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_);
			//int offset = 0;
			offset += (i)?(controller_->GetSurfaces(i).size()):(0);
			g_print("\noffset = %li\n", offset);
			//g_print("\noffset = %li\n", offset);
			//g_print("\nsize = %li\n", sizeof(GLuint));
			//GLuint* ptr = &element_buffer_ + sizeof(GLuint)*offset;
      glDrawElements(GL_LINE_LOOP, offset, GL_UNSIGNED_INT, nullptr);
    }

	  //TODO
	  glDisableVertexAttribArray(0);
	  glUseProgram(0);

	}

  private:
    GtkWidget* area_ = nullptr;
    GdkGLContext* context_ = nullptr;
    s21::Widget* mother_ = nullptr;
    s21::Controller* controller_ = nullptr;
    
    GLuint vao_ = 0;
    GLuint vertex_buffer_ = 0;
    GLuint element_buffer_;
    GLuint program_ = 0;
    GLuint mvp_location_ = 0;

    s21::Data* data_ = nullptr;


	void InitArea() {
	  area_ = gtk_gl_area_new();
	  gtk_widget_set_hexpand(area_, true);
	  gtk_widget_set_vexpand(area_, true);
	  gtk_frame_set_child(GTK_FRAME(GetFrame()), area_);
	  g_signal_connect(area_, "realize", G_CALLBACK(Realize), this);
	  g_signal_connect(area_, "render", G_CALLBACK(Render), this);
	  g_signal_connect(area_, "unrealize", G_CALLBACK(Unrealize), this);
	}

	void SetAreaColor() {
	  GdkRGBA color = *(data_->GetAreaColor());
	  //g_print("\nColor = %f, %f, %f\n", color.red, color.blue, color.green);
	  glClearColor(color.red, color.green, color.blue, color.alpha + 1);
	  glEnable(GL_DEPTH_TEST);
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

  void InitBuffer() {
   /* 
    std::vector<float> v {-0.5, 0.0, 0.0,  0.0, 0.5, 0.0,  0.5, 0.0, 0.0,
                          -0.5, 0.0, 0.0,  0.5, -0.0, 0.0, 0.0, 0.0, 0.5,
                          -0.5, 0.0, 0.0,  0.0, 0.5, 0.0, 0.0, 0.0, 0.5};
    */
    std::vector<float> v  = controller_->GetVertex();
		v.shrink_to_fit();
    g_print("\nvertexes:\n");
    for(size_t i = 0; i < v.size(); ++i) {
      g_print("%f\n", v[i]);
    }

    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    glGenBuffers(1, &vertex_buffer_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*v.size(), v.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    size_t element_length = 0;
		for (size_t i = 0; i < controller_->GetSurfacesCount(); ++i) {
		  element_length += controller_->GetSurfaces(i).size();
		}
    glGenBuffers(1, &element_buffer_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*element_length, 0, GL_STATIC_DRAW);
		size_t offset = 0;
    for (size_t i = 0; i < controller_->GetSurfacesCount(); ++i) {
      std::vector<unsigned int> f = controller_->GetSurfaces(i);
			//size_t offset = 0;
			offset += (i)?(controller_->GetSurfaces(i-1).size()):(0);
      glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*offset, sizeof(unsigned int)*f.size(), f.data());
    }
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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

    mvp_location_ = glGetUniformLocation(program_, "mvp");

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

  void ComputeMVP(float* mvp) {
    size_t matrix_size = 9;
    std::vector<float> matrix(matrix_size);
    InitIdentity(matrix);
    Scaling(matrix);
    Rotation(matrix);
    Translation(matrix);
    InitializeMVP(mvp, matrix);
  }

  void InitIdentity(std::vector<float>& matrix) {
    size_t size = 9;
    if (matrix.size() == size) {
      matrix[0] = 1;
      matrix[1] = 0;
      matrix[2] = 0;
      matrix[3] = 0;
      matrix[4] = 1;
      matrix[5] = 0;
      matrix[6] = 0;
      matrix[7] = 0;
      matrix[8] = 1;
    }
  }

  void Scaling(std::vector<float>& matrix) {
    float* scaling_vector = data_->GetScaling();
    controller_->Scaling(matrix, scaling_vector[0], scaling_vector[1], scaling_vector[2]);
  }

  void Rotation(std::vector<float>& matrix) {
    float* rotation_vector = data_->GetRotation();
    controller_->Rotation(matrix, rotation_vector[0], rotation_vector[1], rotation_vector[2]);
  }

  void Translation(std::vector<float>& matrix) {
   // float* translation_vector = data_->GetTranslation();
   // controller_->Translation(matrix, translation_vector[0], translation_vector[1], translation_vector[2]);
  }

  void InitializeMVP(float* mvp, std::vector<float>& matrix) {
    mvp[0] = matrix[0];
    mvp[1] = matrix[1];
    mvp[2] = matrix[2];
    mvp[3] = 0;
    mvp[4] = matrix[3];
    mvp[5] = matrix[4];
    mvp[6] = matrix[5];
    mvp[7] = 0;
    mvp[8] = matrix[6];
    mvp[9] = matrix[7];
    mvp[10] = matrix[8];
    mvp[11] = 0;
    mvp[12] = data_->GetTranslation()[0];//
    mvp[13] = data_->GetTranslation()[1];//
    mvp[14] = data_->GetTranslation()[2];//
    mvp[15] = 1;
  }

};
}


#endif
