#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cmath>
#include "ViewManager.h"

//SceneWidget::SceneWidget() : QGLWidget() {
//}

//void SceneWidget::initializeGL() {
//  glShadeModel(GL_SMOOTH);

//  glClearColor(255.0f, 255.0f, 255.0f, 0.0f);
//  glClearDepth(1.0f);

//  glEnable(GL_DEPTH_TEST);
//  glDepthFunc(GL_LEQUAL);

//  glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
//}

//void SceneWidget::resizeGL(int w, int h) {
//  h = h?h:1;

//  glViewport( 0, 0, (GLint)w, (GLint)h );

//  glMatrixMode(GL_PROJECTION);
//  glLoadIdentity();
//  glOrtho(0, (GLint)w, (GLint)h, 0, 0, 1);
////  GLdouble fovy = 45.0f;
////  GLdouble aspect = (GLfloat)w/(GLfloat)h;
////  GLdouble zNear = 0.1f;
////  GLdouble zFar = 100.0f;
////  GLdouble xmin, xmax, ymin, ymax;

////  ymax = zNear * tan(fovy * M_PI / 360.0);
////  ymin = -ymax;
////  xmin = ymin * aspect;
////  xmax = ymax * aspect;

////  glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);

//  glMatrixMode(GL_MODELVIEW);
//  glLoadIdentity();
//}

//void SceneWidget::paintGL() {
//   glClearColor(255.0f, 255.0f, 255.0f, 0.0f);
//   glClear(GL_COLOR_BUFFER_BIT);
//}

//void SceneWidget::timeOut() {

//}

//void SceneWidget::timeOutSlot() {

//}

//void SceneWidget::keyPressEvent(QKeyEvent *e) {

//}

void ViewManager::paintEvent(QPaintEvent *event) {
  QGraphicsView::paintEvent(event);

  if(captureInProgress_)
  {
    emit(paintEventFinished());
    captureInProgress_ = false;
  }
}

void ViewManager::setCaptureInProgress(bool captureInProgress)
{
  captureInProgress_ = captureInProgress;
}
