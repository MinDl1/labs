import sqlite3

# Создаем подключение к базе данных (файл ValueDB будет создан)
connection = sqlite3.connect('MorzeDB.db')
cursor = connection.cursor()

def select_bd():
    # Выбираем всех пользователей
    cursor.execute('SELECT * FROM Morze')
    results = cursor.fetchall()
    
    for row in results:
        print(row)
    
    # Закрываем соединение
    connection.close()
    
def main():
    select_bd()
    
if __name__ == '__main__':
    main()