/* 1. Include headers & define constants */
#include "main.h"
#include "arm_math.h" // CMSIS-DSP library
#include "ssd1306.h"  // OLED driver

/* 2. Global variables & buffer definitions (must be 32-byte aligned for DMA) */
#define AUDIO_BLOCK_SIZE 256
int32_t dma_buffer[AUDIO_BLOCK_SIZE * 2]; // Double buffer
float32_t dsp_in_buffer[AUDIO_BLOCK_SIZE];
float32_t dsp_out_buffer[AUDIO_BLOCK_SIZE];

/* 3. Filter instance & coefficient definitions */
arm_biquad_casd_df1_inst_f32 filter_instance;
float32_t filter_state[4 * NUM_STAGES];
const float32_t filter_coeffs[5 * NUM_STAGES] = { ... }; // Calculated offline

/* 4. Callback function: Core of audio processing */
void HAL_I2S_RxHalfCpltCallback(I2S_HandleTypeDef *hi2s) {
    // Half-full: Process first half of buffer
    process_audio_block(&dma_buffer[0]);
}

void HAL_I2S_RxCpltCallback(I2S_HandleTypeDef *hi2s) {
    // Full: Process second half of buffer
    process_audio_block(&dma_buffer[AUDIO_BLOCK_SIZE]);
}

/* 5. DSP processing function */
void process_audio_block(int32_t *input) {
    // a. Convert int32 to float32
    // b. Call arm_biquad_cascade_df1_f32() for filtering
    // c. Scale volume
    // d. Convert back to int32 and write to output buffer
}

/* 6. Main function */
int main(void) {
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_I2S_Init();
    MX_DMA_Init();
    MX_I2C_Init(); // For OLED

    // Initialize OLED, filter states, etc.
    ssd1306_Init();
    arm_biquad_cascade_df1_init_f32(&filter_instance, NUM_STAGES, filter_coeffs, filter_state);

    // Start I2S DMA reception (circular mode)
    HAL_I2S_Receive_DMA(&hi2s, (uint16_t*)dma_buffer, AUDIO_BLOCK_SIZE * 2);

    while (1) {
        // UI task: Read rotary encoder, update volume/filter coefficients, refresh OLED
        // Note: Do not put time-consuming operations here; ensure audio processing priority
    }
}