(function(imageproc) {
    "use strict";

    /*
     * Apply sobel edge to the input data
     */
    imageproc.sobelEdge = function(inputData, outputData, threshold) {
        console.log("Applying Sobel edge detection...");

        /* Initialize the two edge kernel Gx and Gy */
        var Gx = [
            [-1, 0, 1],
            [-2, 0, 2],
            [-1, 0, 1]
        ];
        var Gy = [
            [-1,-2,-1],
            [ 0, 0, 0],
            [ 1, 2, 1]
        ];

        /**
         * TODO: You need to write the code to apply
         * the two edge kernels appropriately
         */
        for (var y = 0; y < inputData.height; y++) {
            for (var x = 0; x < inputData.width; x++) {

                var r_temp = 0, g_temp = 0, b_temp = 0;
                var r_x = 0, g_x = 0, b_x = 0;
                var r_y = 0, g_y = 0, b_y = 0;
                var rgba = 0;
                // Then set the blurred result to the output data
                //for (var j = -1; j <= 1; j++) {
                //    for (var i = -1; i <= 1; i++) {
                for (var j = -1; j <= 1; j++) {
                    for (var i = -1; i <= 1; i++) {
                        rgba = imageproc.getPixel(inputData, x + i, y + j, "wrap");
                        //console.log(rgba.r,rgba.g,rgba.b);
                        
                        r_x += rgba.r * Gx[i + 1][j + 1];
                        g_x += rgba.g * Gx[i + 1][j + 1];
                        b_x += rgba.b * Gx[i + 1][j + 1];

                        r_y += rgba.r * Gy[i + 1][j + 1];
                        g_y += rgba.g * Gy[i + 1][j + 1];
                        b_y += rgba.b * Gy[i + 1][j + 1];
                    }
                }

                r_temp = Math.hypot(r_x, r_y);
                g_temp = Math.hypot(g_x, g_y);
                b_temp = Math.hypot(b_x, b_y);

                // r_temp = r_temp / 9;
                // g_temp = g_temp / 9;
                // b_temp = b_temp / 9;
                if((r_temp + g_temp + b_temp)/3 > threshold){
                    r_temp = 255;
                    g_temp = 255;
                    b_temp = 255;
                }else{
                    r_temp = 0;
                    g_temp = 0;
                    b_temp = 0;
                }

                var ii = (x + y * outputData.width) * 4;
                outputData.data[ii]     = r_temp
                outputData.data[ii + 1] = g_temp;
                outputData.data[ii + 2] = b_temp;
            }
        }
        
        for (var y = 0; y < inputData.height; y++) {
            for (var x = 0; x < inputData.width; x++) {
            }
        }

    } 

}(window.imageproc = window.imageproc || {}));
