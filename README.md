# Electronic Harmonium

![Electronic Harmonium](https://via.placeholder.com/800x400?text=Electronic+Harmonium+MBM+University)

## 🎹 Project Overview

This project implements an Electronic Harmonium developed by students at the Department of Computer Science and Engineering, MBM University, Jodhpur. The electronic harmonium combines traditional harmonium sounds with modern digital technology through custom PCB design and Arduino-based control.

## 📋 Features

- 🎵 12-key polyphonic sound generation (one full octave)
- 🔊 Capacitive touch-based keyboard for intuitive playing
- 🎚️ Adjustable octave selection (8 octaves total)
- 🎛️ Volume control via potentiometer
- 🎼 Multiple scale options (Standard, Harmonic, Minor)
- 💡 LED indicators for visual feedback
- 🔌 Custom PCB design for reliable operation
- 🔋 Battery or USB powered operation

## 🛠️ Components Required

| Component | Quantity | Purpose |
|-----------|----------|---------|
| Arduino Nano | 1 | Main controller |
| PCB | 1 | Custom designed circuit board |
| Capacitive Touch Sensors | 12 | For keyboard keys |
| Audio Amplifier (PAM8403) | 1 | Amplifies audio signal |
| Speaker (8 ohm, 2W) | 1 | Sound output |
| Tactile Buttons | 2 | Octave up/down controls |
| LEDs | 2 | Octave indicators |
| Potentiometer (10K) | 1 | Volume control |
| Rotary Switch or Pot | 1 | Scale selection |
| Battery Holder | 1 | For portable power |
| Power Switch | 1 | On/Off control |
| Resistors & Capacitors | Multiple | Various circuit functions |
| 3.5mm Audio Jack | 1 | External audio output |

## 📝 PCB Design

Our PCB is designed using KiCAD and features:

### Design Overview
- 2-layer PCB (top and bottom)
- Dimensions: 160mm x 100mm
- 1.6mm FR4 material with HASL finish
- Silk screen for component placement guides
- Designed for easy soldering and assembly

### Key PCB Features
- Touch key layout in traditional harmonium style
- Integrated microcontroller section with ICSP header
- Audio amplifier section with proper isolation
- Power management circuit with filtering capacitors
- Clearly labeled inputs and outputs

### PCB Sections

#### 1. Microcontroller Section
- Arduino Nano/ATmega328P footprint
- Supporting components (crystal, capacitors)
- Programming header
- Power regulation circuitry

#### 2. Touch Sensor Array
- 12 copper pad touch sensors
- Touch sensitivity adjustment circuit
- Signal conditioning components

#### 3. Audio Section
- PAM8403 amplifier circuit
- Volume control interface
- Speaker and headphone outputs
- Audio filtering components

#### 4. Power Management
- Battery input protection
- USB/Battery power selection
- Power-on indicator LED
- Voltage regulation

### Design Considerations
- Signal integrity for clean audio output
- Ground plane optimization for noise reduction
- Component placement for intuitive assembly
- Thermal considerations for power components
- ESD protection for touch inputs

## 💻 Circuit Diagram

```
                  ┌────────────────────┐
                  │     Arduino Nano   │
                  │                    │
┌───────────┐     │                D2 ├───── Touch Key 1
│ Power     │     │                D3 ├───── Touch Key 2
│ Circuit   ├─────┤ 5V            ... │
│           │     │                D12├───── Touch Key 11
└───────────┘     │                A0 ├───── Touch Key 12
                  │                   │
                  │                A1 ├───── Octave Up LED
                  │                A2 ├───── Octave Down LED
                  │                   │
                  │                A3 ├───── Octave Up Button
┌───────────┐     │                A4 ├───── Octave Down Button
│ Volume    ├─────┤ A6                │
│ Control   │     │                   │
└───────────┘     │                A7 ├───── Scale Selector
                  │                   │
                  │                A5 ├┐
                  └────────────────────┘│
                                        │
                                        │
                         ┌──────────────┘
                         │
                   ┌─────────────┐
                   │  PAM8403    │
                   │ Amplifier   │
                   │             │
                   └─────────────┘
                         │
                         │
                     ┌───────┐
                     │Speaker│
                     └───────┘
```

## 🔌 PCB Manufacturing Guidelines

### Specifications for PCB Fabrication
- **Material**: FR4
- **Thickness**: 1.6mm
- **Copper Weight**: 1oz (35μm)
- **Surface Finish**: HASL (preferred) or ENIG
- **Solder Mask**: Green (or color of choice)
- **Silkscreen**: White
- **Min Track Width**: 10mil
- **Min Spacing**: 10mil
- **Min Hole Size**: 0.3mm

### Assembly Guidelines
1. Start with passive components (resistors, capacitors)
2. Solder the microcontroller socket (do not directly solder the Arduino)
3. Mount power regulation components
4. Add amplifier IC and audio components
5. Mount connectors and interface components
6. Install the Arduino Nano last

### Testing the PCB
Use the provided `PCBTestRoutine.ino` code to verify all PCB functions:
1. LED indicators
2. Touch sensor functionality
3. Audio output
4. Control buttons and potentiometers

## 📶 Software Architecture

The software is divided into three main Arduino sketches:

1. **ElectronicHarmonium.ino**
   - Main program for harmonium operation
   - Sound generation and key handling
   - User interface management

2. **CapacitiveSensing.ino**
   - Dedicated code for capacitive touch calibration
   - Touch sensitivity testing and adjustment

3. **PCBTestRoutine.ino**
   - Comprehensive testing suite for assembled PCB
   - Component verification routines

### Required Libraries
- Tone.h - For sound generation
- CapacitiveSensor.h - For touch key functionality

## 🚀 Getting Started

### PCB Fabrication:
1. Download the provided Gerber files
2. Submit to your preferred PCB manufacturer (JLCPCB, PCBWay, etc.)
3. Order components from the BOM (Bill of Materials)
4. Assemble the PCB following the assembly guidelines

### Software Setup:
1. **Install Arduino IDE:**
   - Download and install the [Arduino IDE](https://www.arduino.cc/en/software)
   - Install required libraries via Library Manager

2. **Upload Test Code:**
   - Connect your assembled PCB via USB
   - Upload `PCBTestRoutine.ino` first to verify all components
   - Follow the test instructions in the Serial Monitor

3. **Calibrate Touch Sensors:**
   - Upload `CapacitiveSensing.ino`
   - Adjust touch sensitivity parameters as needed
   - Document the optimal threshold values

4. **Main Program:**
   - Upload `ElectronicHarmonium.ino`
   - Update with your calibrated touch thresholds if necessary

## 🎵 Using Your Electronic Harmonium

### Playing the Instrument
1. Power on the harmonium
2. Select your preferred scale using the scale selector
3. Set volume to desired level
4. Touch the keys to play notes
5. Use octave up/down buttons to change octave range

### Maintenance Tips
- Keep the touch surfaces clean for optimal sensitivity
- Store in a dry place to prevent moisture damage to the PCB
- Check battery terminals regularly for corrosion
- Update firmware as new versions become available

## 🔍 Troubleshooting

| Problem | Possible Cause | Solution |
|---------|----------------|----------|
| No power | Battery issue | Check battery, connections, power switch |
| No sound | Amplifier/speaker issue | Check audio connections, volume setting |
| Keys not responsive | Touch calibration | Recalibrate touch sensors |
| Inconsistent touch | Grounding issue | Ensure proper grounding of the circuit |
| Distorted sound | Volume too high | Reduce volume or check speaker integrity |
| Random notes playing | EMI interference | Improve shielding, check ground connections |
| LEDs not working | Connection issue | Verify LED connections and polarity |

## 🔮 Future Enhancements

- Add MIDI output capability
- Implement additional scales and tuning systems
- Create a companion mobile app via Bluetooth
- Add preset storage for different harmonium sounds
- Integrate LCD display for better visual feedback
- Develop polyphony for simultaneous note playing
- Add effects like sustain and vibrato

## 👥 Contributors

- Team Members, Department of Computer Science and Engineering, MBM University, Jodhpur

## 📄 License

This project is open-source and available under the MIT License.

---

<p align="center">Department of Computer Science and Engineering<br>MBM University, Jodhpur</p>