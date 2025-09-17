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
    QComboBox *m_scanTypeCombo;
    QSpinBox *m_timeoutSpin;

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