#pragma once

#include <QMainWindow>

#include <memory>

#include "benchmark.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private slots:
    void generateArray();
    void runScalar();
    void runNeon();
    void runBenchmark();

private:
    void ensureArrayGenerated();
    void updateSpeedupLabel();
    void clearSummary();
    void setStatusMessage(const QString& message);

    std::unique_ptr<Ui::MainWindow> ui_;
    AlignedInt32Buffer data_;
    ExecutionMetrics lastScalar_;
    ExecutionMetrics lastNeon_;
    bool hasScalarResult_ = false;
    bool hasNeonResult_ = false;
};
