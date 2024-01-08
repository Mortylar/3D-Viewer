#ifndef SRC_VIEW_WIDGET_GL_AREA_H_
#define SRC_VIEW_WIDGET_GL_AREA_H_

#include <gtk/gtk.h>

#include "widget.h"
#include "opengl_model.h"
#include <epoxy/gl.h>

namespace s21 {
class DrawingArea: public Widget {
  public:
    DrawingArea() {
      InitArea(); 
	}

	~DrawingArea(){};

	void SetMother(s21::Widget* mother) {} //TODO
	void CatchSignal() {} //TODO
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
	  self->RemoveBuffer();
	  self->RemoveShader();
	}

	void DrawFigure() {
	  float mvp[16] = {1, 0, 0, 0,   0,1,0,0,  0,0,1,0, 0,0,0,0};

	  glUseProgram(shader_->GetProgram());
	  g_print("\nmvp = %i\n", shader_->GetMVP());
	  glUniformMatrix4fv(shader_->GetMVP(), 1, GL_FALSE, &mvp[0]);
	  

	  glEnableVertexAttribArray(0);
	  glBindBuffer(GL_ARRAY_BUFFER, buffer_->GetVertexBuffer());
	  glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 0, 0);

	  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_->GetElementBuffer());
      glDrawArrays(GL_LINE_LOOP, 0, 3);
	  //TODO
	  glDisableVertexAttribArray(0);
	  glUseProgram(0);

	}
  private:
    GtkWidget* area_ = nullptr;
	GdkGLContext* context_ = nullptr;
	s21::Buffer* buffer_ = nullptr;
	s21::Shader* shader_ = nullptr;

	void InitArea() {
	  area_ = gtk_gl_area_new();
	  gtk_widget_set_hexpand(area_, true);
	  gtk_widget_set_vexpand(area_, true);
	  gtk_frame_set_child(GTK_FRAME(GetFrame()), area_);
	  g_signal_connect(area_, "realize", G_CALLBACK(Realize), this);
	  g_signal_connect(area_, "render", G_CALLBACK(Render), this);
	  g_signal_connect(area_, "unrealize", G_CALLBACK(Unrealize), this);
	}

    s21::Buffer* AllocateBufferMemory() {return new s21::Buffer();}
	s21::Shader* AllocateShaderMemory() {return new s21::Shader();}
    void RemoveBuffer() {if(buffer_) delete buffer_;}
	void RemoveShader() {if(shader_) delete shader_;}

	void InitBuffer() {
	  buffer_ = AllocateBufferMemory();
	  std::vector<float> v {0.0, 0.0, 0.0,  0.5, 0.5, 0.5,  -0.5, 0.5, 0.0,
                           -0.5, -0.5, 0.0,  0.5, -0.5, 0.0 };
	  std::vector<int> f {1, 2, 3, 1, 4, 5};
	  buffer_->CreateBuffer(v,f);   //TODO
	}

	void InitShader() {
	  shader_ = AllocateShaderMemory();
	  shader_->InitShader();
	}

};
}


#endif
