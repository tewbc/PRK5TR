#include "Arduino.h"
#include "PRK5TR.h"

PRK5TR::PRK5TR(Stream& stream)
{
  this->_stream = &stream;
}

void PRK5TR::setID(uint8_t ID)
{
	a_ID = ID;
}

bool PRK5TR::getMS(DATA& data)
{
  uint8_t command[] = { 0x01,0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x0A };
  RTU_CRC(command, 6, &command[6], &command[7]);
  _recvLen = sentDataLen(command);
  _stream->write(command, sizeof(command));
  delay(100);
  _mode = g_MS;
  _index = 0;
  _data = &data;
  uint16_t timeout = SINGLE_RESPONSE_TIME;
  uint32_t start = millis();
  do
  {
    loop();
    if (_status == STATUS_OK) 
		break;
  } while (millis() - start < timeout);
  killArray();
  return _status == STATUS_OK;
}

bool PRK5TR::getTP(DATA& data)
{
  uint8_t command[] = { 0x01,0x03, 0x00, 0x01, 0x00, 0x01, 0xD5, 0xCA };
  RTU_CRC(command, 6, &command[6], &command[7]);
  _recvLen = sentDataLen(command);
  _stream->write(command, sizeof(command));
  delay(100);
  _mode = g_TP;
  _index = 0;
  _data = &data;
  uint16_t timeout = SINGLE_RESPONSE_TIME;
  uint32_t start = millis();
  do
  {
    loop();
    if (_status == STATUS_OK) 
		break;
  } while (millis() - start < timeout);
  killArray();
  return _status == STATUS_OK;
}

bool PRK5TR::getEC(DATA& data)
{
  uint8_t command[] = { 0x01,0x03, 0x00, 0x02, 0x00, 0x01, 0x25, 0xCA };
  RTU_CRC(command, 6, &command[6], &command[7]);
  _recvLen = sentDataLen(command);
  _stream->write(command, sizeof(command));
  delay(100);
  _mode = g_EC;
  _index = 0;
  _data = &data;
  uint16_t timeout = SINGLE_RESPONSE_TIME;
  uint32_t start = millis();
  do
  {
    loop();
    if (_status == STATUS_OK) 
		break;
  } while (millis() - start < timeout);
  killArray();
  return _status == STATUS_OK;
}

bool PRK5TR::getPH(DATA& data)
{
  uint8_t command[] = { 0x01,0x03, 0x00, 0x03, 0x00, 0x01, 0x74, 0x0A };
  RTU_CRC(command, 6, &command[6], &command[7]);
  _recvLen = sentDataLen(command);
  _stream->write(command, sizeof(command));
  delay(100);
  _mode = g_PH;
  _index = 0;
  _data = &data;
  uint16_t timeout = SINGLE_RESPONSE_TIME;
  uint32_t start = millis();
  do
  {
    loop();
    if (_status == STATUS_OK) 
		break;
  } while (millis() - start < timeout);
  killArray();
  return _status == STATUS_OK;
}

bool PRK5TR::getN(DATA& data)
{
  uint8_t command[] = { 0x01,0x03, 0x00, 0x04, 0x00, 0x01, 0xC5, 0xCB };
  RTU_CRC(command, 6, &command[6], &command[7]);
  _recvLen = sentDataLen(command);
//  showCMD(command, sizeof(command));
  _stream->write(command, sizeof(command));
  delay(100);
  _mode = g_N;
  _index = 0;
  _data = &data;
  uint16_t timeout = SINGLE_RESPONSE_TIME;
  uint32_t start = millis();
  do
  {
    loop();
    if (_status == STATUS_OK) 
		break;
  } while (millis() - start < timeout);
  killArray();
  return _status == STATUS_OK;
}

bool PRK5TR::getP(DATA& data)
{
  uint8_t command[] = { 0x01,0x03, 0x00, 0x05, 0x00, 0x01, 0x94, 0x0B };
  RTU_CRC(command, 6, &command[6], &command[7]);
  _recvLen = sentDataLen(command);
  _stream->write(command, sizeof(command));
  delay(100);
  _mode = g_P;
  _index = 0;
  _data = &data;
  uint16_t timeout = SINGLE_RESPONSE_TIME;
  uint32_t start = millis();
  do
  {
    loop();
    if (_status == STATUS_OK) 
		break;
  } while (millis() - start < timeout);
/*
	Serial.print("P: ");
	showMSG();
*/
  killArray();
  return _status == STATUS_OK;
}

bool PRK5TR::getK(DATA& data)
{
  uint8_t command[] = { 0x01,0x03, 0x00, 0x06, 0x00, 0x01, 0x64, 0x0B };
  RTU_CRC(command, 6, &command[6], &command[7]);
  _recvLen = sentDataLen(command);
  _stream->write(command, sizeof(command));
  delay(100);
  _mode = g_K;
  _index = 0;
  _data = &data;
  uint16_t timeout = SINGLE_RESPONSE_TIME;
  uint32_t start = millis();
  do
  {
    loop();
    if (_status == STATUS_OK) 
		break;
  } while (millis() - start < timeout);
/*
	Serial.print("K: ");
	showMSG();
*/
  killArray();
  return _status == STATUS_OK;
}

bool PRK5TR::getALL(DATA& data)
{
  uint8_t command[] = { 0x01, 0x03, 0x00, 0x00, 0x00, 0x07, 0x04, 0x08 };
  RTU_CRC(command, 6, &command[6], &command[7]);
  _recvLen = sentDataLen(command);
  _stream->write(command, sizeof(command));
  delay(100);
  _mode = g_ALL;
  _index = 0;
  _data = &data;
  uint16_t timeout = SINGLE_RESPONSE_TIME;
  uint32_t start = millis();
  do
  {
    loop();
    if (_status == STATUS_OK) 
		break;
  } while (millis() - start < timeout);
 /* 
	Serial.print("NPK: ");
	showMSG();
*/	  
  killArray();
  return _status == STATUS_OK;
}

void PRK5TR::loop() {
	 _status = STATUS_WAITING;
	if (_stream->available()) {
		uint8_t ch = _stream->read();
		_payload[_index] = ch;
		switch (_index) {
		case 0:
		  if (ch != a_ID) {
			return;
		  }
		  break;
		case 1:
		  if (ch != 0x03) {
			_index = 0;
			return;
		  }
		  break;
		case 2:
		  _frameLen = ch;
		  if(_frameLen != _recvLen){
			_index = 0;
			return;
		  }
		  break;
		default: {
			double Y_MS,Y_TP,Y_EC,Y_PH,Y_N, Y_P, Y_K = 0.0000f;
			if(_index == _recvLen + 4 )  // position of last byte
			{
				uint8_t _LSB = 0;
				uint8_t _MSB = 0;
				RTU_CRC(_payload, _recvLen + 3, &_LSB, &_MSB);
				_checksum           = makeWord(_payload[_recvLen+3], _payload[_recvLen+4]);
				_calculatedChecksum = makeWord(_LSB, _MSB);
				if (_calculatedChecksum == _checksum) {
					_status = STATUS_OK;
					switch (_mode){
					case g_MS:
						_data->SOILMS   = makeWord(_result[0], _result[1]);
						Y_MS = _data->SOILMS;
						_data->SOILMS = (uint16_t)Y_MS;
				    break;
					case g_TP:
						_data->SOILTP   = makeWord(_result[0], _result[1]);
						Y_TP = _data->SOILTP;
						_data->SOILTP = (uint16_t)Y_TP;
				    break;
					case g_EC:
						_data->SOILEC   = makeWord(_result[0], _result[1]);
						Y_EC = _data->SOILEC;
						_data->SOILEC = (uint16_t)Y_EC;
				    break;
					case g_PH:
						_data->SOILPH   = makeWord(_result[0], _result[1]);
						Y_PH = _data->SOILPH;
						_data->SOILPH = (uint16_t)Y_PH;
				    break;
					case g_N:
						_data->SOIL_N   = makeWord(_result[0], _result[1]);
						Y_N = (-0.00006579082*(_data->SOIL_N^4))+(0.017572425*(_data->SOIL_N^3))+(-1.734044423*(_data->SOIL_N^2))+(74.85391835*_data->SOIL_N)-1161.253647;
						_data->SOIL_N = (int)Y_N;
					  break;
					case g_P:
						_data->SOIL_P  = makeWord(_result[0], _result[1]);
						Y_P = (-0.00000943138*(_data->SOIL_P^4))+(0.003681183*(_data->SOIL_P^3))+(-0.525996162*(_data->SOIL_P^2))+(32.65077477*_data->SOIL_P)-704.1543286;
						_data->SOIL_P = (int)Y_P;
					  break;
					case g_K:
						_data->SOIL_K = makeWord(_result[0], _result[1]);
						Y_K = (-0.00000015821*(_data->SOIL_K^4))+(0.000125045*(_data->SOIL_K^3))+(-0.035897927*(_data->SOIL_K^2))+(4.387916011*_data->SOIL_K)+35.42507285;
						_data->SOIL_K = (int)Y_K;
					  break;
					case g_ALL:
						_data->SOILMS   = makeWord(_result[0], _result[1]);
						Y_MS = _data->SOILMS;
						_data->SOILMS = (uint16_t)Y_MS;
						_data->SOILTP   = makeWord(_result[2], _result[3]);
						Y_TP = _data->SOILTP;
						_data->SOILTP = (uint16_t)Y_TP;
						_data->SOILEC   = makeWord(_result[4], _result[5]);
						Y_EC = _data->SOILEC;
						_data->SOILEC = (uint16_t)Y_EC;
						_data->SOILPH   = makeWord(_result[6], _result[7]);
						Y_PH = _data->SOILPH;
						_data->SOILPH = (uint16_t)Y_PH;
						_data->SOIL_N   = makeWord(_result[8], _result[9]);
						Y_N = (-0.00006579082*(_data->SOIL_N^4))+(0.017572425*(_data->SOIL_N^3))+(-1.734044423*(_data->SOIL_N^2))+(74.85391835*_data->SOIL_N)-1161.253647;
						_data->SOIL_N = (int)Y_N;
						_data->SOIL_P  = makeWord(_result[10], _result[11]);
						Y_P = (-0.00000943138*(_data->SOIL_P^4))+(0.003681183*(_data->SOIL_P^3))+(-0.525996162*(_data->SOIL_P^2))+(32.65077477*_data->SOIL_P)-704.1543286;
						_data->SOIL_P = (int)Y_P;
						_data->SOIL_K = makeWord(_result[12], _result[13]);
						Y_K = (-0.00000015821*(_data->SOIL_K^4))+(0.000125045*(_data->SOIL_K^3))+(-0.035897927*(_data->SOIL_K^2))+(4.387916011*_data->SOIL_K)+35.42507285;
						_data->SOIL_K = (int)Y_K;
					  break;
					}	//switch (_mode)
				}	// if (_calculatedChecksum == _checksum)
			} else if(_index != _frameLen + 3) {
				uint8_t payloadIndex = _index - 3;
				if (payloadIndex < sizeof(_result))
					_result[payloadIndex] = ch;
			}	// if(_index == _recvLen + 4 )
		}	// switch (_index)
  }		// if (_stream->available())
  _index++;
}

uint8_t PRK5TR::recvPacketLen(byte buf[]) {
	return buf[2];
}

uint8_t PRK5TR::sentDataLen(byte buf[]) {
	return buf[5] * 2;
}

void PRK5TR::showCMD(byte buf[], int len) {
	for (int i = 0; i < len; i++) {
	  Serial.print(buf[i], HEX);
	  if(i < len - 1)
		Serial.print(", ");
	}
	Serial.println();
}
void PRK5TR::killArray() {
	memset(_payload, 0, sizeof(_payload));
	memset(_result, 0, sizeof(_result));
}

void PRK5TR::showMSG() {
  for(uint8_t i = 0; i < sizeof(_payload); i++) {
	  Serial.print(_payload[i], HEX);
	  if(i < sizeof(_payload)-1)
		Serial.print(", ");
  }
  Serial.print(" ANS: ");
  for(uint8_t i = 0; i < sizeof(_result); i++) {
	  Serial.print(_result[i], HEX);
	  if(i < sizeof(_payload)-1)
		Serial.print(", ");
  }	  
  Serial.println();
}

void PRK5TR::RTU_CRC(byte buf[], int len, uint8_t *LB, uint8_t *HB) {
/*
	len       = length of Addr+Func+[Ret.Number]+COMMAND - 2bytes (CRC-CHECK)
	*LB / *HB = Position in array of command's sent or receieved
*/
  uint16_t crc = 0xFFFF;
  for (int pos = 0; pos < len; pos++) {
    crc ^= (uint16_t)buf[pos];          // XOR byte into least sig. byte of crc
    for (int i = 8; i != 0; i--) {      // Loop over each bit
      if ((crc & 0x0001) != 0) {        // If the LSB is set
        crc >>= 1;                      // Shift right and XOR 0xA001
        crc ^= 0xA001;
      } else                            // Else LSB is not set
        crc >>= 1;                      // Just shift right
    }
  }
  // Note, this number has low and high bytes swapped, so use it accordingly (or swap bytes)
  *HB = (crc & 0xFF00) >> 8;
  *LB =  crc & 0x00FF; 
/*
    Serial.printf("LB:%02X HB:%02X\n", *LB, *HB);
*/
}