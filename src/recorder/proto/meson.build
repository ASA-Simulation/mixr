protoc = find_program('protoc')

mixr_recorder_proto_cc = custom_target(
  'mixr_recorder_proto_cc',
  input : ['DataRecord.proto'],
  output : ['@BASENAME@.pb.cc'],
  command : [
    protoc,
    '--proto_path=@CURRENT_SOURCE_DIR@',
    '--cpp_out=@OUTDIR@',
    '@INPUT@',
  ]
)

mixr_recorder_proto_h = custom_target(
  'mixr_recorder_proto_h',
  input : ['DataRecord.proto'],
  output : ['@BASENAME@.pb.h'],
  command : [
    protoc,
    '--proto_path=@CURRENT_SOURCE_DIR@',
    '--cpp_out=@OUTDIR@',
    '@INPUT@',
  ],
  install : true,
  install_dir : get_option('includedir') / 'mixr/recorder/proto',
)

mixr_recorder_proto = library(
  'mixr_recorder_proto',
  [mixr_recorder_proto_cc],
  dependencies : [protobuf_dep],
  install : true,
)

mixr_recorder_proto_dep = declare_dependency(
  sources: [mixr_recorder_proto_cc, mixr_recorder_proto_h],
  link_with: mixr_recorder_proto,
)

pkg.generate(mixr_recorder_proto, name : 'mixr-recorder_proto')
