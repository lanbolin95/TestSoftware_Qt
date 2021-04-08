#ifndef USBOPERATION_H
#define USBOPERATION_H

#include <QMainWindow>
#include <QObject>
#include "hidapi.h"

using namespace std;
//class UsbOperation;

class UsbOperation : public QObject
{
    Q_OBJECT
public:
    UsbOperation(QObject *parent = 0);

    hid_device *mhid;
    unsigned char *usb_send_read(std::initializer_list<unsigned char> list);
    void usb_send(std::initializer_list<unsigned char> list);
    int usb_read_page(unsigned char* pgbuf);
    int DevConnect();
    int clearUsb();
    bool enlarge = false;
};

#endif // USBOPERATION_H
