#include "mainWidget.h"

MainWidget::MainWidget()
{
    /*
    QPushButton* _convertASCIIBtn;
    QPushButton* _resetBtn;
    QPushButton* _getInfoBtn;
    QPushButton* _testConnectionBtn;
    QPushButton* _readBtn;

    QLabel* _hostName;
    QLabel* _hostIP;
    QLabel* _IPAddressLabel;
    QLabel* _PortLabel;
    QLabel* _PLCReadVariableLabel_1;
    QLabel* _PLCReadValueLabel_1;
    QLabel* _PLCReadVariableLabel_2;
    QLabel* _PLCReadValueLabel_2;
    QLabel* _writingStatus;

    QComboBox* _connectFrameworkBox;
    QComboBox* _connectModuleBox;

    QLineEdit* _convertRequest;
    QLineEdit* _convertResponse;
    QLineEdit* _IPAddressInput;
    QLineEdit* _PortInput;
    QLineEdit* _PLCVariableInput_1;
    QLineEdit* _PLCVariableInput_2;
    QLineEdit* _PLCVariableInput_3;
    QLineEdit* _PLCValue_1;
    QLineEdit* _PLCValue_2;
    QLineEdit* _PLCValue_3;
    */

   _convertASCIIBtn = new QPushButton("Convert to ASCII");
   _resetBtn = new QPushButton("Reset");
   _getInfoBtn = new QPushButton("Get Info of host");
   _testConnectionBtn = new QPushButton("Test Connection");
   _readBtn = new QPushButton("Read manually");

   _hostName = new QLabel("host Name: ");
   _hostIP = new QLabel("host IP: ");
   _IPAddressLabel = new QLabel("IP Address");
   _PortLabel = new QLabel("Port");
   _PLCReadVariableLabel_1 = new QLabel("PLC Variables");
   _PLCReadValueLabel_1 = new QLabel("Values");
   _PLCReadVariableLabel_1 = new QLabel("PLC Variables");
   _PLCReadValueLabel_2 = new QLabel("Values");
   _writingStatus = new QLabel("Status");
}

MainWidget::~MainWidget()
{

}