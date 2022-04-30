import re
from flask import Flask, request, Markup, abort, render_template

import serial
app = Flask(__name__)

# ser = serial.Serial('/dev/tty.usbserial-0001', 115200, timeout=1)


# print(ser.read_all())
@app.route('/')
def index():
    # print(ser.read_all())
    return render_template('index.html')


@app.route('/open', methods=['POST'])
def open():
    # print(ser.read_all())
    if request.method == 'POST':

        
        ser.write(bytes('1', 'utf-8'))
       
        return index()


@app.route('/close', methods=['POST'])
def close():
    # print(ser.read_all())
    if request.method == 'POST':

        # ser.write(bytes('2', 'utf-8'))
        

        return index()


if __name__ == '__main__':
    
    app.run(port=8000, debug=True)
