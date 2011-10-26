#ifndef ASTRONOMICAN_MAIN_WINDOW_H_
#define ASTRONOMICAN_MAIN_WINDOW_H_

#include <QMainWindow>
#include <QDesktopWidget>
#include <QUrl>
#include <QtDeclarative/QDeclarativeView>
#include <QtScript/QScriptEngine>
#include <cv.h>
#include <string>

#include "MovableUnit.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow();
  ~MainWindow();
public slots:
//  void SetTileSize(int new_size);
  void ShowTheBoard();
  void CleanBackGround();
  void UiSizeChanged();
  void Resize();
  void DrawCircle(MovableUnit unit);

signals:
  void detect();
  void calibrate();
  void sizeChanged(int new_width, int new_height);
  void tileSizeChanged(int new_size);

private:
  QDeclarativeView *ui;
};


#endif
