{
  'conditions': [
    ['bastian_engine == "v8"', {
      'defines': [
        'BASTIAN_V8'
      ],
    }],
    ['bastian_engine == "jsc"', {
      'defines': [
        'BASTIAN_JSC'
      ],
    }]
  ],
  'include_dirs': [
    '.',
    './include',
    './deps/v8/include'
  ]
}