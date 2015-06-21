#ifndef ADDER_H
#define ADDER_H

#include "adder_global.h"

#include <plugin_interface.h>
#include <QObject>

class ADDERSHARED_EXPORT Adder : public QObject, public ISimplePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "PatternRecognizer.ISimplePlugin" FILE "adderplugin.json")
    Q_INTERFACES(ISimplePlugin)
public:
    Adder() { }
    virtual int operation(const int& a, const int& b) const {
        return a + b;
    }
};

#endif // ADDER_H
