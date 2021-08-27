#ifdef GCCBUILD
#define HOLISTIC_API __attribute__((visibility("default")))
#else
#define HOLISTIC_API __declspec(dllexport)
#endif
#include "mediapipe/framework/calculator_graph.h"
#include "mediapipe/framework/formats/image.h"
#include "mediapipe/framework/formats/landmark.pb.h"

namespace mediapipe {
	extern "C"
	{
		HOLISTIC_API CalculatorGraph* create_holistic_graph();
		HOLISTIC_API Image* create_image_frame(int format, int width, int height, int width_step, uint8* pixel_data);
		HOLISTIC_API OutputStreamPoller* get_output_stream_poller(CalculatorGraph* graph, char* stream_name);
		HOLISTIC_API void start_run(CalculatorGraph* graph);
		HOLISTIC_API void add_packet_to_input_stream(CalculatorGraph* graph, Image* image_frame, int64 timestamp);
		HOLISTIC_API void close_input_stream(CalculatorGraph* graph, char* stream_name);
		HOLISTIC_API Packet* create_new_packet();
		HOLISTIC_API bool poller_next_packet(OutputStreamPoller* poller, Packet* packet);
		HOLISTIC_API void graph_wait_until_done(CalculatorGraph* graph);
		HOLISTIC_API void graph_wait_until_observed_output(CalculatorGraph* graph);
		HOLISTIC_API void delete_graph(CalculatorGraph* graph);
		HOLISTIC_API void delete_packet(Packet* packet);
		HOLISTIC_API void delete_output_stream_poller(OutputStreamPoller* poller);
		HOLISTIC_API void get_landmark_list_from_packet(Packet* packet, char* str);
		HOLISTIC_API void get_normalized_landmark_list_from_packet(Packet* packet, char* str);
	}
}