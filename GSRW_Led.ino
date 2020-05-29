/*
    ------------------------------
    GSRW - Google Sheet Read Write
    ------------------------------
    Examples of programs for writing and reading cells in Google sheets.
    Using GET http client request.
    Inspired by the work of Sujay S. Phadke, Github: https://github.com/electronicsguy.
    Differ to his work here only uses standart the ESP8266HTTPClient.h library instead of using the HTTPSRedirect.h library.
    Version : 1.0
    Author:Ridwan Nurmatullah
    Github:@stoneroweast
    email:stoneroweast@gmail.com

*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* ssid     = "BIS.NET 3";
const char* password = "pild0614";

String httpsAddr =  "https://script.google.com/macros/s/AKfycbyn8obG5LG6SKmF2h5EE5D6nK-beXdq50_nYnpDvzmc0ZhVcMO/exec";

char *cellName  = "A1";

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println();
  Serial.print("Connecting to wifi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {

  WiFiClientSecure client;
  HTTPClient http;

  client.setInsecure();
  http.setFollowRedirects(true);
  http.setRedirectLimit(10);

  /* Read Cell */
  /* ....................*/
  //append cell name dan cell value to httpsAddr
  String payload = httpsAddr + "?cmd=read" + "&&cell=" + cellName;

  //cek connection to HTTPS Server...
  Serial.print("Connecting to https Server...\n");
  if (!http.begin(client, payload)) {
    Serial.println("Unable to connect...");
    return;
  }
ulang:
  //Send GET request to write cell
  Serial.println("Send request to Server to read value to cell");
  int httpCode = http.GET();

  //cek http code
  if (!(httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY)) {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    http.end();
    return;
  }
  //read the value
  payload = http.getString();
  int value = payload.toInt();

  Serial.print("Value of cell ");
  Serial.print(cellName);
  Serial.print(" is ");
  Serial.println(value);

  if (value) {
    digitalWrite(LED_BUILTIN, LOW);
  }
  else {
    digitalWrite(LED_BUILTIN, HIGH);
  }
goto ulang;
  http.end();
  delay(1000);
}
