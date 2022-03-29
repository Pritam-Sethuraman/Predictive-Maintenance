# Predictive-Maintenance
![image](https://user-images.githubusercontent.com/78743757/160560229-49d9e958-373d-4cc1-9451-382e67f147dc.png)

---

## Table of Contents
- [Description](#description)
- [How To Use](#how-to-use)
- [References](#references)
- [License](#license)
- [Author Info](#author-info)

---

## Description

This project is for industrial application of IoT

#### Components & Technologies

- ESP32
- I2C
- MQTT
- Node-RED

---

## How To Use

### EMQX MQTT Broker
1. Download zip from [here](https://www.emqx.com/en/downloads/broker?osType=Linux)
2. Unzip the file
```html
unzip emqx-4.4.1-otp23.0-windows-amd64.zip
```
3. Start emqx
```html
.\bin\emqx start
```
4. Check if emqx is running
```html
.\bin\emqx_ctl status
.\bin\emqx ping
```
5. Stop emqx
```html
.\bin\emqx stop
````

### Node-RED
Windows CMD:
```html
node --version && npm --version
npm install -g --unsafe-perm node-red
node-red
```

---

## References

- Analysis and Control of The Motor Vibration using Arduino and Machine Learning Model by S. Krishnaveni, S. Senthil Raja, T. Jayasankar and P. Sathish Babu
- Machine Learning approach for Predictive Maintenance in Industry 4.0 by Marina Paolanti, Luca Romeo Andrea Felicetti, Jelena Loncarski, et. al.
- Machine Learning Approaches for Failure Type Detection and Predictive Maintenance by Patrick Jahnke
- Machine Learning for Predictive Maintenance: A Multiple Classifier Approach by Gian Antonio Susto, Andrea Schirru, Simone Pampuri, Se´an McLoone and Alessandro Beghi

---

## License
MIT License

Copyright (c) 2022 Pritam Sethuraman

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

---

## Author Info

- LinkedIn - [@pritamsethuraman](https://www.linkedin.com/in/pritam-sethuraman/)

[Back To The Top](#predictive-maintenance)
