#ifndef VariableSettingsLIST_H
#define VariableSettingsLIST_H
#include "IfCore.h"

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QSet>
#include <QtCore/QSettings>

class QTimer;

#include "VariableSet.h"
#include "VariableSettings.h"

class IFCORE_EXPORT VariableSettingsList : public QObject
{
    Q_OBJECT

public:
    explicit VariableSettingsList(QObject * parent=0);
    ~VariableSettingsList();
    void add(VariableSettings * vsi);
    void add(QString string);
    void addTrigger(const VariableKey & key);
    bool isTrigger(const VariableKey & key);
    void setUpdateMsec(const int msec);
    void setUpdateRead(const bool readOnUpdate);
    bool contains(const VariableKey & key) const;
    VariableSettings * settings(const int index) const;
    void read(void);
    QVariant read(const VariableKey & key,
                  const QVariant & defaultValue=QVariant());
    void write(void) const;
    void write(const VariableKey & key, const QVariant & newValue);
    void set(const Variable & vbl);
    void set(const VariableKey & key, const QVariant & value);
    void setDefault(const Variable & vbl);
    void setDefault(const VariableKey & key, const QVariant & value);
    Variable at(const VariableKey & key) const;
    QVariant value(const VariableKey & key) const;
    VariableSet exportSection(const VariableKey & sectionKey) const;

signals:
    void started(void);
    void stopped(void);
    void triggered(QString key, QVariant value);

private slots:
    void update(void);

public slots:
    void start(void);
    void stop(void);

private:
    VariableSettings * mpDefault;
    QList<VariableSettings *> mSettingsList;
    QSet<VariableKey> mTriggerSet;
    int mUpdateMsec;
    bool mIsUpdateRead;
    QTimer * mpWatchTimer;
};

#endif // VariableSettingsLIST_H
