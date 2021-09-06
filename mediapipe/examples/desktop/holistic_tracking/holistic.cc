// Copyright 2019 The MediaPipe Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// A simple example to print out "Hello World!" from a MediaPipe graph.

#include "mediapipe/framework/calculator_graph.h"
#include "mediapipe/framework/formats/image_frame.h"
#include "mediapipe/framework/formats/image.h"
#include "mediapipe/framework/port/logging.h"
#include "mediapipe/framework/port/parse_text_proto.h"
#include "mediapipe/framework/port/status.h"
#include "mediapipe/framework/formats/landmark.pb.h"
#include "holistic.h"
#include <memory>

namespace mediapipe {

	HOLISTIC_API CalculatorGraph* create_holistic_graph()
	{
		CalculatorGraphConfig config =
			ParseTextProtoOrDie<CalculatorGraphConfig>(R"pb(
        input_stream: "IMAGE:input_video"
        output_stream: "POSE_LANDMARKS:pose_landmarks"
        output_stream: "FACE_LANDMARKS:face_landmarks"
        output_stream: "LEFT_HAND_LANDMARKS:left_hand_landmarks"
        output_stream: "RIGHT_HAND_LANDMARKS:right_hand_landmarks"
        node {
            calculator: "HolisticLandmarkCpu"
            input_stream: "IMAGE:input_video"
            output_stream: "POSE_LANDMARKS:pose_landmarks"
            output_stream: "FACE_LANDMARKS:face_landmarks"
            output_stream: "LEFT_HAND_LANDMARKS:left_hand_landmarks"
            output_stream: "RIGHT_HAND_LANDMARKS:right_hand_landmarks"
        }
      )pb");
		CalculatorGraph* graph = new CalculatorGraph();
		auto status = graph->Initialize(config);
		std::cout << "Created and initialized Holistic graph" << status << std::endl;
		return graph;
	}


	HOLISTIC_API ImageFrame* create_image_frame(int format, int width, int height, int width_step, uint8* pixel_data)
	{
		auto frame = new ImageFrame(
			(ImageFormat::Format)format, width, height,
			width_step, pixel_data, [](uint8*) {});
		std::cout << "created ImageFrame" << std::endl;
		return frame;
	}

	HOLISTIC_API OutputStreamPoller* get_output_stream_poller(CalculatorGraph* graph, char* stream_name)
	{
		StatusOrPoller status = graph->AddOutputStreamPoller(stream_name);
		std::cout<<"got outputstream poller == " << status.status() << " for stream: " << stream_name << std::endl
		return status.value();
	}

	HOLISTIC_API void start_run(CalculatorGraph* graph)
	{
		auto status = graph->StartRun({});
		std::cout << "called start run returned Status " << status << std::endl;
	}

	HOLISTIC_API void add_packet_to_input_stream(CalculatorGraph* graph, ImageFrame* image_frame, long long timestamp)
	{
		graph->AddPacketToInputStream(
			"input_video", MakePacket<ImageFrame>(std::move(*image_frame)).At(Timestamp(timestamp)));
		std::cout << "Added Image to input stream with timestamp: " << timestamp << std::endl;
	}

	HOLISTIC_API void close_input_stream(CalculatorGraph* graph, char* stream_name)
	{
		graph->CloseInputStream("input_video");
		std::cout << "closed input stream" << std::endl;
	}

	HOLISTIC_API Packet* create_new_packet()
	{
		auto packet = new Packet();
		std::cout << "Created new Packet" << std::endl;
		return packet;
	}

	HOLISTIC_API bool poller_next_packet(OutputStreamPoller* poller, Packet* packet)
	{
		return poller->Next(packet);
	}

	HOLISTIC_API void graph_wait_until_done(CalculatorGraph* graph)
	{
		auto status = graph->WaitUntilDone();
		std::cout << "waited until graph is done " << status << std::endl;
	}

	HOLISTIC_API void graph_wait_until_observed_output(CalculatorGraph* graph)
	{
		auto status = graph->WaitForObservedOutput();
		std::cout << "waited until observed output " << status << std::endl;
	}

	HOLISTIC_API void delete_graph(CalculatorGraph* graph)
	{
		delete graph;
	}

	HOLISTIC_API void delete_packet(Packet* packet)
	{
		delete packet;
	}

	HOLISTIC_API void delete_output_stream_poller(OutputStreamPoller* poller)
	{
		delete poller;
	}

	HOLISTIC_API void delete_image_frame(ImageFrame* frame)
	{
		delete frame;
	}

	HOLISTIC_API void delete_landmark_list(LandmarkList* list)
	{
		delete list;
	}

	HOLISTIC_API void delete_normalized_landmark_list(NormalizedLandmarkList* list)
	{
		delete list;
	}

	HOLISTIC_API LandmarkList* get_landmark_list_from_packet(Packet* packet)
	{
		return new LandmarkList(packet->Get<LandmarkList>());
	}

	HOLISTIC_API NormalizedLandmarkList* get_normalized_landmark_list_from_packet(Packet* packet)
	{
		return new NormalizedLandmarkList(packet->Get<NormalizedLandmarkList>());
	}

	HOLISTIC_API int get_landmark_list_size(LandmarkList* list)
	{
		return list->landmark_size();
	}

	HOLISTIC_API int get_normalized_landmark_list_size(NormalizedLandmarkList* list)
	{
		return list->landmark_size();
	}

	HOLISTIC_API float landmark_x(LandmarkList* list, int index)
	{
		return list->landmark(index).x();
	}

	HOLISTIC_API float landmark_y(LandmarkList* list, int index)
	{
		return list->landmark(index).y();
	}

	HOLISTIC_API float landmark_z(LandmarkList* list, int index)
	{
		return list->landmark(index).z();
	}

	HOLISTIC_API float normalized_landmark_x(NormalizedLandmarkList* list, int index)
	{
		return list->landmark(index).x();
	}

	HOLISTIC_API float normalized_landmark_y(NormalizedLandmarkList* list, int index)
	{
		return list->landmark(index).y();
	}

	HOLISTIC_API float normalized_landmark_z(NormalizedLandmarkList* list, int index)
	{
		return list->landmark(index).z();
	}

}  // namespace mediapipe