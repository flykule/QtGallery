#include "picturewidget.h"
#include "picturemodel.h"
#include "ui_picturewidget.h"
#include <thumbnailproxymodel.h>

PictureWidget::PictureWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::PictureWidget), mModel(nullptr),
      mSelectionModel(nullptr) {
  ui->setupUi(this);
  connect(ui->backButton, &QPushButton::clicked, this,
          &PictureWidget::backToGallery);
  connect(ui->deleteButton, &QPushButton::clicked, this,
          &PictureWidget::deletePicture);

  connect(ui->previousButton, &QPushButton::clicked, [this] {
    QModelIndex current = mSelectionModel->currentIndex();
    QModelIndex previous =
        mSelectionModel->model()->index(current.row() - 1, 0);
    mSelectionModel->setCurrentIndex(previous,
                                     QItemSelectionModel::SelectCurrent);
  });

  connect(ui->nextButton, &QPushButton::clicked, [this] {
    QModelIndex current = mSelectionModel->currentIndex();
    QModelIndex next = mSelectionModel->model()->index(current.row() + 1, 0);
    mSelectionModel->setCurrentIndex(next, QItemSelectionModel::SelectCurrent);
  });
}

PictureWidget::~PictureWidget() { delete ui; }

void PictureWidget::setModel(ThumbnailProxyModel *model) { mModel = model; }

void PictureWidget::setSelectionModel(QItemSelectionModel *selectionModel) {
  mSelectionModel = selectionModel;
  if (!mSelectionModel)
    return;
  connect(mSelectionModel, &QItemSelectionModel::selectionChanged, this,
          &PictureWidget::loadPicture);
}

void PictureWidget::resizeEvent(QResizeEvent *event) {
  QWidget::resizeEvent(event);
  updatePicturePixmap();
}

void PictureWidget::deletePicture() {
  // Remove the current picture
  int row = mSelectionModel->currentIndex().row();
  mModel->removeRow(mSelectionModel->currentIndex().row());

  // Try to select the previous picture
  QModelIndex previousModelIndex = mModel->index(row - 1, 0);
  if (previousModelIndex.isValid()) {
    mSelectionModel->setCurrentIndex(previousModelIndex,
                                     QItemSelectionModel::SelectCurrent);
    return;
  }

  // Try to select the next picture
  QModelIndex nextModelIndex = mModel->index(row + 1, 0);
  if (nextModelIndex.isValid()) {
    mSelectionModel->setCurrentIndex(nextModelIndex,
                                     QItemSelectionModel::SelectCurrent);
    return;
  }

  emit backToGallery();
}

void PictureWidget::loadPicture(const QItemSelection &selected) {
  QModelIndexList localIndexes = selected.indexes();
  if (localIndexes.empty()) {
    ui->nameLabel->setText("");
    ui->pictureLabel->setPixmap(QPixmap());
    ui->deleteButton->setEnabled(false);
    return;
  }
  const QModelIndex current = localIndexes.at(0);
  QString path =
      mModel->data(current, PictureModel::PictureRole::FilePathRole).toString();
  mPixmap = QPixmap(path);
  ui->nameLabel->setText(path);
  updatePicturePixmap();

  ui->previousButton->setEnabled(current.row() > 0);
  ui->nextButton->setEnabled(current.row() < (mModel->rowCount() - 1));
  ui->deleteButton->setEnabled(true);
}

void PictureWidget::updatePicturePixmap() {
  if (mPixmap.isNull()) {
    return;
  }
  ui->pictureLabel->setPixmap(
      mPixmap.scaled(ui->pictureLabel->size(), Qt::KeepAspectRatio));
}
