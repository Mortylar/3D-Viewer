#include "factory.h"

s21::Widget *s21::TranslationPannelFactory::CreateWidget() {
  s21::DSliderPannel *translation_pannel =
      new s21::DSliderPannel{GetAdjustment(), GetAdjustment(), GetAdjustment()};
  translation_pannel->SetName("Translation_Pannel");
  translation_pannel->SetName(0, "X_AXIS");
  translation_pannel->SetName(1, "Y_AXIS");
  translation_pannel->SetName(2, "Z_AXIS");
  return translation_pannel;
}

s21::Widget *s21::RotationPannelFactory::CreateWidget() {
  s21::DSliderPannel *rotation_pannel =
      new s21::DSliderPannel{GetAdjustment(), GetAdjustment(), GetAdjustment()};
  rotation_pannel->SetName("Rotation_Pannel");
  rotation_pannel->SetName(0, "X_AXIS");
  rotation_pannel->SetName(1, "Y_AXIS");
  rotation_pannel->SetName(2, "Z_AXIS");
  return rotation_pannel;
}

s21::Widget *s21::ScalingPannelFactory::CreateWidget() {
  s21::DSliderPannel *scaling_pannel =
      new s21::DSliderPannel{GetAdjustment(), GetAdjustment(), GetAdjustment()};
  scaling_pannel->SetName("Scaling_Pannel");
  scaling_pannel->SetName(0, "X_AXIS");
  scaling_pannel->SetName(1, "Y_AXIS");
  scaling_pannel->SetName(2, "Z_AXIS");
  return scaling_pannel;
}

s21::Widget *s21::FileNamePannelFactory::CreateWidget() {
  s21::LabelPair *file_name_pair = new s21::LabelPair();
  file_name_pair->SetName("   Source_File   ");
  file_name_pair->SetValue("   No_File   ");
  return file_name_pair;
}

s21::Widget *s21::VertexInfoPannelFactory::CreateWidget() {
  s21::LabelPair *vertex_info_pair = new s21::LabelPair();
  vertex_info_pair->SetName("   Vertex_Count   ");
  vertex_info_pair->SetValue("   0   ");
  return vertex_info_pair;
}

s21::Widget *s21::EdgesInfoPannelFactory::CreateWidget() {
  s21::LabelPair *edge_info_pair = new s21::LabelPair();
  edge_info_pair->SetName("   Edges_Count   ");
  edge_info_pair->SetValue("   0   ");
  return edge_info_pair;
}

s21::Widget *s21::LineTypeFactory::CreateWidget() {
  const char *name = "Line Type";
  const char *types[4] = {"NO_LINE", "SOLID_LINE", "DOTTED_LINE", nullptr};
  s21::LabelDropDownButtonPair *line_type =
      new s21::LabelDropDownButtonPair(name, types);
  return line_type;
}

s21::Widget *s21::LineColorFactory::CreateWidget() {
  const char *name = "Line Color";
  s21::LabelColorButtonPair *color_button = new s21::LabelColorButtonPair(name);
  return color_button;
}

s21::Widget *s21::LineSizeFactory::CreateWidget() {
  const char *name = "Line Width";
  GtkAdjustment *adjustment =
      gtk_adjustment_new(0.0, 0.0, 2048.0, 0.1, 0.0, 0.0);
  s21::LabelDSpinButtonPair *line_size =
      new s21::LabelDSpinButtonPair(name, adjustment);
  return line_size;
}

s21::Widget *s21::PointTypeFactory::CreateWidget() {
  const char *name = "Point Type";
  const char *types[5] = {"NO_POINT", "ROUND_POINT", "TRIANGLE_POINT",
                          "SQUARE_POINT", nullptr};
  s21::LabelDropDownButtonPair *point_type =
      new s21::LabelDropDownButtonPair(name, types);
  return point_type;
}

s21::Widget *s21::PointColorFactory::CreateWidget() {
  const char *name = "Point Color";
  s21::LabelColorButtonPair *color_button = new s21::LabelColorButtonPair(name);
  return color_button;
}

s21::Widget *s21::PointSizeFactory::CreateWidget() {
  const char *name = "Point Size";
  GtkAdjustment *adjustment =
      gtk_adjustment_new(0.0, 0.0, 2048.0, 0.1, 0.0, 0.0);
  s21::LabelDSpinButtonPair *point_size =
      new s21::LabelDSpinButtonPair(name, adjustment);
  return point_size;
}

s21::Widget *s21::CapturePannelFactory::CreateWidget() {
  const char *name = "Capture Pannel";
  const char *extensions[4] = {"PNG", "JPG", "BMP", nullptr};
  s21::FileSaverDropDownButtonPair *capture_pannel =
      new s21::FileSaverDropDownButtonPair(extensions);
  capture_pannel->SetName(name);
  return capture_pannel;
}

s21::Widget *s21::GifPannelFactory::CreateWidget() {
  const char *name = "Gif Pannel";
  GtkAdjustment *adjustment = gtk_adjustment_new(0.0, 0.0, 60.0, 1.0, 0.0, 0.0);
  s21::FileSaverDSpinButtonPair *gif_pannel =
      new s21::FileSaverDSpinButtonPair(adjustment);
  gif_pannel->SetName("Gif Pannel");
  return gif_pannel;
}

s21::Widget *s21::AreaColorFactory::CreateWidget() {
  const char *name = "Area Color";
  s21::LabelColorButtonPair *color_button = new s21::LabelColorButtonPair(name);
  return color_button;
}
