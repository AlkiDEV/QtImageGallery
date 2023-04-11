#include "gallery.h"
#include "ui_gallery.h"
#include "scenemanager.h"

#include <QFileDialog>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QDropEvent>
#include <QMimeData>

Gallery::Gallery(SceneManager& manager, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Gallery)
    , sceneManager(manager)
{
    ui->setupUi(this);

    setWindowTitle(defaultWindowTitle);
    ui->imageView->setScene(sceneManager.scene());

    connect(ui->exit, &QPushButton::clicked, this, &Gallery::onExitClicked);
    connect(ui->next, &QPushButton::clicked, this, &Gallery::onNextButtonClicked);
    connect(ui->previous, &QPushButton::clicked, this, &Gallery::onPreviousButtonClicked);
    connect(&sceneManager, &SceneManager::imageChanged, this, &Gallery::onImageChanged);
    connect(ui->open, &QPushButton::clicked, this, &Gallery::onOpenButtonClicked);

}

Gallery::~Gallery()
{
    delete ui;
}


void Gallery::onExitClicked()
{
    this->close();
}

void Gallery::openImage(const QString &fullpath){
    if(sceneManager.isFileSupported(fullpath)){
        sceneManager.openImage(fullpath);
        fitInView();
    }
    updateButtons();
}

void Gallery::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
        case Qt::Key_Left:
            previousImage();
            break;
        case Qt::Key_Right:
            nextImage();
            break;
        case Qt::Key_O:
            if(event->modifiers() & Qt::ControlModifier)
                showOpenDialog();
            break;
        default:
            QWidget::keyPressEvent(event);
    }
}

void Gallery::wheelEvent(QWheelEvent *event){
    if(event->angleDelta().y() > 0) zoomIn();
    else zoomOut();
}

void Gallery::mouseDoubleClickEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton)
        fitInView();
    QWidget::mouseDoubleClickEvent(event);
}

void Gallery::dragEnterEvent(QDragEnterEvent *event){
    auto mimeData = event->mimeData();
    if(mimeData->hasUrls()){
        auto urls = mimeData->urls();
        if(sceneManager.isFileSupported(urls[0].toLocalFile())){
            event->acceptProposedAction();
        }
    }
}

void Gallery::dropEvent(QDropEvent *event){
    auto urls = event->mimeData()->urls();
    if(urls.size()){
        openImage(urls[0].toLocalFile());
    }
}

void Gallery::onNextButtonClicked(){
    nextImage();
}

void Gallery::onPreviousButtonClicked(){
    previousImage();
}

void Gallery::onOpenButtonClicked(){
    Gallery::showOpenDialog();
}

void Gallery::onImageChanged(const QString &fileName){
    setWindowTitle(QString("%0 - \"%1\"").arg(defaultWindowTitle).arg(fileName));
}

void Gallery::previousImage(){
    if(sceneManager.hasPrevious()){
        sceneManager.previousImage();
        fitInView();
    }
    updateButtons();
}

void Gallery::nextImage(){
    if(sceneManager.hasNext()){
        sceneManager.nextImage();
        fitInView();
    }
    updateButtons();
}

void Gallery::fitInView(){
    sceneManager.fitInView();
}

void Gallery::zoomIn(){
    ui->imageView->scale(1.1, 1.1);
}

void Gallery::zoomOut(){
    ui->imageView->scale(0.9, 0.9);
}

void Gallery::showOpenDialog(){
    QString imageExtensions = QString("Images(%0)").arg(sceneManager.suppoetedExtensions().join(" "));

    QString path = QFileDialog::getOpenFileName(this, "Open image", "", imageExtensions);
    if(path.size())
        openImage(path);

}

void Gallery::updateButtons(){
    ui->previous->setEnabled(sceneManager.hasPrevious());
    ui->next->setEnabled(sceneManager.hasNext());
}




