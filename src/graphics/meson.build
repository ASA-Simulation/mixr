source_files = [
    './fonts/AbstractFont.cpp',
    './fonts/AbstractFtglFont.cpp',
    './fonts/BitmapFont.cpp',
    './fonts/FtglBitmapFont.cpp',
    './fonts/FtglExtrdFont.cpp',
    './fonts/FtglHaloFont.cpp',
    './fonts/FtglOutlineFont.cpp',
    './fonts/FtglPixmapFont.cpp',
    './fonts/FtglPolygonFont.cpp',
    './fonts/FtglTextureFont.cpp',
    './fonts/StrokeFont.cpp',
    './readouts/AbstractField.cpp',
    './readouts/AsciiText.cpp',
    './readouts/Cursor.cpp',
    './readouts/DirectionReadout.cpp',
    './readouts/HexReadout.cpp',
    './readouts/LatitudeReadout.cpp',
    './readouts/LongitudeReadout.cpp',
    './readouts/NumericReadout.cpp',
    './readouts/OctalReadout.cpp',
    './readouts/ReformatScanner.cpp',
    './readouts/Rotary.cpp',
    './readouts/Rotary2.cpp',
    './readouts/TimeReadout.cpp',
    './BmpTexture.cpp',
    './Clip3D.cpp',
    './ColorGradient.cpp',
    './ColorRotary.cpp',
    './Display.cpp',
    './factory.cpp',
    './Graphic.cpp',
    './Image.cpp',
    './Material.cpp',
    './Page.cpp',
    './Polygon.cpp',
    './Rotators.cpp',
    './Scanline.cpp',
    './Shapes.cpp',
    './SymbolLoader.cpp',
    './Texture.cpp',
    './Translator.cpp',
    './MfdPage.cpp',
    './MapPage.cpp',
]

mixr_graphics = library(
    'mixr_graphics',
    source_files,
    include_directories : public_headers,
    dependencies : [
        mixr_base_dep,
        gl_dep,
        glu_dep,
        freetype_dep,
        ftgl_dep,
    ],
    link_args : [
        static_flags
    ],
    install : true,
)

mixr_graphics_dep = declare_dependency(
    link_with : mixr_graphics,
    include_directories : public_headers
)

pkg.generate(mixr_graphics, name : 'mixr-graphics')
