#include "mainwindow.h"
#include "ui_mainwindow.h"//the widgets created in Qt Designer

#include <QBrush>//fill colors of shapes
#include <QPen> //border wire color
#include <QGraphicsTextItem> //text on the graphics scene
#include <QThread> // used here for msleep
#include <QCoreApplication> // lets GUI refresh with processEvents()
#include <QDir> // folder handling
#include <QFile> // file writing
#include <QTextStream> //writing text into file
#include <QInputDialog> //popup asking user for a pin number

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
    , ui(new Ui::MainWindow)//Creates the UI object.
    , compilerProcess(new QProcess(this)) //Creates a process object that will later run arduino-cli.
{
    ui->setupUi(this);

    ui->btnRun->setEnabled(false);
    ui->txtDebug->setText("Debug messages...");
    ui->txtOutput->setText("Compilation output...");

    setupSimulator();
    addDefaultComponents();
}

//when window close (cleaning)
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupSimulator()
{
    scene = new QGraphicsScene(this);//creates a drawing area called scene
    ui->graphicsView->setScene(scene);//put inside graphics view
    scene->setSceneRect(0, 0, 500, 300);//sets the size of the drawing space

    arduinoBoard = scene->addRect(40, 90, 220, 120, QPen(Qt::white)); //a rectangle for the Arduino board
    arduinoBoard->setBrush(QBrush(Qt::darkBlue));
    scene->addText("Arduino UNO")->setPos(105, 140);



    // simple pin labels
    for (int pin : {13, 12, 11, 2}) {
        scene->addText(QString("D%1").arg(pin))->setPos(pinX(pin) - 8, 70);
        scene->addLine(pinX(pin), 90, pinX(pin), 82, QPen(Qt::yellow));
    }

    // resistor visual only
    QGraphicsRectItem *resistor = scene->addRect(320, 70, 50, 12, QPen(Qt::white));
    resistor->setBrush(QBrush(QColor(120, 80, 40)));
    scene->addText("Resistor")->setPos(315, 45);
}

void MainWindow::addDefaultComponents()
{
    // LED on pin 13
    LedComponent led13;
    led13.pin = 13;
    led13.item = scene->addEllipse(380, 95, 28, 28, QPen(Qt::white));
    led13.item->setBrush(QBrush(Qt::red));
    scene->addText("LED 13")->setPos(372, 126);
    led13.wire = scene->addLine(pinX(13), 82, 394, 95, QPen(Qt::green, 2));
    leds.append(led13);

    // Button on pin 2
    ButtonComponent btn2;
    btn2.pin = 2;
    btn2.pressed = false;
    btn2.item = scene->addRect(380, 185, 38, 24, QPen(Qt::white));
    btn2.item->setBrush(QBrush(Qt::gray));
    scene->addText("BTN 2")->setPos(372, 214);
    btn2.wire = scene->addLine(pinX(2), 82, 399, 185, QPen(Qt::cyan, 2));
    buttons.append(btn2);
}

//This converts a pin number into an x-position on the board drawing.
int MainWindow::pinX(int pin) const
{
    switch (pin) {
    case 13: return 90;
    case 12: return 120;
    case 11: return 150;
    case 2:  return 240;
    default: return 90;
    }
}

void MainWindow::resetLeds()
{
    for (auto &ledComp : leds) {
        ledComp.item->setBrush(QBrush(Qt::red));
    }
}

int MainWindow::extractDelay(const QString &code) const
{
    int start = code.indexOf("delay(");
    if (start == -1)
        return 500;

    start += 6;
    int end = code.indexOf(")", start);
    if (end == -1)
        return 500;

    bool ok = false;
    int value = code.mid(start, end - start).trimmed().toInt(&ok);
    return ok ? value : 500;
}

bool MainWindow::prepareSketchFile(const QString &code)
{
    QDir dir(QDir::tempPath());
    sketchFolderPath = dir.filePath("qt_arduino_sim_sketch");
    sketchFilePath = QDir(sketchFolderPath).filePath("qt_arduino_sim_sketch.ino");

    if (!dir.mkpath(sketchFolderPath)) {
        ui->txtDebug->append("Failed to create temp sketch folder.");
        return false;
    }

    QFile file(sketchFilePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        ui->txtDebug->append("Failed to write temporary sketch file.");
        return false;
    }

    QTextStream out(&file);
    out << code;
    file.close();

    ui->txtDebug->append("Temporary sketch file created:");
    ui->txtDebug->append(sketchFilePath);
    return true;
}

void MainWindow::compileSketch()
{
    ui->txtDebug->append("Starting external compilation...");
    ui->txtOutput->clear();

    QString program = "C:/Users/abdul/Desktop/CLI/arduino-cli.exe";
    QStringList args;
    args << "compile"
         << "--fqbn" << "arduino:avr:uno"
         << sketchFolderPath;

    compilerProcess->start(program, args);

    if (!compilerProcess->waitForStarted()) {
        ui->txtOutput->setText("Could not start arduino-cli. Make sure it is installed and in PATH.");
        ui->txtDebug->append("arduino-cli failed to start.");
        buildSuccess = false;
        ui->btnRun->setEnabled(false);
        return;
    }

    compilerProcess->waitForFinished(-1);

    QString stdOut = compilerProcess->readAllStandardOutput();
    QString stdErr = compilerProcess->readAllStandardError();
    ui->txtOutput->setText(stdOut + "\n" + stdErr);

    if (compilerProcess->exitCode() == 0) {
        ui->txtDebug->append("External compilation finished successfully.");
        buildSuccess = true;
        ui->btnRun->setEnabled(true);
    } else {
        ui->txtDebug->append("External compilation failed.");
        buildSuccess = false;
        ui->btnRun->setEnabled(false);
    }
}

void MainWindow::on_btnBuild_clicked()
{
    QString code = ui->txtEditor->toPlainText();
    ui->txtDebug->append("Build button clicked.");

    if (code.trimmed().isEmpty()) {
        ui->txtOutput->setText("Build failed: No Arduino code entered.");
        ui->txtDebug->append("No code found in editor.");
        ui->btnRun->setEnabled(false);
        buildSuccess = false;
        return;
    }

    if (!prepareSketchFile(code)) {
        ui->txtOutput->setText("Build failed: Could not prepare sketch file.");
        ui->btnRun->setEnabled(false);
        buildSuccess = false;
        return;
    }

    compileSketch();
}

void MainWindow::runSimpleSimulation(const QString &code)
{
    resetLeds();

    if (code.contains("pinMode(13, OUTPUT)")) {
        ui->txtDebug->append("Pin 13 configured as OUTPUT.");
    }
    if (code.contains("pinMode(2, INPUT)") || code.contains("pinMode(2, INPUT_PULLUP)")) {
        ui->txtDebug->append("Pin 2 configured as INPUT.");
    }

    const bool blink13 =
        code.contains("digitalWrite(13, HIGH)") &&
        code.contains("digitalWrite(13, LOW)") &&
        code.contains("delay");

    if (blink13) {
        int delayMs = extractDelay(code);
        ui->txtDebug->append(QString("Blink detected on pin 13. Delay = %1 ms").arg(delayMs));

        for (int i = 0; i < 8; ++i) {
            leds[0].item->setBrush(QBrush(Qt::green));
            QCoreApplication::processEvents();
            QThread::msleep(delayMs);

            leds[0].item->setBrush(QBrush(Qt::red));
            QCoreApplication::processEvents();
            QThread::msleep(delayMs);
        }
        return;
    }

    if (code.contains("digitalWrite(13, HIGH)")) {
        leds[0].item->setBrush(QBrush(Qt::green));
        ui->txtDebug->append("LED on pin 13 is ON.");
    } else if (code.contains("digitalWrite(13, LOW)")) {
        leds[0].item->setBrush(QBrush(Qt::red));
        ui->txtDebug->append("LED on pin 13 is OFF.");
    } else {
        ui->txtDebug->append("No supported LED command found.");
    }

    if (code.contains("digitalRead(2)")) {
        ui->txtDebug->append("Button read on pin 2 detected in code.");
    }
}

void MainWindow::on_btnRun_clicked()
{
    if (!buildSuccess) {
        ui->txtDebug->append("Run blocked: build was not successful.");
        return;
    }

    ui->txtDebug->append("Simulation started.");
    QString code = ui->txtEditor->toPlainText();
    runSimpleSimulation(code);
}

void MainWindow::on_btnAddLed_clicked()
{
    bool ok;
    int pin = QInputDialog::getInt(this, "Pin", "Enter pin number:", 13, 0, 13, 1, &ok);
    if (!ok) return;

    LedComponent ledComp;
    ledComp.pin = pin;

    int x = 350 + leds.size() * 40;
    ledComp.item = scene->addEllipse(x, 120, 25, 25, QPen(Qt::white));
    ledComp.item->setBrush(Qt::red);

    ledComp.wire = scene->addLine(pinX(pin), 82, x + 12, 120, QPen(Qt::green, 2));

    leds.append(ledComp);

    ui->txtDebug->append("LED added on pin " + QString::number(pin));
}

void MainWindow::on_btnAddButton_clicked()
{
    bool ok;
    int pin = QInputDialog::getInt(this, "Pin", "Enter button pin number:", 2, 0, 13, 1, &ok);
    if (!ok)
        return;

    ButtonComponent buttonComp;
    buttonComp.pin = pin;
    buttonComp.pressed = false;

    int x = 350 + buttons.size() * 45;
    int y = 180;

    buttonComp.item = scene->addRect(x, y, 35, 22, QPen(Qt::white));
    buttonComp.item->setBrush(Qt::gray);

    buttonComp.wire = scene->addLine(pinX(pin), 82, x + 17, y, QPen(Qt::cyan, 2));

    buttons.append(buttonComp);

    scene->addText(QString("BTN %1").arg(pin))->setPos(x - 5, y + 28);

    ui->txtDebug->append("Button added on pin " + QString::number(pin));
}



void MainWindow::on_btnRemoveLast_clicked()
{
    if (!leds.isEmpty()) {
        auto ledComp = leds.takeLast();
        scene->removeItem(ledComp.item);
        scene->removeItem(ledComp.wire);
        delete ledComp.item;
        delete ledComp.wire;
        ui->txtDebug->append("Last LED removed.");
        return;
    }

    if (!buttons.isEmpty()) {
        auto buttonComp = buttons.takeLast();
        scene->removeItem(buttonComp.item);
        scene->removeItem(buttonComp.wire);
        delete buttonComp.item;
        delete buttonComp.wire;
        ui->txtDebug->append("Last button removed.");
        return;
    }

    ui->txtDebug->append("No component to remove.");
}
/***/