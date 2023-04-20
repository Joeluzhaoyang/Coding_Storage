(function(imageproc) {
    "use strict";

    /*
     * Apply blur to the input data
     */
    imageproc.blur = function(inputData, outputData, kernelSize) {
        console.log("Applying blur...");

        // You are given a 3x3 kernel but you need to create a proper kernel
        // using the given kernel size
        if(kernelSize == 3){
            var kernel = [ [1, 1, 1], [1, 1, 1], [1, 1, 1] ];
        }else if(kernelSize == 5){
            var kernel = [[1, 1, 1, 1, 1], [1, 1, 1, 1, 1], [1, 1, 1, 1, 1], [1, 1, 1, 1, 1], [1, 1, 1, 1, 1]];
        }else if(kernelSize == 7){
            var kernel = [[1, 1, 1, 1, 1, 1, 1], [1, 1, 1, 1, 1, 1, 1], [1, 1, 1, 1, 1, 1, 1], [1, 1, 1, 1, 1, 1, 1], [1, 1, 1, 1, 1, 1, 1], [1, 1, 1, 1, 1, 1, 1], [1, 1, 1, 1, 1, 1, 1]];
        }else if(kernelSize == 9){
            var kernel = [[1, 1, 1, 1, 1, 1, 1, 1, 1], [1, 1, 1, 1, 1, 1, 1, 1, 1], [1, 1, 1, 1, 1, 1, 1, 1, 1], [1, 1, 1, 1, 1, 1, 1, 1, 1], [1, 1, 1, 1, 1, 1, 1, 1, 1], [1, 1, 1, 1, 1, 1, 1, 1, 1], [1, 1, 1, 1, 1, 1, 1, 1, 1], [1, 1, 1, 1, 1, 1, 1, 1, 1], [1, 1, 1, 1, 1, 1, 1, 1, 1]];
        }

        /**
         * TODO: You need to extend the blur effect to include different
         * kernel sizes and then apply the kernel to the entire image
         */

        // Apply the kernel to the whole image
        for (var y = 0; y < inputData.height; y++) {
            for (var x = 0; x < inputData.width; x++) {

                var r_temp = 0, g_temp = 0, b_temp = 0;
                var rgba = 0;
                // Then set the blurred result to the output data
                //for (var j = -1; j <= 1; j++) {
                //    for (var i = -1; i <= 1; i++) {
                for (var j = (-kernelSize + 1) / 2; j <= (kernelSize-1) / 2; j++) {
                    for (var i = (-kernelSize + 1) / 2; i <= (kernelSize - 1) / 2; i++) {
                        rgba = imageproc.getPixel(inputData, x + i, y + j, "wrap");
                        //console.log(rgba.r,rgba.g,rgba.b);
                        r_temp += rgba.r * kernel[i + (kernelSize - 1) / 2][j + (kernelSize - 1) / 2];
                        g_temp += rgba.g * kernel[i + (kernelSize - 1) / 2][j + (kernelSize - 1) / 2];
                        b_temp += rgba.b * kernel[i + (kernelSize - 1) / 2][j + (kernelSize - 1) / 2];
                    }
                }
                r_temp = r_temp / (kernelSize * kernelSize);
                g_temp = g_temp / (kernelSize * kernelSize);
                b_temp = b_temp / (kernelSize * kernelSize);
                //console.log(r_temp, g_temp, b_temp);
                
                var i = (x + y * outputData.width) * 4;
                outputData.data[i]     = r_temp;
                outputData.data[i + 1] = g_temp;
                outputData.data[i + 2] = b_temp;
            }
        }
    } 

}(window.imageproc = window.imageproc || {}));
