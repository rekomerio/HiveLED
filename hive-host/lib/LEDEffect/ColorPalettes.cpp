#include "LEDEffect.h"

DEFINE_GRADIENT_PALETTE(bhw3_21_gp){
    0, 1, 40, 98,
    48, 1, 65, 68,
    76, 2, 161, 96,
    104, 0, 81, 25,
    130, 65, 182, 82,
    153, 0, 86, 170,
    181, 17, 207, 182,
    204, 17, 207, 182,
    255, 1, 23, 46};

DEFINE_GRADIENT_PALETTE(bhw2_turq_gp){
    0, 1, 33, 95,
    38, 1, 107, 37,
    76, 42, 255, 45,
    127, 255, 255, 45,
    178, 42, 255, 45,
    216, 1, 107, 37,
    255, 1, 33, 95};

DEFINE_GRADIENT_PALETTE(bhw3_11_gp){
    0, 192, 252, 49,
    20, 171, 252, 15,
    53, 82, 241, 13,
    86, 153, 248, 88,
    109, 92, 248, 64,
    137, 229, 255, 160,
    155, 161, 250, 32,
    188, 54, 244, 34,
    216, 66, 246, 46,
    247, 69, 248, 21,
    255, 69, 248, 21};

DEFINE_GRADIENT_PALETTE(bhw3_02_gp){
    0, 121, 1, 1,
    63, 255, 57, 1,
    112, 255, 79, 25,
    145, 255, 79, 25,
    188, 244, 146, 3,
    255, 115, 14, 1};

DEFINE_GRADIENT_PALETTE(bhw3_61_gp){
    0, 14, 1, 27,
    48, 17, 1, 88,
    104, 1, 88, 156,
    160, 1, 54, 42,
    219, 9, 235, 52,
    255, 139, 235, 233};

DEFINE_GRADIENT_PALETTE(rgi_15_gp){
    0, 4, 1, 31,
    31, 55, 1, 16,
    63, 197, 3, 7,
    95, 59, 2, 17,
    127, 6, 2, 34,
    159, 39, 6, 33,
    191, 112, 13, 32,
    223, 56, 9, 35,
    255, 22, 6, 38};

DEFINE_GRADIENT_PALETTE(bhw1_purplered_gp){
    0, 255, 0, 0,
    255, 107, 1, 205};

DEFINE_GRADIENT_PALETTE(wave_gp){
    0, 255, 22, 16,
    42, 88, 104, 0,
    84, 14, 255, 16,
    127, 0, 104, 92,
    170, 14, 22, 255,
    212, 88, 0, 92,
    255, 255, 22, 16};

DEFINE_GRADIENT_PALETTE(bhw1_28_gp){
    0, 75, 1, 221,
    30, 252, 73, 255,
    48, 169, 0, 242,
    119, 0, 149, 242,
    170, 43, 0, 242,
    206, 252, 73, 255,
    232, 78, 12, 214,
    255, 0, 149, 242};

// Gradient palette "bhw1_23_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_23.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 20 bytes of program space.

DEFINE_GRADIENT_PALETTE(bhw1_23_gp){
    0, 83, 6, 1,
    84, 194, 52, 1,
    122, 182, 105, 34,
    165, 194, 52, 1,
    255, 83, 6, 1};

// Gradient palette "bhw1_05_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw1/tn/bhw1_05.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 8 bytes of program space.

DEFINE_GRADIENT_PALETTE(bhw1_05_gp){
    0, 1, 221, 53,
    255, 73, 3, 178};

// Gradient palette "bhw2_greenman_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw2/tn/bhw2_greenman.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 12 bytes of program space.

DEFINE_GRADIENT_PALETTE(bhw2_greenman_gp){
    0, 1, 22, 1,
    130, 1, 168, 2,
    255, 1, 22, 1};

// Gradient palette "bhw3_32_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw3/tn/bhw3_32.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 52 bytes of program space.

DEFINE_GRADIENT_PALETTE(bhw3_32_gp){
    0, 234, 231, 1,
    15, 171, 43, 6,
    40, 121, 0, 0,
    53, 95, 1, 29,
    71, 73, 1, 168,
    94, 38, 63, 221,
    109, 115, 51, 221,
    127, 38, 63, 221,
    147, 73, 1, 168,
    181, 203, 28, 1,
    193, 155, 16, 11,
    216, 73, 1, 168,
    255, 1, 4, 29};

// Gradient palette "bhw3_07_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/bhw/bhw3/tn/bhw3_07.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 44 bytes of program space.

DEFINE_GRADIENT_PALETTE(bhw3_07_gp){
    0, 132, 5, 1,
    30, 12, 13, 147,
    53, 54, 32, 166,
    73, 103, 39, 98,
    84, 239, 52, 27,
    96, 71, 2, 1,
    117, 46, 8, 33,
    130, 54, 32, 166,
    163, 10, 7, 78,
    196, 239, 52, 27,
    255, 1, 1, 14};

// Gradient palette "velvet_ocean_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/colo/Skyblue2u/tn/velvet_ocean.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 40 bytes of program space.

DEFINE_GRADIENT_PALETTE(velvet_ocean_gp){
    0, 1, 79, 80,
    51, 1, 79, 80,
    51, 1, 62, 62,
    102, 1, 62, 62,
    102, 1, 43, 40,
    153, 1, 43, 40,
    153, 1, 27, 23,
    204, 1, 27, 23,
    204, 1, 13, 10,
    255, 1, 13, 10};

// Gradient palette "Dusk_Finds_Us_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/jjg/ccolo/Skyblue2u/tn/Dusk_Finds_Us.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 44 bytes of program space.

DEFINE_GRADIENT_PALETTE(Dusk_Finds_Us_gp){
    0, 64, 66, 82,
    66, 64, 66, 82,
    132, 71, 55, 73,
    137, 78, 47, 65,
    142, 86, 40, 57,
    147, 92, 32, 51,
    153, 101, 25, 45,
    161, 110, 19, 39,
    170, 128, 10, 29,
    212, 148, 4, 20,
    255, 148, 4, 20};

// Gradient palette "mellon_ball_surprise_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/jjg/ccolo/Skyblue2u/tn/mellon_ball_surprise.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 44 bytes of program space.

DEFINE_GRADIENT_PALETTE(mellon_ball_surprise_gp){
    0, 152, 227, 85,
    25, 152, 227, 85,
    51, 182, 235, 95,
    76, 215, 244, 106,
    102, 234, 189, 79,
    127, 255, 142, 56,
    153, 255, 115, 51,
    178, 255, 90, 45,
    204, 242, 59, 52,
    229, 229, 36, 62,
    255, 229, 36, 62};

// Gradient palette "r_a_i_n_y_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/jjg/ccolo/hana/tn/r_a_i_n_y.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 44 bytes of program space.

DEFINE_GRADIENT_PALETTE(r_a_i_n_y_gp){
    0, 8, 1, 54,
    25, 8, 1, 54,
    51, 2, 9, 67,
    76, 1, 33, 83,
    102, 2, 55, 82,
    127, 5, 84, 80,
    153, 27, 99, 78,
    178, 72, 117, 75,
    204, 92, 124, 69,
    229, 117, 130, 64,
    255, 117, 130, 64};

// Gradient palette "October_Sky_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/jjg/ccolo/sugar/tn/October_Sky.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 44 bytes of program space.

DEFINE_GRADIENT_PALETTE(October_Sky_gp){
    0, 42, 7, 11,
    71, 42, 7, 11,
    142, 75, 9, 12,
    156, 121, 11, 14,
    170, 153, 18, 12,
    184, 192, 25, 11,
    198, 213, 43, 8,
    212, 232, 66, 5,
    226, 229, 91, 7,
    240, 227, 122, 9,
    255, 227, 122, 9};

// Gradient palette "Id_Like_To_Dive_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/jjg/ccolo/sugar/tn/Id_Like_To_Dive.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 44 bytes of program space.

DEFINE_GRADIENT_PALETTE(Id_Like_To_Dive_gp){
    0, 59, 125, 77,
    20, 59, 125, 77,
    40, 30, 104, 75,
    75, 11, 85, 74,
    109, 14, 55, 79,
    117, 17, 33, 84,
    124, 18, 17, 73,
    141, 18, 6, 63,
    158, 12, 2, 39,
    206, 7, 1, 22,
    255, 7, 1, 22};

// Gradient palette "Another_Earth_gp", originally from
// http://soliton.vm.bytemark.co.uk/pub/cpt-city/jjg/ccolo/vredeling/tn/Another_Earth.png.index.html
// converted for FastLED with gammas (2.6, 2.2, 2.5)
// Size: 44 bytes of program space.

DEFINE_GRADIENT_PALETTE(Another_Earth_gp){
    0, 73, 156, 1,
    25, 73, 156, 1,
    51, 53, 146, 3,
    76, 37, 138, 11,
    102, 24, 128, 23,
    127, 14, 119, 42,
    153, 7, 111, 69,
    178, 3, 103, 103,
    204, 1, 95, 145,
    229, 1, 87, 197,
    255, 1, 87, 197};

// Remember to add palette to /data/json/palettes.json
extern const TProgmemRGBGradientPalettePtr hiveColorPalettes[] = {
    bhw3_21_gp,
    bhw2_turq_gp,
    bhw3_11_gp,
    bhw3_02_gp,
    bhw3_61_gp,
    rgi_15_gp,
    bhw1_purplered_gp,
    wave_gp,
    bhw1_28_gp,
    bhw1_23_gp,
    bhw1_05_gp,
    bhw2_greenman_gp,
    bhw3_32_gp,
    bhw3_07_gp,
    velvet_ocean_gp,
    Dusk_Finds_Us_gp,
    mellon_ball_surprise_gp,
    r_a_i_n_y_gp,
    October_Sky_gp,
    Id_Like_To_Dive_gp,
    Another_Earth_gp};

extern const uint8_t hiveColorPaletteCount = sizeof(hiveColorPalettes) / sizeof(TProgmemRGBGradientPalettePtr);