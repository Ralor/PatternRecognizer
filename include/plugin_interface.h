#include <QtPlugin>

class ISimplePlugin {
public:
    virtual ~ISimplePlugin() { }
    virtual int operation(const int& a, const int& b) const = 0;
};

#define ISimplePlugin_iid "PatternRecognizer.ISimplePlugin"

Q_DECLARE_INTERFACE(ISimplePlugin, ISimplePlugin_iid)
