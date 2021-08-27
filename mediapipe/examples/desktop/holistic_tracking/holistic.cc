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
    std::cout << status << std::endl;
    return graph;
}

HOLISTIC_API Image* create_image_frame(int format, int width, int height, int width_step, uint8* pixel_data)
{
    Image* image = new Image();
    image->GetImageFrameSharedPtr()->AdoptPixelData((ImageFormat::Format)format, width, height, width_step, pixel_data, std::default_delete<uint8[]>());
    return image;
}

HOLISTIC_API OutputStreamPoller* get_output_stream_poller(CalculatorGraph* graph, char* stream_name)
{
    constexpr OutputStreamPoller* expr = nullptr;
    ASSIGN_OR_RETURN(OutputStreamPoller poller,
        graph->AddOutputStreamPoller(stream_name), expr);
    return &poller;
}

HOLISTIC_API void start_run(CalculatorGraph* graph)
{
    graph->StartRun({});
}

HOLISTIC_API void add_packet_to_input_stream(CalculatorGraph* graph, Image* image_frame, int64 timestamp)
{
    graph->AddPacketToInputStream(
        "input_video", MakePacket<Image>((*image_frame)).At(Timestamp(timestamp)));
}

HOLISTIC_API void close_input_stream(CalculatorGraph* graph, char* stream_name)
{
    graph->CloseInputStream(stream_name);
}

HOLISTIC_API Packet* create_new_packet()
{
    return new Packet();
}

HOLISTIC_API bool poller_next_packet(OutputStreamPoller* poller, Packet* packet)
{
    return poller->Next(packet);
}

HOLISTIC_API void graph_wait_until_done(CalculatorGraph* graph)
{
    graph->WaitUntilDone();
}

HOLISTIC_API void graph_wait_until_observed_output(CalculatorGraph* graph)
{
    graph->WaitForObservedOutput();
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

HOLISTIC_API void get_landmark_list_from_packet(Packet* packet, char* str)
{
    std::string stri = str;
    packet->Get<LandmarkList>().SerializeToString(&stri);
    strcpy(str, stri.c_str());
}

HOLISTIC_API void get_normalized_landmark_list_from_packet(Packet* packet, char* str) 
{
    std::string stri = str;
    packet->Get<NormalizedLandmarkList>().SerializeToString(&stri);
    strcpy(str, stri.c_str());
}

}  // namespace mediapipe