#ifndef SCENE_WIDGET_H_
#define SCENE_WIDGET_H_

#include <QGLWidget>
#include <QWidget>
#include <QObject>
#include <QtGui/QGraphicsView>

class ViewManager : public QGraphicsView
{
  Q_OBJECT
public:
//  SceneWidget();

protected:
//  void initializeGL();
//  void resizeGL(int w, int h);
//  void paintGL();
//  void timeOut();
//  void keyPressEvent(QKeyEvent *e);
  void paintEvent(QPaintEvent *event);

signals:
//  void calibrate();
//  void detect();
//  void sizeChanged(int, int);
  void paintEventFinished();

public slots:
//  void timeOutSlot();
  void setCaptureInProgress(bool captureInProgress);

private:
//  QTimer *m_timer;
  bool captureInProgress_;
};

#endif
