int lowest_n_zeros(int n) {
    return ~((1 << n) - 1);
}

int lowest_m_zeros_and_n_ones(int m, int n) {
    return ((1 << n) - 1) << m;
}
