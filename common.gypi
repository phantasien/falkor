{
  'conditions': [
    ['falkor_platform == "android"', {
      'defines': [
        'FALKOR_ANDROID'
      ],
    }],
    ['falkor_platform == "ios"', {
      'defines': [
        'FALKOR_IOS'
      ],
    }]
  ]
}
