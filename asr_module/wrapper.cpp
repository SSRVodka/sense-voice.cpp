#include <pybind11/pybind11.h>
#include <pybind11/stl.h> // For STL support (e.g., std::string, std::vector)
#include "asr_handler.hpp" // Include the header file for the C++ library

namespace py = pybind11;

// Wrap the ASRHandler class and its associated structures
PYBIND11_MODULE(_asr_module, m) {
    // Bind the asr_params struct
    py::class_<ASRHandler::asr_params>(m, "ASRParams")
        .def(py::init<>())
        .def_readwrite("n_threads", &ASRHandler::asr_params::n_threads)
        .def_readwrite("n_processors", &ASRHandler::asr_params::n_processors)
        .def_readwrite("offset_t_ms", &ASRHandler::asr_params::offset_t_ms)
        .def_readwrite("offset_n", &ASRHandler::asr_params::offset_n)
        .def_readwrite("duration_ms", &ASRHandler::asr_params::duration_ms)
        .def_readwrite("progress_step", &ASRHandler::asr_params::progress_step)
        .def_readwrite("max_context", &ASRHandler::asr_params::max_context)
        .def_readwrite("max_len", &ASRHandler::asr_params::max_len)
        .def_readwrite("n_mel", &ASRHandler::asr_params::n_mel)
        .def_readwrite("best_of", &ASRHandler::asr_params::best_of)
        .def_readwrite("beam_size", &ASRHandler::asr_params::beam_size)
        .def_readwrite("audio_ctx", &ASRHandler::asr_params::audio_ctx)
        .def_readwrite("word_thold", &ASRHandler::asr_params::word_thold)
        .def_readwrite("entropy_thold", &ASRHandler::asr_params::entropy_thold)
        .def_readwrite("logprob_thold", &ASRHandler::asr_params::logprob_thold)
        .def_readwrite("grammar_penalty", &ASRHandler::asr_params::grammar_penalty)
        .def_readwrite("temperature", &ASRHandler::asr_params::temperature)
        .def_readwrite("temperature_inc", &ASRHandler::asr_params::temperature_inc)
        .def_readwrite("threshold", &ASRHandler::asr_params::threshold)
        .def_readwrite("neg_threshold", &ASRHandler::asr_params::neg_threshold)
        .def_readwrite("min_speech_duration_ms", &ASRHandler::asr_params::min_speech_duration_ms)
        .def_readwrite("max_speech_duration_ms", &ASRHandler::asr_params::max_speech_duration_ms)
        .def_readwrite("min_silence_duration_ms", &ASRHandler::asr_params::min_silence_duration_ms)
        .def_readwrite("speech_pad_ms", &ASRHandler::asr_params::speech_pad_ms)
        .def_readwrite("debug_mode", &ASRHandler::asr_params::debug_mode)
        .def_readwrite("translate", &ASRHandler::asr_params::translate)
        .def_readwrite("detect_language", &ASRHandler::asr_params::detect_language)
        .def_readwrite("diarize", &ASRHandler::asr_params::diarize)
        .def_readwrite("tinydiarize", &ASRHandler::asr_params::tinydiarize)
        .def_readwrite("split_on_word", &ASRHandler::asr_params::split_on_word)
        .def_readwrite("no_fallback", &ASRHandler::asr_params::no_fallback)
        .def_readwrite("output_txt", &ASRHandler::asr_params::output_txt)
        .def_readwrite("output_vtt", &ASRHandler::asr_params::output_vtt)
        .def_readwrite("output_srt", &ASRHandler::asr_params::output_srt)
        .def_readwrite("output_wts", &ASRHandler::asr_params::output_wts)
        .def_readwrite("output_csv", &ASRHandler::asr_params::output_csv)
        .def_readwrite("output_jsn", &ASRHandler::asr_params::output_jsn)
        .def_readwrite("output_jsn_full", &ASRHandler::asr_params::output_jsn_full)
        .def_readwrite("output_lrc", &ASRHandler::asr_params::output_lrc)
        .def_readwrite("no_prints", &ASRHandler::asr_params::no_prints)
        .def_readwrite("print_special", &ASRHandler::asr_params::print_special)
        .def_readwrite("print_colors", &ASRHandler::asr_params::print_colors)
        .def_readwrite("print_progress", &ASRHandler::asr_params::print_progress)
        .def_readwrite("no_timestamps", &ASRHandler::asr_params::no_timestamps)
        .def_readwrite("log_score", &ASRHandler::asr_params::log_score)
        .def_readwrite("use_gpu", &ASRHandler::asr_params::use_gpu)
        .def_readwrite("flash_attn", &ASRHandler::asr_params::flash_attn)
        .def_readwrite("need_prefix", &ASRHandler::asr_params::need_prefix)
        .def_readwrite("use_itn", &ASRHandler::asr_params::use_itn)
        .def_readwrite("language", &ASRHandler::asr_params::language)
        .def_readwrite("prompt", &ASRHandler::asr_params::prompt)
        .def_readwrite("model", &ASRHandler::asr_params::model)
        .def_readwrite("openvino_encode_device", &ASRHandler::asr_params::openvino_encode_device)
        .def_readwrite("fname_inp", &ASRHandler::asr_params::fname_inp)
        .def_readwrite("fname_out", &ASRHandler::asr_params::fname_out);

    // Bind the asr_result struct
    py::class_<ASRHandler::asr_result>(m, "ASRResult")
        .def(py::init<>())
        .def(py::init<ASRHandler::task_id_t, std::string>())
        .def_readwrite("request_id", &ASRHandler::asr_result::request_id)
        .def_readwrite("text", &ASRHandler::asr_result::text);

    // Bind the ASRHandler class
    py::class_<ASRHandler>(m, "ASRHandler")
        .def(py::init<>())
        .def("handle", &ASRHandler::handle,
             py::arg("request_id"),
             py::arg("params"),
             py::arg("info") = nullptr,
             py::arg("err") = nullptr);
}