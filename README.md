# Container Fill Level Monitor

A simple Arduino project that measures how full a container is using an ultrasonic sensor and displays the fill percentage on a 4-digit LED display.

## What It Does

This project uses an ultrasonic distance sensor to measure the empty space in a container, then calculates and displays the fill level as a percentage (0-100%) on a TM1637 LED display.

## Hardware Requirements

- **Arduino Board** (Uno, Nano, or compatible)
- **HC-SR04 Ultrasonic Sensor** (or compatible)
- **TM1637 4-Digit 7-Segment Display**
- Jumper wires
- USB cable for programming and power

## Wiring Diagram

### TM1637 Display
- `CLK` → Arduino Pin 2
- `DIO` → Arduino Pin 3
- `VCC` → 5V
- `GND` → GND

### HC-SR04 Ultrasonic Sensor
- `TRIG` → Arduino Pin 5
- `ECHO` → Arduino Pin 6
- `VCC` → 5V
- `GND` → GND

## Software Requirements

### Arduino Libraries
You need to install the following library through the Arduino IDE Library Manager:

1. Open Arduino IDE
2. Go to **Sketch → Include Library → Manage Libraries**
3. Search for and install:
   - **TM1637Display** by Avishay Orpaz

## Setup Instructions

1. **Wire the components** according to the wiring diagram above
2. **Measure your container's depth** from the sensor mounting point to the bottom
3. **Update the code** with your container's height:
   ```cpp
   const float BOX_HEIGHT_CM = 20.0; // Change this to your container's depth in cm
   ```
4. **Upload the code** to your Arduino
5. **Mount the sensor** at the top of your container, pointing straight down

## How It Works

1. The ultrasonic sensor sends sound waves downward
2. The sensor measures how long it takes for the echo to return
3. The code calculates the distance to the surface of the contents
4. It converts this to a fill percentage based on your container height
5. The percentage is displayed on the LED screen and sent to the Serial Monitor

### Calculation Formula
```
Filled Height = Container Height - Measured Distance
Fill Percentage = (Filled Height / Container Height) × 100
```

## Features

- **Real-time monitoring**: Updates every 0.5 seconds
- **Bad reading filtering**: Ignores invalid measurements (>100cm or 0)
- **Safety limits**: Ensures percentage stays between 0-100%
- **Serial output**: View detailed readings in the Arduino Serial Monitor (9600 baud)
- **Startup test**: Displays "8888" for 1 second to verify the display works

## Troubleshooting

**Display shows nothing:**
- Check wiring connections
- Verify the TM1637 library is installed
- Adjust brightness setting (0-7) in the code

**Readings are inaccurate:**
- Ensure sensor is mounted perpendicular to the container bottom
- Check that `BOX_HEIGHT_CM` matches your actual container depth
- Verify sensor has a clear line of sight (no obstructions)

**Readings jump around:**
- The container contents may have an uneven surface
- Try increasing the delay between readings
- Mount the sensor more securely to reduce vibration

**Display shows 0% when container is full:**
- Double-check your `BOX_HEIGHT_CM` value
- Verify the sensor is measuring from the correct reference point

## Customization Options

- **Change brightness**: Modify the value in `display.setBrightness(5);` (0-7)
- **Update speed**: Change `delay(500);` at the end of the loop (in milliseconds)
- **Distance range**: Adjust the `currentDistance > 100` threshold for larger containers

## Serial Monitor Output

Open the Serial Monitor (9600 baud) to see detailed output:
```
Distance: 15.2 cm | Filled: 24%
Distance: 10.8 cm | Filled: 46%
Distance: 5.3 cm | Filled: 73%
```

## License

This project is open source and free to use for any purpose.

## Credits

Uses the TM1637Display library by Avishay Orpaz.
