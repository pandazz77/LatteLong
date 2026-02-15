#include <QApplication>
#include <QCommandLineParser>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QTextBrowser>
#include <QMouseEvent>

#include "Latte/Graphics/View/MapGraphicsView.h"
#include "Latte/Graphics/View/Controls/ClickControl.h"
#include "Latte/Providers/GeoJsonProvider.h"
#include "Latte/Graphics/Items/GraphicsPath.h"

#include "ProjComboBox.hpp"

GeoJsonProvider provider;

void onGeoJsonOpen(MapGraphicsView *view, QString fileName){
    view->scene()->clear();
    GraphicsGroup *group = provider.fromFile(fileName);
    group->addTo(view);
}

class GeoJsonInspectControl: public ClickControl{
    public:
        using ClickControl::ClickControl;

        void setOutput(QTextBrowser *outputBrowser){
            output = outputBrowser;
        }

    protected:
        bool handleClick(const QPointF &scenePos) override{
            QPoint xy = view()->mapFromScene(scenePos);
            auto items = view()->items(xy);
            if(items.size()){
                QGraphicsItem *item = items[0];
                QVariantMap props = item->data(0).toMap();
                QJsonDocument doc = QJsonDocument::fromVariant(props);
                QByteArray jsonProps = doc.toJson(QJsonDocument::Indented);

                if(GraphicsPath *gpath = dynamic_cast<GraphicsPath*>(item)){
                    highlight(gpath);
                }

                if(output){
                    output->clear();
                    output->setText(QString::fromUtf8(jsonProps));
                }
            }

            return false;
        }

        // highlight GraphicsPath on scene
        void highlight(GraphicsPath *item){
            // restore previous
            if(lastPath){
                lastPath->setPen(lastPathPen);
                lastPath->update();
            }

            QPen pen = item->pen();
            lastPathPen = pen;
            lastPath = item;

            pen.setColor(Qt::red);
            pen.setWidth(5);
            item->setPen(pen);
            item->update();
        }

    private:
        QTextBrowser *output = nullptr;
        GraphicsPath *lastPath = nullptr;
        QPen lastPathPen;
};


int main(int argc, char *argv[]){
    QApplication app(argc,argv);

    QCommandLineParser parser;
    QCommandLineOption input_file_option(QStringList() << "i" << "input","geojson input file","input");
    parser.addOption(input_file_option);

    parser.process(app);

    QWidget *window = new QWidget;
    QHBoxLayout *mainLayout = new QHBoxLayout(window);
    window->resize(800,600);
    window->setLayout(mainLayout);
    QVBoxLayout *rightLayout = new QVBoxLayout(nullptr);

    MapGraphicsView *map = new MapGraphicsView();
    GeoJsonInspectControl *inspector = new GeoJsonInspectControl();
    map->addControl(inspector);

    mainLayout->addWidget(map);
    mainLayout->addLayout(rightLayout);

    rightLayout->addWidget(new ProjComboBox(map));
    QPushButton *selectFileBtn = new QPushButton("Select geojson file",window);
    rightLayout->addWidget(selectFileBtn);
    selectFileBtn->connect(selectFileBtn,&QPushButton::clicked,[&](){
        QString fileName = QFileDialog::getOpenFileName(window,"Open GeoJson file");
        if(fileName.isEmpty()) return;
        onGeoJsonOpen(map,fileName);
    });
    QTextBrowser *geojsonPropertiesBrowser = new QTextBrowser();
    inspector->setOutput(geojsonPropertiesBrowser);
    rightLayout->addWidget(geojsonPropertiesBrowser);
    // rightLayout->addStretch(1);

    if(parser.isSet(input_file_option)){
        QString filename = parser.value(input_file_option);
        onGeoJsonOpen(map,filename);
    }
   
    window->show();
    return app.exec(); 
}