#include "SceneManager.h"
#include "QtCore"

SceneManager::SceneManager(){
  size_ = QSize(800, 600);
  tile_size_ = 100;
}

void SceneManager::SetSize(const QSize &new_size) {
    size_ = new_size;
    qDebug() << "Current size is:" << size_;
}

void SceneManager::SetTileSize(const int new_tile_size) {
  tile_size_ = new_tile_size;
}

QSize& SceneManager::GetSize() {
  return size_;
}

int SceneManager::GetTileSize() {
  return tile_size_;
}
