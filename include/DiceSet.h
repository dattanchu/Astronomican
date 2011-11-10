#ifndef DICE_SET_H_
#define DICE_SET_H_
#include <QObject>
#include <opencv/cv.h>
#include <opencv2/highgui/highgui.hpp>
#include <vector>
#include <QString>

class DiceSet : QObject{
  Q_OBJECT

public:
  DiceSet();
  ~DiceSet();

  virtual void loadTemplate();
  virtual void SaveTemplate();
  int Detect(const cv::Mat& ROI);
  void RegisterTempls(QString name, vector<cv::Mat> templs);

private:
  cv::Mat templs_;
  QString name_;
};

#endif
