#include "mainwindow.h"
#include <QMenuBar>
#include <QMessageBox>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_centralWidget(nullptr)
    , m_mainLayout(nullptr)
    , m_targetGroup(nullptr)
    , m_targetInput(nullptr)
    , m_cidrCombo(nullptr)
    , m_scanTypeCombo(nullptr)
    , m_timeoutSpin(nullptr)
    , m_noResolveCheckbox(nullptr)
    , m_outputGroup(nullptr)
    , m_outputFileInput(nullptr)
    , m_browseButton(nullptr)
    , m_buttonLayout(nullptr)
    , m_startButton(nullptr)
    , m_stopButton(nullptr)
    , m_clearButton(nullptr)
    , m_resultsGroup(nullptr)
    , m_resultsText(nullptr)
    , m_progressBar(nullptr)
    , m_statusLabel(nullptr)
{
    setupUI();
    setupMenuBar();
    setupStatusBar();

    setWindowTitle("NetDiscover Buddy - Network Discovery Tool");
    setMinimumSize(800, 600);
    resize(1000, 700);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setupUI()
{
    // Central widget and main layout
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);
    m_mainLayout = new QVBoxLayout(m_centralWidget);

    // Target configuration group
    m_targetGroup = new QGroupBox("Target Configuration", this);
    QGridLayout *targetLayout = new QGridLayout(m_targetGroup);

    // Target input with CIDR dropdown
    targetLayout->addWidget(new QLabel("Target Network/IP:"), 0, 0);
    m_targetInput = new QLineEdit("192.168.1.0", this);
    m_targetInput->setPlaceholderText("e.g., 192.168.1.0 or 10.0.0.1");
    targetLayout->addWidget(m_targetInput, 0, 1);

    targetLayout->addWidget(new QLabel("CIDR:"), 0, 2);
    m_cidrCombo = new QComboBox(this);
    m_cidrCombo->addItems({"/8", "/16", "/24", "/25", "/26", "/27", "/28", "/29", "/30"});
    m_cidrCombo->setCurrentText("/24");
    targetLayout->addWidget(m_cidrCombo, 0, 3);

    // Scan type
    targetLayout->addWidget(new QLabel("Scan Type:"), 1, 0);
    m_scanTypeCombo = new QComboBox(this);
    m_scanTypeCombo->addItems({"ARP Scan", "Ping Scan"});
    targetLayout->addWidget(m_scanTypeCombo, 1, 1);

    // Timeout setting
    targetLayout->addWidget(new QLabel("Timeout (ms):"), 1, 2);
    m_timeoutSpin = new QSpinBox(this);
    m_timeoutSpin->setRange(100, 10000);
    m_timeoutSpin->setValue(1000);
    m_timeoutSpin->setSuffix(" ms");
    targetLayout->addWidget(m_timeoutSpin, 1, 3);

    // No resolve checkbox
    m_noResolveCheckbox = new QCheckBox("No DNS resolution (-n)", this);
    m_noResolveCheckbox->setChecked(true);
    targetLayout->addWidget(m_noResolveCheckbox, 2, 0, 1, 2);

    // Output configuration group
    m_outputGroup = new QGroupBox("Output Configuration", this);
    QHBoxLayout *outputLayout = new QHBoxLayout(m_outputGroup);

    outputLayout->addWidget(new QLabel("Output File:"));
    m_outputFileInput = new QLineEdit(this);
    m_outputFileInput->setPlaceholderText("Optional: /path/to/output.txt");
    outputLayout->addWidget(m_outputFileInput);

    m_browseButton = new QPushButton("Browse...", this);
    outputLayout->addWidget(m_browseButton);

    // Control buttons
    m_buttonLayout = new QHBoxLayout();
    m_startButton = new QPushButton("Start Scan", this);
    m_stopButton = new QPushButton("Stop Scan", this);
    m_clearButton = new QPushButton("Clear Results", this);

    m_startButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; font-weight: bold; padding: 8px; }");
    m_stopButton->setStyleSheet("QPushButton { background-color: #f44336; color: white; font-weight: bold; padding: 8px; }");
    m_clearButton->setStyleSheet("QPushButton { background-color: #2196F3; color: white; font-weight: bold; padding: 8px; }");

    m_stopButton->setEnabled(false);

    m_buttonLayout->addWidget(m_startButton);
    m_buttonLayout->addWidget(m_stopButton);
    m_buttonLayout->addWidget(m_clearButton);
    m_buttonLayout->addStretch();

    // Results group
    m_resultsGroup = new QGroupBox("Scan Results", this);
    QVBoxLayout *resultsLayout = new QVBoxLayout(m_resultsGroup);

    m_resultsText = new QTextEdit(this);
    m_resultsText->setReadOnly(true);
    m_resultsText->setFont(QFont("Courier", 10));
    m_resultsText->setPlainText("Ready to scan. Configure your target and click 'Start Scan'.\n");

    m_progressBar = new QProgressBar(this);
    m_progressBar->setVisible(false);

    resultsLayout->addWidget(m_resultsText);
    resultsLayout->addWidget(m_progressBar);

    // Add all groups to main layout
    m_mainLayout->addWidget(m_targetGroup);
    m_mainLayout->addWidget(m_outputGroup);
    m_mainLayout->addLayout(m_buttonLayout);
    m_mainLayout->addWidget(m_resultsGroup);

    // Connect signals
    connect(m_startButton, &QPushButton::clicked, this, &MainWindow::onStartScan);
    connect(m_stopButton, &QPushButton::clicked, this, &MainWindow::onStopScan);
    connect(m_clearButton, &QPushButton::clicked, this, &MainWindow::onClearResults);
    connect(m_browseButton, &QPushButton::clicked, this, &MainWindow::onBrowseOutputFile);
}

void MainWindow::setupMenuBar()
{
    QMenuBar *menuBar = this->menuBar();

    // File menu
    QMenu *fileMenu = menuBar->addMenu("&File");
    QAction *exitAction = fileMenu->addAction("E&xit");
    exitAction->setShortcut(QKeySequence::Quit);
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    // Help menu
    QMenu *helpMenu = menuBar->addMenu("&Help");
    QAction *aboutAction = helpMenu->addAction("&About");
    connect(aboutAction, &QAction::triggered, this, [this]() {
        QMessageBox::about(this, "About NetDiscover Buddy",
                          "NetDiscover Buddy v1.0.0\n\n"
                          "Network Discovery Tool\n"
                          "Perform ARP scan or PING scan of a network to detect active hosts.\n\n"
                          "Features:\n"
                          "• ARP and PING scanning\n"
                          "• CIDR network notation support\n"
                          "• Output file export\n"
                          "• No DNS resolution option (-n)\n\n"
                          "Built with Qt6 and C++\n\n"
                          "Note: Actual scanning implementation will be added in the next phase.\n\n"
                          "© 2024-2025 CyberOak By AlphaSecurity");
    });
}

void MainWindow::setupStatusBar()
{
    m_statusLabel = new QLabel("Ready", this);
    statusBar()->addWidget(m_statusLabel);
    statusBar()->showMessage("Ready to start network scanning", 3000);
}

void MainWindow::onStartScan()
{
    QString target = m_targetInput->text().trimmed();
    if (target.isEmpty()) {
        QMessageBox::warning(this, "Invalid Target", "Please enter a target network or IP address.");
        return;
    }

    m_startButton->setEnabled(false);
    m_stopButton->setEnabled(true);
    m_progressBar->setVisible(true);
    m_progressBar->setRange(0, 0); // Indeterminate progress

    m_statusLabel->setText("Scanning...");

    QString scanType = m_scanTypeCombo->currentText();
    QString cidr = m_cidrCombo->currentText();
    QString fullTarget = target + cidr;
    int timeout = m_timeoutSpin->value();
    bool noResolve = m_noResolveCheckbox->isChecked();
    QString outputFile = m_outputFileInput->text().trimmed();

    // Build netdiscover command
    QString command = "netdiscover";

    if (scanType == "ARP Scan") {
        command += " -r " + fullTarget;
    } else if (scanType == "Ping Scan") {
        command += " -p -r " + fullTarget;
    }

    if (noResolve) {
        command += " -n";
    }

    if (!outputFile.isEmpty()) {
        command += " > " + outputFile;
    }

    m_resultsText->append(QString("=== Starting %1 ===").arg(scanType));
    m_resultsText->append(QString("Target: %1").arg(fullTarget));
    m_resultsText->append(QString("Timeout: %1 ms").arg(timeout));
    m_resultsText->append(QString("No DNS Resolution: %1").arg(noResolve ? "Yes" : "No"));
    if (!outputFile.isEmpty()) {
        m_resultsText->append(QString("Output File: %1").arg(outputFile));
    }
    m_resultsText->append(QString("Command: %1").arg(command));
    m_resultsText->append("Scanning in progress...\n");

    // TODO: Implement actual scanning logic here
    // For now, we'll just show a placeholder message
    m_resultsText->append("Note: Actual scanning implementation will be added in the next phase.");
    m_resultsText->append("This is a basic GUI framework for the NetDiscover Buddy application.\n");
}

void MainWindow::onStopScan()
{
    m_startButton->setEnabled(true);
    m_stopButton->setEnabled(false);
    m_progressBar->setVisible(false);

    m_statusLabel->setText("Scan stopped");
    m_resultsText->append("=== Scan Stopped ===\n");
}

void MainWindow::onClearResults()
{
    m_resultsText->clear();
    m_resultsText->setPlainText("Ready to scan. Configure your target and click 'Start Scan'.\n");
    m_statusLabel->setText("Ready");
}

void MainWindow::onBrowseOutputFile()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        "Select Output File",
        QDir::homePath() + "/netdiscover_results.txt",
        "Text files (*.txt);;All files (*.*)");

    if (!fileName.isEmpty()) {
        m_outputFileInput->setText(fileName);
    }
}