// https://github.com/espressif/arduino-esp32


#include <BluetoothSerial.h>  //ESP32 bluetooth library https://github.com/espressif/arduino-esp32/tree/master/libraries/BluetoothSerial/examples

//Creation of the bluetooth object
BluetoothSerial SerialBT;

int TestInt = 7;

//Control for the bluetooth or serial enabled
int BluetoothEnabled = 1;
int SerialEnabled = 1;

void setup() {
  // put your setup code here, to run once:
  SerialBT.begin("ESP32 Device");  //Bluetooth device name
}

void loop() {
  // put your main code here, to run repeatedly:
  PrintMessage("Test Statement : "); //This will not print the message without an extra print added after
  PrintMessageLn(String(TestInt)); 
  delay(5000);
}

void PrintMessage(String Message) {  //Used to send outputs over both serial and IR, used to make other sections cleaner
  if (SerialEnabled == 1) {
    Serial.print(Message);
  }
  if (BluetoothEnabled == 1) {  //Doesnt print bluetooth message, only adds to buffer. Will be printed once the PrintMessageLn() command is used. Is due to library problems
    uint8_t buf[Message.length()];
    memcpy(buf, Message.c_str(), Message.length());
    SerialBT.write(buf, Message.length());
  }
}

void PrintMessageLn(String MessageLn) {  //Used to send outputs over both serial and IR, used to make other sections cleaner
  if (SerialEnabled == 1) {
    Serial.println(MessageLn);
  }
  if (BluetoothEnabled == 1) {  //Assembles the message, writes it to buffer then sends buffer
    uint8_t buf[MessageLn.length()];
    memcpy(buf, MessageLn.c_str(), MessageLn.length());
    SerialBT.write(buf, MessageLn.length());
    SerialBT.println();
  }
}


/* Can be stripped down to just these functions if you do not need syncronous

void PrintMessage(String Message) {  //Used to send outputs over both serial and IR, used to make other sections cleaner
    uint8_t buf[Message.length()];
    memcpy(buf, Message.c_str(), Message.length());
    SerialBT.write(buf, Message.length());
}

void PrintMessageLn(String MessageLn) {  //Used to send outputs over both serial and IR, used to make other sections cleaner
    uint8_t buf[MessageLn.length()];
    memcpy(buf, MessageLn.c_str(), MessageLn.length());
    SerialBT.write(buf, MessageLn.length());
    SerialBT.println();
}

*/
