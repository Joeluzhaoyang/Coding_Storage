// This object represent the waveform generator
var WaveformGenerator = {
    // The generateWaveform function takes 4 parameters:
    //     - type, the type of waveform to be generated
    //     - frequency, the frequency of the waveform to be generated
    //     - amp, the maximum amplitude of the waveform to be generated
    //     - duration, the length (in seconds) of the waveform to be generated
    generateWaveform: function(type, frequency, amp, duration) {
        var nyquistFrequency = sampleRate / 2; // Nyquist frequency
        var totalSamples = Math.floor(sampleRate * duration); // Number of samples to generate
        var result = []; // The temporary array for storing the generated samples

        switch(type) {
            case "sine-time": // Sine wave, time domain
                for (var i = 0; i < totalSamples; ++i) {
                    var currentTime = i / sampleRate;
                    result.push(amp * Math.sin(2.0 * Math.PI * frequency * currentTime));
                }
                break;

            case "square-time": // Square wave, time domain
            var oneCycle = sampleRate / frequency;
            var halfCycle = oneCycle / 2;
                for (var i = 0; i < totalSamples; ++i) {
                    var currentTime = i / sampleRate;
                    var Timedeter = i % parseInt(oneCycle);
                    if (Timedeter < halfCycle)
                        result.push(amp); 
                    else
                        result.push(-amp);
                }
                break;

            case "square-additive": // Square wave, additive synthesis
                for (var i = 0; i < totalSamples; i++) {
                    var t = i / sampleRate;
                    var sample = 0;
                    var k = 1;
                    while (k * frequency < nyquistFrequency) {
                        sample += (1.0 / k) * Math.sin(2 * Math.PI * k * frequency * t);
                        k += 2;
                    }
                    result.push(sample*amp);
                }
                break;

            case "sawtooth-time": // Sawtooth wave, time domain
                var oneCycle = sampleRate / frequency;
                for (var i = 0; i < totalSamples; ++i) {
                    var currentTime = i / sampleRate;
                    var PosInCycle = i % parseInt(oneCycle);
                    var fractionInTheCycle = PosInCycle / oneCycle;
                    result.push(2 * (1.0 - fractionInTheCycle) - 1);
                }
                break;

            case "sawtooth-additive": // Sawtooth wave, additive synthesis
                for (var i = 0; i < totalSamples; i++) {
                    var t = i / sampleRate;
                    var sample = 0;
                    var k = 1;
                    while (k * frequency < nyquistFrequency) {
                        sample += (1.0 / k) *
                            Math.sin(2 * Math.PI * k *
                                frequency * t);
                        k++;
                    }
                    result.push(sample*amp);
                }
                break;

            case "triangle-additive": // Triangle wave, additive synthesis
                for (var i = 0; i < totalSamples; i++) {
                    var t = i / sampleRate;
                    var sample = 0;
                    k = 1;
                    while (k * frequency < nyquistFrequency) {
                        sample += (1.0 / (k * k)) *
                            Math.cos(2 * Math.PI * k *
                                frequency * t);
                        k += 2;
                    }
                    result.push(sample*amp);
                }
                break;

            case "customized-additive-synthesis": // Customized additive synthesis
                /**
                * TODO: Complete this generator
                **/

                // Obtain all the required parameters
				var harmonics = [];
				for (var h = 1; h <= 10; ++h) {
					harmonics.push($("#additive-f" + h).val());
				}

                for (var i = 0; i < totalSamples; i++) {
                    var t = i / sampleRate;
                    var sample = 0;
                    k = 1;
                    while (k * frequency < nyquistFrequency && k <= 10) {
                        sample += parseFloat(harmonics[k-1]) * Math.sin(2 * Math.PI * k * frequency * t);
                        k++;
                    }
                    result.push(sample * amp);
                }

                break;

            case "white-noise": // White noise
                for (var i = 0; i < totalSamples; i++) {
                    result.push(Math.random() * amp * 2 - amp);
                }
                break;

            case "karplus-strong": // Karplus-Strong algorithm
                /**
                * TODO: Complete this generator
                **/

                // Obtain all the required parameters
                var base = $("#karplus-base>option:selected").val();
                var b = parseFloat($("#karplus-b").val());
                var delay = parseInt($("#karplus-p").val());

                break;

            case "fm": // FM
                /**
                * TODO: Complete this generator
                **/
                
                // Obtain all the required parameters
                var carrierFrequency = parseFloat($("#fm-carrier-frequency").val());
                var carrierAmplitude = parseFloat($("#fm-carrier-amplitude").val());
                var modulationFrequency = parseFloat($("#fm-modulation-frequency").val());
                var modulationAmplitude = parseFloat($("#fm-modulation-amplitude").val());
                var sample = 0;
                var useADSR = $("#fm-use-adsr").prop("checked");
                var useFreqMul = $("#fm-use-freq-multiplier").prop("checked");
                if(useFreqMul){
                    carrierFrequency *= frequency;
                    modulationFrequency *= frequency;
                }
                if(useADSR) { // Obtain the ADSR parameters
                    var attackDuration = parseFloat($("#fm-adsr-attack-duration").val()) * sampleRate;
                    var decayDuration = parseFloat($("#fm-adsr-decay-duration").val()) * sampleRate;
                    var releaseDuration = parseFloat($("#fm-adsr-release-duration").val()) * sampleRate;
                    var sustainLevel = parseFloat($("#fm-adsr-sustain-level").val()) / 100.0;
                }

                for (var i = 0; i < totalSamples; ++i) {
                    var currentTime = i / sampleRate;
                    var loopAmp = modulationAmplitude;
                    if (useADSR) {
                        if (i <= attackDuration && i >= 0) {
                            loopAmp *= lerp(0, 1, i / attackDuration);
                        }
                        else if (i > attackDuration && i <= decayDuration + attackDuration) {
                            loopAmp *= lerp(1, sustainLevel, (i - attackDuration) / decayDuration);
                        }
                        else if (i > attackDuration + decayDuration && i <= (6 * sampleRate - releaseDuration)) {
                            loopAmp *= sustainLevel;
                        }
                        else if (i > (6 * sampleRate - releaseDuration) && i <= 6 * sampleRate) {
                            loopAmp *= lerp(sustainLevel, 0, (releaseDuration - (6 * sampleRate - i)) / releaseDuration);
                        }
                    }
                    var modulator = loopAmp * Math.sin(2.0 * Math.PI * modulationFrequency * currentTime);
                    sample = carrierAmplitude * Math.sin(2.0 * Math.PI * carrierFrequency * currentTime + modulator);
                    result.push(sample*amp);
                }

                break;

            case "repeating-narrow-pulse": // Repeating narrow pulse
                var cycle = Math.floor(sampleRate / frequency);
                for (var i = 0; i < totalSamples; ++i) {
                    if(i % cycle === 0) {
                        result.push(amp * 1.0);
                    } else if(i % cycle === 1) {
                        result.push(amp * -1.0);
                    } else {
                        result.push(0.0);
                    }
                }
                break;

            default:
                break;
        }

        return result;
    }
};
