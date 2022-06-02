#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort>
#include "QMessageBox"

enum SERIALSTATE { PRTCL_STATE_IDLE,
                   PRTCL_STATE_FREE,
                   PRTCL_STATE_1,
                   PRTCL_STATE_2,
                   PRTCL_STATE_3,
                   PRTCL_STATE_4,
                   PRTCL_STATE_IMAGESIZE_WAIT_WIDTH_MSB,
                   PRTCL_STATE_IMAGESIZE_WAIT_WIDTH_LSB,
                   PRTCL_STATE_IMAGESIZE_WAIT_HEIGHT_MSB,
                   PRTCL_STATE_IMAGESIZE_WAIT_HEIGHT_LSB,
                   PRTCL_STATE_WAIT_PIXELFORMAT_LEN,
                   PRTCL_STATE_WAIT_PIXELFORMAT,
                   PRTCL_STATE_WAIT_IMAGELEN,
                   PRTCL_STATE_WAIT_IMAGE_DATA,
                   PRTCL_STATE_IMAGE_RECEIVED
                 };

enum COMMANDSTATE { COMMANDSTATE_IDLE,
                    COMMANDSTATE_RUNNING,
                    COMMANDSTATE_FAILED,
                    COMMANDSTATE_PASSED
                  };

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QSerialPort serialPort;

signals:
    void commandStateChanged();
    void imageReceived();

private slots:
    void on_button_connect_clicked();

    void on_button_refreshPorts_clicked();
    void clearResults(void);
    void showPortInfo(int idx);
    void getImage(QByteArray data);
    void readSerialData();
    void processSerialData(QByteArray data);

    void on_button_testImage_clicked();

    void on_button_disconnect_clicked();

private:
    Ui::MainWindow *ui;

    SERIALSTATE serialState = PRTCL_STATE_FREE;
    COMMANDSTATE commandState = COMMANDSTATE_IDLE;
    QByteArray serialData;
    bool receiveImage = false;

    void fillPortsParameters();
    void fillPortsInfo();

    unsigned char imageheight_msb;
    unsigned char imageheight_lsb;
    unsigned char imagewidth_msb;
    unsigned char imagewidth_lsb;
    QString  imageformat;
    unsigned char imageformat_len_cnt;
    unsigned char imageformat_len;
    unsigned char imagelength_bytes[4];
    unsigned char imagelength_cnt;
    unsigned int  imagelength;
    unsigned int  imagedata_cnt;
    QByteArray    imagedata;
    unsigned short imagewidth, imageheight;

};
#endif // MAINWINDOW_H
