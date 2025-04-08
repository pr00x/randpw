#include <stdio.h>
#include <getopt.h>
#include <stdint.h>
#include <sys/random.h>

#define PROGRAM_NAME "randpw"
#define VERSION "v1.0.0"
#define DEFAULT_PW_LENGTH 32

char *program_name = PROGRAM_NAME;

void help() {
    printf(
        "A simple and secure command-line tool for generating random, high-entropy passwords using /dev/urandom.\n"
        "Usage: %s [option]\n\n"
        "Options:\n"
        "    -h, --help         print %s command line options (currently set)\n"
        "    -v, --version      print %s version\n"
        "    -n, --length       length of the generated password (default: 32)\n",
        program_name, program_name, program_name
    );
}

int16_t str2uint(const char *str) {
    int16_t num = 0;

    if(!*str)
        return -1;

    for(int16_t i = 0; i < 4; i++) {
        if(!str[i])
            break;
        else if(str[i] < '0' || str[i] > '9')
            return -1;

        num = num * 10 + (int)(str[i] - '0');
    }

    return num;
}

int8_t generate_random_pw(int16_t length) {
    const char charset[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789#!?-_";
    size_t charset_len = sizeof(charset) - 1;

    unsigned char buffer[length * 2];
    char rand_pw[length + 1];

    ssize_t result = getrandom(buffer, length * 2, 0);

    if(result == -1) {
        perror(program_name);
        return -1;
    }
    else if(result != length * 2) {
        fprintf(stderr, "%s: failed to read random bytes.\n", program_name);
        return -1;
    }

    for(int16_t i = 0; i < length; i++) {
        // Use 16 bits of entropy per character to minimize modulo bias
        uint16_t randval = (buffer[i * 2] << 8) | buffer[i * 2 + 1];
        rand_pw[i] = charset[randval % charset_len];
    }
    
    rand_pw[length] = '\0';
    puts(rand_pw);

    return 0;
}

int run(int argc, char **argv) {
    struct option long_args[] = {
        { "help", 0, 0, 'h' },
        { "version", 0, 0, 'v' },
        { "length", 0, 0, 'n' },
        { 0, 0, 0, 0}
    };

    int16_t length = DEFAULT_PW_LENGTH;
    int opt;

    while((opt = getopt_long_only(argc, argv, "hvn:", long_args, NULL)) != -1) {
        switch(opt) {
            case 'h':
                help();
                return 0;
            case 'v':
                puts(VERSION);
                return 0;
            case 'n':
                length = str2uint(optarg);

                if(length == -1) {
                    fprintf(
                        stderr,
                        "%s: invalid password length.\nTry `%s --help' for more information.\n",
                        program_name, program_name);
                    return -1;
                }
                else if(length < 8 || length > 999) {
                        if(length < 8)
                            fprintf(stderr, "%s: The password must contain at least 8 characters.\n", program_name);
                        else
                            fprintf(stderr, "%s: The maximum password length is 999 characters.\n", program_name);

                        return -1;
                }

                break;
            case '?':
                fprintf(stderr, "Try '%s --help' for more information.\n", program_name);
                return -1;
        }
    }

    return generate_random_pw(length);
}

int main(int argc, char **argv) {
    program_name = **argv != '\0' ? *argv : PROGRAM_NAME;
    return run(argc, argv);
}