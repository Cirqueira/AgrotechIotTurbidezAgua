# 🌾 AgroTech: Monitoramento Ambiental IoT

Este projeto é uma solução completa de IoT para monitoramento agrícola ou residencial. Ele utiliza um Arduino para coletar dados de sensores ambientais, exibe as informações em um display OLED local e envia os dados via comunicação serial para um servidor Flask (Python), onde são armazenados em um banco de dados SQLite e exibidos em um Dashboard Web em tempo real.

## 🚀 Funcionalidades

- **Monitoramento em Tempo Real:** Captura de temperatura, umidade do ar, umidade do solo e Total de Sólidos Dissolvidos (TDS) na água.
- **Display Local:** Visualização imediata dos dados através de um display OLED SSD1306.
- **Armazenamento de Dados:** Registro histórico das leituras em banco de dados SQLite.
- **Dashboard Web:** Interface responsiva e moderna para acompanhamento remoto com indicadores visuais (cards) e tabela de histórico.
- **Alertas Visuais:** Legendas dinâmicas que ajudam a interpretar os níveis de umidade do solo e qualidade da água.

## 🛠️ Hardware Necessário

- **Microcontrolador:** Arduino (Uno, Nano, Mega, etc.)
- **Sensores:**
  - Sensor de Temperatura e Umidade **DHT11**
  - Sensor de **Umidade do Solo** (Analógico)
  - Sensor de **TDS** (Total Dissolved Solids) para qualidade da água
- **Display:** OLED I2C **SSD1306** (128x64)
- **Outros:** Protoboard, Jumpers e cabo USB.

### Pinagem Sugerida
| Componente | Pino Arduino |
|------------|--------------|
| DHT11 (Data) | D2 |
| Umidade do Solo | A0 |
| Sensor TDS | A1 |
| OLED SDA | A4 (ou SDA dedicado) |
| OLED SCL | A5 (ou SCL dedicado) |

## 💻 Tecnologias Utilizadas

- **Firmware:** C++ (Arduino IDE)
- **Backend:** Python 3.10+, Flask, PySerial
- **Banco de Dados:** SQLite
- **Frontend:** HTML5, CSS3 (Google Fonts), JavaScript (Fetch API)

## 🔧 Instalação e Configuração

### 1. Arduino
1. Abra o arquivo `Arduino.ino` na Arduino IDE.
2. Instale as bibliotecas necessárias:
   - `Adafruit GFX Library`
   - `Adafruit SSD1306`
   - `DHT sensor library`
3. Faça o upload do código para o seu Arduino.

### 2. Ambiente Python
1. Certifique-se de ter o Python instalado.
2. Instale as dependências necessárias via terminal:
   ```bash
   pip install flask pyserial

   No arquivo App.py, verifique a linha que define a porta serial:
    Python

    with serial.Serial('COM13', 9600, timeout=2) as arduino:

    Nota: Altere 'COM13' para a porta onde seu Arduino está conectado (ex: /dev/ttyUSB0 no Linux ou COM3 no Windows).

🏃 Como Rodar

    Conecte o Arduino ao computador via USB.

    Execute o servidor Flask:
    Bash

    python App.py

    Abra o navegador e acesse:

    [http://127.0.0.1:5000](http://127.0.0.1:5000)

📊 Estrutura de Arquivos

    /static: Contém imagens/ícones usados no Dashboard.

    /templates: Contém o arquivo index.html.

    App.py: Servidor Flask e lógica de leitura serial.

    Arduino.ino: Código fonte do microcontrolador.

    dados.db: Banco de dados SQLite (gerado automaticamente na primeira execução).

📝 Notas de Calibração

    Umidade do Solo: O código usa a função map para converter valores de 0 a 1023 em porcentagem. Ajuste conforme a sensibilidade do seu sensor.

    TDS: Utiliza uma fórmula polinomial para converter a tensão analógica em PPM (Partes por Milhão), calibrada para sensores de 5V.

Desenvolvido como parte de um projeto de monitoramento inteligente.


---

### Dicas adicionais para o seu repositório:

1.  **Imagens:** O seu HTML tenta carregar imagens de `/static/img/`. Certifique-se de criar essa pasta no GitHub e colocar os ícones lá (temperatura.png, soil.png, etc.), ou o dashboard ficará com ícones quebrados.
2.  **O nome do Template:** No seu `App.py`, Lembre-se de deixar os nomes iguais para não dar erro 500 no Flask. --> `return render_template('index5.html')`, mas o código chama-se apenas `index.html`. Lembre-se de deixar os nomes iguais para não dar erro 500 no Flask.
