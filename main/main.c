#include <stdio.h>
#include <string.h>
#include <math.h>



#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"
#include "driver/sigmadelta.h"
#include "esp_system.h"
#include "esp_vfs.h"
#include "esp_vfs_fat.h"
#include "esp_log.h"
#include "spiffs_vfs.h"
#include "driver/gpio.h"
#include "soc/uart_struct.h"


// #include "simple.inc"

#define BLINK_GPIO 2

#define ECHO_TEST_TXD  4
#define ECHO_TEST_RXD  5
#define ECHO_TEST_RTS  18
#define ECHO_TEST_CTS  19

#define BUF_SIZE 256

const int uart_num = UART_NUM_1;
uint8_t* data;
int second;

float inbuf[64], outbuf[128];  // one input channel, two output channels
                                // block size 64, one tick per buffer


// void hello_task(void *pvParameter)
// {
// 	while(1)
// 	{
// 	    printf("Hello world!\n");
// 	    vTaskDelay(500 / portTICK_RATE_MS);
// 	}
// }

#include "z_libpd.h"

pid_t fork() {
  return 0;
}

void pipe(int x) {
}

void dup2(int a, int b) {
}

int execl(const char *p, const char *args, ...) {
  return 0;
}

char *getcwd(char *c) {
  return "";  
}

uid_t getuid(void) {
  return 0;
}

void setuid(uid_t x) {
}

void d_soundfile_setup(void) {
}

void pdprint(const char *s) {
  printf("%s", s);
}

void pdnoteon(int ch, int pitch, int vel) {
  printf("noteon: %d %d %d\n", ch, pitch, vel);
}

/*
int main(int argc, char **argv) {
  if (argc < 3) {
    fprintf(stderr, "usage: %s file folder\n", argv[0]);
    return -1;
  }
  // now run pd for ten seconds (logical time)
  return 0;
}
*/

// void blinky(void *pvParameter)
// {
//     gpio_pad_select_gpio(BLINK_GPIO);
//     /* Set the GPIO as a push/pull output */
//     gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
//     while(1) {
//         /* Blink on (output high) */
//         gpio_set_level(BLINK_GPIO, 1);
//         second = 1;
//         vTaskDelay(1000 / portTICK_RATE_MS);
//         /* Blink off (output low) */
//         gpio_set_level(BLINK_GPIO, 0);
//         second = 0;
//         vTaskDelay(1000 / portTICK_RATE_MS);
//         /* Blink on (output high) */
//         gpio_set_level(BLINK_GPIO, 1);
//         second = 1;
//         vTaskDelay(200 / portTICK_RATE_MS);
//         /* Blink off (output low) */
//         gpio_set_level(BLINK_GPIO, 0);
//         second = 0;
//         vTaskDelay(800 / portTICK_RATE_MS);
//     }
// }

void pdloop(void *pvParameter)
{
    // gpio_pad_select_gpio(BLINK_GPIO);
    /* Set the GPIO as a push/pull output */
    // gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    // char *buf = "bauds=115200\xFF\xFF\xFF";
    // uart_write_bytes(uart_num, (const char*) buf, strlen(buf));
    // buf = "baud=115200\xFF\xFF\xFF";
    // uart_write_bytes(uart_num, (const char*) buf, strlen(buf));
    // buf = "vis 255,0\xFF\xFF\xFF";
    // uart_write_bytes(uart_num, (const char*) buf, strlen(buf));

    // int N = 1;
    // int X = 10;
    // int Y = 10;
    // int DX = 1;
    // int DY = 0;
    // int VY = 0;

    // int timer = 0;
    // float t = 0.0;
    int frame = 0;

    long samples = 0;

    // char *textbuffer = malloc(100);

    // char *buf3 = "cls 1\xFF\xFF\xFF";
    // uart_write_bytes(uart_num, (const char*) buf3, strlen(buf3));

  float duty = 0;
    while(1) {
        vTaskDelay(10 / portTICK_RATE_MS);

        int i, j;
        for (i = 0; i < 2; i++) {
          // fill inbuf here
          for(j = 0; j<64; j++) {
            inbuf[j] = 0.0f;
          }

          libpd_process_float(1, inbuf, outbuf);
          samples += 64;
          // use outbuf here
        }

        // int duty = (int)(127.0f * outbuf[0]);
        sigmadelta_set_duty(SIGMADELTA_CHANNEL_0, (int)duty);

        duty += 0.1;
        if (duty > 120) duty = -120;

        if (frame % 10 == 0) {
          printf("%d (%ld): %1.3f %1.3f (%d)\n", frame, samples, outbuf[0], outbuf[64], (int)duty);
        }

        // vTaskDelay(1000 / portTICK_RATE_MS);

        // printf("Rendering image #%d\n", N);
        // sprintf(textbuffer, "pic %d,%d,%d\xFF\xFF\xFF", X,Y,N);
        // uart_write_bytes(uart_num, (const char*) textbuffer, strlen(textbuffer));

        // for(int k=frame%3; k<240; k+=3) {
        //     float kt = t - (float)k * 0.1;
        //     float dy = k + 20 + 10 * sin(kt / 6.0);
        //     float dx = 40 + 10 * cos(kt / 7.0) + 10 * sin(kt / 8.0);

        //     sprintf(textbuffer, "xpic %d,%d,%d,%d,%d,%d,%d\xFF\xFF\xFF", 60,k, 200,1, (int)dx,(int)dy, 1+second);
        //     // printf("Sending: %s\n", textbuffer);
        //     uart_write_bytes(uart_num, (const char*) textbuffer, strlen(textbuffer));
        // }

        // N ++;
        // if (N > 100) {
        //     N = 0;
        // }

        // X += 10;
        // if (X > 180) {
        //     X = 0;
        // }

        // Y += 10;
        // if (Y > 50) {
        //     Y = 0;
        // }

        // memset(data, 0, BUF_SIZE);
        // int len = uart_read_bytes(uart_num, data, BUF_SIZE, 1 / portTICK_RATE_MS);
        // if (len > 0) {
        //     printf("Got %d bytes.\n", len);
        //     for(int k=0; k<len; k++) {
        //         printf("0x%02X ", data[k]);
        //         if (k % 16 == 15) printf("\n");
        //     }
        //     printf("\n");
        // }

        // vTaskDelay(1000 / portTICK_RATE_MS);
        // char *buf2 = "cls RED\xFF\xFF\xFF";
        // uart_write_bytes(uart_num, (const char*) buf2, strlen(buf2));
        // char *buf5 = "pic 30,40,2\xFF\xFF\xFF";
        // uart_write_bytes(uart_num, (const char*) buf5, strlen(buf5));

        // timer ++;
        // t += 1.0;
        frame ++;
    }
}

void app_main()
{
    printf("Hellow orld\n");

    printf("Setting up vfs...\n");

     sigmadelta_config_t sigmadelta_cfg = {
       .channel = SIGMADELTA_CHANNEL_0,
       .sigmadelta_duty = 10,
       .sigmadelta_prescale = 256,
       .sigmadelta_gpio = 2,
     };
    sigmadelta_config(&sigmadelta_cfg);

    vfs_spiffs_register();

   	do {
      printf("waiting for vfs registration.\n");
		  vTaskDelay(50 / portTICK_RATE_MS);
    } while (!spiffs_is_registered);

   	do {
      printf("waiting for vfs mount.\n");
		  vTaskDelay(50 / portTICK_RATE_MS);
    } while (!spiffs_is_mounted);

    // FILE *f = fopen("/spiffs/simple.pd", "rb");
    // printf("f = %X\n", (int)f);
    // if (f != NULL) {
    //   // if (f)
    //   fseek(f, 0, SEEK_END);
    //   int len = ftell(f);
    //   printf("len = %d\n", len);
    //   fseek(f, 0, SEEK_SET);
    //   int pos = ftell(f);
    //   printf("pos = %d\n", pos);
    //   /* int len = ftell(f);
    //   char textbuf[10] = { 0, };
    //   fread(&textbuf, 1, 8, f);
    //   printf("textbuf = \"%s\"\n", textbuf);
    //   */
    //   fclose(f);
    // }

    printf("before libpd setup\n");
    // // init pd
    int srate = 44100;
    libpd_set_printhook(pdprint);
    libpd_set_noteonhook(pdnoteon);
    libpd_init();
    libpd_init_audio(1, 2, srate);
    // compute audio    [; pd dsp 1(
    libpd_start_message(1); // one entry in list
    libpd_add_float(1.0f);
    libpd_finish_message("pd", "dsp");

    printf("after libpd setup\n");

    // open patch       [; pd open file folder(
    libpd_openfile("simple.pd", "/spiffs");

    printf("after libpd open\n");

    // uart_config_t uart_config = {
    //     .baud_rate = 115200, // 9600,
    //     .data_bits = UART_DATA_8_BITS,
    //     .parity = UART_PARITY_DISABLE,
    //     .stop_bits = UART_STOP_BITS_1,
    //     .flow_ctrl = UART_HW_FLOWCTRL_DISABLE, // UART_HW_FLOWCTRL_CTS_RTS,
    //     .rx_flow_ctrl_thresh = 122,
    // };
    // uart_param_config(uart_num, &uart_config);
    // //Set UART1 pins(TX: IO4, RX: I05, RTS: IO18, CTS: IO19)
    // uart_set_pin(uart_num, ECHO_TEST_TXD, ECHO_TEST_RXD, ECHO_TEST_RTS, ECHO_TEST_CTS);
    // uart_driver_install(uart_num, BUF_SIZE * 2, 0, 0, NULL, 0);
    // data = (uint8_t*) malloc(BUF_SIZE);

    xTaskCreate(&pdloop, "pd", 16384, NULL, 10, NULL);
    // pdloop(NULL);
}

