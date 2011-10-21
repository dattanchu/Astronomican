#ifndef ASTRONOMICAN_MAIN_WINDOW_H_
#define ASTRONOMICAN_MAIN_WINDOW_H_

#include <QMainWindow>
#include <QtDeclarative/QDeclarativeView>
#include <QDesktopWidget>
#include <QUrl>
#include <cv.h>
#include <string>


class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow();
  ~MainWindow();

public slots:
  void SetTileSize(int new_size);
  void ShowTheBoard();
  void CleanBackGround();

signals:
  void sizeChanged(int new_width, int new_height);

private:
  QDeclarativeView *ui;
};


#endif
