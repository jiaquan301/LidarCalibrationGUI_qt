#ifndef OPERATION_H
#define OPERATION_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFileDialog>
#include <QTextBrowser>
#include <QLineEdit>
#include <QInputDialog>
#include <QButtonGroup>
#include <QRadioButton>
#include <QComboBox>
#include <QTimer>

#include <math.h>
#include <iostream>
#include <fstream>

#include "include/dds_participant.h"
#include "include/dds_publisher.h"
#include "include/dds_subscriber.h"
#include "include/LaserScan.h"
#include "include/LaserScanPubSubTypes.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


class InputDataWindow: public QWidget{
    Q_OBJECT
public:
    InputDataWindow(QWidget *parent= 0);

    cmdrDDS::DdsParticipant mParticipant;
    cmdrDDS::DdsSubscriber<commander_robot_msg::LaserScan, commander_robot_msg::LaserScanPubSubType> subscriber_lidar1;
    cmdrDDS::DdsSubscriber<commander_robot_msg::LaserScan, commander_robot_msg::LaserScanPubSubType> subscriber_lidar2;
    QTimer *tmr1;
    QTimer *tmr2;

    double lidar1_angle[1080];
    double lidar1_range[1080];
    double lidar2_angle[1080];
    double lidar2_range[1080];

    std::vector<float> range1;
    std::vector<float> range2;

    bool have_lidar1;
    bool have_lidar2;


    std::string path_lidar1 = "/Desktop/LidarCalibrationGUI_qt/data/lidar1_data.txt";
    std::string path_lidar2 = "/Desktop/LidarCalibrationGUI_qt/data/lidar2_data.txt";
//    std::string path_lidar1 = "/CodeBase/LidarCalibrationGUI_qt/data/lidar1_data.txt";
//    std::string path_lidar2 = "/CodeBase/LidarCalibrationGUI_qt/data/lidar2_data.txt";

//    std::string path_lidar1 = "/yuchen/LidarCalibrationGUI_qt/data/lidar1_data.txt";
//    std::string path_lidar2 = "/yuchen/LidarCalibrationGUI_qt/data/lidar2_data.txt";


    // 控件部分
    QHBoxLayout *sourcelayout;
    QComboBox *car_version;
    QButtonGroup *data_source;
    QRadioButton *data_online;
    QRadioButton *data_offline;

    QVBoxLayout *inputDatalayout;
    QPushButton *inputData_lidar1;
    QPushButton *inputData_lidar2;
    QPushButton *initial_extrinsic;
    QPushButton *draw_data;
    QPushButton *clear_data;
    QPushButton *write_calibfile;

    QGridLayout *pathlayout;
    QLabel *inputData_lidar1path;
    QLabel *inputData_lidar1path_now;
    QLabel *inputData_lidar2path;
    QLabel *inputData_lidar2path_now;

    static void ReceiveMessage_fromlidar1(commander_robot_msg::LaserScan *message);
    static void ReceiveMessage_fromlidar2(commander_robot_msg::LaserScan *message);

signals:
    void UpdataCarVersion(int);
    void SendData_lidar1(bool, std::vector<float>);
    void SendData_lidar2(bool, std::vector<float>);
    void SendStatus_lidar1(bool);
    void SendStatus_lidar2(bool);

    void command_initialExtrinsic();
    void command_draw_byButton();
    void command_draw_byTimer();
    void command_clear();
    void command_enablebutton();
    void command_writeCalibFile();

private slots:
    void slotCurrentIndexChanged(int);
    void UpdateLidar1();
    void UpdateLidar2();
    void InputDataLidar1();
    void InputDataLidar2();
    void InitialExtrinsic();
    void DrawDataByButton();
    void DrawDataByTimer();
    void ClearData();
    void WriteCalibFile();
    void EnableButton();

};

class OperationWindow: public QWidget{
    Q_OBJECT
public:
    OperationWindow(QWidget *parent= 0);

    std::string path_calibFile_extrinsic_planner = "../LidarCalibrationGUI_qt/file/params2_ex.json";
    std::string path_calibFile_extrinsic_slam = "../LidarCalibrationGUI_qt/file/sensor_extrinsic.lua";
    std::string path_calibFile_intrinsic_slam = "../LidarCalibrationGUI_qt/file/sensor_intrinsic.json";


    std::string extrinsic_slam_content = "SENSOR_EXTRINSIC = {\n"\
        "    imu_extrinsic = {\n"\
        "        frame_id = \"imu\",\n"\
        "        trans_x = 0.,\n"\
        "        trans_y = 0.,\n"\
        "        trans_z = 0.,\n"\
        "        rotat_w = 1.,\n"\
        "        rotat_x = 0.,\n"\
        "        rotat_y = 0.,\n"\
        "        rotat_z = 0.,\n"\
        "    },\n"\
        "    odom_extrinsic = {\n"\
        "        frame_id = \"odom\",\n"\
        "        trans_x = 0.,\n"\
        "        trans_y = 0.,\n"\
        "        trans_z = 0.,\n"\
        "        rotat_w = 1.,\n"\
        "        rotat_x = 0.,\n"\
        "        rotat_y = 0.,\n"\
        "        rotat_z = 0.,\n"\
        "    },\n"\
        "    scan_1_extrinsic = {\n"\
        "        frame_id = \"scan_1\",\n"\
        "        trans_x = %f,\n"\
        "        trans_y = %f,\n"\
        "        trans_z = 0.,\n"\
        "        rotat_w = %f,\n"\
        "        rotat_x = 0.,\n"\
        "        rotat_y = 0.,\n"\
        "        rotat_z = %f,\n"\
        "    },\n"\
        "    scan_2_extrinsic = {\n"\
        "        frame_id = \"scan_2\",\n"\
        "        trans_x = %f,\n"\
        "        trans_y = %f,\n"\
        "        trans_z = 0.,\n"\
        "        rotat_w = %f,\n"\
        "        rotat_x = 0.,\n"\
        "        rotat_y = 0.,\n"\
        "        rotat_z = %f,\n"\
        "    },\n"\
        "    camera_1_extrinsic = {\n"\
        "        frame_id = \"camera_1\",\n"\
        "        trans_x = 0.,\n"\
        "        trans_y = 0.,\n"\
        "        trans_z = 0.,\n"\
        "        rotat_w = 1.,\n"\
        "        rotat_x = 0.,\n"\
        "        rotat_y = 0.,\n"\
        "        rotat_z = 0.,\n"\
        "    },\n"\
    "}\n";

    std::string intrinsic_slam_content = "{\n"\
    "  \"scan_1\":{\"angle_increment\": %f, \"mount_type\": %s },\n"\
    "  \"scan_2\":{\"angle_increment\": %f, \"mount_type\": %s }\n"\
    "}";

    int car_version; // 车型
    std::string lidar_installWay; // 雷达的安装方式
    double car_length; // 雷达在车长方向的距离
    double car_width; // 雷达在车宽方向的距离

    // 控件部分
    QVBoxLayout *operationlayout;
    QTextBrowser *command_record;
    int command_row;

    QButtonGroup *lidar_show;
    QRadioButton *lidarAll_show;
    QRadioButton *lidar1_show;
    QRadioButton *lidar2_show;

    QLabel *lidar1_increment;
    QLabel *lidar1_increment_now;
    QPushButton *lidar1_increment_set;
    QLabel *lidar2_increment;
    QLabel *lidar2_increment_now;
    QPushButton *lidar2_increment_set;

    QLabel *extrinsic_x;
    QLabel *extrinsic_x_now;
    QPushButton *x_set;
    QPushButton *x_subtract;
    QPushButton *x_add;

    QLabel *extrinsic_y;
    QLabel *extrinsic_y_now;
    QPushButton *y_set;
    QPushButton *y_subtract;
    QPushButton *y_add;

    QLabel *extrinsic_theta;
    QLabel *extrinsic_theta_now;
    QPushButton *theta_set;
    QPushButton *theta_subtract;
    QPushButton *theta_add;

    QLabel *dx;
    QLabel *dx_now;
    QPushButton *dx_set;
    QPushButton *dx_subtract;
    QPushButton *dx_add;

    QLabel *dy;
    QLabel *dy_now;
    QPushButton *dy_set;
    QPushButton *dy_subtract;
    QPushButton *dy_add;

    QLabel *dtheta;
    QLabel *dtheta_now;
    QPushButton *dtheta_set;
    QPushButton *dtheta_subtract;
    QPushButton *dtheta_add;
signals:
    void command_draw(std::string, std::string, double, double, double, double, double, double);
    void command_resetPicture();
private slots:
    void ReceiveStatus_carVersion(int);
    void ReceiveStatus_lidar1(bool);
    void ReceiveStatus_lidar2(bool);
    void InitialExtrinsic();
    void DrawDataByButton();
    void DrawDataByTimer();
    void DrawData();
    void DrawData(std::string);
    void WriteCalibFile();

    void DrawWhichLidar();

    void EnableButton();
    void DisableButton();

    void SetIncrement_lidar1();
    void SetIncrement_lidar2();
    void SetX();
    void SubtractX();
    void AddX();

    void SetY();
    void SubtractY();
    void AddY();

    void SetTheta();
    void SubtractTheta();
    void AddTheta();

    void SetDX();
    void SubtractDX();
    void AddDX();

    void SetDY();
    void SubtractDY();
    void AddDY();

    void SetDTheta();
    void SubtractDTheta();
    void AddDTheta();
};

#endif // OPERATIONWINDOW_H
