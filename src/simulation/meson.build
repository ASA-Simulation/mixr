source_files = [
    './Simulation.cpp',
    './StationBgPeriodicThread.cpp',
    './AbstractNib.cpp',
    './AbstractRecorderComponent.cpp',
    './StationTcPeriodicThread.cpp',
    './SimulationBgSyncThread.cpp',
    './factory.cpp',
    './SimulationTcSyncThread.cpp',
    './AbstractPlayer.cpp',
    './AbstractIgHost.cpp',
    './StationNetPeriodicThread.cpp',
    './AbstractDataRecorder.cpp',
    './Station.cpp',
    './AbstractNetIO.cpp',
]

mixr_simulation = library(
    'mixr_simulation',
    source_files,
    include_directories: public_headers,
    dependencies: [mixr_base_dep],
    install : true,
)

mixr_simulation_dep = declare_dependency(
    link_with : mixr_simulation
)

pkg.generate(mixr_simulation, name : 'mixr-simulation')
