
#include "asr.hpp"

int main(int argc, char **argv) {
    ASRServer server;
    return server.cli_main(argc, argv);
}
