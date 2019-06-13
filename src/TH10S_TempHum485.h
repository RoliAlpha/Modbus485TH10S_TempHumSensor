#pragma once
#ifndef _TH10S_TempHum485_h
#define _TH10S_TempHum485_h
#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
//��ͬ���ӹ��ڡ�ModbusRTUComm(MySerial * port, long baud, byte slaveId);���С�port���Ķ��岻ͬ��
//mega2560�������HardwareSerial��lenoard ������� Serial_
#if defined (USBCON)
#define  MySerial Serial_
#else
#define  MySerial HardwareSerial 
#endif

#include<SensorBase.h>
#include"ModbusMaster.h"

class TH10S_TempHum485 :public SensorBase
{
public:
	TH10S_TempHum485(MySerial * port, long baud, byte slaveId);
	~TH10S_TempHum485();
	virtual int GetChnanelNum() override;
	virtual int Update() override;
	virtual float Read(int chanelNo) override;
	virtual int Write(int channelNo, float value, bool isAllowed = false) override;
private:
	float temp;//channelNo 0
	float humm;//channelNo 1
	int TH10SsensorAddress;//channelNo 2
	int TotalChannel = 3;//�����ܵ�channel����
	int result;//���ܽ��
	ModbusMaster node;//ʵ������վ�ڵ㣬�������Ϊ��վ��������Ϊ��վ
	Stream* _Myport;//���ڴ���
};


#endif // ! _TH10S_TempHum485_h
