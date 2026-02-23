#include <Latte/Geometry/FooGeometry.h>
#include <QDebug>

int main(int argc, char *argv[]){
    FooGeometry foo(
        {1,1},
        {2,2}
    );

    qDebug() << foo.p1;

    return 0;
}