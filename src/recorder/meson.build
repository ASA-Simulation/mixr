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
    [source_files, mixr_recorder_proto_cc, mixr_recorder_proto_h],
    include_directories: public_headers,
    dependencies: [
        mixr_base_dep,
        mixr_simulation_dep,
        mixr_models_dep,
        protobuf_dep,
    ],
    install : true,
    install_dir: get_option('prefix') / 'lib',
)

mixr_recorder_dep = declare_dependency(
    link_with : mixr_recorder
)

pkg.generate(mixr_recorder, name : 'mixr-recorder')

