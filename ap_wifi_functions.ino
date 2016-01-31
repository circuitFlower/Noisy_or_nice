
void setup_AP()
{
  Serial.println();
  Serial.print("Configuring access point...");
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid_AP, password_AP);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.on("/submit", handleSubmit);
  server.begin();
  Serial.println("HTTP server started");
  AP_mode = 1;
}

void setupWIFI(char max_tries){
  Serial.print("Connecting to ");
  Serial.print(ssid);
  WiFi.mode(WIFI_STA);
  delay(100);
  WiFi.begin(ssid, password);
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts<max_tries) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  if( WiFi.status() == WL_CONNECTED ){
    Serial.println("WiFi connected");  
    Serial.println("IP address: " + WiFi.localIP());  
    connect_success = 1;
  }
  else{
    Serial.println("WiFi could not be connected");
    connect_success = 0;
  }
}

void handleRoot() 
{
  String html_code;
  html_code += "<html>";
  html_code += "<head>";
  html_code += "<title> Smart Light Switch Wifi Connection </title>";
  html_code += "<style>  body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000080; } </style>";
  html_code += "</head>";
  html_code += "<body>";
  html_code += "<h1>Lets Get Connected!</h1><br><br><br><br>";

  html_code += "<p> 1. SELECT YOUR WIFI </p> <br>"; 
  html_code += "<form action='http://192.168.4.1/submit' method='POST'><br>";
  
  //***************************************GETTING ALL ACTIVE WIFI CONNECTIONS IN REACH AND ADDING THEM TO HTML CODE*************************
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0){
      Serial.println("no networks found");
  }
  else{
    Serial.print(n);
    Serial.println(" networks found: ");
    String details = "";
    for (int i = 0; i < n; i++){
      // Print SSID and RSSI for each network found
      details += (WiFi.SSID(i));
      details += (" (");
      details += (WiFi.RSSI(i));
      details += (")");
      details += ((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
      delay(10);
      Serial.println(details);
      //html_code += "<p> " + details + "</p>";
      html_code = html_code + "<input type='radio' name='ssid' value=" + WiFi.SSID(i) +"> "+ WiFi.SSID(i)+ "<br>";
      details = "";
    }
  }//*************************************************************DONE ADDING ALL WIFIS TO HTML PAGE*******************************

  html_code += "<br><br><br>";
  html_code += "<p> 2. NOW ENTER YOUR PASSWORD </p><br>";
  html_code += "Password: <input type='text' name='pass'> <br><br><br>";
  html_code += "<input type='submit' value='Submit'> <br>";
  html_code += "</form>";
  html_code += "</body>";
  html_code += "</html>";
  server.send(200, "text/html", html_code);
}


void handleSubmit(){
  if (server.args() > 0 ){
    for ( uint8_t i = 0; i < server.args(); i++ ){
      if (server.argName(i) == "ssid"){
         Serial.print("SSID: ");
         server.arg(i).toCharArray(ssid, 50);
         Serial.println(ssid);
         wifi_info_submitted = 1;
      }
      else if ( server.argName(i) == "pass" ){
        Serial.print("Password: ");
        server.arg(i).toCharArray(password, 50);
        Serial.println(password);
      }
    }
  }
  String html_code = "";
  html_code+=  "<html>";
  html_code+= "<head>";
  html_code+= "<title>Smart Light Switch Wifi Connection</title>";
  html_code+= "<style>";
  html_code+= "body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000080; }";
  html_code+= "</style>"; 
  html_code+= "</head>";
  html_code+= "<body>";
  html_code+= "<h1>Lets Get Connected to WIFI</h1>";
  html_code+= "<p> Thanks! Wifi details successfully saved!</p>";
  html_code+= "</body>";
  html_code+= "</html>";
  html_code+= "";
  server.send(200, "text/html", html_code);
  //WiFi.mode(WIFI_OFF);
}

void print_mac(){
  WiFi.macAddress(mac);
  Serial.print("MAC: ");
  Serial.print(mac[5],HEX);
  Serial.print(":");
  Serial.print(mac[4],HEX);
  Serial.print(":");
  Serial.print(mac[3],HEX);
  Serial.print(":");
  Serial.print(mac[2],HEX);
  Serial.print(":");
  Serial.print(mac[1],HEX);
  Serial.print(":");
  Serial.println(mac[0],HEX);
}
