#include "CameraWindow.h"

#include <QTime>
#include <QFileDialog>
#include <QShortcut>
#include <QSpinBox>
#include <QDateTime>

CameraWindow::CameraWindow(QWidget* parent) :
	QMainWindow(parent),
	m_ui(new Ui::CameraWindowClass())
{
	m_ui->setupUi(this);
	adjustSize();
	setupShortcuts();
	resetUi();

	// Connexion des boutons aux signaux
	connect(m_ui->openButton, &QPushButton::clicked, this, &CameraWindow::openButtonClicked);
	connect(m_ui->closeButton, &QPushButton::clicked, this, &CameraWindow::closeButtonClicked);
	connect(m_ui->startButton, &QPushButton::clicked, this, &CameraWindow::startButtonClicked);
	connect(m_ui->stopButton, &QPushButton::clicked, this, &CameraWindow::stopButtonClicked);
	connect(m_ui->deviceComboBox, &QComboBox::currentIndexChanged, this, &CameraWindow::deviceChanged);
}

CameraWindow::~CameraWindow()
{
	delete m_ui;
}

void CameraWindow::closeEvent(QCloseEvent* event)
{
	event->ignore();
	emit closing();
}

void CameraWindow::resetUi()
{
	m_ui->openButton->setEnabled(true);
	m_ui->closeButton->setEnabled(false);
	m_ui->startButton->setEnabled(false);
	m_ui->stopButton->setEnabled(false);
	m_ui->deviceComboBox->setEnabled(true);

	m_ui->dimensionsLabel->clear();
	m_ui->fpsLabel->clear();
	m_ui->frameLabel->clear();
}

void CameraWindow::setupShortcuts()
{
	// Ctrl+O -> Ouvrir la caméra
	QShortcut* shortcutOpen = new QShortcut(QKeySequence("Ctrl+O"), this);
	connect(shortcutOpen, &QShortcut::activated, this, &CameraWindow::openButtonClicked);

	// Ctrl+C -> Fermer la caméra
	QShortcut* shortcutClose = new QShortcut(QKeySequence("Ctrl+C"), this);
	connect(shortcutClose, &QShortcut::activated, this, &CameraWindow::closeButtonClicked);

	// Ctrl+S -> Démarrer ou arrêter l'enregistrement
	QShortcut* shortcutRecord = new QShortcut(QKeySequence("Ctrl+S"), this);
	connect(shortcutRecord, &QShortcut::activated, this, &CameraWindow::onStartOrStopAction);
}

void CameraWindow::setDimensionsLabel(const QString& dimensions)
{
	m_ui->dimensionsLabel->setText(dimensions);
}

void CameraWindow::setFpsLabel(const QString& fps)
{
	m_ui->fpsLabel->setText(fps);
}

void CameraWindow::setFrameLabel(const QImage& image)
{
	internalSetFrame((image.width() > 640 || image.height() > 480) ? resizeFrame(image) : image);
}

void CameraWindow::internalSetFrame(const QImage& image)
{
	m_ui->frameLabel->clear();
	m_ui->frameLabel->setPixmap(QPixmap::fromImage(image));
}

QImage CameraWindow::resizeFrame(const QImage& image)
{
	int originalWidth = image.width();
	int originalHeight = image.height();

	int newWidth;
	int newHeight;

	if (originalWidth > originalHeight)
	{
		// Width is the dominant dimension
		newWidth = 640;
		newHeight = (int)((float)originalHeight * (640.f / (float)originalWidth));
	}
	else
	{
		// Height is the dominant dimension
		newHeight = 480;
		newWidth = (int)((float)originalWidth * (480.f / (float)originalHeight));
	}
	return image.scaled(newWidth, newHeight, Qt::IgnoreAspectRatio, Qt::FastTransformation);
}

void CameraWindow::onDeviceConnected()
{
	m_ui->openButton->setEnabled(false);
	m_ui->closeButton->setEnabled(true);
	m_ui->startButton->setEnabled(true);
	m_ui->deviceComboBox->setEnabled(false);

	log("Device connected");
}

void CameraWindow::onDeviceDisconnected()
{
	log("Device disconnected");
	resetUi();
}

void CameraWindow::onRecordingStarted(const QString& filename)
{
	log("Device recording started at: " + filename);

	m_ui->startButton->setEnabled(false);
	m_ui->stopButton->setEnabled(true);
}

void CameraWindow::onRecordingStopped()
{
	log("Device recording stopped");
	m_ui->startButton->setEnabled(true);
	m_ui->stopButton->setEnabled(false);
}

void CameraWindow::log(const QString& message)
{
	QString timestamp = QTime::currentTime().toString("hh:mm:ss");
	m_ui->logTextEdit->append(QString("[%1] [log] > %2").arg(timestamp, message));
}

void CameraWindow::logError(const QString& error, const QString& errorMessage)
{
	QString timestamp = QTime::currentTime().toString("hh:mm:ss");
	m_ui->logTextEdit->append(QString("[%1] [err] > %2: %3").arg(timestamp, error, errorMessage));
}

QString CameraWindow::getVideoFilename() const
{
	QString defaultName = "record_" + QDateTime::currentDateTime().toString("yyyy_MM_dd-hh_mm_ss");
	return QFileDialog::getSaveFileName(
		(QWidget*)this,
		tr("Save Video"),
		defaultName,
		tr("AVI Video (*.avi)")
	);
}

QSize CameraWindow::getFrameLabelSize() const
{
	return m_ui->frameLabel->size();
}

void CameraWindow::onStartOrStopAction()
{
	if (m_ui->startButton->isEnabled()) 
	{
		emit startButtonClicked();
	}
	else 
	{
		emit stopButtonClicked();
	}
}