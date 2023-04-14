(function(imageproc) {
    "use strict";

    /*
     * Apply negation to the input data
     */
    imageproc.negation = function(inputData, outputData) {
        console.log("Applying negation...");

        for (var i = 0; i < inputData.data.length; i += 4) {
            outputData.data[i]     = 255 - inputData.data[i];
            outputData.data[i + 1] = 255 - inputData.data[i + 1];
            outputData.data[i + 2] = 255 - inputData.data[i + 2];
        }
    }

    /*
     * Convert the input data to grayscale
     */
    imageproc.grayscale = function(inputData, outputData) {
        console.log("Applying grayscale...");

        /**
         * TODO: You need to create the grayscale operation here
         */

        for (var i = 0; i < inputData.data.length; i += 4) {
            // Find the grayscale value using simple averaging
            var Average_gray = (inputData.data[i] + inputData.data[i+1] + inputData.data[i+2])/3;
            // Change the RGB components to the resulting value

            outputData.data[i] = Average_gray;
            outputData.data[i + 1] = Average_gray;
            outputData.data[i + 2] = Average_gray;
        }
    }

    /*
     * Applying brightness to the input data
     */
    imageproc.brightness = function(inputData, outputData, offset) {
        console.log("Applying brightness...");

        /**
         * TODO: You need to create the brightness operation here
         */

        for (var i = 0; i < inputData.data.length; i += 4) {
            // Change the RGB components by adding an offset

            outputData.data[i]     = inputData.data[i] + offset;
            if(outputData.data[i] < 0){
                outputData.data[i] = 0;
            } else if (outputData.data[i]>255){
                outputData.data[i] = 255;
            }

            outputData.data[i + 1] = inputData.data[i + 1] + offset;
            if (outputData.data[i+1] < 0) {
                outputData.data[i+1] = 0;
            } else if (outputData.data[i+1] > 255) {
                outputData.data[i+1] = 255;
            }

            outputData.data[i + 2] = inputData.data[i + 2] + offset;
            if (outputData.data[i+2] < 0) {
                outputData.data[i+2] = 0;
            } else if (outputData.data[i+2] > 255) {
                outputData.data[i+2] = 255;
            }

            // Handle clipping of the RGB components
        }
    }

    /*
     * Applying contrast to the input data
     */
    imageproc.contrast = function(inputData, outputData, factor) {
        console.log("Applying contrast...");

        /**
         * TODO: You need to create the brightness operation here
         */

        for (var i = 0; i < inputData.data.length; i += 4) {
            // Change the RGB components by multiplying a factor

            outputData.data[i]     = inputData.data[i] * factor;
            if (outputData.data[i] < 0) {
                outputData.data[i] = 0;
            } else if (outputData.data[i] > 255) {
                outputData.data[i] = 255;
            }

            outputData.data[i + 1] = inputData.data[i + 1] * factor;
            if (outputData.data[i + 1] < 0) {
                outputData.data[i + 1] = 0;
            } else if (outputData.data[i + 1] > 255) {
                outputData.data[i + 1] = 255;
            }

            outputData.data[i + 2] = inputData.data[i + 2] * factor;
            //outputData.data[i + 2] = inputData.data[i + 2] + offset;
            if (outputData.data[i + 2] < 0) {
                outputData.data[i + 2] = 0;
            } else if (outputData.data[i + 2] > 255) {
                outputData.data[i + 2] = 255;
            }

            // Handle clipping of the RGB components
        }
    }

    /*
     * Make a bit mask based on the number of MSB required
     */
    function makeBitMask(bits) {
        var mask = 0;
        for (var i = 0; i < bits; i++) {
            mask >>= 1;
            mask |= 128;
        }
        return mask;
    }

    /*
     * Apply posterization to the input data
     */
    imageproc.posterization = function(inputData, outputData,
                                       redBits, greenBits, blueBits) {
        console.log("Applying posterization...");

        /**
         * TODO: You need to create the posterization operation here
         */

        // Create the red, green and blue masks
        // A function makeBitMask() is already given

        for (var i = 0; i < inputData.data.length; i += 4) {
            // Apply the bitmasks onto the RGB channels

            outputData.data[i]     = inputData.data[i] & makeBitMask(redBits);
            outputData.data[i + 1] = inputData.data[i + 1] & makeBitMask(greenBits);
            outputData.data[i + 2] = inputData.data[i + 2] & makeBitMask(blueBits);
        }
    }

    /*
     * Apply threshold to the input data
     */
    imageproc.threshold = function(inputData, outputData, thresholdValue) {
        console.log("Applying thresholding...");

        /**
         * TODO: You need to create the thresholding operation here
         */

        for (var i = 0; i < inputData.data.length; i += 4) {
            // Find the grayscale value using simple averaging
            // You will apply thresholding on the grayscale value
            var GrayScale = (inputData.data[i] + inputData.data[i + 1] + inputData.data[i+2])/3;
            // Change the colour to black or white based on the given threshold
            if(GrayScale < thresholdValue){
                outputData.data[i] = 0;
                outputData.data[i + 1] = 0;
                outputData.data[i + 2] = 0;
            }else{
                outputData.data[i] = 255;
                outputData.data[i + 1] = 255;
                outputData.data[i + 2] = 255;
            }
        }
    }

    /*
     * Build the histogram of the image for a channel
     */
    function buildHistogram(inputData, channel) {
        var histogram = [];
        for (var i = 0; i < 256; i++)
           {histogram[i] = 0;}
        
        switch(channel){
        case "gray":
            for(var i = 0; i < inputData.data.length; i++){
                var grays = parseInt((inputData.data[i*4]+inputData.data[i*4+1]+
                            inputData.data[i*4+2])/3);
                histogram[grays]++;
            }
            break;

        case "red":
            for(var i = 0; i < inputData.data.length; i++){
                var grays = inputData.data[i*4];
                histogram[grays]++;
            }
            break;
        case "green":
                for (var i = 0; i < inputData.data.length; i++) {
                    var grays = inputData.data[i * 4+1];
                    histogram[grays]++;
                }
                break;
        case "blue":
                for (var i = 0; i < inputData.data.length; i++) {
                    var grays = inputData.data[i * 4+2];
                    histogram[grays]++;
                }
                break;
        }
        /**
         * TODO: You need to build the histogram here
         */

        // Accumulate the histogram based on the input channel
        // The input channel can be:
        // "red"   - building a histogram for the red component
        // "green" - building a histogram for the green component
        // "blue"  - building a histogram for the blue component
        // "gray"  - building a histogram for the intensity
        //           (using simple averaging)

        return histogram;
    }

    /*
     * Find the min and max of the histogram
     */
    function findMinMax(histogram, pixelsToIgnore) {
        var min = 0, max = 255;
        var pixalmin = pixelsToIgnore;
        /**
         * TODO: You need to build the histogram here
         */
        if(pixelsToIgnore == 0){
            for(var i = 0; i < 256; i++){
                if(histogram[i] > 0 ){
                    min = i;
                    break;
                }
            }
            for(var i = 255; i > -1; i--){
                if(histogram[i] > 0){
                    max = i;
                    break;
                }
            }
        }
        else{
            for (var i = 0; i < 256; i++) {
                pixalmin -= histogram[i];
                if (pixalmin <= 0 && histogram[i] != 0) {
                    min = i;
                    break;
                }
            }
            pixalmin = pixelsToIgnore;
            for (var i = 255; i > -1; i--) {
                pixalmin -= histogram[i];
                if (pixalmin <= 0 && histogram[i] != 0) {
                    max = i;
                    break;
                }
            }
        }

        // Find the minimum in the histogram with non-zero value by
        // ignoring the number of pixels given by pixelsToIgnore
       
        // Find the maximum in the histogram with non-zero value by
        // ignoring the number of pixels given by pixelsToIgnore
        
        return {"min": min, "max": max};
    }

    /*
     * Apply automatic contrast to the input data
     */
    imageproc.autoContrast = function(inputData, outputData, type, percentage) {
        console.log("Applying automatic contrast...");

        // Find the number of pixels to ignore from the percentage
        var pixelsToIgnore = (inputData.data.length / 4) * percentage;

        var histogram, minMax;
        if (type == "gray") {
            // Build the grayscale histogram
            histogram = buildHistogram(inputData, "gray");
            console.log(histogram.slice(0, 10).join(","));

            // Find the minimum and maximum grayscale values with non-zero pixels
            minMax = findMinMax(histogram, pixelsToIgnore);

            var min = minMax.min, max = minMax.max, range = max - min;
            console.log(min,max);
            /**
             * TODO: You need to apply the correct adjustment to each pixel
             */

            for (var i = 0; i < inputData.data.length; i += 4) {
                // Adjust each pixel based on the minimum and maximum values

                outputData.data[i]     = (inputData.data[i] - min)/range*255;
                outputData.data[i + 1] = (inputData.data[i+1] - min) / range * 255;
                outputData.data[i + 2] = (inputData.data[i+2] - min) / range * 255;
            }
        }
        else {

            /**
             * TODO: You need to apply the same procedure for each RGB channel
             *       based on what you have done for the grayscale version
             */
            var Rhistogram = buildHistogram(inputData, "red");
            minMax = findMinMax(Rhistogram, pixelsToIgnore);
            var Rmin = minMax.min, Rmax = minMax.max, Rrange = Rmax - Rmin;

            var Ghistogram = buildHistogram(inputData, "green");
            minMax = findMinMax(Ghistogram, pixelsToIgnore);
            var Gmin = minMax.min, Gmax = minMax.max, Grange = Gmax - Gmin;

            var Bhistogram = buildHistogram(inputData, "blue");
            minMax = findMinMax(Bhistogram, pixelsToIgnore);
            var Bmin = minMax.min, Bmax = minMax.max, Brange = Bmax - Bmin;

            for (var i = 0; i < inputData.data.length; i += 4) {
                // Adjust each channel based on the histogram of each one

                outputData.data[i] = (inputData.data[i] - Rmin) / Rrange * 255;
                outputData.data[i + 1] = (inputData.data[i+1] - Gmin) / Grange * 255;;
                outputData.data[i + 2] = (inputData.data[i+2] - Bmin) / Brange * 255;;
            }
        }
    }

}(window.imageproc = window.imageproc || {}));
