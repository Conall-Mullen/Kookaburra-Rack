#include "plugin.hpp"
#include <dsp/ringbuffer.hpp>
#include "daisysp.h"
#include "../libDaisy/src/util/ringbuffer.h"
#include <stdio.h>

struct Kookaburra : Module {
	enum ParamId {
		GRAIN_SIZE_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		CV_IN_INPUT,
		AUDIO_IN_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		AUDIO_OUT_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	Kookaburra() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(GRAIN_SIZE_PARAM, 0.f, 1.f, 0.f, "Grain Size");
		configInput(CV_IN_INPUT, "CV in");
		configInput(AUDIO_IN_INPUT, "In");
		configOutput(AUDIO_OUT_OUTPUT, "Out");
	}

	void process(const ProcessArgs& args) override {
		ring_buffer[i] = inputs[AUDIO_IN_INPUT].getVoltage();
		i++;
		if(i > (buffer_size - 1))
			i = 0;
		grain_size = static_cast<size_t>(params[GRAIN_SIZE_PARAM].getValue() * 2500);
		outputs[AUDIO_OUT_OUTPUT].setVoltage(ring_buffer[i % (grain_size + 10)]);
	}
	static const size_t buffer_size = 48000;
	size_t i = 0;
	size_t grain_size = 1250;
	float ring_buffer[buffer_size];
}; 


struct KookaburraWidget : ModuleWidget {
	KookaburraWidget(Kookaburra* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/Kookaburra.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.287, 31.547)), module, Kookaburra::GRAIN_SIZE_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(15.287, 54.654)), module, Kookaburra::CV_IN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(15.287, 77.762)), module, Kookaburra::AUDIO_IN_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(15.287, 100.87)), module, Kookaburra::AUDIO_OUT_OUTPUT));
	}
};


Model* modelKookaburra = createModel<Kookaburra, KookaburraWidget>("Kookaburra");