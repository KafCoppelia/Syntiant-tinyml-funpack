/* Edge Impulse ingestion SDK
 * Copyright (c) 2021 EdgeImpulse Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "src/syntiant.h"
#include <NDP.h>
#include <NDP_utils.h>
#include <Arduino.h>

/**
 * @brief      Called when a inference matches 1 of the features
 *
 * @param[in]  event          The event
 * @param[in]  confidence     The confidence
 * @param[in]  anomaly_score  The anomaly score
 */
typedef enum {
    _BLINK,
    _TURN_ON,
    _TURN_OFF,
    //_Z_OPENSET = 0U
} Led_Status;

Led_Status last_state = _TURN_OFF;

void on_classification_changed(const char *event, float confidence, float anomaly_score) {

    // here you can write application code, e.g. to toggle LEDs based on keywords
    if (strcmp(event, "blink") == 0) {
        blink_cb();
    }

    else if (strcmp(event, "turn_off") == 0) {
        turn_off_cb();
    }

    else if (strcmp(event, "turn_on") == 0) {
        turn_on_cb();
    }

    // if (strcmp(event, "z_openset") == 0) {
    //     others_handle();
    // }
}

void on_classification_unmatched(void) {
    if (last_state == _BLINK)
        blink_cb();
    else if (last_state == _TURN_ON)
        turn_on_cb();
    else
        turn_off_cb();
}

void turn_on_cb() {
    last_state = _TURN_ON;
    digitalWrite(LED_GREEN, HIGH);
}

void turn_off_cb() {
    last_state = _TURN_OFF;
    digitalWrite(LED_GREEN, LOW);
}

void blink_cb() {
    last_state = _BLINK;
    // digitalWrite(LED_BLUE, 1-digitalRead(LED_BLUE));

    digitalWrite(LED_BLUE, HIGH);
    delay(200);
    digitalWrite(LED_BLUE, LOW);
    delay(200);
    digitalWrite(LED_BLUE, HIGH);
    delay(200);
    digitalWrite(LED_BLUE, LOW);
}

void setup(void)
{
    syntiant_setup();
}

void loop(void)
{
    syntiant_loop();
}
