# RelayController
A libarary to controll Relay.
# Install to Arduino IDE
1. Download ZIP
2. Add Library

Sketch -> Include library -> Add .ZIP Library...
![image](https://user-images.githubusercontent.com/58265068/71096722-2680d100-21f2-11ea-8b55-8a70f5b19fec.png)

3. Select downloaded folder and Click "Open" button.
# Useage
## Relay
You can initialize output pin and the array.
~~~bash
int pin[10] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
Relay Relay(pin, 10);
~~~
## sing
You can sing Relay by designating time (milli seconds) first argument
And at second argument, you must designate note
And at final argument, you must designate tempo
~~~bash
Relay.sing(3000, 4, 120);
Relay.sing(3000, 4000, 4, 120);
~~~
