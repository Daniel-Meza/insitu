#include <Notification/Notification_dialog.hpp>
#include <Notification/Notification.hpp>

using namespace notification_filter;

namespace insitu_plugins
{
NotificationDialog::NotificationDialog(insitu::Filter * parent_)
: FilterDialog(parent_)
{
    layout = new QGridLayout();

    error_msg = new QErrorMessage();

    nameEdit = new QLineEdit(QString::fromStdString(DEFAULT_NAME));
    nameLabel = new QLabel(tr("Name: "), nameEdit);
    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(nameEdit, 0, 1);

    topicEdit = new QLineEdit(QString::fromStdString(DEFAULT_TOPIC));
    topicLabel = new QLabel(tr("Topic: "), topicEdit);
    layout->addWidget(topicLabel, 1, 0);
    layout->addWidget(topicEdit, 1, 1);

    queueEdit = new QLineEdit(QString::fromStdString(DEFAULT_QUEUE_SIZE));
    queueLabel = new QLabel(tr("Number of Messages: "), queueEdit);
    layout->addWidget(queueLabel, 2, 0);
    layout->addWidget(queueEdit, 2, 1);

    // queueBox = new QDoubleSpinBox();
    // queueBox->setRange(1, 8);
    // queueBox->setSingleStep(1);
    // queueBox->setDecimals(0);
    // queueBox->setValue(DEFAULT_QUEUE_SIZE2);
    // queueLabel2 = new QLabel(tr("Number of Messages"));
    // layout->addWidget(queueLabel2, 5, 0);
    // layout->addWidget(queueBox, 5, 1);

    dirBox = new QCheckBox(tr("Message Direction: Down"), this);
    dirBox->setChecked(true);
    layout->addWidget(dirBox, 3, 0, 1, 2);

    cancelButton = new QPushButton(tr("Cancel"));
    layout->addWidget(cancelButton, 4, 0);

    okButton = new QPushButton(tr("OK"));
    okButton->setDefault(true);
    layout->addWidget(okButton, 4, 1);

    setLayout(layout);

    QObject::connect(okButton, SIGNAL(clicked()), SLOT(onOK()));
    QObject::connect(cancelButton, SIGNAL(clicked()), SLOT(reject()));
 }

void NotificationDialog::onOK(void)
{
    Json::Value & settings = parent->getSettingsValue();

    settings["name"] = nameEdit->text().toStdString();

    static_cast<insitu_plugins::Notification*>(parent)->onTopicChange(
        topicEdit->text().toStdString());
    settings["topic"] = topicEdit->text().toStdString();

    int queue_size;
    try {
        queue_size = std::stoul(queueEdit->text().toStdString());
        if (queue_size < 1) {
            throw std::invalid_argument("received negative value");
        }
    }
    catch (const std::invalid_argument& e) {
        queue_size = std::stoul(DEFAULT_QUEUE_SIZE);
        error_msg->showMessage(
            "Unable to read Number of Messages value, using default");
    }
    static_cast<insitu_plugins::Notification*>(parent)->onQueueChange(
        queue_size);
    settings["queue_size"] = queue_size;

    static_cast<insitu_plugins::Notification*>(parent)->onDirectionChange(
        dirBox->isChecked());
    settings["msg_direction_down"] = dirBox->isChecked();

    accept();
}

} // end namespace insitu_plugins
