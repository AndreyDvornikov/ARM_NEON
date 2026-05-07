/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *controlsGroupBox;
    QHBoxLayout *horizontalLayout;
    QLabel *arraySizeLabel;
    QSpinBox *arraySizeSpinBox;
    QPushButton *generateButton;
    QPushButton *runScalarButton;
    QPushButton *runNeonButton;
    QPushButton *runBenchmarkButton;
    QGroupBox *summaryGroupBox;
    QGridLayout *gridLayout;
    QLabel *scalarTimeLabel;
    QLabel *scalarTimeValueLabel;
    QLabel *neonTimeLabel;
    QLabel *neonTimeValueLabel;
    QLabel *speedupLabel;
    QLabel *speedupValueLabel;
    QLabel *scalarSumLabel;
    QLabel *scalarSumValueLabel;
    QLabel *neonSumLabel;
    QLabel *neonSumValueLabel;
    QLabel *statusLabel;
    QLabel *statusValueLabel;
    QGroupBox *resultsGroupBox;
    QVBoxLayout *verticalLayout_2;
    QTableWidget *benchmarkTable;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(960, 640);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        controlsGroupBox = new QGroupBox(centralwidget);
        controlsGroupBox->setObjectName(QString::fromUtf8("controlsGroupBox"));
        horizontalLayout = new QHBoxLayout(controlsGroupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        arraySizeLabel = new QLabel(controlsGroupBox);
        arraySizeLabel->setObjectName(QString::fromUtf8("arraySizeLabel"));

        horizontalLayout->addWidget(arraySizeLabel);

        arraySizeSpinBox = new QSpinBox(controlsGroupBox);
        arraySizeSpinBox->setObjectName(QString::fromUtf8("arraySizeSpinBox"));

        horizontalLayout->addWidget(arraySizeSpinBox);

        generateButton = new QPushButton(controlsGroupBox);
        generateButton->setObjectName(QString::fromUtf8("generateButton"));

        horizontalLayout->addWidget(generateButton);

        runScalarButton = new QPushButton(controlsGroupBox);
        runScalarButton->setObjectName(QString::fromUtf8("runScalarButton"));

        horizontalLayout->addWidget(runScalarButton);

        runNeonButton = new QPushButton(controlsGroupBox);
        runNeonButton->setObjectName(QString::fromUtf8("runNeonButton"));

        horizontalLayout->addWidget(runNeonButton);

        runBenchmarkButton = new QPushButton(controlsGroupBox);
        runBenchmarkButton->setObjectName(QString::fromUtf8("runBenchmarkButton"));

        horizontalLayout->addWidget(runBenchmarkButton);


        verticalLayout->addWidget(controlsGroupBox);

        summaryGroupBox = new QGroupBox(centralwidget);
        summaryGroupBox->setObjectName(QString::fromUtf8("summaryGroupBox"));
        gridLayout = new QGridLayout(summaryGroupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        scalarTimeLabel = new QLabel(summaryGroupBox);
        scalarTimeLabel->setObjectName(QString::fromUtf8("scalarTimeLabel"));

        gridLayout->addWidget(scalarTimeLabel, 0, 0, 1, 1);

        scalarTimeValueLabel = new QLabel(summaryGroupBox);
        scalarTimeValueLabel->setObjectName(QString::fromUtf8("scalarTimeValueLabel"));

        gridLayout->addWidget(scalarTimeValueLabel, 0, 1, 1, 1);

        neonTimeLabel = new QLabel(summaryGroupBox);
        neonTimeLabel->setObjectName(QString::fromUtf8("neonTimeLabel"));

        gridLayout->addWidget(neonTimeLabel, 0, 2, 1, 1);

        neonTimeValueLabel = new QLabel(summaryGroupBox);
        neonTimeValueLabel->setObjectName(QString::fromUtf8("neonTimeValueLabel"));

        gridLayout->addWidget(neonTimeValueLabel, 0, 3, 1, 1);

        speedupLabel = new QLabel(summaryGroupBox);
        speedupLabel->setObjectName(QString::fromUtf8("speedupLabel"));

        gridLayout->addWidget(speedupLabel, 1, 0, 1, 1);

        speedupValueLabel = new QLabel(summaryGroupBox);
        speedupValueLabel->setObjectName(QString::fromUtf8("speedupValueLabel"));

        gridLayout->addWidget(speedupValueLabel, 1, 1, 1, 1);

        scalarSumLabel = new QLabel(summaryGroupBox);
        scalarSumLabel->setObjectName(QString::fromUtf8("scalarSumLabel"));

        gridLayout->addWidget(scalarSumLabel, 1, 2, 1, 1);

        scalarSumValueLabel = new QLabel(summaryGroupBox);
        scalarSumValueLabel->setObjectName(QString::fromUtf8("scalarSumValueLabel"));

        gridLayout->addWidget(scalarSumValueLabel, 1, 3, 1, 1);

        neonSumLabel = new QLabel(summaryGroupBox);
        neonSumLabel->setObjectName(QString::fromUtf8("neonSumLabel"));

        gridLayout->addWidget(neonSumLabel, 2, 0, 1, 1);

        neonSumValueLabel = new QLabel(summaryGroupBox);
        neonSumValueLabel->setObjectName(QString::fromUtf8("neonSumValueLabel"));

        gridLayout->addWidget(neonSumValueLabel, 2, 1, 1, 1);

        statusLabel = new QLabel(summaryGroupBox);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));

        gridLayout->addWidget(statusLabel, 2, 2, 1, 1);

        statusValueLabel = new QLabel(summaryGroupBox);
        statusValueLabel->setObjectName(QString::fromUtf8("statusValueLabel"));

        gridLayout->addWidget(statusValueLabel, 2, 3, 1, 1);


        verticalLayout->addWidget(summaryGroupBox);

        resultsGroupBox = new QGroupBox(centralwidget);
        resultsGroupBox->setObjectName(QString::fromUtf8("resultsGroupBox"));
        verticalLayout_2 = new QVBoxLayout(resultsGroupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        benchmarkTable = new QTableWidget(resultsGroupBox);
        if (benchmarkTable->columnCount() < 7)
            benchmarkTable->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        benchmarkTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        benchmarkTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        benchmarkTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        benchmarkTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        benchmarkTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        benchmarkTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        benchmarkTable->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        benchmarkTable->setObjectName(QString::fromUtf8("benchmarkTable"));

        verticalLayout_2->addWidget(benchmarkTable);


        verticalLayout->addWidget(resultsGroupBox);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "ARM NEON Array Processor", nullptr));
        controlsGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Controls", nullptr));
        arraySizeLabel->setText(QCoreApplication::translate("MainWindow", "Array Size", nullptr));
        generateButton->setText(QCoreApplication::translate("MainWindow", "Generate Array", nullptr));
        runScalarButton->setText(QCoreApplication::translate("MainWindow", "Run Scalar", nullptr));
        runNeonButton->setText(QCoreApplication::translate("MainWindow", "Run NEON", nullptr));
        runBenchmarkButton->setText(QCoreApplication::translate("MainWindow", "Run Benchmark", nullptr));
        summaryGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Last Run Summary", nullptr));
        scalarTimeLabel->setText(QCoreApplication::translate("MainWindow", "Scalar Time", nullptr));
        scalarTimeValueLabel->setText(QCoreApplication::translate("MainWindow", "N/A", nullptr));
        neonTimeLabel->setText(QCoreApplication::translate("MainWindow", "NEON Time", nullptr));
        neonTimeValueLabel->setText(QCoreApplication::translate("MainWindow", "N/A", nullptr));
        speedupLabel->setText(QCoreApplication::translate("MainWindow", "Speedup", nullptr));
        speedupValueLabel->setText(QCoreApplication::translate("MainWindow", "N/A", nullptr));
        scalarSumLabel->setText(QCoreApplication::translate("MainWindow", "Scalar Sum", nullptr));
        scalarSumValueLabel->setText(QCoreApplication::translate("MainWindow", "N/A", nullptr));
        neonSumLabel->setText(QCoreApplication::translate("MainWindow", "NEON Sum", nullptr));
        neonSumValueLabel->setText(QCoreApplication::translate("MainWindow", "N/A", nullptr));
        statusLabel->setText(QCoreApplication::translate("MainWindow", "Status", nullptr));
        statusValueLabel->setText(QCoreApplication::translate("MainWindow", "Idle", nullptr));
        resultsGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Benchmark Results", nullptr));
        QTableWidgetItem *___qtablewidgetitem = benchmarkTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Size", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = benchmarkTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Scalar ms", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = benchmarkTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "NEON ms", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = benchmarkTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Speedup", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = benchmarkTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Scalar Sum", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = benchmarkTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "NEON Sum", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = benchmarkTable->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "Status", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
