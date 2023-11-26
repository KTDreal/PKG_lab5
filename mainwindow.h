
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <fstream>
#include <QMainWindow>
#include <QPainter>
#include <QPen>
#include <QFileDialog>
#include <QTextStream>
#include <QVector2D>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_zoomIn_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    QPixmap *pix;
    void paintEvent(QPaintEvent *);
    void updatePicture();
    QVector<double> DrawLiangaBarski(QLine line);
    QVector<double> DrawCyrusBeck(QLine line);
    QPoint getNormal(QPoint p1, QPoint p2, QPoint q);
    int Xmin = 0, Ymin = 0, Xmax = 0, Ymax = 0;
    QVector <QPoint> polygon;
    int range = 15;
    double step = 0.9/(2 * range);
    double delta;
    int n = 0;
    int k = 0;
    bool polygonChosen = false;
    QVector<QLine> lines;
    QRect *rect;
    std::pair<double, double> getXY(double x, double y);
};

#endif // MAINWINDOW_H
