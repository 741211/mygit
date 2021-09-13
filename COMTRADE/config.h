#ifndef CONFIG_H
#define CONFIG_H
#include <QMetaType>
#include<QString>
struct A{
    int an;
    QString ch_id;//通道名称
    QString ph;//通道相位特征
    QString ccbm;
    QString uu;//单位
    double a;
    double b;
    double skew;
    int min;
    int max;
    double primary;
    double secondary;
    QString ps;
};

struct D{
    int dn;
    QString ch_id;
    QString ph;
    QString ccbm;
    bool y;
};
struct Nrate{
    double samp;
    long long  endsamp;
};
struct FirstTime{
    QString date1;
    QString date2;
};
struct SecondTime{
    QString date1;
    QString date2;
};
Q_DECLARE_METATYPE(A)
Q_DECLARE_METATYPE(D)
Q_DECLARE_METATYPE(Nrate)
Q_DECLARE_METATYPE(FirstTime)
Q_DECLARE_METATYPE(SecondTime)
class Config{
public:
    Config();
    //Config(const Config &other);
    ~Config();
    QString station_name;
    QString rec_dev__id;
    int rev_year;
    int TT;
    int Anum;
    int Dnum;
    A as[999999];
    D ds[999999];
    double IF;
    int nrates;
    Nrate nrate[999];
    FirstTime firstTime;
    SecondTime secondTime;
    QString ft;
    double timemult;
    double waveLength;
};

#endif // CONFIG_H
