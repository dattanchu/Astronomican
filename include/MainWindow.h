#ifndef ASTRONOMICAN_MAIN_WINDOW_H_
#define ASTRONOMICAN_MAIN_WINDOW_H_

#include <QMainWindow>
#include <QDesktopWidget>
#include <QUrl>
#include <cv.h>
#include <string>
#include <QObject>
#include <QStackedWidget>
#include <QSettings>
#include <QComboBox>
#include <QtGui>
#include <QString>
#include <QSize>

#include <QtDeclarative/QDeclarativeView>
#include <QtScript/QScriptEngine>

#include "MovableUnit.h"
#include "ViewManager.h"
#include "ui_MainWindow.h"
#include "SceneManager.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow();
  ~MainWindow();
  cv::Mat TakeScreenshot();
  void SetUpSceneView(SceneManager* scene);
  void readSettings();
  void writeSettings();
  QSize GetUISize();
protected:
  void closeEvent(QCloseEvent *event);
  void keyPressEvent(QKeyEvent *);

public slots:
//  void SetTileSize(int new_size);
//  void ShowTheBoard();
//  void CleanBackGround();
  void UiSizeChanged();
//  void DrawCircle(MovableUnit unit);
//  void ClearColorBuffer(QColor color);
//  void repaintGamePage();
  void Toggle();
  void SwitchToGamePage();
  void RepaintGamePage(QColor color);

signals:
  void ViewColorCleared(QColor);
  void NewScreenShot(cv::Mat* screen);
  void Detect();
  void Calibrate();
  void DiceRegisterSetup();
  void DiceRegisterMain();
  void sizeChanged(int new_width, int new_height);
  void tileSizeChanged(int new_size);
  void takePicture();
  void Quit();

private:
//  QSettings *settings_;
  QDeclarativeView *qml_Page_;
  Ui::MainWindow ui;
  ViewManager *game_page_;
};


#endif
