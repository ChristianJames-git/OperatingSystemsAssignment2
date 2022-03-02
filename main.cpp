#include <getopt.h>
#include "populatetree.h"
#include "countwords.h"

int main(int argc, char **argv) {
    if (argc < 3) { //make sure correct args amount
        cout << "Please input correct number of inputs" << endl;
        exit(EXIT_FAILURE);
    }
    int p=-1, h=-1, n=-1, c;
    char* filenames[2];
    while (optind < argc) {
        if ((c = getopt(argc, argv, ":p:h:n:")) != -1) {
            switch (c) {
                case 'p':
                    p = strtol(optarg, nullptr, 10);
                    if (p < 10) {
                        cout << "Number of progress marks must be a number and at least 10" << endl;
                        exit(EXIT_FAILURE);
                    }
                    break;
                case 'h':
                    h = strtol(optarg, nullptr, 10);
                    if (h <= 0 || h > 10) {
                        cout
                                << "Hash mark interval for progress must be a number, greater than 0, and less than or equal to 10"
                                << endl;
                        exit(EXIT_FAILURE);
                    }
                    break;
                case 'n':
                    n = strtol(optarg, nullptr, 10);
                    break;
                default:
                    break;
            }
        } else {
            filenames[optind-1] = argv[optind];
            optind++;
        }
    }
    auto *sharedData = new EXEC_STATUS(p, h, n);
    delete(&sharedData);
}
