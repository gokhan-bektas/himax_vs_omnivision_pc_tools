#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtSerialPort"
#include "QImage"
#include "QPainter"
#include "guiworker.h"

static const char blankString[] = QT_TRANSLATE_NOOP("SettingsDialog", "N/A");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("MAX78000 Profiler Tool");

    QPixmap pix("://board_image.png");
    //this->ui->label_image->setPixmap(pix);

    this->fillPortsInfo();

    connect(this->ui->serialPortInfoListBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::showPortInfo);

    connect(&serialPort, SIGNAL(readyRead()), this, SLOT(readSerialData()));

    // set up the thread for our worker and move it to the thread
    auto worker = new GUIWorker();
    auto thread = new QThread();
    worker->moveToThread(thread);

    this->fillPortsInfo();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_button_connect_clicked()
{
    this->serialPort.setBaudRate(921600);

    this->serialPort.setPortName(this->ui->serialPortInfoListBox->currentText());
    if ( this->serialPort.open(QIODevice::ReadWrite) ) {
        qDebug()<<"Serial port opened";

        commandState = COMMANDSTATE_RUNNING;
        QTimer timer;
        timer.setSingleShot(true);
        QEventLoop loop;
        connect(this, &MainWindow::commandStateChanged, &loop, &QEventLoop::quit);
        connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
        timer.start(1000);
/*
        QByteArray txdata = QByteArrayLiteral("#V\x0d\x0a");
        this->serialPort.clear();
        this->serialPort.write(txdata,txdata.length());
        this->serialPort.flush();
        this->serialPort.waitForBytesWritten();

        loop.exec();

        if((timer.isActive() == false) || (commandState != COMMANDSTATE_PASSED)) {
            QMessageBox msgBox;
            msgBox.setWindowTitle("Error");
            msgBox.setIcon(QMessageBox::Critical);
            msgBox.setText("MAX78000FTHR is not responding");
            msgBox.setInformativeText("Please make sure MAX78000FTHR is connected to this port and production test firmware is loaded on MAX78000FTHR");
            msgBox.exec();

            this->serialPort.close();
            this->ui->serialPortInfoListBox->setEnabled(true);
            this->ui->button_connect->setEnabled(true);
            this->ui->button_refreshPorts->setEnabled(true);
            this->ui->button_disconnect->setEnabled(false);
            statusBar()->showMessage(tr(""));
            return;
        }*/
    }
    else {
        qDebug()<<"Port open error";
        this->ui->group_tests->setEnabled(false);

        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setText("Can Not Open Serial Port");
        msgBox.setInformativeText("Please check if the port exists by clicking Refresh button and make sure the port is not already in use");
        msgBox.exec();
        return;
    }

    this->ui->group_tests->setEnabled(true);
    this->ui->serialPortInfoListBox->setEnabled(false);
    this->ui->button_connect->setEnabled(false);
    this->ui->button_refreshPorts->setEnabled(false);
    this->ui->button_disconnect->setEnabled(true);
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::clearResults(void) {

    this->ui->widget_testImage->setStyleSheet("background-color:transparent;");

}

void MainWindow::showPortInfo(int idx)
{
    if (idx == -1)
        return;

    const QStringList list = this->ui->serialPortInfoListBox->itemData(idx).toStringList();
    this->ui->descriptionLabel->setText(tr("Description: %1").arg(list.count() > 1 ? list.at(1) : tr(blankString)));
    this->ui->manufacturerLabel->setText(tr("Manufacturer: %1").arg(list.count() > 2 ? list.at(2) : tr(blankString)));
    this->ui->serialNumberLabel->setText(tr("Serial number: %1").arg(list.count() > 3 ? list.at(3) : tr(blankString)));
    this->ui->locationLabel->setText(tr("Location: %1").arg(list.count() > 4 ? list.at(4) : tr(blankString)));
    this->ui->vidLabel->setText(tr("Vendor Identifier: %1").arg(list.count() > 5 ? list.at(5) : tr(blankString)));
    this->ui->pidLabel->setText(tr("Product Identifier: %1").arg(list.count() > 6 ? list.at(6) : tr(blankString)));
}

void MainWindow::fillPortsInfo()
{
    this->ui->serialPortInfoListBox->clear();
    QString description;
    QString manufacturer;
    QString serialNumber;
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos) {
        QStringList list;
        description = info.description();
        manufacturer = info.manufacturer();
        serialNumber = info.serialNumber();
        list << info.portName()
             << (!description.isEmpty() ? description : blankString)
             << (!manufacturer.isEmpty() ? manufacturer : blankString)
             << (!serialNumber.isEmpty() ? serialNumber : blankString)
             << info.systemLocation()
             << (info.vendorIdentifier() ? QString::number(info.vendorIdentifier(), 16) : blankString)
             << (info.productIdentifier() ? QString::number(info.productIdentifier(), 16) : blankString);

        this->ui->serialPortInfoListBox->addItem(list.first(), list);
    }

//    this->ui->serialPortInfoListBox->addItem(tr("Custom"));
}

void MainWindow::on_button_refreshPorts_clicked()
{
    this->fillPortsInfo();
    clearResults();
}

void MainWindow::getImage(QByteArray data)
{
//    qDebug()<<data;

    QByteArray::iterator i;

    for (i = data.begin(); i !=data.end(); ++i) {

        switch( serialState ) {
           case PRTCL_STATE_IDLE:

           break;
           case PRTCL_STATE_FREE:
                if ( *i == '*' ) {
                    serialState = PRTCL_STATE_1;
                    ///qDebug()<<"serialState = state1";
                }
           break;
           case PRTCL_STATE_1:
                if ( *i == 'S' ) {
                    serialState = PRTCL_STATE_2;
                    ///qDebug()<<"serialState = state2";
                }
                else
                if ( *i == '*' )
                    serialState = PRTCL_STATE_1;
                else
                    serialState = PRTCL_STATE_FREE;
           break;
           case PRTCL_STATE_2:
                if ( *i == 'T' ) {
                    serialState = PRTCL_STATE_3;
                    ///qDebug()<<"serialState = state3";
                }
                else
                if ( *i == '*' )
                    serialState = PRTCL_STATE_1;
                else
                    serialState = PRTCL_STATE_FREE;
           break;
           case PRTCL_STATE_3:
                if ( *i == 'R' ) {
                    serialState = PRTCL_STATE_4;
                    ///qDebug()<<"serialState = state4";
                }
                else
                if ( *i == '*' )
                    serialState = PRTCL_STATE_1;
                else
                    serialState = PRTCL_STATE_FREE;
            break;
            case PRTCL_STATE_4:
                if ( *i == '*' ) {
                    serialState = PRTCL_STATE_IMAGESIZE_WAIT_WIDTH_MSB;
                     ///qDebug()<<"Header found";
                     this->ui->textBrowser->append("  Header found");
                    break;
                }
                else
                    serialState = PRTCL_STATE_FREE;
            break;
            case PRTCL_STATE_IMAGESIZE_WAIT_WIDTH_MSB:
                imagewidth_msb = *i;
                serialState = PRTCL_STATE_IMAGESIZE_WAIT_WIDTH_LSB;
            break;
            case PRTCL_STATE_IMAGESIZE_WAIT_WIDTH_LSB:
                imagewidth_lsb = *i;
                serialState = PRTCL_STATE_IMAGESIZE_WAIT_HEIGHT_MSB;
            break;
            case PRTCL_STATE_IMAGESIZE_WAIT_HEIGHT_MSB:
                imageheight_msb = *i;
                serialState = PRTCL_STATE_IMAGESIZE_WAIT_HEIGHT_LSB;
            break;
            case PRTCL_STATE_IMAGESIZE_WAIT_HEIGHT_LSB:
                imageheight_lsb = *i;
                serialState = PRTCL_STATE_WAIT_PIXELFORMAT_LEN;

                imagewidth  = (unsigned short) ( imagewidth_msb << 8 ) + imagewidth_lsb;
                imageheight = (unsigned short) ( imageheight_msb << 8 ) + imageheight_lsb;
            break;
            case PRTCL_STATE_WAIT_PIXELFORMAT_LEN:
//                ///qDebug() << QString("0x%1").arg((unsigned char)*i, 0, 16);
                imageformat_len = *i;
                imageformat_len_cnt = 0;

                serialState = PRTCL_STATE_WAIT_PIXELFORMAT;
            break;
            case PRTCL_STATE_WAIT_PIXELFORMAT:
//                ///qDebug() << QString("0x%1").arg((unsigned char)*i, 0, 16);
                imageformat[imageformat_len_cnt] = *i;
                imageformat_len_cnt++;

                if ( imageformat_len_cnt >= imageformat_len ) {
                    imagelength_cnt = 0;
                    serialState = PRTCL_STATE_WAIT_IMAGELEN;
                }
            break;
            case PRTCL_STATE_WAIT_IMAGELEN:
//                ///qDebug() << QString("0x%1").arg((unsigned char)*i, 0, 16);
                imagelength_bytes[imagelength_cnt] = *i;
                imagelength_cnt++;

                if ( imagelength_cnt == 4 ) {
                    imagedata_cnt = 0;

                    imagelength = (unsigned int) ( imagelength_bytes[0] << 24 ) +
                                                 ( imagelength_bytes[1] << 16 ) +
                                                 ( imagelength_bytes[2] << 8 )  +
                                                 ( imagelength_bytes[3] );

                    this->ui->textBrowser->append("  Receiving image : "  + QString::number(imagewidth ) + "x" + QString::number( imageheight ) +
                                                  "   Image Format Len: " + QString::number( imageformat_len) +
                                                  "   Image Format: " + imageformat +
                                                  "   Image Data Size: " + QString::number( imagelength ));

                    qDebug() << "Receiving image : "  << QString::number(imagewidth ) << "x" << QString::number( imageheight ) <<
                           "   Image Format Len: " << QString::number( imageformat_len) <<
                           "   Image Format: " << imageformat <<
                           "   Image Data Size: " << QString::number( imagelength );

                    imagedata.clear();
                    serialState = PRTCL_STATE_WAIT_IMAGE_DATA;
                }

            break;
            case PRTCL_STATE_WAIT_IMAGE_DATA:
                imagedata.append(*i);
                imagedata_cnt++;

                this->ui->progressBar_imageAcquisition->setValue(100 * (float(imagedata_cnt) / float(imagelength)));

                if ( imagedata_cnt >= imagelength ) {
                    serialState = PRTCL_STATE_IMAGE_RECEIVED;
                }

            break;
            case PRTCL_STATE_IMAGE_RECEIVED:
                this->ui->textBrowser->append("  Image received");
                qDebug() << "Image received";

                QByteArray::iterator shuffle;
                unsigned char temp;

                for(shuffle=imagedata.begin();shuffle<imagedata.end()-1; shuffle=shuffle+2) {
                    temp = *shuffle;
                    *shuffle = *(shuffle+1);
                    *(shuffle+1) = temp;
                }

                QImage::Format format = QImage::Format_RGB16;
                if (imageformat == "RGB565") {
                    format = QImage::Format_RGB16;
                } else if (imageformat == "RGB888") {
                    format = QImage::Format_RGB888;
                } else if (imageformat == "RGB444") {
                    format = QImage::Format_RGB444;
                } else {
                    qDebug() << "unknown format";
                }

                QImage myimage( (const uchar*) imagedata.data(), imagewidth, imageheight, format);
                QPainter painter(&myimage);
                this->ui->label_image_2->setPixmap(QPixmap::fromImage(myimage) );

                QString fileName("yourFile.png");
                QFile file(fileName);
                if(file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
                    myimage.save(&file, "PNG");
                }
                else {
                    qDebug() << "Can't open file: " << fileName;
                }


                serialState = PRTCL_STATE_FREE;
                emit imageReceived();
                receiveImage = false;
                processSerialData(data);

                if ( this->ui->checkBoxContinuous->isChecked()) {

                    this->on_button_testImage_clicked();

                }
            break;
        }
    }
}

void MainWindow::readSerialData()
{
    QByteArray readChunk;

    readChunk = serialPort.readAll();
//    qDebug() << "Chunk: " << readChunk;

    if (receiveImage) {
        getImage(readChunk);
    } else {
        processSerialData(readChunk);
    }
}

void MainWindow::processSerialData(QByteArray data)
{
    QByteArray readLine;

    serialData.append(data);

    while (serialData.indexOf('\n') >= 0) {
        readLine = serialData.left(serialData.indexOf('\n')).simplified();
        serialData.remove(0, serialData.indexOf('\n') + 1);
        ///qDebug() << readLine;
 ///       this->ui->textBrowser->append(readLine);
//        qDebug() << "Data: " << serialData;
        if (readLine.startsWith("#CMPL")) {
            commandState = COMMANDSTATE_PASSED;
            emit commandStateChanged();
        } else if (readLine.startsWith("#FL")) {
            commandState = COMMANDSTATE_FAILED;
            emit commandStateChanged();
        }
    }
}

void MainWindow::on_button_testImage_clicked()
{
    this->ui->group_tests->setEnabled(false);
    this->ui->widget_testImage->setStyleSheet("background-color:yellow;");
    this->ui->progressBar_imageAcquisition->setEnabled(true);
    this->ui->progressBar_imageAcquisition->setValue(0);

    receiveImage = true;
    commandState = COMMANDSTATE_RUNNING;
    QTimer timer;
    timer.setSingleShot(true);
    QEventLoop loop;
    connect(this, &MainWindow::imageReceived, &loop, &QEventLoop::quit);
    connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
    timer.start(20000);

    QByteArray txdata = QByteArrayLiteral("#T1\x0d\x0a");
    this->serialPort.clear();
    this->serialPort.write(txdata,txdata.length());
    this->serialPort.flush();
    this->serialPort.waitForBytesWritten();
    qDebug()<<"Requesting Image Test";

    loop.exec();

    this->ui->group_tests->setEnabled(true);
    if((timer.isActive() == false) || (commandState != COMMANDSTATE_PASSED)) {
        this->ui->widget_testImage->setStyleSheet("background-color:red;");
    } else {
        this->ui->widget_testImage->setStyleSheet("background-color:green;");
    }
    this->ui->progressBar_imageAcquisition->setEnabled(false);
    this->ui->progressBar_imageAcquisition->setValue(0);
}

void MainWindow::on_button_disconnect_clicked()
{
    this->serialPort.close();
    this->ui->serialPortInfoListBox->setEnabled(true);
    this->ui->group_tests->setEnabled(false);
    this->ui->button_connect->setEnabled(true);
    this->ui->button_refreshPorts->setEnabled(true);
    this->ui->button_disconnect->setEnabled(false);
    statusBar()->showMessage(tr(""));
    clearResults();
}
