#ifndef PRK5TR_H
#define PRK5TR_H
	#include "Stream.h"

	class PRK5TR
	{
	public:
	  static const uint16_t SINGLE_RESPONSE_TIME = 500;
	  struct DATA {
		uint16_t SOILMS;
		uint16_t SOILTP;
 		uint16_t SOILEC;
		uint16_t SOILPH;
		uint16_t SOIL_N;
		uint16_t SOIL_P;
		uint16_t SOIL_K;
	  };

	  PRK5TR(Stream&);
	  bool getEC(DATA& data);
	  bool getMS(DATA& data);
	  bool getTP(DATA& data);
	  bool getPH(DATA& data);
	  bool getN(DATA& data);
	  bool getP(DATA& data);
	  bool getK(DATA& data);
	  bool getALL(DATA& data);
	  void setID(uint8_t ID);

	private:
	  enum STATUS { STATUS_WAITING, STATUS_OK};
	  enum MODE { g_MS,g_TP,g_EC,g_PH,g_N, g_P, g_K, g_ALL };

	  uint8_t recvPacketLen(byte buf[]);
	  uint8_t sentDataLen(byte buf[]);
	  void showCMD(byte buf[], int len);
	  void RTU_CRC(byte buf[], int len, uint8_t *LB, uint8_t *HB);
	  
	  uint8_t _payload[19];				// For data 11 bytes MAX.
	  uint8_t _result[14];
	  Stream* _stream;
	  DATA* _data;
	  STATUS _status;
	  MODE _mode = g_N;

	  uint8_t _index = 0;
	  uint8_t _recvLen = 0;				// Size of data N-th
	  uint8_t a_ID = 0x01;				// Default Slave address
	  uint16_t _frameLen;				// Data read from slave
	  uint16_t _checksum;
	  uint16_t _calculatedChecksum;

	  void loop();
	  void killArray();
	  void showMSG();
	};
#endif