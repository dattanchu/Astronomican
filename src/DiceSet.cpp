#include "DiceSet.h"

DiceSet::DiceSet() : QObject(){

}

DiceSet::~DiceSet() {

}

void DiceSet::loadTemplate() {

}

void DiceSet::SaveTemplate() {
  QString filename = name_ + ".PNG";
  cv::imwrite(filename.toStdString(), templs_);
}

int DiceSet::Detect(const cv::Mat &ROI)
{
  return 0;
}

void DiceSet::RegisterTempls(QString name, vector<cv::Mat> templs)
{
  name_ = name;
  cv::Mat temp;
  temp.create(0, templs.front().size().width, templs.front().type());
  foreach( cv::Mat templ, templs )
  {
    temp.push_back(templ);
  }
  templs_ = temp.clone();
}
