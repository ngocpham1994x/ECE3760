# ECE3760
🏫 University of Manitoba - Digital System Design 1

Demonstration / Progress Videos [here](https://www.youtube.com/playlist?list=PL25XFi5JMg36iqCR__kG-orZFBlpt5zU0)

References:

- [Getting Started with ESP-NOW (ESP32 with Arduino IDE)](https://randomnerdtutorials.com/esp-now-esp32-arduino-ide/)

- [Installing the ESP32 Board in Arduino IDE (Windows, Mac OS X, Linux)](https://randomnerdtutorials.com/installing-the-esp32-board-in-arduino-ide-windows-instructions/)

- [Arduino IDE + ESP32 | Communication between ESP32 (Two or more ESP32) with ESP-NOW Protocol](https://www.youtube.com/watch?v=xOLG-88Ld3A&t=882s)

## OPERATIONS
- If skip wants to send sweep hard command to Right sweeper: holding down the Right button 
- If skip wants to send sweep soft command to Right sweeper: press the Right button 
- If skip wants to send sweep hard command to Left sweeper: holding down the Left button 
- If skip wants to send sweep soft command to Left sweeper: press the Left button
- If skip wants to send stop command: press the Stop button to broadcast stop command to both sweepers

## In other words:
- Stop: press the stop button
- Hard sweep: holding down on a button 
- Soft sweep: press a button

## DEVICES
- ESP-A: Skip device 
- ESP-B: Right sweep device 
- ESP-C: Left sweep device

## NOTES
- Getting started with ESP32:
  - Board module: NodeMCU-32s
  - Everytime uploading to board, hold IO0 button until connection established
- For easy understanding and coding, use the same pins for IO accordingly on both boards.
- GNDs on each board should not be tied together. GND for different devices are different.
- Each device on each board should have different GND
- 4-leg LED can have different wiring diagrams: common anode, or common cathode. The ones I have is common cathode.
- Since my wiring is common cathode, my program is sending LOW to turn LED ON, and sending HIGH to turn LED OFF


## CREDITS & TEAM MEMBERS:
<table>
<tr>
    <td style="text-align: center;">
        <a href="https://github.com/ngocpham1994x">
            <img src="https://github.com/ngocpham1994x/iRecipe/blob/d514d48323253405f33b0a152cbcda17be023de2/website/NgocPham_headshot.JPG" width="100px;"/>
            <br/>
            <sub>
                <b>Ngoc Pham </b>
            </sub>
        </a>
    </td>
    <td style="text-align: center;">
        <a href="">
            <img src="" width="100px;"/>
            <br/>
            <sub>
                <b>Matthew Mora</b>
            </sub>
        </a>
    </td>
    <td style="text-align: center;">
        <a href="">
            <img src="" width="100px;"/>
            <br/>
            <sub>
                <b>Ian Roller</b>
            </sub>
        </a>
    </td>
</tr>
</table>
