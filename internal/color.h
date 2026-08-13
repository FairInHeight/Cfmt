#ifndef COLOR_H
#define COLOR_H

typedef enum
{
    // Standard colors 0-7
    Black, Red, Green, Yellow, Blue, Magenta, Cyan, White,
    
    // Bright colors 8-15
    Bright_Black, Bright_Red, Bright_Green, Bright_Yellow,
    Bright_Blue, Bright_Magenta, Bright_Cyan, Bright_White,

    // 6x6x6 color cube 16-231
    rgb_000, rgb_001, rgb_002, rgb_003, rgb_004, rgb_005,
    rgb_010, rgb_011, rgb_012, rgb_013, rgb_014, rgb_015,
    rgb_020, rgb_021, rgb_022, rgb_023, rgb_024, rgb_025,
    rgb_030, rgb_031, rgb_032, rgb_033, rgb_034, rgb_035,
    rgb_040, rgb_041, rgb_042, rgb_043, rgb_044, rgb_045,
    rgb_050, rgb_051, rgb_052, rgb_053, rgb_054, rgb_055,
    rgb_100, rgb_101, rgb_102, rgb_103, rgb_104, rgb_105,
    rgb_110, rgb_111, rgb_112, rgb_113, rgb_114, rgb_115,
    rgb_120, rgb_121, rgb_122, rgb_123, rgb_124, rgb_125,
    rgb_130, rgb_131, rgb_132, rgb_133, rgb_134, rgb_135,
    rgb_140, rgb_141, rgb_142, rgb_143, rgb_144, rgb_145,
    rgb_150, rgb_151, rgb_152, rgb_153, rgb_154, rgb_155,
    rgb_200, rgb_201, rgb_202, rgb_203, rgb_204, rgb_205,
    rgb_210, rgb_211, rgb_212, rgb_213, rgb_214, rgb_215,
    rgb_220, rgb_221, rgb_222, rgb_223, rgb_224, rgb_225,
    rgb_230, rgb_231, rgb_232, rgb_233, rgb_234, rgb_235,
    rgb_240, rgb_241, rgb_242, rgb_243, rgb_244, rgb_245,
    rgb_250, rgb_251, rgb_252, rgb_253, rgb_254, rgb_255,
    rgb_300, rgb_301, rgb_302, rgb_303, rgb_304, rgb_305,
    rgb_310, rgb_311, rgb_312, rgb_313, rgb_314, rgb_315,
    rgb_320, rgb_321, rgb_322, rgb_323, rgb_324, rgb_325,
    rgb_330, rgb_331, rgb_332, rgb_333, rgb_334, rgb_335,
    rgb_340, rgb_341, rgb_342, rgb_343, rgb_344, rgb_345,
    rgb_350, rgb_351, rgb_352, rgb_353, rgb_354, rgb_355,
    rgb_400, rgb_401, rgb_402, rgb_403, rgb_404, rgb_405,
    rgb_410, rgb_411, rgb_412, rgb_413, rgb_414, rgb_415,
    rgb_420, rgb_421, rgb_422, rgb_423, rgb_424, rgb_425,
    rgb_430, rgb_431, rgb_432, rgb_433, rgb_434, rgb_435,
    rgb_440, rgb_441, rgb_442, rgb_443, rgb_444, rgb_445,
    rgb_450, rgb_451, rgb_452, rgb_453, rgb_454, rgb_455,
    rgb_500, rgb_501, rgb_502, rgb_503, rgb_504, rgb_505,
    rgb_510, rgb_511, rgb_512, rgb_513, rgb_514, rgb_515,
    rgb_520, rgb_521, rgb_522, rgb_523, rgb_524, rgb_525,
    rgb_530, rgb_531, rgb_532, rgb_533, rgb_534, rgb_535,
    rgb_540, rgb_541, rgb_542, rgb_543, rgb_544, rgb_545,
    rgb_550, rgb_551, rgb_552, rgb_553, rgb_554, rgb_555,

    // Grayscale ramp 232-255
    Dark_Gray_1, Dark_Gray_2, Dark_Gray_3, Dark_Gray_4, Dark_Gray_5, Dark_Gray_6, Dark_Gray_7, Dark_Gray_8,
    Gray_1, Gray_2, Gray_3, Gray_4, Gray_5, Gray_6, Gray_7, Gray_8,
    Light_Gray_1, Light_Gray_2, Light_Gray_3, Light_Gray_4, Light_Gray_5, Light_Gray_6, Light_Gray_7, Light_Gray_8,
    
    DEFAULT = 256

} Color;

extern Color color;

#define Dark_Gray Dark_Gray_8
#define Light_Gray Light_Gray_1
#define Gray Gray_5

#endif