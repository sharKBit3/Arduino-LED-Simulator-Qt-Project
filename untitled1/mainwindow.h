#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsRectItem>
#include <QGraphicsLineItem>
#include <QProcess>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

struct LedComponent {
    int pin;
    QGraphicsEllipseItem *item;
    QGraphicsLineItem *wire;
};

struct ButtonComponent {
    int pin;
    bool pressed;
    QGraphicsRectItem *item;
    QGraphicsLineItem *wire;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnBuild_clicked();
    void on_btnRun_clicked();

    void on_btnAddLed_clicked();
    void on_btnAddButton_clicked();
    void on_btnRemoveLast_clicked();

private:
    Ui::MainWindow *ui;
    bool buildSuccess = false;

    QGraphicsScene *scene;
    QGraphicsRectItem *arduinoBoard;
    QProcess *compilerProcess;

    QList<LedComponent> leds;
    QList<ButtonComponent> buttons;

    QString sketchFolderPath;
    QString sketchFilePath;

    void setupSimulator();
    void addDefaultComponents();
    void resetLeds();
    void runSimpleSimulation(const QString &code);
    int extractDelay(const QString &code) const;
    bool prepareSketchFile(const QString &code);
    void compileSketch();
    int pinX(int pin) const;
};

#endif // MAINWINDOW_H