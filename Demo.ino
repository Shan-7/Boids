#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Boid parameters
const int NUM_BOIDS = 10;
float posX[NUM_BOIDS], posY[NUM_BOIDS], velX[NUM_BOIDS], velY[NUM_BOIDS];
const float MAX_SPEED = 5;
const float PERCEPTION_RADIUS = 20;
const float SEPARATION_RADIUS = 10;

// Initialize boids randomly
void setupBoids() {
    for (int i = 0; i < NUM_BOIDS; i++) {
        posX[i] = SCREEN_WIDTH / 2; // Start at center
        posY[i] = SCREEN_HEIGHT / 2;
        velX[i] = random(-MAX_SPEED, MAX_SPEED);
        velY[i] = random(-MAX_SPEED, MAX_SPEED);
    }
}

// Boid rules
void updateBoids() {
    for (int i = 0; i < NUM_BOIDS; i++) {
        float alignX = 0, alignY = 0;
        float cohesionX = 0, cohesionY = 0;
        float separationX = 0, separationY = 0;
        int count = 0;

        for (int j = 0; j < NUM_BOIDS; j++) {
            if (i != j) {
                float dist = sqrt(pow(posX[i] - posX[j], 2) + pow(posY[i] - posY[j], 2));

                // Alignment (match velocity)
                if (dist < PERCEPTION_RADIUS) {
                    alignX += velX[j];
                    alignY += velY[j];
                    cohesionX += posX[j];
                    cohesionY += posY[j];
                    count++;
                }

                // Separation (avoid crowding)
                if (dist < SEPARATION_RADIUS) {
                    separationX += posX[i] - posX[j];
                    separationY += posY[i] - posY[j];
                }
            }
        }

        if (count > 0) {
            alignX /= count;
            alignY /= count;
            cohesionX = (cohesionX / count - posX[i]) * 0.01;
            cohesionY = (cohesionY / count - posY[i]) * 0.01;
        }

        // Update velocity with weighted behaviors
        velX[i] += (alignX * 0.05) + cohesionX + separationX * 0.05;
        velY[i] += (alignY * 0.05) + cohesionY + separationY * 0.05;

        // Limit speed
        float speed = sqrt(velX[i] * velX[i] + velY[i] * velY[i]);
        if (speed > MAX_SPEED) {
            velX[i] = (velX[i] / speed) * MAX_SPEED;
            velY[i] = (velY[i] / speed) * MAX_SPEED;
        }

        // Update position
        posX[i] += velX[i];
        posY[i] += velY[i];

        // Wrap around screen
        if (posX[i] < 0) posX[i] = SCREEN_WIDTH;
        if (posX[i] > SCREEN_WIDTH) posX[i] = 0;
        if (posY[i] < 0) posY[i] = SCREEN_HEIGHT;
        if (posY[i] > SCREEN_HEIGHT) posY[i] = 0;
    }
}

// Draw boids on OLED
void drawBoids() {
    display.clearDisplay();
    for (int i = 0; i < NUM_BOIDS; i++) {
        display.fillCircle(posX[i], posY[i], 2, SSD1306_WHITE);
    }
    display.display();
}

void showIntro() {
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(20, 20);
    display.println("Boids");
    display.setCursor(20, 40);
    display.println("Algorithm");
    display.display();
    delay(2000); // Display for 2 seconds
}

void setup() {
    Serial.begin(115200);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }
    
    showIntro();  // Show "Boids Algorithm" before starting

    display.clearDisplay();
    display.display();
    setupBoids();
}

void loop() {
    updateBoids();
    drawBoids();
    delay(50); // Adjust speed of movement
}
