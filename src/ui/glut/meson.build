source_files = [
    './factory.cpp',
    './GlutDisplay.cpp',
    './Shapes3D.cpp',
]

mixr_ui_glut = library(
    'mixr_ui_glut',
    source_files,
    include_directories : public_headers,
    dependencies : [
        mixr_base_dep,
        mixr_graphics_dep,
        gl_dep,
        glu_dep,
        glut_dep,
    ],
    link_args : [
        static_flags
    ],
    install : true,
)

mixr_ui_glut_dep = declare_dependency(
    link_with : mixr_ui_glut,
    include_directories : public_headers
)

pkg.generate(mixr_ui_glut, name : 'mixr-ui_glut')
