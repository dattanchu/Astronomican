#ifndef DICE_SET_H_
#define DICE_SET_H_
#include <QObject>
#include <cv.h>
#include <QString>
#include <QSize>
#include <QDebug>
#include <vector>

class DiceSet : QObject{
  Q_OBJECT

public:
  DiceSet();
  ~DiceSet();

  virtual void loadTemplate();
  virtual void SaveTemplate();
  virtual int Detect(const cv::Mat& ROI);
  virtual void RegisterTempls(QString name, std::vector<cv::Mat> templs);

  static void TestTemplateMatching();

private:
  cv::Mat templs_;
  QString name_;
  QSize template_size;
  int faces_;

  static cv::Mat TemplateMatching(const cv::Mat &src,
                                  const cv::Mat &templ,
                           cv::Point &matchLoc, double &matchVal,
                           int match_method);

};

#endif
