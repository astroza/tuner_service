/* (c) 2016 - Felipe Astroza (felipe@astroza.cl)
 * Under BSD license
 */
#include "webservice.h"
#include "fmlib.h"
#include <stdlib.h>

#define TUNER_DEVICE 	"/dev/radio0"
#define TUNER_INDEX 	0
DUDA_REGISTER("V4L2 Tuner Service", "Tuner");

struct tuner radio_tuner;

static int getpost_double_param(duda_request_t *dr, double *param_value)
{
    char *data, *endp;
    unsigned long len;
    unsigned long value_str_len;
    char value_str[16];
    double value;

    if (request->is_post(dr) == MK_TRUE) {
        data = request->get_data(dr, &len);
        gc->add(dr, data);
       	value_str_len = len > sizeof(value_str)-1? sizeof(value_str)-1 : len;
        memcpy(value_str, data, value_str_len);
        value_str[value_str_len] = 0;
        value = strtod(value_str, &endp);
        if(endp != data) {
            *param_value = value;
            return 0;
        } else
            return -1;
    }
    return 0;
}

void cb_frequency(duda_request_t *dr)
{
    static double current_frequency = 89.50;
    double frequency = current_frequency;
    int status = 200;

    if(getpost_double_param(dr, &frequency) == 0) {
        if(frequency != current_frequency) {
            if(tuner_set_freq(&radio_tuner, (long long int)(frequency * 16000), 0) == 0)
                current_frequency = frequency;
            else
                status = 400;
        }
    } else
        status = 400;

    response->http_status(dr, status);
    response->printf(dr, "%.2f\n", current_frequency);
    response->end(dr, NULL);
}

void cb_volume(duda_request_t *dr)
{
    double current_volume = tuner_get_volume(&radio_tuner);
    double volume = current_volume;
    int status = 200;

    if(getpost_double_param(dr, &volume) == 0) {
        if(volume != current_volume) {
            if(tuner_set_volume(&radio_tuner, volume) == 0)
                current_volume = volume;
            else
                status = 400;
        }
    } else
        status = 400;

    response->http_status(dr, status);
    response->printf(dr, "%.2f\n", current_volume);
    response->end(dr, NULL);
}

int duda_main()
{
    if(tuner_open(&radio_tuner, TUNER_DEVICE, TUNER_INDEX) != 0)
        return MK_ERROR;

    map->static_add("/frequency", "cb_frequency");
    map->static_add("/volume", "cb_volume");

    return 0;
}
