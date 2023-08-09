#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define OLEDADD 0x3C
#define PATH "/dev/i2c-2"
int fd;

void OLED_Init(){
char OledWrite[1];

OledWrite[0] = 0xAE;
OledWrite[1] = 0xAF;

write(fd,OledWrite,1);

}

void I2C_Init(){
fd = open(PATH,O_RDWR);
if(fd < 0){
printf(": Path is not open : ");
return 1;
}
if(ioctl(fd,I2C_SLAVE,OLEDADD<0){
printf(" : Failed to Set OLED : ");
return 1;	
}
}

void Oled_display(char Character){
char OledWrite[1];
OledWrite[0] = 0x00;
OledWrite[1] = character;

write(fd,OledWrite,1);
}


void OLED_Print(char const *str){
while(*str){
Oled_display(*str);
str++;	
}

}

int main(){
I2C_Init();
OLED_Init();
OLED_Print("Hello World");
while(1);

}
