#include <stdio.h>


#define BUFFER_SIZE 10 // ringBuffer size
#define EEPROM_WRITE_TIMES 3 // EEPROM retry times

bool bufferFull = false; // ringBuffer full or not; 0-notFull, 1-full
int ringBuffer[BUFFER_SIZE];
int writeIndex = 0; // ringBuffer index
int initOnce = 0; //init peripheral one time

// peripheral init() already implemented
void initADC();
void initEEPROM();
int readTemperature();
bool writeEEPROM(int data[], int size);

// timer interrupt
void timerISR()
{
	if (bufferFull)
	{
		return;
	}

	int temp = readTemperature();
	ringBuffer[writeIndex] = temp;
	writeIndex ++;

	if (writeIndex == 10)
	{
		bufferFull = true;
		writeIndex = 0;
	}
}

void handleMissingTemperature(int *data, int minTemp, int maxTemp, int size)
{
	int missIndex = 0;
	int dataSum = 0;
	int Sum = (minTemp + maxTemp) * size / 2;

	for (int i = 0; i < size; i ++)
	{
		if (data[i] >= minTemp) && (data[i] <= maxTemp)
		{
			dataSum += data[i];
		}
		else
		{
			missIndex = i;
		}
	}
	data[i] = Sum - dataSum;
}

void logCorrectedTemperatureData(int interval, int dataSize, int minTemp, int maxTemp)
{
	if (initOnce == 0)
	{
		initADC();
		initEEPROM();
		initTimer1_ISR(interval);
		initOnce = 1;
	}

	while (bufferFull == false)
	{
		;
	}

	handleMissingTemperature(ringBuffer, minTemp, maxTemp, dataSize);

	int retry = 0;
	while ((writeEEPROM(ringBuffer, dataSize) == false) && (retry < EEPROM_WRITE_TIMES))
	{
		retry ++;
	}

	if (retry == EEPROM_WRITE_TIMES)
	{
		printf("EEPROM write failed\r\n");
	}
	else
	{
		printf("EEPROM write success\r\n");
	}

	bufferIndex = 0;
	bufferFull = false;
}