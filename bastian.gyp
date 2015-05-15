{
  'targets': [
    {
      'target_name': 'testme',
      'type': 'executable',
      'include_dirs': [
        '.',
        './include'
      ],
      'dependencies': [
        'bastian'
      ],
      'sources': [
        './testme.cc'
      ],
      'conditions': [
        ['BASTIAN_ENGINE=="jsc"', {
          'defines': [
            'BASTIAN_JSC',
          ],
          'link_settings': {
            'libraries': [
              '$(SDKROOT)/System/Library/Frameworks/JavascriptCore.framework',
            ],
          },
        }],
      ],
    },
    {
      'target_name': 'bastian',
      'type': 'static_library',
      'include_dirs': [
        '.',
        './include'
      ],
      'conditions': [
        ['BASTIAN_ENGINE=="v8"', {
          'defines': [
            'BASTIAN_V8',
          ],
          'include_dirs': [
            './deps/v8/include'
          ],
          'dependencies': [
            './deps/v8/tools/gyp/v8.gyp:v8_libbase'
          ]
        }],
        ['BASTIAN_ENGINE=="jsc"', {
          'defines': [
            'BASTIAN_JSC',
          ]
        }],
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