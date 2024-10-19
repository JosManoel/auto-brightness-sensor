import serial
import os
import subprocess

def adjust_brightness(brightness, monitors):
    normalized_brightness = brightness / 1023.0
    print(f'Brightness: {normalized_brightness:.2f}')
    
    for monitor in monitors:
        print(f'Adjusting brightness for {monitor}')
        set_brightness(monitor, normalized_brightness)

def set_brightness(monitor_name, normalized_brightness):
    os.system(f'xrandr --output {monitor_name} --brightness {normalized_brightness:.2f}')

def get_connected_monitors():
    result = subprocess.run(['xrandr'], stdout=subprocess.PIPE)
    output = result.stdout.decode('utf-8')

    monitors = []
    for line in output.splitlines():
        if ' connected' in line:
            monitor_name = line.split()[0]
            monitors.append(monitor_name)

    return monitors

consolePort = serial.Serial('/dev/ttyUSB0', 9600)
monitors = get_connected_monitors()

while True:
    line = consolePort.readline().decode('utf-8').strip()
    
    try:
        photoresistor_value = int(line)
        adjust_brightness(photoresistor_value, monitors)

    except ValueError:
        print("Error! Invalid input")
