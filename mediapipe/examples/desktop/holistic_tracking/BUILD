# Copyright 2020 The MediaPipe Authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

licenses(["notice"])

package(default_visibility = ["//mediapipe/examples:__subpackages__"])

config_setting(
    name = "build_on_gcc",
    define_values = {
        "GCCBUILD": "1",
    },
    visibility = ["//visibility:public"],
)

cc_binary(
   name = "holisticlib",
   srcs = ["holistic.cc","holistic.h"],
   deps = [        
       "//mediapipe/calculators/core:pass_through_calculator",
       "//mediapipe/framework:calculator_graph",
       "//mediapipe/framework/port:logging",
       "//mediapipe/framework/port:parse_text_proto",
       "//mediapipe/framework/port:status",
       "//mediapipe/graphs/holistic_tracking:holistic_tracking_cpu_graph_deps"],
   linkshared = 1,
   linkstatic = 1,
   defines = select({
        "//conditions:default": [],
        "build_on_gcc": ["GCCBUILD=1"],
    })
)

cc_binary(
    name = "holistic_tracking_cpu",
    deps = [
        "//mediapipe/examples/desktop:demo_run_graph_main",
        "//mediapipe/graphs/holistic_tracking:holistic_tracking_cpu_graph_deps",
    ],
)

# Linux only
cc_binary(
    name = "holistic_tracking_gpu",
    deps = [
        "//mediapipe/examples/desktop:demo_run_graph_main_gpu",
        "//mediapipe/graphs/holistic_tracking:holistic_tracking_gpu_deps",
    ],
)
