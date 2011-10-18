#include "SceneManager.h"
SceneManager::SceneManager(){
  size_ = QSize(-1, -1);
}

void SceneManager::SetSize(const QSize &new_size) {
    size_ = new_size;
}

QSize& SceneManager::GetSize() {
  return size_;
}
