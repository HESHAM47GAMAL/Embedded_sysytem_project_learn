# Explain prolems for exercises and challenges
- [Exercise-1](#Exercise-1)


## Exercise-1
<p>Configure MCU clock for 8MHZ</p>
<p>Connect Pin 0 (LED1)& 1 (LED2)in PORTA using positive logic </p> 
<p>Connect pin 7 (LED3)in PORTD using positive logic</p>
<p>when program start turn LED1 on for half second then turn LED1 off and turn LED2 on for half second then turn it off</p>
<p>open WatchDog I configure timeout Period = 2.1 S </p>
<p>then turn LED3 on for 1 second then turn off </p>
<p>Inside while(1) I <strong><h3>toggle</h3></strong> LED3 every 200 ms </p>
<p>when Enter while(1) mostly ramian <strong><font size = "4">1.1 second</font></strong> for expiration timeout </p>
<p>so <strong><font size = "4">During while(1)</font></strong> Expiration of Timeout period happen</p>
<p>To <strong><font size = "4">avoid Timeout expiration</font></strong> so turn off watch dog  as can turn it off before while(1) </p>
