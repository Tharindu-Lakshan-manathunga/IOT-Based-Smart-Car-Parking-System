 #include <SPI.h>  
 #include <MFRC522.h>  
 #include <Wire.h>   
 #include <LiquidCrystal_I2C.h> 
 #include <Servo.h> 
 #include <SoftwareSerial.h>
 
 #define SS_PIN 10  
 #define RST_PIN 9   
 //#define BUZZER 2

 SoftwareSerial nodemcu(0,1);
 LiquidCrystal_I2C lcd(0x27, 20, 4);  
 Servo myservo1;
 Servo myservo2;
 
 int pos1 = 90;
 int pos2 = 90; 
 int exit_gate = 4;

 

 int parking1_slot1_ir_s = 5; 
 int parking1_slot2_ir_s = 6;
 int parking1_slot3_ir_s = 7;
 int parking1_slot4_ir_s = 8;

 const float hourlyRate = 100; 

 String sensor1; 
 String sensor2; 
 String sensor3; 
 String sensor4;

 String cdata ="";
   
 MFRC522 mfrc522(SS_PIN, RST_PIN);   
 
        void setup()   
        {  
            Serial.begin(9600); 
            nodemcu.begin(9600); 
            SPI.begin();   
            mfrc522.PCD_Init();   
            lcd.init();   
            lcd.backlight(); 
   
            lcd.setCursor(3, 0);
            lcd.print("IOT Based Smart");
            lcd.setCursor(4, 1);
            lcd.print("Car Parking");
            lcd.setCursor(7, 2);
            lcd.print("System");
            delay(1000);
            lcd.clear();
            lcd.setCursor(2, 0);
            lcd.print("**Group Members**");
            lcd.setCursor(0, 2);
            lcd.print("1.Tharindu");
            lcd.setCursor(12, 2);
            lcd.print("2.Amath");
            lcd.setCursor(0, 3);
            lcd.print("3.Sahas");
            lcd.setCursor(12, 3);
            lcd.print("4.Shehan");
            delay(5000);
            lcd.clear();
            

            pinMode(exit_gate, INPUT);   
            //pinMode(BUZZER, OUTPUT);  
            //noTone(BUZZER);

            pinMode(parking1_slot1_ir_s, INPUT);
            pinMode(parking1_slot2_ir_s, INPUT);
            pinMode(parking1_slot3_ir_s, INPUT);
            pinMode(parking1_slot4_ir_s, INPUT);

            myservo1.attach(3);
            myservo2.attach(2);
        }  
        
        void loop()   
        {    
            gates();
            p1slot1(); 
            p1slot2();
            p1slot3(); 
            p1slot4();

            
            
            

            cdata = cdata + sensor1 +"," + sensor2 + ","+ sensor3 +","+ sensor4 + ","; // comma will be used a delimeter
            Serial.println(cdata); 
            nodemcu.println(cdata);
           delay(200); // 100 milli seconds
            cdata = ""; 

            digitalWrite(parking1_slot1_ir_s, HIGH); 
            digitalWrite(parking1_slot2_ir_s, HIGH); 
            digitalWrite(parking1_slot3_ir_s, HIGH);
            digitalWrite(parking1_slot4_ir_s, HIGH);

            digitalWrite(exit_gate, HIGH);

             if ((digitalRead(parking1_slot1_ir_s ) == HIGH) || (digitalRead(parking1_slot2_ir_s ) == HIGH) || (digitalRead(parking1_slot3_ir_s ) == HIGH) || (digitalRead(parking1_slot4_ir_s) == HIGH))
            {
                float parkingFee = calculateFee();
                displayfee(parkingFee);
                
                delay(200);
            }
  
            if ( ! mfrc522.PICC_IsNewCardPresent())   
            {    
                //lcd.setCursor(3,0);  
               // lcd.print("Please Put Your");  
                //lcd.setCursor(7,1);  
                //lcd.print("ID CARD");   
                return;  
            }  
            else{  
                    lcd.clear();  
                }  
   
            if ( ! mfrc522.PICC_ReadCardSerial())   
            {  
                    return;  
            }    
  
            Serial.print("UID tag :");  
            String content= "";  
            byte letter;  

            for (byte i = 0; i < mfrc522.uid.size; i++)   
            {  
                  Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");  
                  Serial.print(mfrc522.uid.uidByte[i], HEX);  
                  content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));  
                  content.concat(String(mfrc522.uid.uidByte[i], HEX));  
            }  
  
            Serial.println();  
            content.toUpperCase();   
           
           if ((digitalRead(parking1_slot1_ir_s ) == LOW) && (digitalRead(parking1_slot2_ir_s ) == LOW) && (digitalRead(parking1_slot3_ir_s ) == LOW) && (digitalRead(parking1_slot4_ir_s) == LOW))
           {
             lcd.print("All slots taken");
             delay(2000);
             lcd.clear();
           }

            else if (content.substring(1) == "53 4F 26 1C")  
            {  
  
                  lcd.print("Welcome Tharindu !");    
                  //tone(BUZZER, 500);
                  delay(300);
                 // noTone(BUZZER);
                  for (pos1 = 0; pos1 <= 90 ; pos1 += 1) 
                  {
                        myservo1.write(pos1);             
                        delay(15);                       
                  }
                  delay(1000);
                  
                  for (pos1 = 90; pos1 >= 0; pos1 -= 1) 
                  { 
                        myservo1.write(pos1);             
                        delay(15);                       
                  }    
     
     
                  delay(1000);    
                  lcd.clear();  

            }  
            else if (content.substring(1) == "43 F4 60 1C")  
            {  
                  lcd.print("Welcome Amath !");    
                //  tone(BUZZER, 500);
                  delay(300);
                 // noTone(BUZZER);
                
                  for (pos1 = 0; pos1 <= 90 ; pos1 += 1) 
                  { 
                        myservo1.write(pos1);              
                        delay(15);                       
                  }
                  delay(1000);
                 
                  for (pos1 = 90; pos1 >= 0; pos1 -= 1) 
                  { 
                        myservo1.write(pos1);             
                        delay(15);                       
                  }     
                  delay(1000);    
                  lcd.clear();   
            }  
            else if (content.substring(1) == "A1 92 94 1B")  
            {  
                  lcd.print("Welcome Sahas !");    
                 // tone(BUZZER, 500);
                  delay(300);
                 // noTone(BUZZER);
   
                  for (pos1 = 0; pos1 <= 90 ; pos1 += 1) 
                  { 
        
                        myservo1.write(pos1);              
                        delay(15);                      
                  }
                  delay(1000);
        
                  for (pos1 = 90; pos1 >= 0; pos1 -= 1) 
                  { 
                        myservo1.write(pos1);            
                        delay(15);                     
                  }    
                  delay(1000);    
                  lcd.clear(); 
            }  
            else if (content.substring(1) == "A1 EF 0D 1B")
            {  
                  lcd.print("Welcome Shehan !");    
                  //tone(BUZZER, 500);
                  delay(300);
                 // noTone(BUZZER);
               
                 for (pos1 = 0; pos1 <= 90 ; pos1 += 1) 
                 { 
                        myservo1.write(pos1);             
                        delay(15);                       
                 }
                 delay(1000);
               
                 for (pos1 = 90; pos1 >= 0; pos1 -= 1) 
                 { // goes from 180 degrees to 0 degrees
                        myservo1.write(pos1);            
                        delay(15);                       
                 }    
                 delay(1000);    
                 lcd.clear(); 
            } 
            else  
            {  
                    lcd.print("UNAUTHORIZE");  
                    lcd.setCursor(0,1);  
                    lcd.print("ACCESS");     
                   // tone(BUZZER, 300);  
                    delay(2000);    
                  //  noTone(BUZZER);  
                    lcd.clear();  
            }
           
        }  
        void gates()
        { 
            
              if (digitalRead(exit_gate) == LOW)
              {  
                    for (pos2 = 90; pos2 <= 180 ; pos2 += 1) 
                    { 
                            myservo2.write(pos2);              
                            delay(15);                       
                    }
                    delay(1000);
        
                    for (pos2 = 180; pos2 >= 90; pos2 -= 1) 
                    { 
                            myservo2.write(pos2);              
                            delay(15);                     
                    }
               }
        }
        void p1slot1() 
        {
              if( digitalRead(parking1_slot1_ir_s) == LOW) 
              {     
                    lcd.setCursor(0, 0);
                    lcd.print("Slot full");
                    sensor1 = "255";
                    delay(200); 
              } 
              if( digitalRead(parking1_slot1_ir_s) == HIGH)
              {
                    lcd.setCursor(0, 0);
                    lcd.print("Slot free");
                    sensor1 = "0";  
                    delay(200);  
              }

        }

        void p1slot2() 
        {
              if( digitalRead(parking1_slot2_ir_s) == LOW) 
              {     
                    lcd.setCursor(0, 1);
                    lcd.print("Slot full");
                    sensor2 = "255"; 
                    delay(200); 
              }
              if( digitalRead(parking1_slot2_ir_s) == HIGH)  
              {   

                    lcd.setCursor(0, 1);
                    lcd.print("Slot free");
                    sensor2 = "0";  
                    delay(200);
              } 
        }


        void p1slot3() 
        {
              if( digitalRead(parking1_slot3_ir_s) == LOW) 
              {
                    lcd.setCursor(11, 0);
                    lcd.print("Slot full");
                    sensor3 = "255"; 
                    delay(200); 
              }
              if( digitalRead(parking1_slot3_ir_s) == HIGH)  
              {     
                    lcd.setCursor(11, 0);
                    lcd.print("Slot free");
                    sensor3 = "0";  
                    delay(200);
              } 
        }


        void p1slot4() 
        {
              if( digitalRead(parking1_slot4_ir_s) == LOW) 
              {
                    lcd.setCursor(11, 1);
                    lcd.print("Slot full");
                    sensor4 = "255"; 
                    delay(200); 
              }
              if( digitalRead(parking1_slot4_ir_s) == HIGH)  
              {
                    lcd.setCursor(11, 1);
                    lcd.print("Slot free");
                    
                    sensor4 = "0";  
                    delay(200);
              } 
        }

        float calculateFee()
        {
          unsigned long startTime = millis();
         // while ((digitalRead(parking1_slot1_ir_s ) == LOW) || (digitalRead(parking1_slot2_ir_s ) == LOW) || (digitalRead(parking1_slot3_ir_s ) == LOW) || (digitalRead(parking1_slot4_ir_s) == LOW))
          //{
            
          //}
            unsigned long endTime = millis();
            float duration = (endTime - startTime) / 1000.0 / 3600.0;
            float fee = duration * hourlyRate;
            return fee;
          
        }
          void displayfee(float fee)
          {
            lcd.clear();
            lcd.setCursor(0, 3);
            lcd.print("Parking fee: Rs");
            lcd.print(fee);
            Serial.print("parking fee:");
            Serial.print(fee);
            //delay(1000);
          }


        

        

          
        
