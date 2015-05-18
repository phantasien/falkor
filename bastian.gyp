{
  'targets': [
    {
      'target_name': 'bastian',
      'type': 'static_library',
      'defines': [
        'BASTIAN_V8',
      ],
      'include_dirs': [
        '.',
        './include'
      ],
      'dependencies': [
        './deps/v8/tools/gyp/v8.gyp:v8'
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