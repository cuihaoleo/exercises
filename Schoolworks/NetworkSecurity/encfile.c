#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include "openssl/aes.h"

#define MAX_FILE_SIZE 16777216  // 16MB

void encrypt_data(
        const unsigned char *data,
        long data_len,
        unsigned char **enc,
        long *enc_len,
        const char *pwd,
        int pwd_len,
        int keysize) {
    const int byte_keysize = keysize >> 3;
    int i, n_block, res_len;
    unsigned char *aes_keybuf;
    unsigned char pad_buf[16] = { 0 };
    AES_KEY aes_key;

    // setup key
    aes_keybuf = (unsigned char*)malloc(byte_keysize);
    memset(aes_keybuf, 0x90, 32);
    if (pwd_len > byte_keysize) pwd_len = byte_keysize;
    memcpy(aes_keybuf, pwd, pwd_len);
    AES_set_encrypt_key(aes_keybuf, keysize, &aes_key);

    // grouping
    n_block = data_len / 16 + 1;
    *enc_len = n_block << 4;
    *enc = (unsigned char*)malloc(*enc_len);
    memset(*enc, 0, *enc_len);

    for (i = 0; i < n_block - 1; i ++)
        AES_encrypt(data + (i<<4), *enc + (i<<4), &aes_key);

    // padding
    res_len = data_len - (i<<4);
    memcpy(pad_buf, data + (i<<4), res_len);
    pad_buf[res_len] = 0xff;
    AES_encrypt(pad_buf, *enc + (i<<4), &aes_key);

    free(aes_keybuf);
}

void decrypt_data(
        const unsigned char *enc,
        long enc_len,
        unsigned char **dec,
        long *dec_len,
        const char *pwd,
        int pwd_len,
        int keysize) {
    const int byte_keysize = keysize >> 3;
    int i, n_block, res_len;
    unsigned char *aes_keybuf;
    unsigned char pad_buf[16] = { 0 };
    AES_KEY aes_key;

    // setup key
    aes_keybuf = (unsigned char*)malloc(byte_keysize);
    memset(aes_keybuf, 0x90, 32);
    if (pwd_len > byte_keysize) pwd_len = byte_keysize;
    memcpy(aes_keybuf, pwd, pwd_len);
    AES_set_decrypt_key(aes_keybuf, keysize, &aes_key);

    // deal with padding
    AES_decrypt(enc + enc_len - 16, pad_buf, &aes_key);
    for (res_len = 15; pad_buf[res_len] == 0; res_len--)
        continue;

    *dec_len = enc_len - 16 + res_len;
    *dec = (unsigned char*)malloc(*dec_len + 1);
    (*dec)[*dec_len] = 0;
    memcpy(*dec + enc_len - 16, pad_buf, res_len);

    // grouping
    n_block = enc_len / 16 - 1;
    for (i = 0; i < n_block; i++)
        AES_decrypt(enc + (i<<4), *dec + (i<<4), &aes_key);

    free(aes_keybuf);
}

int main(int argc, char* argv[]) {
    unsigned char *read_buf;
    const char *fname_in;
    char *fname_out;
    const char *passwd;
    unsigned char *out;
    long out_len, file_size;
    FILE *fin, *fout;

    void (*opr)(
            const unsigned char *, long,
            unsigned char **, long *,
            const char *, int, int);

    if (argc != 4 || strlen(argv[1]) != 3) {
        fprintf(stderr, "Invalid arguments!");
        return -1;
    }

    if (strcmp(argv[1], "enc") == 0)
        opr = encrypt_data;
    else if (strcmp(argv[1], "dec") == 0)
        opr = decrypt_data;
    else {
        fprintf(stderr, "Invalid arguments!");
        return -1;
    }

    fname_in = argv[2];
    passwd = argv[3];

    fin = fopen(fname_in, "rb");
    fseek(fin, 0L, SEEK_END);
    file_size = ftell(fin);
    fseek(fin, 0L, SEEK_SET);

    if (file_size > MAX_FILE_SIZE) {
        fprintf(stderr, "My naive program load whole file to memory.");
        fprintf(stderr, "Refuse to load because file is too big.");
        return -1;
    }

    read_buf = malloc(file_size);
    fread(read_buf, 1, file_size, fin);
    fclose(fin);

    opr(read_buf, file_size,
        &out, &out_len,
        passwd, strlen(passwd), 256);
    free(read_buf);

    fname_out = malloc(strlen(fname_in) + 5);
    strcpy(fname_out, fname_in);
    strcat(strcat(fname_out, "."), argv[1]);
    fprintf(stderr, "Output: %s\n", fname_out);

    fout = fopen(fname_out, "wb");
    fwrite(out, 1, out_len, fout);

    free(fname_out);
    fclose(fout);

    return 0;
}
