#pragma once

#ifndef GALLERY_H
#define GALLERY_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class Gallery; }
QT_END_NAMESPACE

class SceneManager;

class Gallery : public QMainWindow
{
    Q_OBJECT

public:
    Gallery(SceneManager& manager, QWidget *parent = nullptr);
    ~Gallery();

    void openImage(const QString& fullpath);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void dragEnterEvent(QDragEnterEvent * event) override;
    void dropEvent(QDropEvent *event) override;

private slots:
    void onExitClicked();

    void onNextButtonClicked();
    void onPreviousButtonClicked();
    void onOpenButtonClicked();

    void onImageChanged(const QString &fileName);

    void previousImage();
    void nextImage();
    void fitInView();
    void zoomIn();
    void zoomOut();

    void showOpenDialog();
    void updateButtons();

private:
    Ui::Gallery *ui;

    SceneManager& sceneManager;

    const QString defaultWindowTitle = "Image Gallery";

};
#endif // GALLERY_H
