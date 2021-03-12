#include "usboperation.h"
#include <QThread>
#include <QDebug>

hid_device *usb_handle = nullptr;

int UsbOperation::DevConnect()
{
    hid_device *handle = nullptr;
    int SeekCount = 10;

    while (handle == nullptr)
    {
        handle = hid_open(0x0416, 0x1200, NULL);

        if (handle != nullptr) { break; }

        handle = hid_open(0x0416, 0x1100, NULL);
        if (handle != nullptr) { break; }

        handle = hid_open(0x0416, 0x1101, NULL);
        if (handle != nullptr) { break; }

        handle = hid_open(0x0416, 0x1102, NULL);
        if (handle != nullptr) { break; }

        handle = hid_open(0x0416, 0x1103, NULL);
        if (handle != nullptr) { break; }

        if(SeekCount < 1) { break; }

        SeekCount --;
        QThread::msleep(50);
    }

    if(handle == nullptr)
    {
        //        ui->plainTextEdit->appendPlainText("ERROR! Compatible device not found.2");
        qDebug()<< SeekCount<<"handle == nullptr";
        return 1;
    }else {
        //        ui->plainTextEdit->appendPlainText("Device connected.");
        qDebug()<< SeekCount<< "handle != nullptr";
        usb_handle = handle;
//        mhid = usb_handle;
        return 0;
    }
}

int UsbOperation::clearUsb()
{
    unsigned char buf[512];
    int res;

    if (usb_handle == NULL)
    {
        return 2;
    }

    memset(buf, 0, 64);
    res = hid_read_timeout(usb_handle, buf, 64, 10);

    if (res < 1)
    {
        return res;
    }
    else {
        return 1;
    }
}

int UsbOperation::usb_read_page(unsigned char *pgbuf)
{
    unsigned char buf[512];
    int res;

    if (usb_handle == nullptr) {
        qDebug()<<"Invalid USB handle";
        return 2;
    }

    int idx = 0;
    while (true)
    {
        memset(buf, 0, 64);
        res = hid_read(usb_handle, buf, 64);
        if (res > 3)
        {
            if (idx == 0)
            {
                if (buf[1] == 0xFE)
                {
                    for (int i = 0; i < 61; i++) {
                        pgbuf[i] = buf[3 + i];
                    }
                    idx = 61;
                }
            }
            else {
                if (buf[1] == 0x7E)
                {
                    memcpy(&pgbuf[idx], &buf[2], 62);
                    idx += 62;
                }
                else if (buf[1] <= 62)
                {
                    memcpy(&pgbuf[idx], &buf[2], buf[1]);
                    idx += buf[1];
                    return idx;
                }
            }
        }
    }
    return 0;
}

unsigned char *UsbOperation::usb_send_read(std::initializer_list<unsigned char> list)
{
    static unsigned char buf[512];
    int i = 2;

    memset(buf, 0, 64);

    buf[0] = 0x01;
    buf[1] = 0x80 + list.size();
    for (auto elem : list)
    {
        buf[i++] = elem;
    }

    hid_write(usb_handle, buf, 64);

    memset(buf, 0, 64);
    hid_read(usb_handle, buf, 64);

    return buf;
}

void UsbOperation::usb_send(std::initializer_list<unsigned char> list)
{
    static unsigned char buf[512];
    int i = 2;

    memset(buf, 0, 64);

    buf[0] = 0x01;
    buf[1] = 0x80 + list.size();
    for (auto elem : list)
    {
        buf[i++] = elem;
    }

    hid_write(usb_handle, buf, 64);

    return;
}
