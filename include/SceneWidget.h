#ifndef SCENE_WIDGET_H_
#define SCENE_WIDGET_H_

#include <QGLWidget>
#include <QWidget>
#include <QObject>
#include <QtGui/QGraphicsView>

class SceneWidget : public QGraphicsView
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

signals:
//  void calibrate();
//  void detect();
//  void sizeChanged(int, int);

public slots:
//  void timeOutSlot();

private:
  QTimer *m_timer;
};

#endif
