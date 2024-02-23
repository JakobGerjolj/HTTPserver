#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QHttpServer>
#include <QHttpServerResponse>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>


void startHttpServer(QHttpServer* s){
    s->route("/", []() {

        return "Hello world";
    });

    s->route("/start", [](){
        qDebug() << "START";
        return "Starting TEST!";


    } );

    s->route("/getResult", [] {

        qDebug() << "GET RESULT";
        qDebug() <<"JSON result: ";


        QJsonObject so={
                {"key1", "1"},
                {"key2", "2"},
                {"key3", "3"}


        };
        qDebug()<<so;
        return so;
    });

    const auto port = s->listen(QHostAddress::Any);
    qInfo().noquote()
        << QCoreApplication::translate("QHttpServerExample",
                                       "Running on http://127.0.0.1:%1/"
                                       "(Press CTRL+C to quit)").arg(port);


}


int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/HTTPserver/Main.qml"_qs);
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.load(url);

    QHttpServer httpServer;
    startHttpServer(&httpServer);


    return app.exec();
}




