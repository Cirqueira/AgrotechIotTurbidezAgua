#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define UMIDADE_SOLO_PIN A0
#define TDS_PIN A1

void setup() {
  Serial.begin(9600);
  
  dht.begin();

  // Inicializa o display OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Erro ao iniciar o display OLED"));
    while(true);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0,0);
  display.println("Iniciando sensores...");
  display.display();
  delay(2000);
}

void loop() {
  // Lê os dados do DHT11
  float temperatura = dht.readTemperature();
  float umidadeAr = dht.readHumidity();

  // Lê a umidade do solo (0 a 1023)
  int umidadeSoloRaw = analogRead(UMIDADE_SOLO_PIN);
  float umidadeSoloPercent = map(umidadeSoloRaw, 1023, 0, 0, 100); // seco=1023, molhado=0

  // Lê o valor do TDS Meter (simples leitura analógica)
  int tdsRaw = analogRead(TDS_PIN);
  float tensao = tdsRaw * (5.0 / 1023.0);
  float tdsValue = (133.42 * tensao * tensao * tensao
                    - 255.86 * tensao * tensao
                    + 857.39 * tensao) * 0.5; // Fator de calibração

  // Exibe os dados no OLED
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("Temperatura: ");
  display.print(temperatura);
  display.println(" C");

  display.print("Umidade Ar: ");
  display.print(umidadeAr);
  display.println(" %");

  display.print("Umidade Solo: ");
  display.print(umidadeSoloPercent);
  display.println(" %");

  display.println("Tot Solido Dissolv: ");
  display.print(tdsValue, 1);
  display.println(" parte p/ milhao");

  display.display();

  // Aguarda 2 segundos
  delay(2000);
}