{
  'targets': [
    {
      'target_name': 'falkor',
      'type': 'static_library',
      'includes': [
        './deps/bastian/common.gypi',
        './common.gypi'
      ],
      'dependencies': [
        './deps/bastian/bastian.gyp:bastian',
      ],
      'defines': [
        'USE_CXX0X',
        'FORCE_TR1'
      ],
      'include_dirs': [
        './deps/re2',
        './deps/bastian/include',
        './deps/bastian/deps/v8/include'
      ],
      'sources': [
        './deps/re2/re2/bitstate.cc',
        './deps/re2/re2/compile.cc',
        './deps/re2/re2/dfa.cc',
        './deps/re2/re2/filtered_re2.cc',
        './deps/re2/re2/mimics_pcre.cc',
        './deps/re2/re2/nfa.cc',
        './deps/re2/re2/onepass.cc',
        './deps/re2/re2/parse.cc',
        './deps/re2/re2/perl_groups.cc',
        './deps/re2/re2/prefilter.cc',
        './deps/re2/re2/prefilter_tree.cc',
        './deps/re2/re2/prog.cc',
        './deps/re2/re2/re2.cc',
        './deps/re2/re2/regexp.cc',
        './deps/re2/re2/set.cc',
        './deps/re2/re2/simplify.cc',
        './deps/re2/re2/stringpiece.cc',
        './deps/re2/re2/tostring.cc',
        './deps/re2/re2/unicode_casefold.cc',
        './deps/re2/re2/unicode_groups.cc',
        './deps/re2/util/benchmark.cc',
        './deps/re2/util/hash.cc',
        './deps/re2/util/pcre.cc',
        './deps/re2/util/random.cc',
        './deps/re2/util/rune.cc',
        './deps/re2/util/stringprintf.cc',
        './deps/re2/util/strutil.cc',
        './deps/re2/util/test.cc',
        './deps/re2/util/thread.cc',
        './deps/re2/util/valgrind.cc',
        './src/engine.cc',
        './src/file.cc',
      ]
    }
  ]
}