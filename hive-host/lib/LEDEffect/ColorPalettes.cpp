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

// Remember to add palette to /data/json/palettes.json
extern const TProgmemRGBGradientPalettePtr hiveColorPalettes[] = {
    wave_gp,
    bhw1_purplered_gp,
    rgi_15_gp,
    bhw3_61_gp,
    bhw3_02_gp,
    bhw3_11_gp,
    bhw2_turq_gp,
    bhw3_21_gp};

extern const uint8_t hiveColorPaletteCount = sizeof(hiveColorPalettes) / sizeof(TProgmemRGBGradientPalettePtr);