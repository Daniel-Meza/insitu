#ifndef insitu_FILTERED_VIEW_HPP
#define insitu_FILTERED_VIEW_HPP

// QT includes
#include <QtWidgets>

// ROS includes
#include <ros/ros.h>
#include <ros/master.h>
#include <sensor_msgs/Image.h>
#include <image_transport/image_transport.h>

// OpenCV includes
#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>

// insitu includes
#include "insitu_utils.hpp"

namespace insitu {

class FilteredView : public QWidget
{

Q_OBJECT
private:
    // UI elements
    QComboBox * topicBox;
    QPushButton * refreshTopicButton;
    QLabel * imgLabel;
    QScrollArea *imgPan;

    // layout elements
    QHBoxLayout * menuBar;
    QVBoxLayout * vBox;

    // ROS
    ros::NodeHandle nh;
    image_transport::Subscriber sub;
    void callbackImg(const sensor_msgs::Image::ConstPtr& msg);

    // OpenCV
    cv::Mat imgMat;

public Q_SLOTS:
    void onTopicChange(QString topic_transport);
    void refreshTopics(void);

public:
    FilteredView(QString _topic, QWidget * parent = nullptr);
    ~FilteredView(void);

};

} // end namespace insitu

#endif
