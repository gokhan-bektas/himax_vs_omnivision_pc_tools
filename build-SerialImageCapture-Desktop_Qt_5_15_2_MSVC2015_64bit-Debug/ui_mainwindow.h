/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QGroupBox *group_serial;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *serialPortInfoListBox;
    QPushButton *button_refreshPorts;
    QPushButton *button_connect;
    QPushButton *button_disconnect;
    QLabel *descriptionLabel;
    QLabel *manufacturerLabel;
    QLabel *serialNumberLabel;
    QLabel *locationLabel;
    QLabel *vidLabel;
    QLabel *pidLabel;
    QGroupBox *group_tests;
    QGridLayout *gridLayout;
    QCheckBox *checkBoxSaveToFile;
    QCheckBox *checkBoxContinuous;
    QPushButton *button_testImage;
    QWidget *widget_testImage;
    QCheckBox *checkBoxShowMetadata;
    QGroupBox *group_image;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_image_2;
    QProgressBar *progressBar_imageAcquisition;
    QGroupBox *group_power;
    QLabel *labelPower1;
    QLabel *labelPower1_2;
    QLabel *labelPower1_3;
    QLabel *labelPower1_4;
    QLabel *labelPower1_5;
    QLabel *labelPower1_6;
    QLabel *labelPower1_7;
    QLabel *labelPower1_8;
    QTextBrowser *textBrowser;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(763, 604);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        group_serial = new QGroupBox(centralwidget);
        group_serial->setObjectName(QString::fromUtf8("group_serial"));
        group_serial->setMaximumSize(QSize(16777215, 250));
        verticalLayout_2 = new QVBoxLayout(group_serial);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        serialPortInfoListBox = new QComboBox(group_serial);
        serialPortInfoListBox->setObjectName(QString::fromUtf8("serialPortInfoListBox"));

        horizontalLayout_3->addWidget(serialPortInfoListBox);

        button_refreshPorts = new QPushButton(group_serial);
        button_refreshPorts->setObjectName(QString::fromUtf8("button_refreshPorts"));

        horizontalLayout_3->addWidget(button_refreshPorts);

        button_connect = new QPushButton(group_serial);
        button_connect->setObjectName(QString::fromUtf8("button_connect"));

        horizontalLayout_3->addWidget(button_connect);

        button_disconnect = new QPushButton(group_serial);
        button_disconnect->setObjectName(QString::fromUtf8("button_disconnect"));
        button_disconnect->setEnabled(false);

        horizontalLayout_3->addWidget(button_disconnect);

        horizontalLayout_3->setStretch(0, 4);

        verticalLayout_2->addLayout(horizontalLayout_3);

        descriptionLabel = new QLabel(group_serial);
        descriptionLabel->setObjectName(QString::fromUtf8("descriptionLabel"));

        verticalLayout_2->addWidget(descriptionLabel);

        manufacturerLabel = new QLabel(group_serial);
        manufacturerLabel->setObjectName(QString::fromUtf8("manufacturerLabel"));

        verticalLayout_2->addWidget(manufacturerLabel);

        serialNumberLabel = new QLabel(group_serial);
        serialNumberLabel->setObjectName(QString::fromUtf8("serialNumberLabel"));

        verticalLayout_2->addWidget(serialNumberLabel);

        locationLabel = new QLabel(group_serial);
        locationLabel->setObjectName(QString::fromUtf8("locationLabel"));

        verticalLayout_2->addWidget(locationLabel);

        vidLabel = new QLabel(group_serial);
        vidLabel->setObjectName(QString::fromUtf8("vidLabel"));

        verticalLayout_2->addWidget(vidLabel);

        pidLabel = new QLabel(group_serial);
        pidLabel->setObjectName(QString::fromUtf8("pidLabel"));

        verticalLayout_2->addWidget(pidLabel);


        horizontalLayout->addWidget(group_serial);

        group_tests = new QGroupBox(centralwidget);
        group_tests->setObjectName(QString::fromUtf8("group_tests"));
        group_tests->setEnabled(false);
        gridLayout = new QGridLayout(group_tests);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        checkBoxSaveToFile = new QCheckBox(group_tests);
        checkBoxSaveToFile->setObjectName(QString::fromUtf8("checkBoxSaveToFile"));

        gridLayout->addWidget(checkBoxSaveToFile, 2, 0, 1, 1);

        checkBoxContinuous = new QCheckBox(group_tests);
        checkBoxContinuous->setObjectName(QString::fromUtf8("checkBoxContinuous"));

        gridLayout->addWidget(checkBoxContinuous, 1, 0, 1, 1);

        button_testImage = new QPushButton(group_tests);
        button_testImage->setObjectName(QString::fromUtf8("button_testImage"));

        gridLayout->addWidget(button_testImage, 0, 0, 1, 1);

        widget_testImage = new QWidget(group_tests);
        widget_testImage->setObjectName(QString::fromUtf8("widget_testImage"));

        gridLayout->addWidget(widget_testImage, 0, 1, 1, 1);

        checkBoxShowMetadata = new QCheckBox(group_tests);
        checkBoxShowMetadata->setObjectName(QString::fromUtf8("checkBoxShowMetadata"));

        gridLayout->addWidget(checkBoxShowMetadata, 3, 0, 1, 1);


        horizontalLayout->addWidget(group_tests);

        horizontalLayout->setStretch(0, 3);

        verticalLayout->addLayout(horizontalLayout);

        group_image = new QGroupBox(centralwidget);
        group_image->setObjectName(QString::fromUtf8("group_image"));
        group_image->setMaximumSize(QSize(16777215, 250));
        verticalLayout_3 = new QVBoxLayout(group_image);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_image_2 = new QLabel(group_image);
        label_image_2->setObjectName(QString::fromUtf8("label_image_2"));

        verticalLayout_3->addWidget(label_image_2);

        progressBar_imageAcquisition = new QProgressBar(group_image);
        progressBar_imageAcquisition->setObjectName(QString::fromUtf8("progressBar_imageAcquisition"));
        progressBar_imageAcquisition->setEnabled(false);
        progressBar_imageAcquisition->setValue(0);

        verticalLayout_3->addWidget(progressBar_imageAcquisition);


        verticalLayout->addWidget(group_image);

        group_power = new QGroupBox(centralwidget);
        group_power->setObjectName(QString::fromUtf8("group_power"));
        labelPower1 = new QLabel(group_power);
        labelPower1->setObjectName(QString::fromUtf8("labelPower1"));
        labelPower1->setGeometry(QRect(80, 20, 47, 13));
        labelPower1_2 = new QLabel(group_power);
        labelPower1_2->setObjectName(QString::fromUtf8("labelPower1_2"));
        labelPower1_2->setGeometry(QRect(20, 20, 47, 13));
        labelPower1_3 = new QLabel(group_power);
        labelPower1_3->setObjectName(QString::fromUtf8("labelPower1_3"));
        labelPower1_3->setGeometry(QRect(220, 20, 47, 13));
        labelPower1_4 = new QLabel(group_power);
        labelPower1_4->setObjectName(QString::fromUtf8("labelPower1_4"));
        labelPower1_4->setGeometry(QRect(160, 20, 47, 13));
        labelPower1_5 = new QLabel(group_power);
        labelPower1_5->setObjectName(QString::fromUtf8("labelPower1_5"));
        labelPower1_5->setGeometry(QRect(280, 20, 47, 13));
        labelPower1_6 = new QLabel(group_power);
        labelPower1_6->setObjectName(QString::fromUtf8("labelPower1_6"));
        labelPower1_6->setGeometry(QRect(340, 20, 47, 13));
        labelPower1_7 = new QLabel(group_power);
        labelPower1_7->setObjectName(QString::fromUtf8("labelPower1_7"));
        labelPower1_7->setGeometry(QRect(390, 20, 47, 13));
        labelPower1_8 = new QLabel(group_power);
        labelPower1_8->setObjectName(QString::fromUtf8("labelPower1_8"));
        labelPower1_8->setGeometry(QRect(450, 20, 47, 13));

        verticalLayout->addWidget(group_power);

        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        textBrowser->setLineWrapMode(QTextEdit::WidgetWidth);

        verticalLayout->addWidget(textBrowser);

        verticalLayout->setStretch(0, 1);
        verticalLayout->setStretch(1, 5);
        verticalLayout->setStretch(2, 1);
        verticalLayout->setStretch(3, 1);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 763, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        group_serial->setTitle(QCoreApplication::translate("MainWindow", "Serial Port", nullptr));
        button_refreshPorts->setText(QCoreApplication::translate("MainWindow", "Refresh", nullptr));
        button_connect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        button_disconnect->setText(QCoreApplication::translate("MainWindow", "Disconnect", nullptr));
        descriptionLabel->setText(QCoreApplication::translate("MainWindow", "Description:", nullptr));
        manufacturerLabel->setText(QCoreApplication::translate("MainWindow", "Manufacturer:", nullptr));
        serialNumberLabel->setText(QCoreApplication::translate("MainWindow", "Serial number:", nullptr));
        locationLabel->setText(QCoreApplication::translate("MainWindow", "Location:", nullptr));
        vidLabel->setText(QCoreApplication::translate("MainWindow", "Vendor ID:", nullptr));
        pidLabel->setText(QCoreApplication::translate("MainWindow", "Product ID:", nullptr));
        group_tests->setTitle(QCoreApplication::translate("MainWindow", "Tests", nullptr));
        checkBoxSaveToFile->setText(QCoreApplication::translate("MainWindow", "Save To File", nullptr));
        checkBoxContinuous->setText(QCoreApplication::translate("MainWindow", "Continuous", nullptr));
        button_testImage->setText(QCoreApplication::translate("MainWindow", "Test Camera", nullptr));
        checkBoxShowMetadata->setText(QCoreApplication::translate("MainWindow", "Show Metadata", nullptr));
        group_image->setTitle(QCoreApplication::translate("MainWindow", "Image Acquisition", nullptr));
        label_image_2->setText(QCoreApplication::translate("MainWindow", "Image", nullptr));
        group_power->setTitle(QCoreApplication::translate("MainWindow", "Power Consumption", nullptr));
        labelPower1->setText(QCoreApplication::translate("MainWindow", "--", nullptr));
        labelPower1_2->setText(QCoreApplication::translate("MainWindow", "Power 0 :", nullptr));
        labelPower1_3->setText(QCoreApplication::translate("MainWindow", "--", nullptr));
        labelPower1_4->setText(QCoreApplication::translate("MainWindow", "Power 1 :", nullptr));
        labelPower1_5->setText(QCoreApplication::translate("MainWindow", "Power 2 :", nullptr));
        labelPower1_6->setText(QCoreApplication::translate("MainWindow", "--", nullptr));
        labelPower1_7->setText(QCoreApplication::translate("MainWindow", "Power 3 :", nullptr));
        labelPower1_8->setText(QCoreApplication::translate("MainWindow", "--", nullptr));
        textBrowser->setDocumentTitle(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
