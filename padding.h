volatile uint32_t bpad[168] = {
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
};


/*volatile uint32_t bpad[3072] = {
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,

    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,

    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,

    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,

    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,

    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,

    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,

    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,

    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,

    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,

    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,
    0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,0x12345678,


};*/