#include <zephyr.h>
#include <device.h>
#include <drivers/i2c.h>
#include <sys/printk.h>

#define TRACKBALL_I2C_ADDRESS 0x0A // Pimoroni Trackball I2C 주소 (기본값)
#define I2C_DEV DT_LABEL(DT_NODELABEL(i2c1))  // I2C 버스 이름 (여기선 i2c1 사용)

#define REG_LED_RED     0x00
#define REG_LED_GRN     0x01
#define REG_LED_BLU     0x02
#define REG_LED_WHT     0x03

// I2C로 LED 색상 설정 함수
int trackball_set_rgb(uint8_t red, uint8_t green, uint8_t blue, uint8_t white)
{
    const struct device *i2c_dev = device_get_binding(I2C_DEV);
    uint8_t data[5];

    // RGBW 값 설정
    data[0] = REG_LED_RED;
    data[1] = red;
    data[2] = green;
    data[3] = blue;
    data[4] = white;

    // I2C로 데이터 전송 (Trackball에 RGBW 값을 설정)
    int ret = i2c_write(i2c_dev, data, sizeof(data), TRACKBALL_I2C_ADDRESS);
    if (ret < 0) {
        printk("Failed to set RGB LED: %d\n", ret);
        return ret;
    }

    printk("RGB LED set to R:%d G:%d B:%d W:%d\n", red, green, blue, white);
    return 0;
}

// 예시: Trackball의 LED를 빨강, 초록, 파랑, 흰색으로 설정
void trackball_test_rgb(void)
{
    // 트랙볼의 LED를 빨간색으로 설정
    trackball_set_rgb(255, 0, 0, 0);
    k_msleep(1000);

    // 트랙볼의 LED를 초록색으로 설정
    trackball_set_rgb(0, 255, 0, 0);
    k_msleep(1000);

    // 트랙볼의 LED를 파란색으로 설정
    trackball_set_rgb(0, 0, 255, 0);
    k_msleep(1000);

    // 트랙볼의 LED를 흰색으로 설정
    trackball_set_rgb(255, 255, 255, 255);
    k_msleep(1000);
}

void main(void)
{
    printk("Starting Trackball RGB Test\n");

    // RGB 테스트 (LED 색 변경)
    trackball_test_rgb();
}
