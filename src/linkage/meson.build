source_files = [
    './IoData.cpp',
    './IoDevice.cpp',
    './MockDevice.cpp',
    './IoHandler.cpp',
    './factory.cpp',
    './IoPeriodicThread.cpp',
    './platform/UsbJoystick_linux.cpp',
    './generators/DiscreteInputFixed.cpp',
    './generators/AbstractGenerator.cpp',
    './generators/AnalogSignalGen.cpp',
    './generators/AnalogInputFixed.cpp',
    './adapters/AbstractAdapter.cpp',
    './adapters/DiscreteOutput.cpp',
    './adapters/Ai2DiSwitch.cpp',
    './adapters/AnalogInput.cpp',
    './adapters/AnalogOutput.cpp',
    './adapters/DiscreteInput.cpp',
]

mixr_linkage = library(
    'mixr_linkage',
    source_files,
    include_directories: public_headers,
    dependencies: [mixr_base_dep],
    link_args : [
        static_flags
    ],
    install : true,
)

mixr_linkage_dep = declare_dependency(
    link_with : mixr_linkage
)

pkg.generate(mixr_linkage, name : 'mixr-linkage')
