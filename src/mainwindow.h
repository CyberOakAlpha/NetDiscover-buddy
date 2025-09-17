#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QProgressBar>
#include <QGroupBox>
#include <QComboBox>
#include <QSpinBox>
#include <QStatusBar>
#include <QCheckBox>
#include <QFileDialog>
#include <QGridLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onStartScan();
    void onStopScan();
    void onClearResults();
    void onBrowseOutputFile();

private:
    void setupUI();
    void setupMenuBar();
    void setupStatusBar();

    // UI Components
    QWidget *m_centralWidget;
    QVBoxLayout *m_mainLayout;

    // Target configuration
    QGroupBox *m_targetGroup;
    QLineEdit *m_targetInput;
    QComboBox *m_cidrCombo;
    QComboBox *m_scanTypeCombo;
    QSpinBox *m_timeoutSpin;
    QCheckBox *m_noResolveCheckbox;

    // Output configuration
    QGroupBox *m_outputGroup;
    QLineEdit *m_outputFileInput;
    QPushButton *m_browseButton;

    // Control buttons
    QHBoxLayout *m_buttonLayout;
    QPushButton *m_startButton;
    QPushButton *m_stopButton;
    QPushButton *m_clearButton;

    // Results area
    QGroupBox *m_resultsGroup;
    QTextEdit *m_resultsText;
    QProgressBar *m_progressBar;

    // Status
    QLabel *m_statusLabel;
};

#endif // MAINWINDOW_H