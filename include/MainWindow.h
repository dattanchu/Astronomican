#ifndef ASTRONOMICAN_MAIN_WINDOW_H_
#define ASTRONOMICAN_MAIN_WINDOW_H_

#include <QMainWindow>
#include <QDesktopWidget>
#include <QUrl>
#include <cv.h>
#include <string>
#include <QObject>
#include <QStackedWidget>

#include <QtDeclarative/QDeclarativeView>
#include <QtScript/QScriptEngine>

#include "MovableUnit.h"
#include "ViewManager.h"
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow();
  ~MainWindow();
  cv::Mat TakeScreenshot();
public slots:
//  void SetTileSize(int new_size);
//  void ShowTheBoard();
//  void CleanBackGround();
  void UiSizeChanged();
//  void DrawCircle(MovableUnit unit);
//  void ClearColorBuffer(QColor color);
  void Toggle();

signals:
  void NewScreenShot(cv::Mat* screen);
  void detect();
  void calibrate();
  void sizeChanged(int new_width, int new_height);
  void tileSizeChanged(int new_size);

private:
  QDeclarativeView *qml_page;
  Ui::MainWindow ui;
  ViewManager *game_page;
};


#endif
