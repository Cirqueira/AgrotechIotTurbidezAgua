import serial
import sqlite3
from flask import Flask, render_template, jsonify
from datetime import datetime

# Conexão com o banco
conn = sqlite3.connect('dados.db', check_same_thread=False)
cursor = conn.cursor()
cursor.execute('''
CREATE TABLE IF NOT EXISTS sensores (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    temperatura REAL,
    umidade REAL,
    solo INTEGER,
    tds INTEGER,
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
)
''')
conn.commit()

# Inicializa o Flask com suporte à pasta "static"
app = Flask(__name__, static_folder='static', template_folder='templates')

@app.route('/')
def index():
    return render_template('index5.html')

@app.route('/dados')
def dados():
    try:
        with serial.Serial('COM13', 9600, timeout=2) as arduino:
            linha = arduino.readline().decode().strip()
            temperatura, umidade, solo, tds = map(float, linha.split(","))
            timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')
            cursor.execute('''
                INSERT INTO sensores (temperatura, umidade, solo, tds, timestamp)
                VALUES (?, ?, ?, ?, ?)
            ''', (temperatura, umidade, solo, tds, timestamp))
            conn.commit()
    except Exception as e:
        print("Erro ao ler da serial:", e)

    cursor.execute('SELECT * FROM sensores ORDER BY id DESC LIMIT 10')
    return jsonify(cursor.fetchall())

if __name__ == '__main__':
    app.run(debug=True)
