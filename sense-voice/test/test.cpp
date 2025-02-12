
#include "asr.hpp"

void log_info(const char *txt) {
    fprintf(stdout, "%s\n", txt);
}
void log_error(const char *txt) {
    fprintf(stderr, "%s\n", txt);
}

int test_invalid_params() {
    ASRServer server;
    ASRServer::asr_params params;
    // params.model = "";
    params.language = "zh";
    ASRServer::asr_result result = server.handle(1, params, log_info, log_error);
    printf("res: {id: %d, text: '%s'}\nexpected: {id: -1, text: ''}\n", result.request_id, result.text.c_str());
    return result.request_id != ASRServer::INVALID_ID;
}
int test_valid_params() {
    ASRServer server;
    ASRServer::asr_params params;
    params.model = "/root/models/sense-voice-small-fp32.gguf";
    params.language = "zh";
    params.fname_inp.push_back("/root/data/hello.wav");
    ASRServer::asr_result result = server.handle(1, params, log_info, log_error);
    printf("res: {id: %d, text: '%s'}\nexpected: {id: %d, text: '%s'}\n",
        result.request_id, result.text.c_str(),
        1, "你好\n请问你是谁\n");
    return result.request_id != 1;
}

int main() {
    int failure = 0;
    failure += test_invalid_params();
    failure += test_valid_params();

    return failure;
}
