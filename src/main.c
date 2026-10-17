#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "miniaudio.h"

#define CHANNELS    2
#define SAMPLE_RATE 44100

#define PI 3.14159265358979324f

typedef struct {
	float root;
	int harmonics;
	float dropoff;
} Note;

typedef struct {
	float t;
	Note note;
} UserData;

float note_at(float t, Note note) {
	float result = 0.0f;
	for (int i = note.harmonics; i > 0; --i) {
		result *= note.dropoff;
		result += sinf(2*PI*note.root * i * t);
	}
	return result;
}

void data_callback(ma_device* device, void* output, const void*, uint32_t frame_count) {
	UserData* data = device->pUserData;
	float t = data->t;
	for (uint32_t frame = 0; frame < frame_count; ++frame) {
		int16_t ft = INT16_MAX * note_at(t, data->note) / 4;
		t += 1.0f / device->sampleRate;
		for (size_t i = 0; i < CHANNELS; ++i) {
			((int16_t *) output)[frame * CHANNELS + i] = ft;
		} 
	}
	data->t = t;
}

int main(int, char**) {
	UserData data = {
		0.0f,
		(Note){220.0f, 8, 0.3f}
	};


	ma_device_config config = ma_device_config_init(ma_device_type_playback);
	config.playback.format   = ma_format_s16;
	config.playback.channels = CHANNELS;
	config.sampleRate        = SAMPLE_RATE;
	config.dataCallback      = data_callback;
	config.pUserData         = &data;


	ma_device device;
	if (ma_device_init(NULL, &config, &device) != MA_SUCCESS) {
		printf("miniaudio device creation failed\n"); getchar();
		return 1;
	}
	ma_device_start(&device);

	getchar();

	ma_device_uninit(&device);

	return 0;
}

