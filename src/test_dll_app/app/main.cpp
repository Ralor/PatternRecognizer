#include <QCoreApplication>
#include <QPluginLoader>
#include <QString>

#include <string>
#include <iostream>

#include <plugin_interface.h>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    cout<<"I need *.dll file name..."<<endl;
    string fileName;
    cin>>fileName;
    QPluginLoader loader(QString::fromStdString(fileName));
    QObject* plugin;
    if( loader.load() && (plugin = loader.instance()) ) {
        cout<<loader.metaData().value("name").toString().toStdString()<<endl;
        cout<<"Give me two ints..."<<endl;
        int a,b;
        cin>>a>>b;
        cout<<qobject_cast<ISimplePlugin*>(plugin)->operation(a,b)<<endl;
    } else {
        cout<<"Failed to load plugin : "<<loader.errorString().toStdString()<<endl;
    }
    return a.exec();
}
