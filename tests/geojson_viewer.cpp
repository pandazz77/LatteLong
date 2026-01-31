#include <QApplication>
#include <QCommandLineParser>
#include <QHBoxLayout>

#include "MapGraphicsView.h"
#include "GeoJsonProvider.h"

#include "ProjComboBox.hpp"


int main(int argc, char *argv[]){
    QApplication app(argc,argv);

    QCommandLineParser parser;
    QCommandLineOption input_file_option(QStringList() << "i" << "input","geojson input file","input");
    parser.addOption(input_file_option);

    parser.process(app);

    QString filename = parser.value(input_file_option);

    QWidget *window = new QWidget;
    window->resize(800,600);
    window->setLayout(new QHBoxLayout(window));

    MapGraphicsView *map = new MapGraphicsView();
    window->layout()->addWidget(map);
    window->layout()->addWidget(new ProjComboBox(map));

    GraphicsGroup *group = GeoJsonProvider::fromFile(filename);
    group->addTo(map);

    window->show();
    return app.exec(); 
}