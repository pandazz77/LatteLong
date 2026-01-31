#include <QApplication>
#include "MapGraphicsView.h"
#include "GeoJsonProvider.h"
#include <QCommandLineParser>


int main(int argc, char *argv[]){
    QApplication app(argc,argv);

    QCommandLineParser parser;
    QCommandLineOption input_file_option(QStringList() << "i" << "input","geojson input file","input");
    parser.addOption(input_file_option);

    parser.process(app);

    QString filename = parser.value(input_file_option);

    MapGraphicsView *map = new MapGraphicsView();

    GraphicsGroup *group = GeoJsonProvider::fromFile(filename);
    group->addTo(map);

    map->show();
    return app.exec(); 
}