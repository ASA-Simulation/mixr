subdir('./proto')

source_files = [
    './DataRecorder.cpp',
    './OutputHandler.cpp',
    './InputHandler.cpp',
    './factory.cpp',
    './TabPrinter.cpp',
    './NetOutput.cpp',
    './DataRecordHandle.cpp',
    './PrintHandler.cpp',
    './PrintPlayer.cpp',
    './FileReader.cpp',
    './NetInput.cpp',
    './PrintSelected.cpp',
    './FileWriter.cpp',
]

mixr_recorder = library(
    'mixr_recorder',
    source_files,
    include_directories: public_headers,
    dependencies: [
        mixr_base_dep,
        mixr_recorder_proto_dep,
        mixr_simulation_dep,
        mixr_models_dep,
        protobuf_dep,
    ],
    install : true,
)

mixr_recorder_dep = declare_dependency(
    link_with : mixr_recorder
)

pkg.generate(mixr_recorder, name : 'mixr-recorder')

