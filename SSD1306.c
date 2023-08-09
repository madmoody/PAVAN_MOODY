#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLEDADD 0x3C
#define PATH "/dev/i2c-2"
int fd;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void OLED_Init() {
    display.begin(SSD1306_I2C_ADDRESS, OLEDADD);
    display.display();
    delay(2000); // Delay for initialization

    display.clearDisplay();
}

void I2C_Init() {
    fd = open(PATH, O_RDWR);
    if (fd < 0) {
        printf(": Path is not open : ");
        exit(1);
    }
    if (ioctl(fd, I2C_SLAVE, OLEDADD) < 0) {
        printf(" : Failed to Set OLED : ");
        exit(1);
    }
}

void OLED_Print(const char *str) {
    display.setTextSize(1);      // Set text size
    display.setTextColor(SSD1306_WHITE); // Set text color
    display.setCursor(0, 0);     // Set text position
    display.println(str);        // Print text
    display.display();
}

int main() {
    I2C_Init();
    OLED_Init();
    OLED_Print("Hello World");
    while (1) {
        // Your main application code here
    }

    return 0;
}
