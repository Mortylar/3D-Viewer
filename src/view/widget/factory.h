#ifndef SRC_VIEW_WIDGET_FACTORY_H_
#define SRC_VIEW_WIDGET_FACTORY_H_

#include "pair_widget.h"
#include "pannel.h"
#include "widget.h"

namespace s21 {
class Factory {
 public:
  Factory(){};
  ~Factory(){};
  virtual s21::Widget *CreateWidget() = 0;
};

class TranslationPannelFactory : public Factory {
 public:
  TranslationPannelFactory(){};
  ~TranslationPannelFactory(){};

  s21::Widget *CreateWidget() override;

 private:
  GtkAdjustment *GetAdjustment() {
    return gtk_adjustment_new(0.0, -5.0, 5.0, 0.01, 0, 0);
  }
};

class RotationPannelFactory : public Factory {
 public:
  RotationPannelFactory(){};
  ~RotationPannelFactory(){};

  s21::Widget *CreateWidget() override;

 private:
  GtkAdjustment *GetAdjustment() {
    return gtk_adjustment_new(0.0, -1 * G_PI, 1 * G_PI, 0.05, 0, 0);
  }
};

class ScalingPannelFactory : public Factory {
 public:
  ScalingPannelFactory(){};
  ~ScalingPannelFactory(){};

  s21::Widget *CreateWidget() override;

 private:
  GtkAdjustment *GetAdjustment() {
    return gtk_adjustment_new(0.0, -0.9999999999, 0.999999999999, 0.001, 0, 0);
  }
};

class FileNamePannelFactory : public Factory {
 public:
  FileNamePannelFactory(){};
  ~FileNamePannelFactory(){};

  s21::Widget *CreateWidget() override;
};

class VertexInfoPannelFactory : public Factory {
 public:
  VertexInfoPannelFactory(){};
  ~VertexInfoPannelFactory(){};

  s21::Widget *CreateWidget() override;
};

class EdgesInfoPannelFactory : public Factory {
 public:
  EdgesInfoPannelFactory(){};
  ~EdgesInfoPannelFactory(){};

  s21::Widget *CreateWidget() override;
};

class LineTypeFactory : public Factory {
 public:
  LineTypeFactory(){};
  ~LineTypeFactory(){};

  s21::Widget *CreateWidget() override;
};

class LineColorFactory : public Factory {
 public:
  LineColorFactory(){};
  ~LineColorFactory(){};

  s21::Widget *CreateWidget() override;
};

class LineSizeFactory : public Factory {
 public:
  LineSizeFactory(){};
  ~LineSizeFactory(){};

  s21::Widget *CreateWidget() override;
};

class PointTypeFactory : public Factory {
 public:
  PointTypeFactory(){};
  ~PointTypeFactory(){};

  s21::Widget *CreateWidget() override;
};

class PointColorFactory : public Factory {
 public:
  PointColorFactory(){};
  ~PointColorFactory(){};

  s21::Widget *CreateWidget() override;
};

class PointSizeFactory : public Factory {
 public:
  PointSizeFactory(){};
  ~PointSizeFactory(){};

  s21::Widget *CreateWidget() override;
};

class CapturePannelFactory : public Factory {
 public:
  CapturePannelFactory(){};
  ~CapturePannelFactory(){};

  s21::Widget *CreateWidget() override;
};

class GifPannelFactory : public Factory {
 public:
  GifPannelFactory(){};
  ~GifPannelFactory(){};

  s21::Widget *CreateWidget() override;
};

class AreaColorFactory : public Factory {
 public:
  AreaColorFactory(){};
  ~AreaColorFactory(){};

  s21::Widget *CreateWidget() override;
};

}  // namespace s21

#endif
