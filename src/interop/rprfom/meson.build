source_files = [
    './NetIO_weapon_fire.cpp',
    './NetIO_munition_detonation.cpp',
    './NetIO_entity_state.cpp',
    './Ntm.cpp',
    './Nib_munition_detonation.cpp',
    './Nib.cpp',
    './factory.cpp',
    './NetIO.cpp',
    './Nib_entity_state.cpp',
    './RprFom.cpp',
    './Nib_weapon_fire.cpp',
]

mixr_interop_rprfom = library(
    'mixr_interop_rprfom',
    source_files,
    include_directories: [public_headers],
    dependencies: [
        mixr_base_dep,
        mixr_simulation_dep,
        mixr_models_dep,
        mixr_interop_common_dep,
        mixr_interop_dis_dep,
        mixr_interop_hla_dep,
        openrti_dep,
        zlib_dep
    ],
    install : true,
)

pkg.generate(mixr_interop_rprfom, name : 'mixr-interop_rprfom')
