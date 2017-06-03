#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>
#include <QDebug>
#include <QStringList>

#include "mythread.h"
#include "datastorage.h"

/**
 * @brief The MyServer class inicia um servidor TCP
 * capaz de "ouvir" a porta 1234
 */
class MyServer : public QTcpServer
{
  Q_OBJECT
public:
  /**
   * @brief MyServer é o construtor da classe
   * @param parent eh o pai do objeto (nao usado)
   */
  MyServer(QObject *parent = 0);
  /**
   * @brief StartServer start the TCP server
   */
  void startServer();
  /**
   * @brief getIPList return a list of IPs used by server
   * @return
   */
  QStringList getIPList();

signals:
  void message(QString);

public slots:
  void receiveMsg(QString str);

protected:
  /**
   * @brief incomingConnection decide o que fazer quando uma
   * nova conexao é iniciada
   * @param socketDescriptor é o identificador do socket para
   * a conexao
   */
  void incomingConnection(qintptr socketDescriptor);
private:
  int ok;
  /**
   * @brief storage eh usado como meio comum de armazenamento
   * de dados para diversas conexoes diferentes
   */
  DataStorage storage;
  QStringList iplist;
};

#endif // MYSERVER_H
