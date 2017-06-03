#include "datastorage.h"
#include <QMutexLocker>
#include <QDebug>

struct RangeTest{
  qint64 limit;
public:
  RangeTest(qint64 _limit) { limit = _limit;}
  bool operator()(qint64 n){
    return n > limit;
  }
};

// constructor
DataStorage::DataStorage() : mutex(){
}

vector<Entry> DataStorage::getData(QHostAddress address, unsigned int lastn){
  // trabalhando aqui...


  vector<Entry> range;
  vector<Entry>::iterator vi;
  // locks the mutex so
  QMutexLocker ml(&mutex);
  dataIterator = data.find(address.toIPv4Address());
  if(dataIterator != data.end()){
    if(dataIterator.value().size() <= lastn){
      qDebug() << "passou dataiterator";
      return (dataIterator.value());
    }
    else{
      qDebug() << "entrou copy";
      qDebug() << "size = " << dataIterator.value().size();
      qDebug() << "distance = " << distance(dataIterator.value().end()-lastn, dataIterator.value().end());
      for(vi=dataIterator.value().end()-lastn; vi!=dataIterator.value().end(); vi++){
        range.push_back(*vi);
      }
      // do not copy until .end()! it will go out of the boundaries O.o
     // range.reserve(distance(dataIterator.value().end()-lastn, dataIterator.value().end()));
     // std::copy(dataIterator.value().end()-lastn, dataIterator.value().end(), range.begin());

      qDebug() << "passou copy = " << range.size();
      return (range);
    }
  }
  //copy_if(dataIterator.value().begin(), dataIterator.value().end(), back_inserter(range), RangeTest(startTime));
  // return(range);
  //return(dataIterator.value());
  else{
      return(vector<Entry>());
  }
}

void DataStorage::addData(QHostAddress address, qint64 time, float measurement){
  Entry entry;

  QMutexLocker ml(&mutex);

  entry.theTime = time;
  entry.measurement = measurement;
  dataIterator = data.find(address.toIPv4Address());
  if(dataIterator != data.end()){
  //  qDebug() << "passou: " << address.toIPv4Address() ;
    data[address.toIPv4Address()].push_back(entry);
  //  qDebug() << "data.size" << data[address.toIPv4Address()].size();
  }
  else{
    vector<Entry> start;
    start.push_back(entry);
    data.insert(address.toIPv4Address(), start);
  }
 // qDebug() << "saiu addData";
}

vector<QHostAddress> DataStorage::getHostList()
{
  vector<QHostAddress> hostList;
  QList<quint32> uintList;
  uintList = data.keys();
  for(int i=0; i<uintList.size(); i++){
    hostList.push_back(QHostAddress(uintList[i]));
  }
  return hostList;
}













