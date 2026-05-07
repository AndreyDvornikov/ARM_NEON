#include "mainwindow.hpp"

#include "ui_mainwindow.h"

#include <QHeaderView>
#include <QString>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui_(std::make_unique<Ui::MainWindow>()) {
    ui_->setupUi(this);

    ui_->arraySizeSpinBox->setRange(1, 50'000'000);
    ui_->arraySizeSpinBox->setValue(100'000);
    ui_->benchmarkTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui_->generateButton, &QPushButton::clicked, this, &MainWindow::generateArray);
    connect(ui_->runScalarButton, &QPushButton::clicked, this, &MainWindow::runScalar);
    connect(ui_->runNeonButton, &QPushButton::clicked, this, &MainWindow::runNeon);
    connect(ui_->runBenchmarkButton, &QPushButton::clicked, this, &MainWindow::runBenchmark);

    generateArray();
}

MainWindow::~MainWindow() = default;

void MainWindow::generateArray() {
    const std::size_t requestedSize = static_cast<std::size_t>(ui_->arraySizeSpinBox->value());

    if (!data_.resize(requestedSize)) {
        setStatusMessage("Failed to allocate aligned memory for the requested array size.");
        return;
    }

    if (!fill_random_data(data_, static_cast<std::uint32_t>(requestedSize))) {
        setStatusMessage("Failed to fill the array with random values.");
        return;
    }

    clearSummary();
    ui_->benchmarkTable->setRowCount(0);
    setStatusMessage(QString("Generated %1 aligned int32 values.").arg(requestedSize));
}

void MainWindow::runScalar() {
    ensureArrayGenerated();
    lastScalar_ = benchmark_scalar(data_.data(), data_.size());
    hasScalarResult_ = true;

    ui_->scalarTimeValueLabel->setText(QString::number(lastScalar_.milliseconds, 'f', 4) + " ms");
    ui_->scalarSumValueLabel->setText(QString::number(lastScalar_.sum));
    updateSpeedupLabel();
    setStatusMessage("Scalar benchmark finished.");
}

void MainWindow::runNeon() {
    ensureArrayGenerated();
    lastNeon_ = benchmark_neon(data_.data(), data_.size());
    hasNeonResult_ = true;

    ui_->neonTimeValueLabel->setText(QString::number(lastNeon_.milliseconds, 'f', 4) + " ms");
    ui_->neonSumValueLabel->setText(QString::number(lastNeon_.sum));
    updateSpeedupLabel();

    if (hasScalarResult_ && lastScalar_.sum != lastNeon_.sum) {
        setStatusMessage("Validation failed: scalar and NEON sums do not match.");
    } else {
        setStatusMessage("NEON benchmark finished.");
    }
}

void MainWindow::runBenchmark() {
    ui_->benchmarkTable->setRowCount(0);

    const auto rows = run_standard_benchmark();
    ui_->benchmarkTable->setRowCount(static_cast<int>(rows.size()));

    bool allValid = true;
    for (int row = 0; row < static_cast<int>(rows.size()); ++row) {
        const BenchmarkRow& item = rows[static_cast<std::size_t>(row)];
        allValid = allValid && item.valid;

        ui_->benchmarkTable->setItem(row, 0, new QTableWidgetItem(QString::number(item.size)));
        ui_->benchmarkTable->setItem(row, 1, new QTableWidgetItem(QString::number(item.scalar_ms, 'f', 4)));
        ui_->benchmarkTable->setItem(row, 2, new QTableWidgetItem(QString::number(item.neon_ms, 'f', 4)));
        ui_->benchmarkTable->setItem(row, 3, new QTableWidgetItem(QString::number(item.speedup, 'f', 2) + "x"));
        ui_->benchmarkTable->setItem(row, 4, new QTableWidgetItem(QString::number(item.scalar_sum)));
        ui_->benchmarkTable->setItem(row, 5, new QTableWidgetItem(QString::number(item.neon_sum)));
        ui_->benchmarkTable->setItem(row, 6, new QTableWidgetItem(item.valid ? "OK" : "Mismatch"));
    }

    setStatusMessage(allValid
        ? "Benchmark completed for 1k, 10k, 100k, and 1M elements."
        : "Benchmark completed, but at least one validation mismatch was detected.");
}

void MainWindow::ensureArrayGenerated() {
    if (data_.size() == 0 || data_.data() == nullptr) {
        generateArray();
    }
}

void MainWindow::updateSpeedupLabel() {
    if (!hasScalarResult_ || !hasNeonResult_ || lastNeon_.milliseconds <= 0.0) {
        ui_->speedupValueLabel->setText("N/A");
        return;
    }

    const double speedup = lastScalar_.milliseconds / lastNeon_.milliseconds;
    ui_->speedupValueLabel->setText(QString::number(speedup, 'f', 2) + "x");
}

void MainWindow::clearSummary() {
    hasScalarResult_ = false;
    hasNeonResult_ = false;
    lastScalar_ = {};
    lastNeon_ = {};

    ui_->scalarTimeValueLabel->setText("N/A");
    ui_->neonTimeValueLabel->setText("N/A");
    ui_->speedupValueLabel->setText("N/A");
    ui_->scalarSumValueLabel->setText("N/A");
    ui_->neonSumValueLabel->setText("N/A");
}

void MainWindow::setStatusMessage(const QString& message) {
    ui_->statusValueLabel->setText(message);
}
