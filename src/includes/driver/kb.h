#pragma once
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <libs/string.h>


uint8_t kybrd_enc_read_buf ();
uint8_t kybrd_ctrl_read_status ();
void kybrd_ctrl_send_cmd (uint8_t cmd);
void kybrd_enc_send_cmd (uint8_t cmd);
void kkybrd_set_leds (bool num, bool caps, bool scroll);
string kb_input();

