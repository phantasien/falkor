{
  'targets': [
    {
      'target_name': 'falkor',
      'type': 'static_library',
      'includes': [
        './deps/bastian/common.gypi',
      ],
      'dependencies': [
        './deps/bastian/bastian.gyp:bastian',
      ],
      'include_dirs': [
        '.',
        './include'
      ],
      'sources': [
        'src/engine.cc',
      ]
    }
  ]
}