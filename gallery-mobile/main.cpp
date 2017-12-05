#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickView>

#include "albummodel.h"
#include "pictureimageprovider.h"
#include "picturemodel.h"

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QGuiApplication app(argc, argv);

  AlbumModel albumModel;
  PictureModel pictureModel(albumModel);

  QQmlApplicationEngine engine;
  QQmlContext *context = engine.rootContext();
  context->setContextProperty("albumModel", &albumModel);
  context->setContextProperty("pictureModel", &pictureModel);
  context->setContextProperty("thumbnailSize",
                              PictureImageProvider::THUMBNAIL_SIZE.width());

  engine.addImageProvider("pictures", new PictureImageProvider(&pictureModel));
  engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));
  if (engine.rootObjects().isEmpty())
    return -1;

  return app.exec();
}
