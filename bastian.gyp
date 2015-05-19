{
  'targets': [
    {
      'target_name': 'testme',
      'type': 'executable',
      'include_dirs': [
        '.',
        './include',
        './deps/v8/include'
      ],
      'libraries': [
        '<(PRODUCT_DIR)<(bastian_sub_dir)/libbastian.a',
      ],
      'sources': [
        './testme.cc'
      ],
      'dependencies': [
        'bastian'
      ],
      'defines': [
        'BASTIAN_V8',
      ]
    },
    {
      'target_name': 'bastian',
      'type': 'static_library',
      'defines': [
        'BASTIAN_V8',
      ],
      'include_dirs': [
        '.',
        './include',
        './deps/v8/include'
      ],
      'dependencies': [
        './deps/v8/tools/gyp/v8.gyp:v8'
      ],
      'libraries': [
        '<(PRODUCT_DIR)/obj.target/deps/v8/tools/gyp/libv8_libbase.a',
        '<(PRODUCT_DIR)/obj.target/deps/v8/tools/gyp/libv8_snapshot.a',
        '<(PRODUCT_DIR)/obj.target/deps/v8/tools/gyp/libv8_libplatform.a',
        '<(PRODUCT_DIR)/obj.target/deps/v8/tools/gyp/libv8_base.a'
      ],
      'sources': [
        'src/engine.cc',
        'src/fcontext.cc',
        'src/objcontext.cc',
        'src/value.cc'
      ]
    }
  ]
}