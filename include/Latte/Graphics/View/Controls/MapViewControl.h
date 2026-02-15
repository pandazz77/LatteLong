#pragma once

#include <QObject>
#include <QEvent>

class MapGraphicsView;

class MapViewControl: public QObject{
    public:
        MapViewControl(QObject *parent = nullptr);

        void setView(MapGraphicsView *view);
        void remove();
        MapGraphicsView *view();

    protected:
        virtual bool onViewEvent(QEvent *event);
        virtual bool onViewportEvent(QEvent *event);

    private:
        bool eventFilter(QObject *obj, QEvent *event) override final;
        MapGraphicsView *_view = nullptr;

    private:
        friend class MapGraphicsView;
        void assignView(MapGraphicsView *view);
};