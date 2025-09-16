#include <ESP8266WiFi.h> 
#include <ESP8266WebServer.h>

/* Установите здесь свои SSID и пароль */
const char* ssid = "Wifis-Dom";  // SSID
const char* password = "iYiE5JRb:L"; // пароль

// Объект веб-сервера. Будет прослушивать порт 80 (по умолчанию для HTTP)
ESP8266WebServer server(80);   

void setup() 
{
  Serial.begin(115200);
  delay(100);

  Serial.println("Connecting to ");
  Serial.println(ssid);

  // подключиться к вашей локальной wi-fi сети
  WiFi.begin(ssid, password);

  // проверить, подключился ли wi-fi модуль к wi-fi сети
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  
  Serial.println(WiFi.localIP());

  server.on("/genericArgs", handleGenericArgs);  // привязать функцию обработчика к URL-пути
  server.on("/specificArgs", handleSpecificArg); // привязать функцию обработчика к URL-пути
  server.on("/test", send_test_code); // привязать функцию обработчика к URL-пути

  server.begin();                                // запуск сервера
  Serial.println("HTTP server started");  

}

void loop() 
{
  server.handleClient();    // обработка входящих запросов

}


void send_test_code() //обработчик
{
  server.send(200, "text/plain", "socket");    // ответить на HTTP запрос
}

void handleGenericArgs() //обработчик
{
  String message = "Number of args received:";
  message += server.args();      // получить количество параметров
  message += "\n";               // переход на новую строку

  for (int i = 0; i < server.args(); i++) 
  {
    message += "Arg nº" + String(i) + " –> "; // добавить текущее значение счетчика
    message += server.argName(i) + ": ";      // получить имя параметра
    message += server.arg(i) + "\n";          // получить значение параметра
  } 
int();
  server.send(200, "text/plain", message);    // ответить на HTTP запрос
}


void handleSpecificArg() 
{ 
  String message = "";

  if (server.arg("Temperature")== "") 
  { // параметр не найден
    message = "Temperature Argument not found";
  }
  else
  { // параметр найден
    message = "Temperature Argument = ";
    message += server.arg("Temperature");     // получить значение параметра запроса
  }

  server.send(200, "text/plain", message);    // возвращаем HTTP-ответ
}
