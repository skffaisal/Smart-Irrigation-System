/*
  Rui Santos
  Complete project details at:
   - ESP32: https://RandomNerdTutorials.com/esp32-send-email-smtp-server-arduino-ide/
   - ESP8266: https://RandomNerdTutorials.com/esp8266-nodemcu-send-email-smtp-server-arduino/
  
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
  Example adapted from: https://github.com/mobizt/ESP-Mail-Client
*/

// To send Emails using Gmail on port 465 (SSL), you need to create an app password: https://support.google.com/accounts/answer/185833
#include <ESP8266WiFi.h>
#include <time.h>
#include <Arduino.h>
const int buttonPin = 2;
int buttonState = 0;
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <ESP_Mail_Client.h>
const char* ssid = "wifi";
const char* password = "Classical243";
int ledPin = 13;
//int buttonState = 0; 
int timezone = 5*3600+1800;
int dst = 0;
#define WIFI_SSID "wifi"
#define WIFI_PASSWORD "Classical243"

#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT 465

/* The sign in credentials */
#define AUTHOR_EMAIL "nithinrash4@gmail.com"
#define AUTHOR_PASSWORD "Classical243"

/* Recipient's email*/
#define RECIPIENT_EMAIL "nithinrash4@gmail.com"

/* The SMTP Session object used for Email sending */
SMTPSession smtp;

/* Callback function to get the Email sending status */
void smtpCallback(SMTP_Status status);

void setup(){
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to AP");
  pinMode(buttonPin, INPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(200);
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /** Enable the debug via Serial port
   * none debug or 0
   * basic debug or 1
  */
  
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,LOW);
  pinMode(buttonPin, INPUT);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Wifi connecting to ");
  Serial.println( ssid );

  WiFi.begin(ssid,password);

  Serial.println();
  
  Serial.print("Connecting");

  while( WiFi.status() != WL_CONNECTED ){
      delay(500);
      Serial.print(".");        
  }

  
  Serial.println();

  Serial.println("Wifi Connected Success!");
  Serial.print("NodeMCU IP Address : ");
  Serial.println(WiFi.localIP() );

  configTime(timezone, dst, "pool.ntp.org","time.nist.gov");
  Serial.println("\nWaiting for Internet time");

  while(!time(nullptr)){
     Serial.print("*");
     delay(1000);
  }
  Serial.println("\nTime response....OK");       
}

void loop(){
  buttonState = digitalRead(buttonPin);  
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
   
  // TURN LED ON

  if( (p_tm->tm_hour == 17) && (p_tm->tm_min == 53)){
      digitalWrite(ledPin,HIGH);
      smtp.debug(1);

  /* Set the callback function to get the sending results */
      smtp.callback(smtpCallback);

  /* Declare the session config data */
      ESP_Mail_Session session;

  /* Set the session config */
      session.server.host_name = SMTP_HOST;
      session.server.port = SMTP_PORT;
      session.login.email = AUTHOR_EMAIL;
      session.login.password = AUTHOR_PASSWORD;
      session.login.user_domain = "";

  /* Declare the message class */
      SMTP_Message message;

  /* Set the message headers */
      message.sender.name = "ESP";
      message.sender.email = AUTHOR_EMAIL;
      message.subject = "Smart system";
      message.addRecipient("Sara", RECIPIENT_EMAIL);      
      String htmlMsg = "<div style=\"color:#2f4468;\"><h1>ok</h1><p>- Motor is on</p></div>";
      message.html.content = htmlMsg.c_str();
      message.html.content = htmlMsg.c_str();
      message.text.charSet = "us-ascii";
      message.html.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

  /*Send HTML message*/


  /*
  //Send raw text message
  String textMsg = "Hello World! - Sent from ESP board";
  message.text.content = textMsg.c_str();
  message.text.charSet = "us-ascii";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
  
  message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_low;
  message.response.notify = esp_mail_smtp_notify_success | esp_mail_smtp_notify_failure | esp_mail_smtp_notify_delay;*/

  /* Set the custom message header */
  //message.addHeader("Message-ID: <abcde.fghij@gmail.com>");

  /* Connect to server with the session config */
  if (!smtp.connect(&session))
    return;

  /* Start sending Email and close the session */
  if (!MailClient.sendMail(&smtp, &message))
    Serial.println("Error sending Email, " + smtp.errorReason());      
  }
  

  // TURN LED OFF

  if( (p_tm->tm_hour == 17) && (p_tm->tm_min == 54)){
      digitalWrite(ledPin,LOW);
  }
  
  delay(1000);
  if (buttonState == HIGH) {
          smtp.debug(1);

  /* Set the callback function to get the sending results */
      smtp.callback(smtpCallback);

  /* Declare the session config data */
      ESP_Mail_Session session;

  /* Set the session config */
      session.server.host_name = SMTP_HOST;
      session.server.port = SMTP_PORT;
      session.login.email = AUTHOR_EMAIL;
      session.login.password = AUTHOR_PASSWORD;
      session.login.user_domain = "";

  /* Declare the message class */
      SMTP_Message message;

  /* Set the message headers */
      message.sender.name = "ESP";
      message.sender.email = AUTHOR_EMAIL;
      message.subject = "Smart system";
      message.addRecipient("Sara", RECIPIENT_EMAIL);      
      String htmlMsg = "<div style=\"color:#2f4468;\"><h1>ok</h1><p>- Motor is on</p></div>";
      message.html.content = htmlMsg.c_str();
      message.html.content = htmlMsg.c_str();
      message.text.charSet = "us-ascii";
      message.html.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

  /*Send HTML message*/


  /*
  //Send raw text message
  String textMsg = "Hello World! - Sent from ESP board";
  message.text.content = textMsg.c_str();
  message.text.charSet = "us-ascii";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
  
  message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_low;
  message.response.notify = esp_mail_smtp_notify_success | esp_mail_smtp_notify_failure | esp_mail_smtp_notify_delay;*/

  /* Set the custom message header */
  //message.addHeader("Message-ID: <abcde.fghij@gmail.com>");

  /* Connect to server with the session config */
  if (!smtp.connect(&session))
    return;

  /* Start sending Email and close the session */
  if (!MailClient.sendMail(&smtp, &message))
    Serial.println("Error sending Email, " + smtp.errorReason());      
  
  

    // turn LED on:
    
  } else {
    // turn LED off:
    Serial.print(".");
  }

}

/* Callback function to get the Email sending status */
void smtpCallback(SMTP_Status status){
  /* Print the current status */
  Serial.println(status.info());

  /* Print the sending result */
  if (status.success()){
    Serial.println("----------------");
    ESP_MAIL_PRINTF("Message sent success: %d\n", status.completedCount());
    ESP_MAIL_PRINTF("Message sent failled: %d\n", status.failedCount());
    Serial.println("----------------\n");
    struct tm dt;

    for (size_t i = 0; i < smtp.sendingResult.size(); i++){
      /* Get the result item */
      SMTP_Result result = smtp.sendingResult.getItem(i);
      time_t ts = (time_t)result.timestamp;
      localtime_r(&ts, &dt);

      ESP_MAIL_PRINTF("Message No: %d\n", i + 1);
      ESP_MAIL_PRINTF("Status: %s\n", result.completed ? "success" : "failed");
      ESP_MAIL_PRINTF("Date/Time: %d/%d/%d %d:%d:%d\n", dt.tm_year + 1900, dt.tm_mon + 1, dt.tm_mday, dt.tm_hour, dt.tm_min, dt.tm_sec);
      ESP_MAIL_PRINTF("Recipient: %s\n", result.recipients);
      ESP_MAIL_PRINTF("Subject: %s\n", result.subject);
    }
    Serial.println("----------------\n");
  }
    if (buttonState == HIGH) {
          smtp.debug(1);

  /* Set the callback function to get the sending results */
      smtp.callback(smtpCallback);

  /* Declare the session config data */
      ESP_Mail_Session session;

  /* Set the session config */
      session.server.host_name = SMTP_HOST;
      session.server.port = SMTP_PORT;
      session.login.email = AUTHOR_EMAIL;
      session.login.password = AUTHOR_PASSWORD;
      session.login.user_domain = "";

  /* Declare the message class */
      SMTP_Message message;

  /* Set the message headers */
      message.sender.name = "ESP";
      message.sender.email = AUTHOR_EMAIL;
      message.subject = "Smart system";
      message.addRecipient("Sara", RECIPIENT_EMAIL);      
      String htmlMsg = "<div style=\"color:#2f4468;\"><h1>ok</h1><p>- Motor is on</p></div>";
      message.html.content = htmlMsg.c_str();
      message.html.content = htmlMsg.c_str();
      message.text.charSet = "us-ascii";
      message.html.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

  /*Send HTML message*/


  /*
  //Send raw text message
  String textMsg = "Hello World! - Sent from ESP board";
  message.text.content = textMsg.c_str();
  message.text.charSet = "us-ascii";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
  
  message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_low;
  message.response.notify = esp_mail_smtp_notify_success | esp_mail_smtp_notify_failure | esp_mail_smtp_notify_delay;*/

  /* Set the custom message header */
  //message.addHeader("Message-ID: <abcde.fghij@gmail.com>");

  /* Connect to server with the session config */
  if (!smtp.connect(&session))
    return;

  /* Start sending Email and close the session */
  if (!MailClient.sendMail(&smtp, &message))
    Serial.println("Error sending Email, " + smtp.errorReason());      
  }
}
    

void mai(){
        smtp.debug(1);

  /* Set the callback function to get the sending results */
      smtp.callback(smtpCallback);

  /* Declare the session config data */
      ESP_Mail_Session session;

  /* Set the session config */
      session.server.host_name = SMTP_HOST;
      session.server.port = SMTP_PORT;
      session.login.email = AUTHOR_EMAIL;
      session.login.password = AUTHOR_PASSWORD;
      session.login.user_domain = "";

  /* Declare the message class */
      SMTP_Message message;

  /* Set the message headers */
      message.sender.name = "ESP";
      message.sender.email = AUTHOR_EMAIL;
      message.subject = "Smart system";
      message.addRecipient("Sara", RECIPIENT_EMAIL);      
      String htmlMsg = "<div style=\"color:#2f4468;\"><h1>ok</h1><p>- There is a leakage in pipe</p></div>";
      message.html.content = htmlMsg.c_str();
      message.html.content = htmlMsg.c_str();
      message.text.charSet = "us-ascii";
      message.html.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

  /*Send HTML message*/


  /*
  //Send raw text message
  String textMsg = "Hello World! - Sent from ESP board";
  message.text.content = textMsg.c_str();
  message.text.charSet = "us-ascii";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
  
  message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_low;
  message.response.notify = esp_mail_smtp_notify_success | esp_mail_smtp_notify_failure | esp_mail_smtp_notify_delay;*/

  /* Set the custom message header */
  //message.addHeader("Message-ID: <abcde.fghij@gmail.com>");

  /* Connect to server with the session config */
  if (!smtp.connect(&session))
    return;

  /* Start sending Email and close the session */
  if (!MailClient.sendMail(&smtp, &message))
    Serial.println("Error sending Email, " + smtp.errorReason());    
      
}
