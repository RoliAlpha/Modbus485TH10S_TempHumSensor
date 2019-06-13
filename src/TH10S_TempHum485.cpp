#include "TH10S_TempHum485.h"

TH10S_TempHum485::TH10S_TempHum485(MySerial * port, long baud, byte slaveId)
{
	this->_Myport = port;
	(*port).begin(baud);
	TH10SsensorAddress = slaveId;//initialize the TH10SsensorAddress
	node.begin(slaveId, *_Myport);
}

TH10S_TempHum485::~TH10S_TempHum485()
{
}

int TH10S_TempHum485::GetChnanelNum()
{
	return TotalChannel;
}

int TH10S_TempHum485::Update()
{
	//get temp
	result = node.readHoldingRegisters(0x0000, 0x0001);
	uint16_t _responseBuffer;
	_responseBuffer = node.getResponseBuffer(0);
	temp = _responseBuffer*0.1;
	//get humm
	result = node.readHoldingRegisters(0x0001, 0x0001);
	_responseBuffer = node.getResponseBuffer(0);
	humm = _responseBuffer*0.1;
	//get address
	result = node.readHoldingRegisters(0x0064, 0x0001);
	_responseBuffer = node.getResponseBuffer(0);
	TH10SsensorAddress = _responseBuffer;
	delay(100);//��ʱ0.1sΪ���Ǹ���SENSOR��ARDUINO���ӵ��շ�������һ����ʱ��
	return 0;
}

float TH10S_TempHum485::Read(int chanelNo)
{
	switch (chanelNo)
	{
	case 0:return temp;
		break;
	case 1:return humm;
		break;
	case 2:return TH10SsensorAddress;
		break;
	}
	
}

int TH10S_TempHum485::Write(int channelNo, float value, bool isAllowed)
{
	switch (channelNo)
	{
	case 0:return 0;
		break;
	case 1:return 0;
		break;
	case 2:
		if (isAllowed == true)
			node.writeSingleRegister(0x0064, value);//�޸�sensor��ַ
		return 0;
		break;
	}
}
