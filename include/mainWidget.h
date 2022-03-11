#include <QtWidgets/QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    MainWidget(QObject* parent=nullptr);
    ~MainWidget();

private:
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

    // Layout
    QVBoxLayout* _vbox1;
    QVBoxLayout* _vbox2;
    QHBoxLayout* _hbox1;
};