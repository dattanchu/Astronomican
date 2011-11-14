#include "DiceSet.h"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/imgproc/imgproc.hpp"

DiceSet::DiceSet() : QObject(){
  faces_ = 6;
}

DiceSet::~DiceSet() {

}
void DiceSet::TestTemplateMatching() {
  cv::Mat img;
  cv::Mat templ;
  cv::Mat output, result;

  templ = cv::imread("test_template.PNG", 1);
  img = cv::imread("matching_src.PNG", 1);

//  cv::imwrite("templ.PNG", templ);
//  cv::imwrite("img.PNG", img);

//  int iwidth = img.cols - templ.cols + 1;
//  int iheight = img.rows - templ.rows + 1;
//  result.create( cvSize( iwidth, iheight ), CV_32FC1 );

  cv::Point matchLoc;
  double matchVal;
  int match_method = CV_TM_CCORR_NORMED;

  output = img.clone();
//  cv::matchTemplate(img, templ, result, match_method);
//  normalize( result, result, 0, 1, cv::NORM_MINMAX, -1, cv::Mat() );

  result = DiceSet::TemplateMatching(img,
                                     templ,
                                     matchLoc,
                                     matchVal,
                                     match_method);

//  double minVal; double maxVal; cv::Point minLoc; cv::Point maxLoc;
//  cv::minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat() );

//  if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )
//  {
//    matchLoc = minLoc;
//    matchVal = minVal;
//  }
//  else
//  {
//    matchLoc = maxLoc;
//    matchVal = maxVal;
//  }

  cv::rectangle(output, matchLoc,
                cv::Point(matchLoc.x + templ.cols,
                          matchLoc.y + templ.rows),
                cv::Scalar::all(0),
                2, 8, 0
                );
  cv::rectangle(result, matchLoc,
                cv::Point(matchLoc.x + templ.cols,
                          matchLoc.y + templ.rows),
                cv::Scalar::all(0),
                2, 8, 0
                );
  cv::imwrite("test_matching_result.png", output);
  cv::imwrite("test_matching_result1.png", result);
}

void DiceSet::loadTemplate() {
  QString filename = name_ + ".PNG";
  templs_  = cv::imread(filename.toStdString()).clone();
  if(templs_.data == NULL)
    qDebug() << "dice set loading templates failed";
}

void DiceSet::SaveTemplate() {
  QString filename = name_ + ".PNG";
  cv::imwrite(filename.toStdString(), templs_);
}

int DiceSet::Detect(const cv::Mat &ROI)
{
  if(templs_.data == NULL)
    loadTemplate();

  cv::Point matchLoc, currLoc;
  double matchVal, currVal;
  int ret;

  cv::Mat templ = templs_(cv::Range::all(),
                           cv::Range(0,
                                     template_size.height()
                                     ));
  TemplateMatching(ROI, templ, currLoc, currVal, 1);
  matchVal = currVal;
  matchLoc = currLoc;
  ret = 0;

  for (int i = 1; i < 6; i++)
  {
    templ = templs_(cv::Range::all(),
                             cv::Range(template_size.height()*i,
                                       template_size.height()*(i+1)
                                       ));
    TemplateMatching(ROI, templ, currLoc, currVal, 1);
    if(matchVal < currVal) {
      matchVal = currVal;
      matchLoc = currLoc;
      ret = i;
    }
  }

  if(currVal < 0.5)
    return -1;
  else
    return ret;
}

void DiceSet::RegisterTempls(QString name, std::vector<cv::Mat> templs)
{
  name_ = name;
  cv::Size sz =  templs.front().size();
  template_size = QSize(sz.width, sz.height);
  cv::Mat temp;
  temp.create(0, template_size.width(), templs.front().type());
  foreach( cv::Mat templ, templs )
  {
    temp.push_back(templ);
  }
  templs_ = temp.clone();
}

cv::Mat DiceSet::TemplateMatching(const cv::Mat &src,
                                  const cv::Mat &templ,
                                  cv::Point &matchLoc,
                                  double &matchVal,
                                  int match_method = 1)
{
  cv::Mat result;
//  cv::imwrite("blah.png", templ);
//  cv::imwrite("blah2.png", src);
  int result_cols = src.cols - templ.cols + 1;
  int result_rows = src.rows - templ.rows + 1;

  result.create( cv::Size( result_cols, result_rows ), CV_32FC1 );

  /// Do matching and normalize
  cv::matchTemplate(src, templ, result, match_method);
  cv::normalize( result, result, 1.0, 0.0, cv::NORM_MINMAX );

  /// Localizing the best match with minMaxLoc
  double minVal; double maxVal; cv::Point minLoc; cv::Point maxLoc;

  cv::minMaxLoc( result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat() );

  /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values.
  /// For all the other methods, the higher the better

  if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )
  {
    matchLoc = minLoc;
    matchVal = minVal;
  }
  else
  {
    matchLoc = maxLoc;
    matchVal = maxVal;
  }
  return result.clone();
}
