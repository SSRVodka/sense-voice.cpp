#pragma once

#include <cmath>
#include <thread>

#include <cstring>
#include <string>
#include <vector>


class ASRHandler {
public:

    typedef int64_t task_id_t;
    static constexpr task_id_t INVALID_ID = -1;

    struct asr_params {
        // comment: default value
        int32_t n_threads;     // = std::min(4, (int32_t) std::thread::hardware_concurrency())
        int32_t n_processors;  // = 1
        int32_t offset_t_ms;   // = 0
        int32_t offset_n;      // = 0
        int32_t duration_ms;   // = 0
        int32_t progress_step; // = 5
        int32_t max_context;   // = -1
        int32_t max_len;       // = 0
        int32_t n_mel;         // = 80
        int32_t best_of;       // = sense_voice_full_default_params(SENSE_VOICE_SAMPLING_GREEDY).greedy.best_of;
        int32_t beam_size;     // = sense_voice_full_default_params(SENSE_VOICE_SAMPLING_BEAM_SEARCH).beam_search.beam_size;
        int32_t audio_ctx;     // = 0

        float word_thold;      // =  0.01f
        float entropy_thold;   // =  2.40f
        float logprob_thold;   // = -1.00f
        float grammar_penalty; // = 100.0f
        float temperature;     // = 0.0f
        float temperature_inc; // = 0.2f

        // vad params
        float threshold;       // = 0.5f
        float neg_threshold;   // = 0.35f
        int32_t min_speech_duration_ms;  // = 250
        int32_t max_speech_duration_ms;  // = 15000
        int32_t min_silence_duration_ms; // = 100
        int32_t speech_pad_ms; // = 30

        bool debug_mode;       // = false
        bool translate;        // = false
        bool detect_language;  // = false
        bool diarize;          // = false
        bool tinydiarize;      // = false
        bool split_on_word;    // = false
        bool no_fallback;      // = false
        bool output_txt;       // = false
        bool output_vtt;       // = false
        bool output_srt;       // = false
        bool output_wts;       // = false
        bool output_csv;       // = false
        bool output_jsn;       // = false
        bool output_jsn_full;  // = false
        bool output_lrc;       // = false
        bool no_prints;        // = false
        bool print_special;    // = false
        bool print_colors;     // = false
        bool print_progress;   // = false
        bool no_timestamps;    // = false
        bool log_score;        // = false
        bool use_gpu;          // = true
        bool flash_attn;       // = false
        bool need_prefix;      // = false
        bool use_itn;          // = false

        std::string language;  // = "auto"
        std::string prompt;    // = ""
        std::string model;     // = "models/ggml-base.en.bin"

        std::string openvino_encode_device; // = "CPU"

        std::vector<std::string> fname_inp; // = {}
        std::vector<std::string> fname_out; // = {}

        // default constructor
        asr_params();
    };

    struct asr_print_user_data {
        const asr_params *params;
    
        const std::vector<std::vector<float>> *pcmf32s;
        int progress_prev;
    };

    struct asr_result {
        task_id_t request_id;
        std::string text;

        // default constructor
        asr_result();
        asr_result(task_id_t, std::string);
    };

    ASRHandler();
    ~ASRHandler();

    // sync op
    asr_result handle(
        task_id_t request_id,
        asr_params &params,
        void(*info)(const char*) = nullptr,
        void(*err)(const char*) = nullptr
    );
    int cli_main(int argc, char **argv);

    static bool asr_params_parse(int argc, char **argv, asr_params &params);
    static const char *print_system_info();
    static void print_usage(int /*argc*/, char **argv, const asr_params &params);

    void register_on_line_append(void(*callback)(task_id_t, std::string));

protected:
    static char *param_turn_lowercase(char *in);
private:
    task_id_t currentId;
    asr_result currentResult;

    void(*on_line_append)(task_id_t, std::string);
};
