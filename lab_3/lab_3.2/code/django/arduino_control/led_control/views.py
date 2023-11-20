from django.shortcuts import render
import sqlite3
import datetime

# Создаем подключение к базе данных (файл MorzeDB будет создан)
connection = sqlite3.connect('MorzeDB.db', check_same_thread=False)
cursor = connection.cursor()

def create_db():
    # Создаем таблицу Users
    sql = '''
    CREATE TABLE IF NOT EXISTS Morze (
    id INTEGER PRIMARY KEY,
    value TEXT,
    log_time timestamp
    );
    '''
    cursor.execute(sql)
    
    print("Table created")

    # Сохраняем изменения
    connection.commit()

create_db()

def insert_data(value, log_time):
    # Добавляем нововы данные датчика
    cursor.execute('INSERT INTO Morze (value, log_time) VALUES (?, ?);', (value, log_time))
    print("data insert")
    connection.commit()

# Create your views here.
from django.shortcuts import render
import serial

def index(request):
    return render(request, 'index.html') 
def control_led(request):
    port = '/dev/cu.usbmodem11401' # используйте свой COM-порт здесь
    baudrate = 115200
    action = request.POST.get("name")+"\n"
    
    insert_data(action, datetime.datetime.now())
    
    send_command(port, baudrate, action)

    return render(request, 'index.html')

def send_command(port, baudrate, command):
    insert_data(command, datetime.datetime.now())
    
    arduino = serial.Serial(port, baudrate, timeout=1)
    arduino.write(command.encode('utf-8'))
    print(command.encode())
    arduino.close()