#include "myserver.h"
#include <QNetworkInterface>
MyServer::MyServer(QObject *parent) :
  QTcpServer(parent)
{

}

void MyServer::startServer(){
  if(!this->listen(QHostAddress::Any, 1234)){
    emit message(QString("<b>server did not start!</b>"));
  }
  else{
    emit message(QString("<b>server started!</b>"));
    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
      if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
        iplist << address.toString();
    }
  }
}

QStringList MyServer::getIPList(){
  return iplist;
}

void MyServer::receiveMsg(QString str){
  emit message(str);
}

void MyServer::incomingConnection(qintptr socketDescriptor){
  QString str;
  str = QString("<i>") + QString().setNum(socketDescriptor) +
      " connecting...</i>";
  emit message(str);
  MyThread *thread = new MyThread(socketDescriptor,this, &storage);
  // assegura que o objeto da thread será deletado quando a thread
  // for finalizada.
  connect(thread,SIGNAL(finished()), thread, SLOT(deleteLater()));

  // redireciona as mensagens enviadas pela thread para serem reemitidos
  // pelo servidor
  connect(thread,SIGNAL(message(QString)), this, SLOT(receiveMsg(QString)));
  thread->run();
}
