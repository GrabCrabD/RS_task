#include <QApplication>

#include "todoapp.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  toDoApp w;
  w.show();
  return a.exec();
}
