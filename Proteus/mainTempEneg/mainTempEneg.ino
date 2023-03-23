/* Main.ino file generated by New Project wizard
 *
 * Created:   Thu Sep 5 2013
 * Processor: ATmega2560
 * Compiler:  Arduino AVR
 */

 /* Equipo 5
Juan Daniel Rodríguez Oropeza A01411625
Jorge Claudio González Becerril A01412375
Luis Angel Ramiro Amaro A01411763
Luis Carlos Olave Vera A01233810
*/
 
 // Pines A del Arduino
 int analogPin = A0;
 int currentPin = A1;
 int currentPin2 = A2;
 int currentPin3 = A3;
 
 // Pines de los LED
 int pinVel3 = 5; // Velocidad 3
 int pinVel2 = 6; // Velocidad 2
 int pinVel1 = 7; // Velocidad 1
 int pinApag = 8; // Apagado
 
 // Variables para la lectura de Voltaje y Corriente
 int sensitivity = 66;
 int adcValue = 0;
 int adcValue2 = 0;
 int adcValue3 = 0;
 int offsetVoltage = 2500;
 double adcVoltage = 0;
 double adcVoltage2 = 0;
 double adcVoltage3 = 0;
 double currentValue = 0;
 double currentValue2 = 0;
 double currentValue3 = 0;
 
void setup()
 { // put your setup code here, to run once:
   Serial.begin(9600);
   pinMode(pinVel3, OUTPUT);
   pinMode(pinVel2, OUTPUT);
   pinMode(pinVel1, OUTPUT);
   pinMode(pinApag, OUTPUT);
 }

void loop()
 { // put your main code here, to run repeatedly:
   // Lectura de Temperatura
   int a=analogRead(analogPin);
   int temp= a*4.88/10;
   Serial.print("Temperatura: ");
   Serial.print(temp);
   
   // Lectura de Voltaje y Corriente para Velocidad 3
   adcValue = analogRead(currentPin);
   adcVoltage = (adcValue / 1024.0) * 5000;
   currentValue = ((adcVoltage - offsetVoltage) / sensitivity);
   
   // Lectura de Voltaje y Corriente para Velocidad 2
   adcValue2 = analogRead(currentPin2);
   adcVoltage2 = (adcValue2 / 1024.0) * 5000;
   currentValue2 = ((adcVoltage2 - offsetVoltage) / sensitivity);
   
   // Lectura de Voltaje y Corriente para Velocidad 1
   adcValue3 = analogRead(currentPin3);
   adcVoltage3 = (adcValue3 / 1024.0) * 5000;
   currentValue3 = ((adcVoltage3 - offsetVoltage) / sensitivity);
   
   // Velocidad 3
   if (temp >= 30){
      digitalWrite(pinVel3, HIGH); // Velocidad 3
      digitalWrite(pinVel2, LOW); // Velocidad 2
      digitalWrite(pinVel1, LOW); // Velocidad 1
      digitalWrite(pinApag, LOW); // Apagado
      
      Serial.print("  Voltaje(mV) = ");
      Serial.print(adcVoltage, 3);
      
      Serial.print("  Corriente = ");
      Serial.print(currentValue, 3);
      
      Serial.println("  Status: Velocidad 3");
   }
   // Velocidad 2
   else if (temp >= 25 && temp < 30){
      digitalWrite(pinVel3, LOW); // Velocidad 3
      digitalWrite(pinVel2, HIGH); // Velocidad 2
      digitalWrite(pinVel1, LOW); // Velocidad 1
      digitalWrite(pinApag, LOW); // Apagado
      
      Serial.print("  Voltaje(mV) = ");
      Serial.print(adcVoltage2, 3);
      
      Serial.print("  Corriente = ");
      Serial.print(currentValue2, 3);
      
      Serial.println("  Status: Velocidad 2");
   }
   // Velocidad 1
   else if (temp >= 21 && temp < 25){
      digitalWrite(pinVel3, LOW); // Velocidad 3
      digitalWrite(pinVel2, LOW); // Velocidad 2
      digitalWrite(pinVel1, HIGH); // Velocidad 1
      digitalWrite(pinApag, LOW); // Apagado
      
      Serial.print("  Voltaje(mV) = ");
      Serial.print(adcVoltage3, 3);
      
      Serial.print("  Corriente = ");
      Serial.print(currentValue3, 3);
      
      Serial.println("  Status: Velocidad 1");
   }
   // Apagado
   else{
      digitalWrite(pinVel3, LOW); // Velocidad 3
      digitalWrite(pinVel2, LOW); // Velocidad 2
      digitalWrite(pinVel1, LOW); // Velocidad 1
      digitalWrite(pinApag, HIGH); // Apagado
      
      Serial.print("  Voltaje(mV) = 0");
      Serial.print("  Corriente (A)= 0");
      Serial.println("  Status: Apagado");
   }
 
   delay(2000);
 }
