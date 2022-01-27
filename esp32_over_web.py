import re
from flask import Flask, request, Markup, abort, render_template

import serial
app = Flask(__name__)

ser = serial.Serial('/dev/tty.usbserial-0001', 115200, timeout=1)


@app.route('/')
def index():
    return render_template('index.html')


@app.route('/open', methods=['POST'])
def open():
    if request.method == 'POST':
        ser.write(bytes('1', 'utf-8'))

        return index()


@app.route('/close', methods=['POST'])
def close():
    if request.method == 'POST':
        ser.write(bytes('2', 'utf-8'))
        return index()


if __name__ == '__main__':
    app.run()