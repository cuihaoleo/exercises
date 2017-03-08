typedef enum { MODE_A, MODE_B, MODE_C, MODE_D, MODE_E } mode_t;

int switch3(int *p1, int *p2, mode_t action) {
    register int result = -1;

    switch (action) {
        case MODE_A:
            result = *p1;
            *p1 = *p2;
            break;
        case MODE_B:
            *p2 = result = *p1 + *p2;
            break;
        case MODE_C:
            *p2 = 15;
            result = *p1;
            break;
        case MODE_D:
            *p2 = *p1;
            result = 17;
        default:
            ;
    }

    return result;
}
