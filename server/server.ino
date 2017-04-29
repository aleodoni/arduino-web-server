#include <SPI.h>
#include <Ethernet.h>

byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192,168,25,44);

EthernetServer server(80);

void setup() {
	Serial.begin(9600);
	while (!Serial) {
		;
	}

	Ethernet.begin(mac, ip);
	server.begin();
	Serial.print("server is at ");
	Serial.println(Ethernet.localIP());
}

void loop() {
	EthernetClient client = server.available();
	if (client) {
		Serial.println("new client");
		boolean currentLineIsBlank = true;
		while (client.connected()) {
			if (client.available()) {
				char c = client.read();
				Serial.write(c);
				if (c == '\n' && currentLineIsBlank) {
					client.println("HTTP/1.1 200 OK");
          			client.println("Content-Type: text/html");
          			client.println("Connection: close");
	  				client.println("Refresh: 5");
          			client.println();
          			client.println("<!DOCTYPE HTML>");
          			client.println("<html>");
          			client.println("<head>");
          			client.println("<link href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css' rel='stylesheet'></link>");
          			client.println("</head>");
          			client.println("<body>");
          			client.println("<div class='jumbotron'>");
          			client.println("<h1 class='display-3'>Arduino server running</h1>");
          			client.println("<p class='lead'>This is a simple message from your arduino web server.</p>");
          			client.println("<hr class='my-4'>");
          			client.println("</div>");
          			client.println("</body>");
          			client.println("</html>");
          			break;
				}
				if (c == '\n') {
          			currentLineIsBlank = true;
        		} 
        		else if (c != '\r') {
          			currentLineIsBlank = false;
        		}
			}
		}
		delay(1);
		client.stop();
		Serial.println("client disonnected");
	}
}
