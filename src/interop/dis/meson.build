source_files = [
    './NetIO_weapon_fire.cpp',
    './Nib_iff.cpp',
    './NetIO_munition_detonation.cpp',
    './EmissionPduHandler.cpp',
    './NetIO_entity_state.cpp',
    './Ntm.cpp',
    './Nib_munition_detonation.cpp',
    './Nib.cpp',
    './factory.cpp',
    './NetIO.cpp',
    './Nib_entity_state.cpp',
    './Nib_weapon_fire.cpp',
]

mixr_interop_dis = library(
    'mixr_interop_dis',
    source_files,
    include_directories: [public_headers],
    dependencies: [mixr_base_dep, mixr_simulation_dep, mixr_models_dep, mixr_interop_common_dep],
    install : true,
    install_dir: get_option('prefix') / 'lib',
)

mixr_interop_dis_dep = declare_dependency(
    link_with : mixr_interop_dis,
    include_directories : public_headers
)

pkg.generate(mixr_interop_dis, name : 'mixr-interop_dis')
