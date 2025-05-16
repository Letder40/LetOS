#ifndef KEYMAPS_H
#define KEYMAPS_H

typedef enum {
    NUL,
    ESC = 27,
    TAB = 9,
    BSP = 8,
    RET = 10,
    SPC = 32,

    CTR = 200,
    SHF = 202,
    ALT = 203,
    BKM = 204,
    BKN = 205,

    F01 = 240,
    F02 = 241,
    F03 = 242,
    F04 = 243,
    F05 = 244,
    F06 = 245,
    F07 = 246,
    F08 = 247,
    F09 = 248,
    F10 = 249,
    F11 = 250,
    F12 = 251,
} SPECIAL_KEYS;

typedef enum {
    IEXC = 161,   // ¡
    N_TL = 209,   // ñ / Ñ (same code)
    ACUT = 39,    // '
    MASC = 186,   // º (masculine ordinal)
    CEDL = 199,   // Ç
    QINV = 191,   // ¿ (inverted question mark)
    DIER = 168,   // ¨ (diaeresis)
    F_ORD = 170,  // ª (feminine ordinal)
    CARE = 94,    // ^ (caret)
    BULL = 183,   // · (middle dot)
    DEGR = 176    // ° (degree)
} SPECIAL_CHARS;

#define KEYMAP_ES \
    NUL,                                                                                    \
    ESC,  '1',  '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  '0',  ACUT, IEXC, BSP,      \
    TAB,  'q',  'w',  'e',  'r',  't',  'y',  'u',  'i',  'o',  'p',  '`',  '+',   RET,      \
    CTR,  'a',  's',  'd',  'f',  'g',  'h',  'j',  'k',  'l',  N_TL, ACUT, MASC,            \
    SHF,  CEDL, 'z',  'x',  'c',  'v',  'b',  'n',  'm',  ',',  '.',  '-',  SHF,             \
    '*',  ALT,  SPC,  BKM,                                                                   \
    F01,  F02,  F03,  F04,  F05,  F06,  F07,  F08,  F09,  F10,                               \
    BKN,  NUL,                                                                               \
    '7',  '8',  '9',  '-',                                                                  \
    '4',  '5',  '6',  '+',                                                                  \
    '1',  '2',  '3',                                                                        \
    '0',  '.',                                                                              \
    NUL,  NUL,                                                                              \
    '<',                                                                                    \
    F11,  F12

#define KEYMAP_ES_SHIFTED \
    NUL,                                                                                    \
    ESC,  '!',  '"',  BULL, '$',  '%',  '&',  '/',  '(',  ')',  '=',  '?',  QINV, BSP,      \
    TAB,  'Q',  'W',  'E',  'R',  'T',  'Y',  'U',  'I',  'O',  'P',  CARE, '*',   RET,      \
    CTR,  'A',  'S',  'D',  'F',  'G',  'H',  'J',  'K',  'L',  N_TL, DIER, F_ORD,           \
    SHF,  CEDL, 'Z',  'X',  'C',  'V',  'B',  'N',  'M',  ';',  ':',  '_',  SHF,             \
    '*',  ALT,  SPC,  BKM,                                                                   \
    F01,  F02,  F03,  F04,  F05,  F06,  F07,  F08,  F09,  F10,                               \
    BKN,  NUL,                                                                               \
    '7',  '8',  '9',  '-',                                                                  \
    '4',  '5',  '6',  '+',                                                                  \
    '1',  '2',  '3',                                                                        \
    '0',  '.',                                                                              \
    NUL,  NUL,                                                                              \
    '<',                                                                                    \
    F11,  F12

#define KEYMAP_ES_PRINTABLE_BMAP \
    0, \
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, \
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, \
    0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, \
    1, 0, 1, 0, \
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, \
    0, 0, \
    1, 1, 1, 1, \
    1, 1, 1, 1, \
    1, 1, 1, \
    1, 1, \
    0, 0, \
    1, \
    0, 0

#endif

