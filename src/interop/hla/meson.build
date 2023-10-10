source_files = [
    './Ambassador.cpp',
    './Nib.cpp',
    './NetIO.cpp',
]

mixr_interop_hla = library(
    'mixr_interop_hla',
    source_files,
    include_directories : [public_headers],
    dependencies : [mixr_base_dep, mixr_interop_common_dep, openrti_dep, zlib_dep],
    install : true,
    install_dir: get_option('prefix') / 'lib',
)

mixr_interop_hla_dep = declare_dependency(
    link_with : mixr_interop_hla,
    include_directories : public_headers
)

pkg.generate(mixr_interop_hla, name : 'mixr-interop_hla')
