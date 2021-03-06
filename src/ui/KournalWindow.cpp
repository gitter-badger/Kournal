#include "KournalWindow.hpp"
#include "ui_KournalWindow.h"

#include "SettingsDialog.hpp"
#include "Static.hpp"

#include <QFileDialog>
#include <QMessageBox>
#include <QStandardPaths>

KournalWindow::KournalWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::KournalWindow)
{
    // Settings setup
    Static::setSettings(new SettingsHandler(this, true));

    // UI setup
    ui->setupUi(this);

    localSettings.beginGroup(QStringLiteral("KournalWindow"));
    restoreGeometry(localSettings.value(QStringLiteral("geometry")).toByteArray());
    restoreState(localSettings.value(QStringLiteral("state")).toByteArray());
    localSettings.endGroup();

    connect(ui->actionClose, SIGNAL(triggered()), this, SLOT(close()));

    welcome = new WelcomeWidget(this);
    ui->fileTabs->addTab(welcome, welcome->windowTitle());  // TODO – add icon
}

KournalWindow::~KournalWindow()
{
    localSettings.beginGroup(QStringLiteral("KournalWindow"));
    localSettings.setValue(QStringLiteral("geometry"), saveGeometry());
    localSettings.setValue(QStringLiteral("state"), saveState());
    localSettings.endGroup();
    localSettings.sync();

    delete ui;
}

void KournalWindow::on_fileTabs_tabCloseRequested(int index)
{
    if (dynamic_cast<WelcomeWidget *>(ui->fileTabs->widget(index)))
    {
        ui->fileTabs->removeTab(index);
    }
}

void KournalWindow::on_actionOpenJournal_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Journal"),
        QStandardPaths::standardLocations(QStandardPaths::HomeLocation).first(),
        tr("Kournal Binary Journal files (*.kbj)"));

    // TODO
}

void KournalWindow::on_actionOptions_triggered()
{
    SettingsDialog settings;
    settings.exec();
}

void KournalWindow::on_actionAboutQt_triggered()
{
    QMessageBox::aboutQt(this, tr("About Qt"));
}
