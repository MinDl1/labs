import time  
import picamera 
 
#Создаем объект камеры  
camera = picamera.PiCamera()  
#Устанавливаем разрешение кадра  
camera.resolution = (720, 576)  
#Устанавливаем длительность видео (в секундах)  
 
video_length = 15  
#Путь к папке для сохранения видео  
output_folder = "/path/to/folder/"  
#Генерируем имя файла на основе даты и времени  
filename = time.strftime("%Y-%m-%d_%H-%M-%S") + ".h264"  
#Полный путь к файлу  
output_path = output_folder + filename  
#Запускаем запись видео  
camera.start_recording(output_path)  
#Ожидаем заданное количество секунд  
time.sleep(video_length)  
#Останавливаем запись видео  
camera.stop_recording()  
#Закрываем объект камеры  
camera.close()