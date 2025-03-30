# Boids Algorithm on ESP32 with OLED Display  

## Overview  
This project implements the **Boids Algorithm** on an **ESP32**, leveraging its **240MHz dual-core processor** and **400kHz I²C** to render smooth flocking behavior on an **SSD1306 OLED display**.  

## Features  
✅ **Swarm Intelligence Simulation** (Alignment, Cohesion, Separation)  
✅ **Optimized for ESP32’s Floating-Point Processing**  
✅ **High-Speed I²C (400kHz) for OLED Updates**  
✅ **Smooth Motion with Real-Time Updates**  

## Algorithm  
Each boid follows these rules:  
1️⃣ **Alignment:** Matches velocity with nearby boids  
2️⃣ **Cohesion:** Moves toward the center of the flock  
3️⃣ **Separation:** Avoids collisions  

### Equations Used:  
- **Velocity Update:**  
  ```
  V_i = V_i + w_a * A + w_c * C + w_s * S
  ```
- **Speed Constraint:**  
  ```
  V_i = min(V_max, V_i)
  ```
- **Position Update:**  
  ```
  P_i = P_i + V_i
  ```

## Hardware Used  
- **ESP32 (240MHz Dual-Core CPU)**  
- **SSD1306 OLED Display (I²C, 128x64 pixels)**  
- **Libraries:**  
  - Adafruit SSD1306  
  - Adafruit GFX  

## Installation & Usage  
1️⃣ Clone this repository:  
   ```
   git clone https://github.com/Shan-7/boids-esp32.git
   ```  
2️⃣ Install required libraries via Arduino IDE or PlatformIO  
3️⃣ Upload the code to your ESP32  
4️⃣ Watch the **boids flocking animation** on your OLED!  

## Future Enhancements  
- 🔹 **Larger Boid Swarms** for more realistic behavior  
- 🔹 **ESP-NOW Integration** for wireless boid communication  
- 🔹 **Optimization using ESP32’s FreeRTOS for parallel processing**  

---

💡 **Contributions & Ideas Welcome!** Open an issue or fork the repo.  
📩 **Let’s connect!** Ping me on [LinkedIn](https://www.linkedin.com/in/shantanu-shendre/).  

#ESP32 #BoidsAlgorithm #SwarmAI #OLED #EmbeddedSystems #Arduino #MachineLearning
