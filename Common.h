#ifndef COMMON_H
#define COMMON_H

#include <QPoint>
#include <QString>
#include <vector>
#include <math.h>

using namespace std;

#define PI              3.1415926
#define MILVALUE_6000   6000
#define MILVALUE_65536  65536

#define RAD_TO_DEG(X)  ( (X) * 57.29577951 )
#define DEG_TO_RAD(X)  ( (X) * 0.017453293 )
#define POWER_X(X)      ( (X) * (X) )

#define IP_DATAPRO          "192.168.1.10"
#define IP_NPORT            "192.168.1.20"
#define IP_MOXA             "192.168.1.30"

#define PORT_RADARRECV          10002
#define PORT_CMDSEND            20001
#define PORT_VIDEOCTL           60002
#define PORT_INFRAREDCTL        60001
#define PORT_TURNTABLERECV      40003
#define PORT_TURNTABLESEND      60003

#define PORT_ANTITHUNDERRECV    40004
#define PORT_ANTITHUNDERSEND    60004

typedef struct
{
    double x;
    double y;
} TPointF;

typedef struct
{
    double dir;         //Degree
    double distance;    //Meter
} TPosition;

enum enumDataType  {EStatus, ETarget};
typedef struct
{
    enumDataType type;
    unsigned char statusType;
    unsigned short devID;
    unsigned char subSysNo;
    unsigned char cmdNo;
    unsigned short dataLen;
    unsigned char dataBuff[65536];
} TDataPacket;

typedef struct
{
    unsigned short ctsID;
    unsigned short ackNo;
    unsigned char subSysNo;
    unsigned char cmdNo;
    vector <unsigned char> param;
} TCmdInfo;

typedef struct
{
//    bool power;
    bool linkState;
    bool scanDir;
    bool scanState;
    bool scanMode;      //0 : 360度扫描 ； 1：扇形扫描
    double aziAngle;
    double pitAngle;
    int workMode;
    bool gpsState;
    double longitude;
    double latitude;    //雷达定位
    double northAngle;
    double tempreture;
    bool systemState;
    int freqCode;
    int systempStateCode;
    bool transmitState;
    QString radarSerial;
    bool manualLocation;    //人工标定位置标志，当人工定位时，此标志为true
//    double longitude_m;     //人工标定位置，当人工定位标志位true时，使用此位置
//    double latitude_m;
    double groundX;
    double groundY;
    int radarHeight;
} TRadarState;

enum    EnumTurnTableMode {ENUMAUTOPOLL, ENUMRADARLEAD, ENUMMANUALCTL, ENUMMANUALLEAD};
extern  EnumTurnTableMode enumTurnTable;
extern  bool flagInfrared;
extern double turntableNortAngle;
extern float DisRangeArrayMeter[];

#endif // COMMON_H
