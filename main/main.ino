#include <SPI.h>
#include <SD.h>
#include <DHT.h>
#include <DHT_U.h>

#define TAHPIN A0
#define CSPIN 4
#define DHTTYPE DHT11
#define BUFFER 20
#define FILE_NAME "file.csv"
#define SLEEP_TIME_IN_MS 60000UL


class TempAndHum {
private:
  DHT* dht;

public:
  TempAndHum(DHT& sensor)
    : dht(&sensor) {}

  void begin() {
    dht->begin();
  }

  float getTemperature() {
    return dht->readTemperature();
  }

  float getHumidity() {
    return dht->readHumidity();
  }

  void logTemperature() {
    Serial.print("Temperature is: ");
    Serial.print(getTemperature());
    Serial.print(" *C\n");
  }

  void logHumidity() {
    Serial.print("Humidity is: ");
    Serial.print(getHumidity());
    Serial.print(" %\n");
  }
};

class Storage {
private:
  File openFile(char* fileName) {
    File openedFile = SD.open(fileName, FILE_WRITE);
    if (!openedFile) {
      Serial.println("Opening the file failed :(");
      return;
    };
    return openedFile;
  };

public:

  void begin() {
    pinMode(CSPIN, OUTPUT);
    Serial.println("CS pin set to output");

    if (!SD.begin(CSPIN)) {
      Serial.println("Failed initialization of SD!");
      while (1)
        ;
    };

    Serial.println("Succesfull initialization");
  }

  void writeToFile(char* stringToWrite, char* fileName) {
    File file = openFile(fileName);
    if (file) {
      Serial.print("Printing to file: ");
      Serial.println(stringToWrite);
      file.println(stringToWrite);
      file.close();
    } else {
      Serial.println("Writing to the file was not successfull :/");
    };
  };
};



DHT dht(TAHPIN, DHTTYPE);
TempAndHum tempAndHum(dht);
File myFile;
Storage storage;
unsigned long myTime;

void setup() {
  Serial.begin(9600);
  while (!Serial) { ; };

  tempAndHum.begin();


  storage.begin();
  myTime = millis();
}

bool hasWrittenHeader = 0;


void loop() {
  if (millis() - myTime >= SLEEP_TIME_IN_MS) {
    Serial.println("Waking up after sleep!");
    myTime = millis();

    if (!hasWrittenHeader) {
      char header[30] = "temp in C, humidity in %\0";
      storage.writeToFile(header, FILE_NAME);
      hasWrittenHeader = 1;
      Serial.println("Here");
    };

    float temp = tempAndHum.getTemperature();
    float humidity = tempAndHum.getHumidity();

    char resultTemp[BUFFER];
    char resultHumidity[BUFFER];
    char row[50] = { 0 };
    dtostrf(temp, 5, 2, resultTemp);
    dtostrf(humidity, 5, 2, resultHumidity);
    strcat(row, resultTemp);
    strcat(row, ",\0");
    strcat(row, resultHumidity);

    storage.writeToFile(row, FILE_NAME);
    row[0] = { 0 };
  } else {
  }
}
