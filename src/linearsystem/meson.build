source_files = [
    './SecondOrderTf.cpp',
    './Limit.cpp',
    './Limit01.cpp',
    './SaH.cpp',
    './ScalerFunc.cpp',
    './DiffEquation.cpp',
    './Sz1.cpp',
    './Sz2.cpp',
    './Limit11.cpp',
    './LowpassFilter.cpp',
    './LagFilter.cpp',
    './FirstOrderTf.cpp',
    './LimitFunc.cpp',
]

mixr_linearsystem = library(
    'mixr_linearsystem',
    source_files,
    include_directories: public_headers,
    dependencies: [mixr_base_dep],
    install : true,
)

mixr_linearsystem_dep = declare_dependency(
    link_with : mixr_linearsystem
)

pkg.generate(mixr_linearsystem, name : 'mixr-linearsystem')
