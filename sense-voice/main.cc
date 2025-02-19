
#include "asr_handler.hpp"

int main(int argc, char **argv) {
    ASRHandler server;
    return server.cli_main(argc, argv);
}
