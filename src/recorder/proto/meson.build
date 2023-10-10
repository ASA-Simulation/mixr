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
  install_dir : get_option('includedir'),
)
